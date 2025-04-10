/**
VideoWallLibBuilder header file.
*/

#ifndef VIDEOWALLLIB_VIDEOWALLLIBBUILDER_H
#define VIDEOWALLLIB_VIDEOWALLLIBBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace VideoWallLib {

class VideoWallLibBuilder : public CDPBuilder
{
public:
    VideoWallLibBuilder(const char* libName);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
    CDPObject* CreateNewObject(const std::string& type) override;
    CDP::StudioAPI::CDPNode* CreateNewCDPNode(const std::string& type) override;
};

}

#endif
