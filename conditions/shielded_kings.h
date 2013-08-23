#if !defined(CONDITIONS_SHIELDED_KINGS_H)
#define CONDITIONS_SHIELDED_KINGS_H

#include "stipulation/stipulation.h"
#include "utilities/boolean.h"

/* Implementation of condition Shielded kings
 */

/* Validate an observation according to Shielded Kings
 * @return true iff the observation is valid
 */
boolean shielded_kings_validate_observation(slice_index si);

/* Try to solve in n half-moves.
 * @param si slice index
 * @param n maximum number of half moves
 * @return length of solution found and written, i.e.:
 *            previous_move_is_illegal the move just played (or being played)
 *                                     is illegal
 *            immobility_on_next_move  the moves just played led to an
 *                                     unintended immobility on the next move
 *            <=n+1 length of shortest solution found (n+1 only if in next
 *                                     branch)
 *            n+2 no solution found in this branch
 *            n+3 no solution found in next branch
 */
stip_length_type shielded_kings_remove_illegal_captures_solve(slice_index si,
                                                              stip_length_type n);

/* Inialise solving in Shielded kings
 * @param si identifies the root slice of the solving machinery
 */
void shielded_kings_initialise_solving(slice_index si);

#endif
