#ifndef VIDEOWALLLIB_MQTTHANDLER_H
#define VIDEOWALLLIB_MQTTHANDLER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace VideoWallLib {

class MQTTHandler : public CDPComponent
{
public:
    MQTTHandler();
    ~MQTTHandler() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
