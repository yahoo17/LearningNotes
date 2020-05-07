
#ifndef ALL_INTERNALS
#define ALL_INTERNALS
#endif

//# USER MODIFIED CODE #INCLUDES#
//# USER MODIFIED CODE #INCLUDES#

#include "AI.h"

//# USER MODIFIED CODE #GLOBAL_DATA#
//# USER MODIFIED CODE #GLOBAL_DATA#

///////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: Construct
//
//  DESCRIPTION:
//
//  The Construct function may be used by the client to
//  modify the default instantiation behavior for
//  this class.
//
//  PARAMETERS:
//
//  reason - The event that is about to occur in the construction process.
//
void
AI::Construct(
    JMASE::Component::Construct_Callback_Reason const & reason)
{
#if defined(_MSC_VER) && (_MSC_VER < 1310)
  Component::ValidateEntryPoint("AI::Construct");
#else
  JMASE::Component::ValidateEntryPoint("AI::Construct");
#endif
  //# USER MODIFIED CODE #Construct_BODY#
  //# USER MODIFIED CODE #Construct_BODY#
}

///////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: Destruct
//
//  DESCRIPTION:
//
//  The Destruct function may be used to modify the
//  default destruction behavior for this class.
//  Setting jmaseDestroyFlag to zero bypasses the default
//  destruction sequence. This is useful for clients
//  that need a customized destructor.
//
//  PARAMETERS:
//
//  jmaseDestroyFlag - Flag used to determine whether the default constructor will
//                     be called for this object.
//
void
AI::Destruct(
    int & jmaseDestroyFlag)
{
#if defined(_MSC_VER) && (_MSC_VER < 1310)
  Component::ValidateEntryPoint("AI::Destruct");
#else
  JMASE::Component::ValidateEntryPoint("AI::Destruct");
#endif
  //# USER MODIFIED CODE #Destruct_BODY#
  int test = 100;
  //# USER MODIFIED CODE #Destruct_BODY#
}

///////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: Initialize
//
//  DESCRIPTION:
//
//  This function initializes `AI' instances.
//
//  PARAMETERS:
//
//  None.
//
void
AI::Initialize()
{
#if defined(_MSC_VER) && (_MSC_VER < 1310)
  Component::ValidateEntryPoint("AI::Initialize");
#else
  JMASE::Component::ValidateEntryPoint("AI::Initialize");
#endif
  //# USER MODIFIED CODE #Initialize_BODY#
  int test = 100;
  //# USER MODIFIED CODE #Initialize_BODY#
}

///////////////////////////////////////////////////////////////////////////////
//
//  OPERATION: Update
//
//  DESCRIPTION:
//
//  This function is called by the JMASE framework
//  in response to a scheduled event.
//
//  PARAMETERS:
//
//  None.
//
void
AI::Update()
{
#if defined(_MSC_VER) && (_MSC_VER < 1310)
  Component::ValidateEntryPoint("AI::Update");
#else
  JMASE::Component::ValidateEntryPoint("AI::Update");
#endif
  //# USER MODIFIED CODE #Update_BODY#
  //# USER MODIFIED CODE #Update_BODY#
}

