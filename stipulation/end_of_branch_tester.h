#if !defined(STIPULATION_END_OF_BRANCH_TESTER_H)
#define STIPULATION_END_OF_BRANCH_TESTER_H

/* Test whether the end of a branch has been reached before going on. We only
 * do this in branches that don't end in a position where the side at the move
 * is immobile (e.g. branches that end in mate or stalemate).
 */

#include "py.h"

/* Instrument STEndOfBranchGoal (and STEndOfBranchForced) slices with the
 * necessary STEndOfBranchTester slices
 * @param root_slice identifes root slice of stipulation
 */
void stip_insert_end_of_branch_testers(slice_index root_slice);

#endif
