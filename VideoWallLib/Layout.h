#ifndef VIDEOWALLLIB_LAYOUT_H
#define VIDEOWALLLIB_LAYOUT_H

#include <CDPSystem/Base/CDPComponent.h>
#include <LayoutPort.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace VideoWallLib {

class Layout : public CDPComponent
{
public:
    Layout();
    ~Layout() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;

protected:
    LayoutPort pLayout;
    CDPSignal<std::string> Source14;
    CDPSignal<std::string> Source13;
    CDPSignal<std::string> Source12;
    CDPSignal<std::string> Source11;
    CDPSignal<std::string> Source04;
    CDPSignal<std::string> Source03;
    CDPSignal<std::string> Source02;
    CDPSignal<std::string> Source01;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
