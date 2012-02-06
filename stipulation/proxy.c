#include "stipulation/proxy.h"
#include "pypipe.h"
#include "pybrafrk.h"
#include "stipulation/branch.h"
#include "stipulation/boolean/binary.h"
#include "trace.h"

#include <assert.h>

/* Allocate a proxy pipe
 * @return newly allocated slice
 */
slice_index alloc_proxy_slice(void)
{
  slice_index result;

  TraceFunctionEntry(__func__);
  TraceFunctionParamListEnd();

  result = alloc_pipe(STProxy);

  TraceFunctionExit(__func__);
  TraceFunctionResult("%u",result);
  TraceFunctionResultEnd();
  return result;
}

static boolean is_proxy(slice_index si)
{
  boolean result;

  switch (slices[si].type)
  {
    case STProxy:
    case STEndOfRoot:
    case STEndOfIntro:
    case STThreatStart:
    case STReadyForAttack:
    case STReadyForDefense:
    case STMaxThreatLengthStart:
    case STReadyForHelpMove:
    case STReadyForDummyMove:
    case STGoalAutoStalemateReachedTester:
    case STGoalDoubleStalemateReachedTester:
    case STGoalStalemateReachedTester:
    case STGoalMateReachedTester:
    case STOutputModeSelector:
    case STShortSolutionsStart:
    case STCheckZigzagLanding:
    case STTestingPrerequisites:
    case STGeneratingMoves:
    case STMove:
    case STSolvingContinuation:
    case STTestingForEndOfBranch:
      result = true;
      break;

    default:
      result = false;
      break;
  }

  return result;
}

/* Substitute a possible link to a proxy slice by the proxy's target
 * @param si address of slice index
 * @param st points at the structure holding the state of the traversal
 */
void proxy_slice_resolve(slice_index *si, stip_structure_traversal *st)
{
  slice_index const prev = slices[*si].prev;
  boolean (* const is_resolved_proxy)[max_nr_slices] = st->param;

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",*si);
  TraceFunctionParam("%p",st);
  TraceFunctionParamListEnd();

  TraceEnumerator(slice_type,slices[*si].type,"");
  TraceValue("%u\n",is_proxy(*si));
  while (*si!=no_slice && is_proxy(*si))
  {
    TraceValue("%u",*si);
    TraceValue("%u",(*is_resolved_proxy)[*si]);
    (*is_resolved_proxy)[*si] = true;
    TraceValue("%u\n",(*is_resolved_proxy)[*si]);
    *si = slices[*si].u.pipe.next;
  }

  if (is_proxy(slices[*si].prev))
    slices[*si].prev = prev;

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}

/* Substitute links to proxy slices by the proxy's target
 * @param si points to variable holding root slice of stipulation; if
 *           that slice's type is STProxy, the variable will be updated
 *           to hold the first non-proxy slice
 */
void resolve_proxies(slice_index *si)
{
  slice_index i;
  stip_structure_traversal st;
  boolean is_resolved_proxy[max_nr_slices] = { false };

  TraceFunctionEntry(__func__);
  TraceFunctionParam("%u",*si);
  TraceFunctionParamListEnd();

  TraceStipulation(*si);

  assert(slices[*si].type==STProxy);

  stip_structure_traversal_init(&st,&is_resolved_proxy);
  stip_structure_traversal_override_by_structure(&st,
                                                 slice_structure_pipe,
                                                 &pipe_resolve_proxies);
  stip_structure_traversal_override_by_structure(&st,
                                                 slice_structure_branch,
                                                 &pipe_resolve_proxies);
  stip_structure_traversal_override_by_structure(&st,
                                                 slice_structure_fork,
                                                 &branch_fork_resolve_proxies);
  stip_structure_traversal_override_by_structure(&st,
                                                 slice_structure_binary,
                                                 &binary_resolve_proxies);

  stip_traverse_structure(*si,&st);

  proxy_slice_resolve(si,&st);

  for (i = 0; i!=max_nr_slices; ++i)
    if (is_resolved_proxy[i])
      dealloc_slice(i);

  TraceFunctionExit(__func__);
  TraceFunctionResultEnd();
}
