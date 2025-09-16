#ifndef VIDEOWALLLIB_VISIONCONTROLLER_H
#define VIDEOWALLLIB_VISIONCONTROLLER_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <Signal/CDPSignal.h>
#include <Generic/CDPUtils.h>

#include "OperationUtilities/Strings/StringHelpers.h"

namespace VideoWallLib {

class VisionController : public CDPComponent
{
public:
    VisionController();
    ~VisionController() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    int MessageToggleFullscreen(void* message);

protected:
    CDPConnector MQTTPublish;
    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;

    int currentFullscreenTile {-1};
    void PublishMQTT();
};

} // namespace VideoWallLib

#endif
