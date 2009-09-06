#include "pynontrv.h"
#include "pydata.h"
#include "pypipe.h"
#include "pydirect.h"
#include "pyoutput.h"
#include "trace.h"

#include <assert.h>
#include <stdlib.h>

stip_length_type min_length_nontrivial;
unsigned int max_nr_nontrivial;

// /* Reset the max threats setting to off
//  */
// void reset_max_nr_nontrivial_length(void)
// {
//   max_len_threat = no_stip_length;
// }

// /* Read the requested max threat length setting from a text token
//  * entered by the user
//  * @param textToken text token from which to read
//  * @return true iff max threat setting was successfully read
//  */
// boolean read_max_nr_nontrivial_length(const char *textToken)
// {
//   boolean result;
//   char *end;
//   unsigned long const requested_max_threat_length = strtoul(textToken,&end,10);

//   if (textToken!=end && requested_max_threat_length<=UINT_MAX)
//   {
//     max_len_threat = (stip_length_type)requested_max_threat_length;
//     result = true;
//   }
//   else
//     result = false;

//   return result;
// }

// /* Retrieve the current max threat length setting
//  * @return current max threat length setting
//  *         no_stip_length if max threats option is not active
//  */
// stip_length_type get_max_nr_nontrivial_length(void)
// {
//   TraceFunctionEntry(__func__);
//   TraceFunctionParamListEnd();

//   TraceFunctionExit(__func__);
//   TraceFunctionResult("%u",max_len_threat);
//   TraceFunctionResultEnd();
//   return max_len_threat;
// }

/* **************** Private helpers ***************
 */

/* Count non-trivial moves of the defending side. Whether a
 * particular move is non-trivial is determined by user input.
 * Stop counting when more than max_nr_nontrivial have been found
 * @return number of defender's non-trivial moves
 */
static
unsigned int count_nontrivial_defenses(slice_index si)
{
  unsigned int result;
  slice_index const next = slices[si].u.pipe.next;
  stip_length_type const parity = slices[si].u.pipe.u.branch.length%2;
  unsigned int const nr_refutations_allowed = max_nr_nontrivial+1;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  result = direct_defender_can_defend_in_n(next,
                                           min_length_nontrivial+parity,
                                           nr_refutations_allowed);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%d",result);
  TraceFunctionResultEnd();
  return result;
}

/* **************** Initialisation ***************
 */

/* Initialise a STMaxFlightsquares slice
 * @param si identifies slice to be initialised
 * @param side mating side
 */
static void init_max_nr_nontrivial_guard_slice(slice_index si)
{
  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  slices[si].type = STMaxNrNonTrivial; 
  slices[si].starter = no_side; 

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}


/* **************** Implementation of interface DirectDefender **********
 */

/* Try to defend after an attempted key move at root level
 * @param table table where to add refutations
 * @param si slice index
 * @return success of key move
 */
attack_result_type max_nr_nontrivial_guard_root_defend(table refutations,
                                                       slice_index si)
{
  attack_result_type result;
  stip_length_type const n = slices[si].u.pipe.u.branch.length;
  slice_index const next = slices[si].u.pipe.next;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();


  if (n>min_length_nontrivial)
  {
    unsigned int const nr_nontrivial = count_nontrivial_defenses(si);
    if (max_nr_nontrivial+1>=nr_nontrivial)
    {
      ++max_nr_nontrivial;
      max_nr_nontrivial -= nr_nontrivial;
      result = direct_defender_root_defend(refutations,next);
      max_nr_nontrivial += nr_nontrivial;
      --max_nr_nontrivial;
    }
    else
      result = attack_has_reached_deadend;
  }
  else
    result = direct_defender_root_defend(refutations,next);

  TraceFunctionExit(__func__);
  TraceEnumerator(attack_result_type,result,"");
  TraceFunctionResultEnd();
  return result;
}

/* Try to defend after an attempted key move at non-root level
 * @param si slice index
 * @param n maximum number of half moves until end state has to be reached
 * @return success of key move
 */
attack_result_type max_nr_nontrivial_guard_defend_in_n(slice_index si,
                                                       stip_length_type n)
{
  slice_index const next = slices[si].u.pipe.next;
  attack_result_type result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParamListEnd();

  if (n>min_length_nontrivial)
  {
    unsigned int const nr_nontrivial = count_nontrivial_defenses(si);
    if (max_nr_nontrivial+1>=nr_nontrivial)
    {
      ++max_nr_nontrivial;
      max_nr_nontrivial -= nr_nontrivial;
      result = direct_defender_defend_in_n(next,n);
      max_nr_nontrivial += nr_nontrivial;
      --max_nr_nontrivial;
    }
    else
      result = attack_has_reached_deadend;
  }
  else
    result = direct_defender_defend_in_n(next,n);

  TraceFunctionExit(__func__);
  TraceEnumerator(attack_result_type,result,"");
  TraceFunctionResultEnd();
  return result;
}

/* Determine whether there are refutations after an attempted key move
 * at non-root level
 * @param si slice index
 * @param n maximum number of half moves until end state has to be reached
 * @param max_result how many refutations should we look for
 * @return number of refutations found (0..max_result+1)
 */
unsigned int max_nr_nontrivial_guard_can_defend_in_n(slice_index si,
                                                     stip_length_type n,
                                                     unsigned int max_result)
{
  slice_index const next = slices[si].u.pipe.next;
  unsigned int result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParamListEnd();

  if (n>min_length_nontrivial)
  {
    unsigned int const nr_nontrivial = count_nontrivial_defenses(si);
    if (max_nr_nontrivial+1>=nr_nontrivial)
    {
      ++max_nr_nontrivial;
      max_nr_nontrivial -= nr_nontrivial;
      result = direct_defender_can_defend_in_n(next,n,max_result);
      max_nr_nontrivial += nr_nontrivial;
      --max_nr_nontrivial;
    }
    else
      result = max_result+1;
  }
  else
    result = direct_defender_can_defend_in_n(next,n,max_result);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Solve threats after an attacker's move
 * @param threats table where to add threats
 * @param si slice index
 * @param n maximum number of half moves until end state has to be reached
 * @return length of threats
 *         (n-slack_length_direct)%2 if the attacker has something
 *           stronger than threats (i.e. has delivered check)
 *         n+2 if there is no threat
 */
stip_length_type max_nr_nontrivial_guard_solve_threats(table threats,
                                                       slice_index si,
                                                       stip_length_type n)
{
  stip_length_type result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  result = direct_defender_solve_threats(threats,slices[si].u.pipe.next,n);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Solve variations after the move that has just been played at root level
 * @param threats table containing threats
 * @param len_threat length of threats
 * @param si slice index
 * @param n maximum length of variations to be solved
 * @return true iff >= 1 variation was found
 */
boolean
max_nr_nontrivial_guard_solve_variations_in_n(table threats,
                                              stip_length_type len_threat,
                                              slice_index si,
                                              stip_length_type n)
{
  boolean result;
  slice_index const next = slices[si].u.pipe.next;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  if (n>min_length_nontrivial)
  {
    unsigned int const nr_nontrivial = count_nontrivial_defenses(si);
    if (max_nr_nontrivial+1<nr_nontrivial)
      result = false;
    else
    {
      ++max_nr_nontrivial;
      max_nr_nontrivial -= nr_nontrivial;
      result = direct_defender_solve_variations_in_n(threats,len_threat,next,n);
      max_nr_nontrivial += nr_nontrivial;
      --max_nr_nontrivial;
    }
  }
  else
    result = direct_defender_solve_variations_in_n(threats,len_threat,next,n);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Solve variations after the move that has just been played at root level
 * @param threats table containing threats
 * @param len_threat length of threats
 * @param refutations table containing refutations to move just played
 * @param si slice index
 */
void max_nr_nontrivial_guard_root_solve_variations(table threats,
                                                   stip_length_type len_threat,
                                                   table refutations,
                                                   slice_index si)
{
  stip_length_type const n = slices[si].u.pipe.u.branch.length;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  if (n>min_length_nontrivial)
  {
    unsigned int const nr_nontrivial = count_nontrivial_defenses(si);
    if (max_nr_nontrivial+1>=nr_nontrivial)
    {
      ++max_nr_nontrivial;
      max_nr_nontrivial -= nr_nontrivial;
      direct_defender_root_solve_variations(threats,len_threat,
                                            refutations,
                                            slices[si].u.pipe.next);
      max_nr_nontrivial += nr_nontrivial;
      --max_nr_nontrivial;
    }
  }
  else
    direct_defender_root_solve_variations(threats,len_threat,
                                          refutations,
                                          slices[si].u.pipe.next);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}


/* **************** Stipulation instrumentation ***************
 */

static boolean nontrivial_guard_inserter_direct_attack(slice_index si,
                                                       slice_traversal *st)
{
  boolean const result = true;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  slice_traverse_children(si,st);

  pipe_insert_after(si);
  init_max_nr_nontrivial_guard_slice(slices[si].u.pipe.next);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

static boolean nontrivial_guard_inserter_self_attack(slice_index si,
                                                     slice_traversal *st)
{
  boolean const result = true;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  slice_traverse_children(si,st);

  pipe_insert_before(si);
  init_max_nr_nontrivial_guard_slice(si);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

static slice_operation const max_nr_nontrivial_guards_inserters[] =
{
  &slice_traverse_children,                 /* STBranchDirect */
  &slice_traverse_children,                 /* STBranchDirectDefender */
  &slice_traverse_children,                 /* STBranchHelp */
  &slice_traverse_children,                 /* STBranchSeries */
  &slice_traverse_children,                 /* STBranchFork */
  &slice_traverse_children,                 /* STLeafDirect */
  &slice_traverse_children,                 /* STLeafHelp */
  &slice_traverse_children,                 /* STLeafForced */
  &slice_traverse_children,                 /* STReciprocal */
  &slice_traverse_children,                 /* STQuodlibet */
  &slice_traverse_children,                 /* STNot */
  &slice_traverse_children,                 /* STMoveInverter */
  &slice_traverse_children,                 /* STDirectRoot */
  &slice_traverse_children,                 /* STDirectDefenderRoot */
  &slice_traverse_children,                 /* STDirectHashed */
  &slice_traverse_children,                 /* STHelpRoot */
  &slice_traverse_children,                 /* STHelpAdapter */
  &slice_traverse_children,                 /* STHelpHashed */
  &slice_traverse_children,                 /* STSeriesRoot */
  &slice_traverse_children,                 /* STSeriesAdapter */
  &slice_traverse_children,                 /* STSeriesHashed */
  &slice_traverse_children,                 /* STSelfCheckGuard */
  &nontrivial_guard_inserter_direct_attack, /* STDirectAttack */
  &slice_traverse_children,                 /* STDirectDefense */
  &slice_traverse_children,                 /* STReflexGuard */
  &nontrivial_guard_inserter_self_attack,   /* STSelfAttack */
  &slice_traverse_children,                 /* STSelfDefense */
  &slice_traverse_children,                 /* STRestartGuard */
  &slice_traverse_children,                 /* STGoalReachableGuard */
  &slice_traverse_children,                 /* STKeepMatingGuard */
  &slice_traverse_children,                 /* STMaxFlightsquares */
  &slice_traverse_children,                 /* STMaxNrNonTrivial */
  &slice_traverse_children                  /* STMaxThreatLength */
};

/* Instrument stipulation with STKeepMatingGuard slices
 */
void stip_insert_max_nr_nontrivial_guards(void)
{
  slice_traversal st;

  TraceFunctionEntry(__func__);
  TraceFunctionParamListEnd();

  TraceStipulation();

  slice_traversal_init(&st,&max_nr_nontrivial_guards_inserters,0);
  traverse_slices(root_slice,&st);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
