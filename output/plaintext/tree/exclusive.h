#if !defined(OUTPUT_PLAINTEXT_TREE_EXCLUSIV_H)
#define OUTPUT_PLAINTEXT_TREE_EXCLUSIV_H

/* This module helps informing the user about undecidable moves in Exclusive Chess
 */

#include "solving/machinery/solve.h"
#include "stipulation/pipe.h"

/* Allocate a STExclusiveChessUndecidableWriterTree slice
 * @return identifier of the allocated slice
 */
slice_index alloc_exclusive_chess_undecidable_writer_tree_slice(void);

/* Try to solve in solve_nr_remaining half-moves.
 * @param si slice index
 * @note assigns solve_result the length of solution found and written, i.e.:
 *            previous_move_is_illegal the move just played is illegal
 *            this_move_is_illegal     the move being played is illegal
 *            immobility_on_next_move  the moves just played led to an
 *                                     unintended immobility on the next move
 *            <=n+1 length of shortest solution found (n+1 only if in next
 *                                     branch)
 *            n+2 no solution found in this branch
 *            n+3 no solution found in next branch
 *            (with n denominating solve_nr_remaining)
 */
void exclusive_chess_undecidable_writer_tree_solve(slice_index si);

#endif
