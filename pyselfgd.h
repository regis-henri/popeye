#if !defined(PYSELFGD_H)
#define PYSELFGD_H

/* In self stipulations, guard against defenses that prematurely reach
 * the goal
 */

#include "stipulation/battle_play/attack_play.h"
#include "stipulation/battle_play/defense_play.h"

/* Determine whether there is a solution in n half moves, by trying
 * n_min, n_min+2 ... n half-moves.
 * @param si slice index of slice being solved
 * @param n maximum number of half moves until end state has to be reached
 * @param n_min minimal number of half moves to try
 * @param n_max_unsolvable maximum number of half-moves that we
 *                         know have no solution
 * @return length of solution found, i.e.:
 *            slack_length_battle-2 defense has turned out to be illegal
 *            <=n length of shortest solution found
 *            n+2 no solution found
 */
stip_length_type
self_defense_direct_has_solution_in_n(slice_index si,
                                      stip_length_type n,
                                      stip_length_type n_min,
                                      stip_length_type n_max_unsolvable);

/* Solve a slice, by trying n_min, n_min+2 ... n half-moves.
 * @param si slice index
 * @param n maximum number of half moves until goal
 * @param n_max_unsolvable maximum number of half-moves that we
 *                         know have no solution
 * @return length of solution found and written, i.e.:
 *            slack_length_battle-2 defense has turned out to be illegal
 *            <=n length of shortest solution found
 *            n+2 no solution found
 */
stip_length_type self_defense_solve_in_n(slice_index si,
                                         stip_length_type n,
                                         stip_length_type n_max_unsolvable);

/* Instrument a branch with STSelfAttack and STSelfDefense slices
 * @param si root of branch to be instrumented
 * @param proxy_to_goal identifies slice leading towards goal
 */
void slice_insert_self_guards(slice_index si, slice_index proxy_to_goal);

/* Instrument a branch leading to a goal to be a self goal branch
 * @param si identifies entry slice of branch
 */
void slice_make_self_goal_branch(slice_index si);

#endif
