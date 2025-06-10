#ifndef VIDEOWALLLIB_CAMERA_H
#define VIDEOWALLLIB_CAMERA_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <CameraPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

#include "OperationUtilities/Parameters/StringParameter.h"
#include "OperationUtilities/Parameters/calibrationparameter.h"
#include "json.hpp"

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
    CDPPort pCamera;
    OperationUtilities::CalibrationParameter Width;
    OperationUtilities::CalibrationParameter Height;
    OperationUtilities::CalibrationParameter Framerate;
    StringParameter DisplayName;
    StringParameter IP;
    StringParameter Format;
    StringParameter Type;
    StringParameter URI;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
