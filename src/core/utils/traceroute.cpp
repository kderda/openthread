#include "common/error.hpp"
#include "traceroute.hpp"
#include "common/as_core_type.hpp"
#include <common/locator_getters.hpp>
#include <net/socket.hpp>

namespace ot {
namespace Utils {

Traceroute::Traceroute(Instance &aInstance)
    : InstanceLocator(aInstance)
    , mTimer(aInstance, Traceroute::HandleTimer)
    , mIcmpHandler(Traceroute::HandleIcmpReceive, this)
    , mSocket(aInstance)
{

}

Error Traceroute::Start(const otIp6Address *aAddress)
{
    otError          error   = OT_ERROR_NONE;
    Message *        message = nullptr;
    Ip6::MessageInfo messageInfo;

    OT_UNUSED_VARIABLE(aAddress);

    messageInfo.SetPeerAddr(AsCoreType(aAddress));
    messageInfo.SetPeerPort(kTraceroutePort);

    message = Get<Ip6::Udp>().NewMessage(0, Message::Settings::From(nullptr));

    SuccessOrExit(error = Get<Ip6::Udp>().SendTo(mSocket, *message, messageInfo));
exit:
    return error;
}

void Traceroute::HandleTimer(Timer &aTimer)
{
    aTimer.Get<Traceroute>().HandleTimer();
}

void Traceroute::HandleTimer()
{

}

void Traceroute::HandleIcmpReceive(void *               aContext,
                                   otMessage *          aMessage,
                                   const otMessageInfo *aMessageInfo,
                                   const otIcmp6Header *aIcmpHeader)
{
    OT_UNUSED_VARIABLE(aContext);
    OT_UNUSED_VARIABLE(aMessage);
    OT_UNUSED_VARIABLE(aMessageInfo);
    OT_UNUSED_VARIABLE(aIcmpHeader);

}

void Traceroute::HandleIcmpReceive(const Message &          aMessage,
                                  const Ip6::MessageInfo & aMessageInfo,
                                  const Ip6::Icmp::Header &aIcmpHeader)
{
    OT_UNUSED_VARIABLE(aMessage);
    OT_UNUSED_VARIABLE(aMessageInfo);
    OT_UNUSED_VARIABLE(aIcmpHeader);
}

}
}