#include "pieces/walks/angle/hoppers.h"
#include "pieces/walks/hoppers.h"
#include "pieces/walks/hamster.h"
#include "solving/move_generator.h"
#include "solving/observation.h"
#include "debugging/trace.h"
#include "pydata.h"

#include <assert.h>

/* Generated moves for an angle hopper
 * @param kanf first vectors index
 * @param kend last vectors index
 * @param angle angle to take from hurdle to arrival squares
 */
static void angle_hoppers_generate_moves(vec_index_type kanf, vec_index_type kend,
                                         angle_t angle)
{
  vec_index_type k;

  TraceFunctionEntry(__func__);
  TraceFunctionParam ("%u",kanf);
  TraceFunctionParam ("%u",kend);
  TraceFunctionParam ("%u",angle);
  TraceFunctionParamListEnd();

  for (k = kend; k>=kanf; k--)
  {
    square const sq_hurdle = find_end_of_line(curr_generation->departure,vec[k]);
    if (!is_square_blocked(sq_hurdle))
    {
      vec_index_type const k1 = 2*k;

      {
        square const sq_arrival= sq_hurdle+angle_vectors[angle][k1];
        if (is_square_empty(sq_arrival)
            || piece_belongs_to_opponent(sq_arrival))
        {
          curr_generation->auxiliary.hopper.sq_hurdle = sq_hurdle;
          curr_generation->auxiliary.hopper.vec_index = k;
          push_move_generation(sq_arrival);
        }
      }

      {
        square const sq_arrival= sq_hurdle+angle_vectors[angle][k1-1];
        if (is_square_empty(sq_arrival)
            || piece_belongs_to_opponent(sq_arrival))
        {
          curr_generation->auxiliary.hopper.sq_hurdle = sq_hurdle;
          curr_generation->auxiliary.hopper.vec_index = k;
          push_move_generation(sq_arrival);
        }
      }
    }
  }

  curr_generation->auxiliary.hopper.sq_hurdle = initsquare;
  curr_generation->auxiliary.hopper.vec_index = 0;

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

static boolean angle_hoppers_is_square_observed_one_dir(square sq_hurdle,
                                                        vec_index_type vec_index_departure_hurdle,
                                                        angle_t angle,
                                                        PieNam p,
                                                        evalfunction_t *evaluate)
{
  square const sq_target = move_generation_stack[current_move[nbply]-1].capture;
  numvec const vec_departure_hurdle = angle_vectors[angle][vec_index_departure_hurdle];
  square const sq_departure = find_end_of_line(sq_hurdle,vec_departure_hurdle);
  PieNam const hopper = get_walk_of_piece_on_square(sq_departure);

  return (hopper==p
          && TSTFLAG(spec[sq_departure],trait[nbply])
          && INVOKE_EVAL(evaluate,sq_departure,sq_target));
}

/* Is a particular square observed by a particular type of angle hopper?
 * @param kanf first vectors index
 * @param kend last vectors index
 * @param angle angle to take from hurdle to arrival squares
 * @param p type of piece
 */
boolean angle_hoppers_is_square_observed(vec_index_type kanf, vec_index_type kend,
                                         angle_t angle,
                                         PieNam p,
                                         evalfunction_t *evaluate)
{
  square const sq_target = move_generation_stack[current_move[nbply]-1].capture;
  boolean result = false;

  TraceFunctionEntry(__func__);
  TraceSquare(sq_target);
  TraceFunctionParam ("%u",kanf);
  TraceFunctionParam ("%u",kend);
  TraceFunctionParam ("%u",angle);
  TracePiece(p);
  TraceFunctionParamListEnd();

  ++observation_context;

  for (interceptable_observation_vector_index[observation_context] = kend;
       interceptable_observation_vector_index[observation_context]>=kanf;
       --interceptable_observation_vector_index[observation_context])
  {
    numvec const vec_hurdle_target = vec[interceptable_observation_vector_index[observation_context]];
    square const sq_hurdle = sq_target+vec_hurdle_target;

    if (!is_square_empty(sq_hurdle) && !is_square_blocked(sq_hurdle))
    {
      vec_index_type const vec_index_departure_hurdle = 2*interceptable_observation_vector_index[observation_context];

      if (angle_hoppers_is_square_observed_one_dir(sq_hurdle,
                                                   vec_index_departure_hurdle,
                                                   angle,
                                                   p,
                                                   evaluate)
          || angle_hoppers_is_square_observed_one_dir(sq_hurdle,
                                                      vec_index_departure_hurdle-1,
                                                      angle,
                                                      p,
                                                      evaluate))
      {
        result = true;
        break;
      }
    }
  }

  --observation_context;

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Generated moves for an Elk
 */
void elk_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_45);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for an Rook Moose
 */
void rook_moose_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_rook_start,vec_rook_end, angle_45);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for an Bishop Moose
 */
void bishop_moose_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_bishop_start,vec_bishop_end, angle_45);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for an Eagle
 */
void eagle_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_90);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for a Rook Eagle
 */
void rook_eagle_generate_moves(void)
{
  angle_hoppers_generate_moves(vec_rook_start,vec_rook_end, angle_90);
}

/* Generated moves for a Bishop Eagle
 */
void bishop_eagle_generate_moves(void)
{
  angle_hoppers_generate_moves(vec_bishop_start,vec_bishop_end, angle_90);
}

/* Generated moves for a Sparrow
 */
void sparrow_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_135);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for a Rook Sparrow
 */
void rook_sparrow_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_rook_start,vec_rook_end, angle_135);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for a Bishop Sparrow
 */
void bishop_sparrow_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_bishop_start,vec_bishop_end, angle_135);
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}

/* Generated moves for a Marguerite
 */
void marguerite_generate_moves(void)
{
  numecoup const save_current_move = current_move[nbply]-1;
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_45);
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_90);
  angle_hoppers_generate_moves(vec_queen_start,vec_queen_end, angle_135);
  hoppers_generate_moves(vec_queen_start,vec_queen_end);
  hamster_generate_moves();
  if (!TSTFLAG(spec[curr_generation->departure],ColourChange))
    remove_duplicate_moves_of_single_piece(save_current_move);
}
