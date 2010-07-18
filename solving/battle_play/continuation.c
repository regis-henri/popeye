#include "stipulation/battle_play/continuation.h"
#include "pydata.h"
#include "pypipe.h"
#include "stipulation/branch.h"
#include "stipulation/battle_play/branch.h"
#include "stipulation/battle_play/defense_play.h"
#include "trace.h"

#include <assert.h>

/* Allocate a STContinuationSolver defender slice.
 * @param length maximum number of half-moves of slice (+ slack)
 * @param min_length minimum number of half-moves of slice (+ slack)
 * @return index of allocated slice
 */
slice_index alloc_continuation_solver_slice(stip_length_type length,
                                            stip_length_type min_length)
{
  slice_index result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",length);
  TraceFunctionParam("%u",min_length);
  TraceFunctionParamListEnd();

  result = alloc_branch(STContinuationSolver,length,min_length);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Try to defend after an attacking move
 * When invoked with some n, the function assumes that the key doesn't
 * solve in less than n half moves.
 * @param si slice index
 * @param n maximum number of half moves until end state has to be reached
 * @param n_min minimum number of half-moves of interesting variations
 *              (slack_length_battle <= n_min <= slices[si].u.branch.length)
 * @param n_max_unsolvable maximum number of half-moves that we
 *                         know have no solution
 * @return <=n solved  - return value is maximum number of moves
 *                       (incl. defense) needed
 *         n+2 refuted - acceptable number of refutations found
 *         n+4 refuted - more refutations found than acceptable
 */
stip_length_type
continuation_solver_defend_in_n(slice_index si,
                                stip_length_type n,
                                stip_length_type n_min,
                                stip_length_type n_max_unsolvable)
{
  stip_length_type result;
  slice_index const next = slices[si].u.pipe.next;
  unsigned int const max_nr_allowed_refutations = 0;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParam("%u",n_min);
  TraceFunctionParam("%u",n_max_unsolvable);
  TraceFunctionParamListEnd();

  result = defense_can_defend_in_n(next,
                                   n,n_max_unsolvable,
                                   max_nr_allowed_refutations);
  if (result<=n)
  {
    stip_length_type defend_result;
    if (result>slack_length_battle+1
        && n_min<=slack_length_battle+1)
      n_min += 2;
    defend_result = defense_defend_in_n(next,result,n_min,n_max_unsolvable);
    assert(defend_result==result);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Determine whether there are defenses after an attacking move
 * @param si slice index
 * @param n maximum number of half moves until end state has to be reached
 * @param n_max_unsolvable maximum number of half-moves that we
 *                         know have no solution
 * @param max_nr_refutations how many refutations should we look for
 * @return <=n solved  - return value is maximum number of moves
 *                       (incl. defense) needed
 *         n+2 refuted - <=max_nr_refutations refutations found
 *         n+4 refuted - >max_nr_refutations refutations found
 */
stip_length_type
continuation_solver_can_defend_in_n(slice_index si,
                                    stip_length_type n,
                                    stip_length_type n_max_unsolvable,
                                    unsigned int max_nr_refutations)
{
  stip_length_type result;
  slice_index const next = slices[si].u.pipe.next;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParam("%u",n_max_unsolvable);
  TraceFunctionParam("%u",max_nr_refutations);
  TraceFunctionParamListEnd();

  result = defense_can_defend_in_n(next,n,n_max_unsolvable,max_nr_refutations);

  TraceFunctionExit(__func__);
  TraceValue("%u",result);
  TraceFunctionResultEnd();
  return result;
}

typedef enum
{
  continuation_handler_not_needed,
  continuation_handler_needed,
  continuation_handler_inserted
} continuation_handler_insertion_state;

/* Append a continuation solver if none has been inserted before
 * @param si identifies slice around which to insert try handlers
 * @param st address of structure defining traversal
 */
static void continuation_solver_append(slice_index si,
                                       stip_structure_traversal *st)
{
  continuation_handler_insertion_state * const state = st->param;
  slice_index const next = slices[si].u.pipe.next;
  stip_length_type const length = slices[next].u.branch.length;
  stip_length_type const min_length = slices[next].u.branch.min_length;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_traverse_structure_children(si,st);

  TraceValue("%u\n",*state);
  if (*state==continuation_handler_needed)
  {
    pipe_append(si,alloc_continuation_solver_slice(length,min_length));
    *state = continuation_handler_inserted;
    TraceValue("->%u\n",*state);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Append a continuation solver if none has been inserted before
 * @param si identifies slice around which to insert try handlers
 * @param st address of structure defining traversal
 */
static void continuation_solver_append_to_move(slice_index si,
                                               stip_structure_traversal *st)
{
  continuation_handler_insertion_state * const state = st->param;
  continuation_handler_insertion_state const save_state = *state;
  stip_length_type const length = slices[si].u.branch.length;
  stip_length_type const min_length = slices[si].u.branch.min_length;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_traverse_structure_children(si,st);

  TraceValue("%u\n",*state);
  if (*state==continuation_handler_needed)
  {
    pipe_append(si,alloc_continuation_solver_slice(length-1,min_length-1));
    *state = continuation_handler_inserted;
    TraceValue("->%u\n",*state);
  }

  *state = save_state;

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Inform predecessors that a continuation solver is needed
 * @param si identifies slice around which to insert try handlers
 * @param st address of structure defining traversal
 */
static void continuation_solver_mark_need(slice_index si,
                                          stip_structure_traversal *st)
{
  continuation_handler_insertion_state * const state = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_traverse_structure_children(si,st);

  *state = continuation_handler_needed;
  TraceValue("->%u\n",*state);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Append a continuation solver if none has been inserted before
 * @param si identifies slice around which to insert try handlers
 * @param st address of structure defining traversal
 */
static
void continuation_solver_insert_defender_filter(slice_index si,
                                                stip_structure_traversal *st)
{
  continuation_handler_insertion_state * const state = st->param;
  continuation_handler_insertion_state const save_state = *state;
  slice_index const proxy_to_goal = slices[si].u.branch_fork.towards_goal;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  assert(slices[proxy_to_goal].type==STProxy);

  stip_traverse_structure(proxy_to_goal,st);

  TraceValue("%u\n",*state);
  if (*state==continuation_handler_needed)
    pipe_append(proxy_to_goal,
                alloc_continuation_solver_slice(slack_length_battle,
                                                slack_length_battle));
  *state = save_state;
  stip_traverse_structure_pipe(si,st);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

static stip_structure_visitor const continuation_handler_inserters[] =
{
  &stip_traverse_structure_children,   /* STProxy */
  &continuation_solver_append_to_move, /* STAttackMove */
  &continuation_solver_mark_need,      /* STDefenseMove */
  &stip_structure_visitor_noop,        /* STHelpMove */
  &stip_structure_visitor_noop,        /* STHelpFork */
  &stip_structure_visitor_noop,        /* STSeriesMove */
  &stip_structure_visitor_noop,        /* STSeriesMoveToGoal */
  &stip_structure_visitor_noop,        /* STSeriesFork */
  &continuation_solver_mark_need,      /* STGoalReachedTester */
  &stip_structure_visitor_noop,        /* STLeaf */
  &stip_traverse_structure_children,   /* STReciprocal */
  &stip_traverse_structure_children,   /* STQuodlibet */
  &stip_traverse_structure_children,   /* STNot */
  &stip_traverse_structure_children,   /* STMoveInverterRootSolvableFilter */
  &stip_traverse_structure_children,   /* STMoveInverterSolvableFilter */
  &stip_traverse_structure_children,   /* STMoveInverterSeriesFilter */
  &continuation_solver_append_to_move, /* STAttackRoot */
  &stip_traverse_structure_children,   /* STDefenseRoot */
  &stip_traverse_structure_children,   /* STPostKeyPlaySuppressor */
  &stip_traverse_structure_children,   /* STContinuationSolver */
  &stip_traverse_structure_children,   /* STContinuationWriter */
  &stip_traverse_structure_children,   /* STBattlePlaySolver */
  &stip_traverse_structure_children,   /* STBattlePlaySolutionWriter */
  &stip_traverse_structure_children,   /* STThreatSolver */
  &stip_traverse_structure_children,   /* STZugzwangWriter */
  &stip_traverse_structure_children,   /* STThreatEnforcer */
  &stip_traverse_structure_children,   /* STThreatCollector */
  &stip_traverse_structure_children,   /* STRefutationsCollector */
  &stip_traverse_structure_children,   /* STVariationWriter */
  &stip_traverse_structure_children,   /* STRefutingVariationWriter */
  &stip_traverse_structure_children,   /* STNoShortVariations */
  &stip_traverse_structure_children,   /* STAttackHashed */
  &stip_structure_visitor_noop,        /* STHelpRoot */
  &stip_structure_visitor_noop,        /* STHelpShortcut */
  &stip_traverse_structure_children,   /* STHelpHashed */
  &stip_structure_visitor_noop,        /* STSeriesRoot */
  &stip_structure_visitor_noop,        /* STSeriesShortcut */
  &stip_traverse_structure_children,   /* STParryFork */
  &stip_traverse_structure_children,   /* STSeriesHashed */
  &continuation_solver_append,         /* STSelfCheckGuardRootSolvableFilter */
  &stip_traverse_structure_children,   /* STSelfCheckGuardSolvableFilter */
  &stip_traverse_structure_children,   /* STSelfCheckGuardAttackerFilter */
  &continuation_solver_append,         /* STSelfCheckGuardDefenderFilter */
  &stip_traverse_structure_children,   /* STSelfCheckGuardHelpFilter */
  &stip_traverse_structure_children,   /* STSelfCheckGuardSeriesFilter */
  &continuation_solver_insert_defender_filter, /* STDirectDefenderFilter */
  &stip_traverse_structure_children,   /* STReflexRootFilter */
  &stip_traverse_structure_children,   /* STReflexHelpFilter */
  &stip_traverse_structure_children,   /* STReflexSeriesFilter */
  &stip_traverse_structure_children,   /* STReflexAttackerFilter */
  &stip_traverse_structure_children,   /* STReflexDefenderFilter */
  &stip_traverse_structure_children,   /* STSelfDefense */
  &stip_traverse_structure_children,   /* STRestartGuardRootDefenderFilter */
  &stip_traverse_structure_children,   /* STRestartGuardHelpFilter */
  &stip_traverse_structure_children,   /* STRestartGuardSeriesFilter */
  &stip_traverse_structure_children,   /* STIntelligentHelpFilter */
  &stip_traverse_structure_children,   /* STIntelligentSeriesFilter */
  &stip_traverse_structure_children,   /* STGoalReachableGuardHelpFilter */
  &stip_traverse_structure_children,   /* STGoalReachableGuardSeriesFilter */
  &stip_traverse_structure_children,   /* STIntelligentDuplicateAvoider */
  &stip_traverse_structure_children,   /* STKeepMatingGuardAttackerFilter */
  &stip_traverse_structure_children,   /* STKeepMatingGuardDefenderFilter */
  &stip_traverse_structure_children,   /* STKeepMatingGuardHelpFilter */
  &stip_traverse_structure_children,   /* STKeepMatingGuardSeriesFilter */
  &stip_traverse_structure_children,   /* STMaxFlightsquares */
  &stip_traverse_structure_children,   /* STDegenerateTree */
  &stip_traverse_structure_children,   /* STMaxNrNonTrivial */
  &stip_traverse_structure_children,   /* STMaxNrNonTrivialCounter */
  &stip_traverse_structure_children,   /* STMaxThreatLength */
  &stip_traverse_structure_children,   /* STMaxTimeRootDefenderFilter */
  &stip_traverse_structure_children,   /* STMaxTimeDefenderFilter */
  &stip_traverse_structure_children,   /* STMaxTimeHelpFilter */
  &stip_traverse_structure_children,   /* STMaxTimeSeriesFilter */
  &stip_traverse_structure_children,   /* STMaxSolutionsRootSolvableFilter */
  &stip_traverse_structure_children,   /* STMaxSolutionsSolvableFilter */
  &stip_traverse_structure_children,   /* STMaxSolutionsRootDefenderFilter */
  &stip_traverse_structure_children,   /* STMaxSolutionsHelpFilter */
  &stip_traverse_structure_children,   /* STMaxSolutionsSeriesFilter */
  &stip_traverse_structure_children,   /* STStopOnShortSolutionsRootSolvableFilter */
  &stip_traverse_structure_children,   /* STStopOnShortSolutionsHelpFilter */
  &stip_traverse_structure_children,   /* STStopOnShortSolutionsSeriesFilter */
  &stip_traverse_structure_children,   /* STEndOfPhaseWriter */
  &stip_traverse_structure_children,   /* STEndOfSolutionWriter */
  &stip_traverse_structure_children,   /* STRefutationWriter */
  &stip_traverse_structure_children,   /* STOutputPlaintextTreeCheckDetectorAttackerFilter */
  &stip_traverse_structure_children,   /* STOutputPlaintextTreeCheckDetectorDefenderFilter */
  &stip_traverse_structure_children,   /* STOutputPlaintextLineLineWriter */
  &stip_traverse_structure_children,   /* STOutputPlaintextTreeGoalWriter */
  &stip_traverse_structure_children,   /* STOutputPlaintextTreeMoveInversionCounter */
  &stip_traverse_structure_children,   /* STOutputPlaintextLineMoveInversionCounter */
  &stip_traverse_structure_children    /* STOutputPlaintextLineEndOfIntroSeriesMarker */
};

/* Instrument the stipulation representation so that it can deal with
 * continuations
 */
void stip_insert_continuation_handlers(void)
{
  stip_structure_traversal st;
  continuation_handler_insertion_state state = continuation_handler_not_needed;

  TraceFunctionEntry(__func__);
  TraceFunctionParamListEnd();

  TraceStipulation(root_slice);

  stip_structure_traversal_init(&st,&continuation_handler_inserters,&state);
  stip_traverse_structure(root_slice,&st);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
