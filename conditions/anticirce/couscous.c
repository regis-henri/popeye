#include "conditions/anticirce/couscous.h"
#include "conditions/anticirce/anticirce.h"
#include "stipulation/has_solution_type.h"
#include "stipulation/stipulation.h"
#include "solving/move_effect_journal.h"
#include "debugging/trace.h"

#include <assert.h>

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
stip_length_type anticirce_couscous_determine_relevant_piece_solve(slice_index si,
                                                                   stip_length_type n)
{
  stip_length_type result;
  move_effect_journal_index_type const top = move_effect_journal_base[nbply];
  move_effect_journal_index_type const capture = top+move_effect_journal_index_offset_capture;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParam("%u",n);
  TraceFunctionParamListEnd();

  anticirce_current_relevant_piece[nbply] = move_effect_journal[capture].u.piece_removal.removed;
  anticirce_current_relevant_spec[nbply] = move_effect_journal[capture].u.piece_removal.removedspec;
  anticirce_current_relevant_side[nbply] = slices[si].starter;

  result = solve(slices[si].next1,n);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Override the Circe instrumentation of the solving machinery with
 * Anticirce Couscous
 * @param si identifies root slice of stipulation
 */
void anticirce_couscous_initialise_solving(slice_index si)
{
  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",si);
  TraceFunctionParamListEnd();

  stip_replace_anticirce_determine_relevant_piece(si,STAnticirceCouscousDetermineRevelantPiece);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
