#include "conditions/shielded_kings.h"
#include "pydata.h"
#include "solving/observation.h"
#include "debugging/trace.h"

#include <stdlib.h>

static boolean shielded_kings_test_support(square sq_observer,
                                           square sq_landing,
                                           square sq_observee)
{
  boolean result;
  Side const moving_side = e[sq_observer]>vide ? White : Black;
  Side const opponent = advers(moving_side);
  square const save_king_square = king_square[opponent];

  TraceFunctionEntry(__func__);
  TraceSquare(sq_observer);
  TraceSquare(sq_landing);
  TraceSquare(sq_observee);
  TraceFunctionParamListEnd();

  king_square[opponent] = sq_observer;
  result = is_king_square_attacked[opponent](&validate_observer);
  king_square[opponent] = save_king_square;

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

static boolean avoid_observation_of_shielded(square sq_observer,
                                             square sq_landing,
                                             square sq_observee)
{
  boolean result;

  TraceFunctionEntry(__func__);
  TraceSquare(sq_observer);
  TraceSquare(sq_landing);
  TraceSquare(sq_observee);
  TraceFunctionParamListEnd();

  if ((sq_observer==king_square[Black] && sq_observee==king_square[White])
      || (sq_observer==king_square[White] && sq_observee==king_square[Black]))
    /* won't work for locust Ks etc.*/
    result = !shielded_kings_test_support(sq_observee,sq_observer,sq_observer);
  else
    result = true;

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

/* Inialise solving in Shielded kings
 */
void shielded_kings_initialise_solving(void)
{
  TraceFunctionEntry(__func__);
  TraceFunctionParamListEnd();

  register_observation_validator(&avoid_observation_of_shielded);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}