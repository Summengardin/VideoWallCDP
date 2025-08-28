#ifndef VIDEOWALLLIB_VISIONCONTROLLER_H
#define VIDEOWALLLIB_VISIONCONTROLLER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

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
    int MessageTileMessageHandler(void* message);
    int MessagePublish(void* message);
    int MessageHandController(void* message);
    int MessageMessageHandler(void* message);
    std::vector<std::string> tiles; // assumes all CDP components are tiles
    CDPSignal<int> numTiles;
    std::vector<std::unique_ptr<CDPConnector>> TileConnectors;

protected:
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace VideoWallLib

#endif
