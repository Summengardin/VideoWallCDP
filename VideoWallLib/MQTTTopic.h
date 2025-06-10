#ifndef VIDEOWALLLIB_MQTTTOPIC_H
#define VIDEOWALLLIB_MQTTTOPIC_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <Signal/CDPSignal.h>

namespace VideoWallLib {

class MQTTTopic : public CDPComponent
{
public:
    MQTTTopic();
    ~MQTTTopic() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    CDPParameter Retain;
    CDPParameter QoS;
    CDPSignal<std::string> Topic;
    CDPSignal<std::string> Payload;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
};

} // namespace VideoWallLib

#endif
