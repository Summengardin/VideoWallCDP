#ifndef VIDEOWALLLIB_SKAARHOJRAWPANELIO_H
#define VIDEOWALLLIB_SKAARHOJRAWPANELIO_H

#include <CDPAlarm/CDPAlarm.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <IO/IOServer.h>
#include <IO/Transport.h>
#include <IO/TCPTransport.h>
#include <OSAPI/Process/OSAPIEvent.h>
#include <OSAPI/Process/OSAPIThread.h>
#include <Signal/CDPSignal.h>
#include <atomic>
#include <sstream>

#include "skhojhandcontroller.h"

namespace VideoWallLib {

  class SKAARHOJRawPanelIO : public IOServer, public OSAPIThread {
  public:
    SKAARHOJRawPanelIO();
    ~SKAARHOJRawPanelIO() override;

    void Create(const char *fullName) override;
    void CreateModel() override;
    void Configure(const char *componentXML) override;
    void Activate() override;
    void Suspend() override;
    bool IsCommProblem() override;
    void FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const override;

  protected:
    void ProcessOffline() override;
    void ProcessOnline() override;

    unsigned int NumberOfNodesInXml() const override;

    bool HandleXMLElement(XMLElementEx *pEx) override;
    void Main() override;

    virtual void ProtocolImplementation();

    using CDPComponent::fs;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    CDP::IO::TCPTransport *m_transport {nullptr};

    OSAPIEvent m_event;
    std::atomic<double> m_lastUpdateTime {0};
    SKHOJ::HandController HandController;
    CDPParameter PanelBrightnessPercent;
    CDPConnector HCOUT;


  };

}// namespace VideoWallLib

#endif
