#ifndef VIDEOWALLLIB_CAMERA_H
#define VIDEOWALLLIB_CAMERA_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPPort.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <CameraPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <CDPCore/OSAPI/Timer/CDPParameterTimer.h>

#include <json.hpp>
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
    void ProcessSaveToJson();
    json toJson() const;

protected:
    CDPPort pCamera;
    CDPParameterTimer timerTest;
    CDPSignal<int> Width;
    CDPSignal<int> Height;
    CDPSignal<std::string> DisplayName;
    CDPSignal<std::string> IP;
    CDPSignal<std::string> Format;
    CDPSignal<float> Framerate;
    CDPSignal<std::string> Type;
    CDPSignal<std::string> URI;
    CDPSignal<bool> SaveTpoJson;
    CDPProperty<std::string> propIP;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
