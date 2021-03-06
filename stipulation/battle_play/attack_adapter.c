#include "stipulation/battle_play/attack_adapter.h"
#include "stipulation/branch.h"
#include "stipulation/slice_insertion.h"
#include "stipulation/battle_play/branch.h"
#include "stipulation/battle_play/defense_adapter.h"
#include "stipulation/pipe.h"
#include "debugging/trace.h"
#include "debugging/assert.h"

/* Allocate a STAttackAdapter slice.
 * @param length maximum number of half-moves of slice (+ slack)
 * @param min_length minimum number of half-moves of slice (+ slack)
 * @return index of allocated slice
 */
slice_index alloc_attack_adapter_slice(stip_length_type length,
                                       stip_length_type min_length)
{
  slice_index result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",length);
  TraceFunctionParam("%u",min_length);
  TraceFunctionParamListEnd();

  result = alloc_branch(STAttackAdapter,length,min_length);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Wrap the slices representing the initial moves of the solution with
 * slices of appropriately equipped slice types
 * @param adapter identifies solve adapter slice
 * @param st address of structure holding the traversal state
 */
void attack_adapter_make_root(slice_index adapter,
                              stip_structure_traversal *st)
{
  spin_off_state_type * const state = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",adapter);
  TraceFunctionParamListEnd();

  battle_make_root(adapter,state);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Apply setplay to a branch with alternate moves
 * @param adapter STAttackAdapter slice
 * @param st holds the setplay application traversal
 */
static void apply_setplay_alternate(slice_index adapter,
                                    stip_structure_traversal *st)
{
  spin_off_state_type * const state = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",adapter);
  TraceFunctionParamListEnd();

  battle_branch_make_setplay(adapter,state);

  if (state->spun_off[adapter]!=no_slice)
  {
    stip_length_type const length = SLICE_U(adapter).branch.length;
    stip_length_type const min_length = SLICE_U(adapter).branch.min_length;
    slice_index const nested = state->spun_off[adapter];
    state->spun_off[adapter] = alloc_defense_adapter_slice(length-1,
                                                           min_length-1);
    link_to_branch(state->spun_off[adapter],nested);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Apply setplay to a series branch
 * @param adapter STAttackAdapter slice
 * @param st holds the setplay application traversal
 */
static void apply_setplay_series(slice_index adapter,
                                 stip_structure_traversal *st)
{
  spin_off_state_type * const state = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",adapter);
  TraceFunctionParamListEnd();

  {
    slice_index const proto = alloc_defense_adapter_slice(0,0);
    slice_insertion_insert(adapter,&proto,1);
  }

  {
    slice_index const defense_adapter = branch_find_slice(STDefenseAdapter,
                                                          adapter,
                                                          stip_traversal_context_intro);
    assert(defense_adapter!=no_slice);
    battle_branch_make_root_slices(defense_adapter,state);
    assert(state->spun_off[defense_adapter]!=no_slice);
    state->spun_off[adapter] = state->spun_off[defense_adapter];
    pipe_remove(defense_adapter);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Remember a defense move in the normal path
 * @param si STMove slice
 * @st holds the defense move finding traversal
 */
static void remember_defense(slice_index si,
                             stip_structure_traversal *st)
{
  boolean * const result = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  if (st->context==stip_traversal_context_defense)
    *result = true;
  else
    stip_traverse_structure_children_pipe(si,st);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Is there a defense move in the "normal" path?
 * @param adapter identifies STAttackAdapter slice
 * @param st holds the setplay application traversal
 * @return true iff there is a defense move on the normal path
 */
static boolean find_defense_in_normal_path(slice_index adapter,
                                           stip_structure_traversal *st)
{
  boolean result = false;
  stip_structure_traversal st_nested;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",adapter);
  TraceFunctionParamListEnd();

  stip_structure_traversal_init_nested(&st_nested,st,&result);
  branch_instrument_traversal_for_normal_path(&st_nested);
  stip_structure_traversal_override_single(&st_nested,STMove,&remember_defense);
  stip_traverse_structure(adapter,&st_nested);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Attempt to add set play to an solve stipulation (battle play, not
 * postkey only)
 * @param adapter identifies solve adapter slice
 * @param st address of structure representing traversal
 */
void attack_adapter_apply_setplay(slice_index adapter,
                                  stip_structure_traversal *st)
{
  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",adapter);
  TraceFunctionParamListEnd();

  if (SLICE_U(adapter).branch.length>0)
  {
    if (find_defense_in_normal_path(adapter,st))
      apply_setplay_alternate(adapter,st);
    else
      apply_setplay_series(adapter,st);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
