#include <openthread/traceroute.h>

#include "common/as_core_type.hpp"
#include "common/locator_getters.hpp"

using namespace ot;

otError otTracerouteStart(otInstance *aInstance, const otIp6Address *aAddress)
{
    return AsCoreType(aInstance).Get<Utils::Traceroute>().Start(aAddress);
}

