#ifndef VIDEOWALLLIB_SKAARHOJRAWPANELMENU_H
#define VIDEOWALLLIB_SKAARHOJRAWPANELMENU_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <OSAPI/Process/OSAPIEvent.h>
#include <OSAPI/Process/OSAPIThread.h>
#include <Signal/CDPSignal.h>

namespace VideoWallLib {

  class SKAARHOJRawPanelMenu : public CDPComponent, public OSAPIThread {
  public:
    SKAARHOJRawPanelMenu();
    ~SKAARHOJRawPanelMenu() override;

    virtual void Create(const char *fullName) override;
    virtual void CreateModel() override;
    virtual void Configure(const char *componentXML) override;
    void ProcessNull() override;
    int MessageFromIO(void* message);
    virtual void Activate() override;
    virtual void Suspend() override;

  protected:
    virtual void Main() override;
    void AccessObjectsUsingMemberAccessMutex();
    void AccessObjectsBySchedulingIntoComponentThread();

    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    OSAPIEvent m_event;
    CDPSignal<unsigned char> m_counter;
    CDPConnector ToIO;
  };

}// namespace VideoWallLib

#endif
