#include "conditions/oscillating_kings.h"
#include "pydata.h"
#include "stipulation/has_solution_type.h"
#include "stipulation/stipulation.h"
#include "stipulation/pipe.h"
#include "stipulation/branch.h"
#include "stipulation/structure_traversal.h"
#include "stipulation/battle_play/branch.h"
#include "stipulation/help_play/branch.h"
#include "solving/move_effect_journal.h"
#include "debugging/trace.h"

#include <assert.h>

boolean OscillatingKingsTypeB[nr_sides];
boolean OscillatingKingsTypeC[nr_sides];
boolean oscillatedKs[toppile+1];

static void perform_oscillation(void)
{
  piece const save_king_square[nr_sides] = {king_square[White],king_square[Black]};
  piece const save_kings[nr_sides] = {e[king_square[White]],e[king_square[Black]]};
  Flags const save_flags[nr_sides] = {spec[king_square[White]],spec[king_square[Black]]};

  TraceFunctionEntry(__func__);
  TraceFunctionParamListEnd();

  move_effect_journal_do_piece_removal(move_effect_reason_oscillating_kings,
                                       king_square[White]);
  move_effect_journal_do_piece_removal(move_effect_reason_oscillating_kings,
                                       king_square[Black]);
  move_effect_journal_do_piece_addition(move_effect_reason_oscillating_kings,
                                        save_king_square[Black],
                                        save_kings[White],
                                        save_flags[White]);
  move_effect_journal_do_piece_addition(move_effect_reason_oscillating_kings,
                                        save_king_square[White],
                                        save_kings[Black],
                                        save_flags[Black]);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Try to solve in n half-moves after a defense.
 * @param si slice index
 * @param n maximum number of half moves until goal
 * @return length of solution found and written, i.e.:
 *            slack_length-2 defense has turned out to be illegal
 *            <=n length of shortest solution found
 *            n+2 no solution found
 */
stip_length_type king_oscillator_attack(slice_index si, stip_length_type n)
{
  Side const starter = slices[si].starter;
  stip_length_type result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParamListEnd();

  if (OscillatingKingsTypeB[starter] && echecc(starter))
  {
    oscillatedKs[nbply] = false;
    result = n+2;
  }
  else
  {
    oscillatedKs[nbply] = !OscillatingKingsTypeC[starter] || echecc(advers(starter));
    if (oscillatedKs[nbply])
      perform_oscillation();

    result = attack(slices[si].next1,n);
  }

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
 * @return <slack_length - no legal defense found
 *         <=n solved  - <=acceptable number of refutations found
 *                       return value is maximum number of moves
 *                       (incl. defense) needed
 *         n+2 refuted - >acceptable number of refutations found
 */
stip_length_type king_oscillator_defend(slice_index si, stip_length_type n)
{
  Side const starter = slices[si].starter;
  stip_length_type result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParamListEnd();

  if (OscillatingKingsTypeB[starter] && echecc(starter))
  {
    oscillatedKs[nbply] = false;
    result = slack_length-1;
  }
  else
  {
    oscillatedKs[nbply] = !OscillatingKingsTypeC[starter] || echecc(advers(starter));
    if (oscillatedKs[nbply])
      perform_oscillation();

    result = defend(slices[si].next1,n);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

static void instrument_move(slice_index si, stip_structure_traversal *st)
{
  Side const starter = slices[si].starter;
  Cond const cond = starter==White ? white_oscillatingKs : black_oscillatingKs;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_traverse_structure_children(si,st);

  if (CondFlag[cond])
  {
    slice_index const prototype = alloc_pipe(STKingOscillator);
    branch_insert_slices_contextual(si,st->context,&prototype,1);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Instrument a stipulation
 * @param si identifies root slice of stipulation
 */
void stip_insert_king_oscillators(slice_index si)
{
  stip_structure_traversal st;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_impose_starter(si,slices[si].starter);

  stip_structure_traversal_init(&st,0);
  stip_structure_traversal_override_single(&st,STMove,&instrument_move);
  stip_traverse_structure(si,&st);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
