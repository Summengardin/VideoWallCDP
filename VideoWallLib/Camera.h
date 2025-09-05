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
    void UpdateSignalFromProp(CDPPropertyBase* prop);
    json toJson() const;

protected:
    OperationUtilities::CalibrationParameter Width;
    OperationUtilities::CalibrationParameter Height;
    OperationUtilities::CalibrationParameter Framerate;
    CDPSignal<std::string> Type;
    CDPSignal<std::string> Format;
    CDPSignal<std::string> URI;
    CDPSignal<std::string> DisplayName;
    CDPSignal<std::string> IP;
    // OperationUtilities::DeliveryConfigString DisplayName;
    // OperationUtilities::DeliveryConfigString IP;
    // OperationUtilities::DeliveryConfigString Format;
    // OperationUtilities::DeliveryConfigString Type;
    // OperationUtilities::DeliveryConfigString URI;

    // local Properties for reading the signal via connections


    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;

    std::vector<std::string> topics {"DisplayName", "IP","URI","Width","Height","Framerate","Format","Type"};
    std::vector<std::string> indexedSignals;
    std::vector<std::string> indexedSignalsPrev;
    std::vector<bool> indexedSignalsChanged;

    Uri UriParser;

    CDPConnector MQTTPublish;
    CDPProperty<double> pWidth;
    CDPProperty<double> pHeight;
    CDPProperty<double> pFramerate;
    CDPProperty<std::string> pDisplayName;
    CDPProperty<std::string> pIP;
    CDPProperty<std::string> pFormat;
    CDPProperty<std::string> pType;
    CDPProperty<std::string> pURI;


    void IndexInputs();
    void PublishMQTT();
    void ParseURI();
    void UpdateLocalProperties();

    bool firstRun {true};
};

} // namespace VideoWallLib

#endif
