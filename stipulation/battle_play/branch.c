#include "stipulation/battle_play/branch.h"
#include "pypipe.h"
#include "stipulation/proxy.h"
#include "stipulation/battle_play/attack_move.h"
#include "stipulation/battle_play/defense_move.h"
#include "trace.h"

#include <assert.h>

/* Allocate a branch that represents battle play
 * @param length maximum number of half-moves of slice (+ slack)
 * @param min_length minimum number of half-moves of slice (+ slack)
 * @return index of entry slice to allocated branch
 */
slice_index alloc_battle_branch(stip_length_type length,
                                stip_length_type min_length)
{
  slice_index result;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",length);
  TraceFunctionParam("%u",min_length);
  TraceFunctionParamListEnd();

  assert(length>slack_length_battle);
  assert(min_length>=slack_length_battle);
  assert(min_length%2==length%2);

  result = alloc_attack_move_slice(length,min_length);

  {
    slice_index const defense = alloc_defense_move_slice(length-1,min_length-1);
    pipe_link(result,defense);
    pipe_link(defense,result);
  }

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}
