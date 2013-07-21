#include "pieces/walks/pawns/reverse.h"
#include "pieces/walks/pawns/pawns.h"
#include "pieces/walks/pawns/pawn.h"
#include "debugging/trace.h"
#include "pydata.h"

#include <assert.h>

/* Generate moves for a reverse pawn
 * @param sq_departure common departure square of the generated moves
 */
void reverse_pawn_generate_moves(square sq_departure)
{
  unsigned int const no_capture_length = pawn_get_no_capture_length(advers(trait[nbply]),
                                                                    sq_departure);

  if (no_capture_length>0)
  {
    int const dir_backward = trait[nbply]==White ? dir_down : dir_up;

    pawns_generate_capture_move(sq_departure,dir_backward+dir_right);
    pawns_generate_capture_move(sq_departure,dir_backward+dir_left);
    pawns_generate_nocapture_moves(sq_departure,dir_backward,no_capture_length);
  }
}