#ifndef VIDEOWALLLIB_OSDTEXT_H
#define VIDEOWALLLIB_OSDTEXT_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <OSDTextPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace VideoWallLib {

class OSDText : public CDPComponent
{
public:
    OSDText();
    ~OSDText() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    CDPSignal<std::string> Text;
    CDPSignal<std::string> FontName;
    CDPSignal<float> FontSize;
    CDPSignal<std::string> FontColor;
    CDPSignal<std::string> BGColor;
    CDPSignal<int> PosX;
    CDPSignal<int> PosY;
    CDPSignal<float> Timeout;
    CDPSignal<std::string> JSONOut;
    CDPSignal<bool> Visible;
    CDPSignal<std::string> Alignment;
    
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
