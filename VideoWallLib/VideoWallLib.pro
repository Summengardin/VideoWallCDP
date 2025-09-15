CDPVERSION = 5.0

TYPE = library
PROJECTNAME = VideoWallLib

DEPS += \

HEADERS += \
    Camera.h \
    CameraContainer.h \
    CameraPort.h \
    Layout.h \
    LayoutPort.h \
    MQTTHandler.h \
    MQTTTopic.h \
    OSDDataDistributor.h \
    OSDRectPort.h \
    SKAARHOJTCPCom.h \
    SourceOrchestrator.h \
    Tile.h \
    TilePort.h \
    VisionControllerContainer.h \
    base64.h \
    handControllerEasy.h \
    skhojhandcontroller.h \
    OSDTextPort.h \
    TimestampGenerator.h \
    iana_posix_map.h \
    uri.h \
    videowalllib.h \
    VideoWallLibBuilder.h

SOURCES += \
    Camera.cpp \
    CameraContainer.cpp \
    CameraPort.cpp \
    Layout.cpp \
    LayoutPort.cpp \
    MQTTHandler.cpp \
    MQTTTopic.cpp \
    OSDDataDistributor.cpp \
    OSDRectPort.cpp \
    SKAARHOJTCPCom.cpp \
    OSDTextPort.cpp \
    SourceOrchestrator.cpp \
    Tile.cpp \
    TilePort.cpp \
    TimestampGenerator.cpp \
    VideoWallLibBuilder.cpp \
    VisionControllerContainer.cpp \
    base64.cpp \
    handControllerEasy.cpp \
    skhojhandcontroller.cpp \
    uri.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/VideoWallLib.Camera.xml \
    Templates/Models/VideoWallLib.CameraContainer.xml \
    Templates/Models/VideoWallLib.CameraPort.xml \
    Templates/Models/VideoWallLib.Layout.xml \
    Templates/Models/VideoWallLib.LayoutPort.xml \
    Templates/Models/VideoWallLib.MQTTHandler.MQTTClient.xml \
    Templates/Models/VideoWallLib.MQTTHandler.xml \
    Templates/Models/VideoWallLib.MQTTTopic.xml \
    Templates/Models/VideoWallLib.OSD.OSDText.xml \
    Templates/Models/VideoWallLib.OSDDataDistributor.xml \
    Templates/Models/VideoWallLib.OSDRectPort.xml \
    Templates/Models/VideoWallLib.OSDTextPort.xml \
    Templates/Models/VideoWallLib.PopulateComboBox_T.xml \
    Templates/Models/VideoWallLib.SKAARHOJTCPCom.xml \
    Templates/Models/VideoWallLib.SourceOrchestrator.xml \
    Templates/Models/VideoWallLib.Tile.Models.MQTTTopic1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtBrightness1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtPanAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtPanSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtSource1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtTiltSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.xml \
    Templates/Models/VideoWallLib.TilePort.xml \
    Templates/Models/VideoWallLib.VisionControllerContainer.xml
    Templates/Models/VideoWallLib.TimestampGenerator.xml

load(cdp)