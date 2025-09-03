#ifndef VIDEOWALLLIB_CAMERA_H
#define VIDEOWALLLIB_CAMERA_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <CameraPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <Generic/CDPUtils.h>

#include "OperationUtilities/Parameters/calibrationparameter.h"
#include "OperationUtilities/Signals/DeliveryConfigString.h"
#include "json.hpp"
#include "uri.h"


using json = nlohmann::json;


namespace VideoWallLib {

class Camera : public CDPComponent
{
public:
    Camera();
    ~Camera() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    json toJson() const;

protected:
    OperationUtilities::CalibrationParameter Width;
    OperationUtilities::CalibrationParameter Height;
    OperationUtilities::CalibrationParameter Framerate;
    OperationUtilities::DeliveryConfigString DisplayName;
    OperationUtilities::DeliveryConfigString IP;
    OperationUtilities::DeliveryConfigString Format;
    OperationUtilities::DeliveryConfigString Type;
    OperationUtilities::DeliveryConfigString URI;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    std::vector<std::string> topics {"DisplayName", "IP","URI","Width","Height","Framerate","Format","Type"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;

    Uri UriParser;
    CDPConnector MQTTPublish;

    void IndexInputs();
    void PublishMQTT();
    void ParseURI();

    bool firstRun {true};
};

} // namespace VideoWallLib

#endif
