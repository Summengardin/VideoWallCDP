#ifndef VIDEOWALLLIB_SKAARHOJTCPCOM_H
#define VIDEOWALLLIB_SKAARHOJTCPCOM_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include <OSAPI/Process/OSAPIThread.h>
#include <OSAPI/Process/OSAPIEvent.h>
#include <IO/Transport.h>
#include <CDPSystem/Base/CDPConnector.h>
#include <IO/IOServer.h>
#include <atomic>
#include <sstream>


namespace VideoWallLib {

class SKAARHOJTCPCom : public IOServer, public OSAPIThread
{
public:
    SKAARHOJTCPCom();
    ~SKAARHOJTCPCom() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void Activate() override;
    void Suspend() override;
    bool IsCommProblem() override;
    void FillNodeChildren(CDP::StudioAPI::NodeStream &serializer) const override;
protected:
    void ProcessOffline() override;
    void ProcessOnline() override;
    int MessageUpdate(void* message);

    unsigned int NumberOfNodesInXml() const override;

    bool HandleXMLElement(XMLElementEx *pEx) override;
    void Main() override;

    virtual void ProtocolImplementation();

    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
    CDP::IO::Transport* m_transport{nullptr};

    OSAPIEvent m_event;
    std::atomic<double> m_lastUpdateTime{0};
    CDPConnector connVisionControllersContainer;
    char buffer[1024];
    std::string replaceSubcomponent(const std::string& input, const std::string& newSubcomponent);
};

} // namespace VideoWallLib

#endif
