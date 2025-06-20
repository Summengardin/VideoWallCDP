CDPVERSION = 5.0

TYPE = library
PROJECTNAME = VideoWallLib

DEPS += \

HEADERS += \
    Camera.h \
    CameraPort.h \
    Layout.h \
    LayoutPort.h \
    MQTTHandler.h \
    MQTTTopic.h \
    OSD.h \
    OSDDataDistributor.h \
    OSDText.h \
    OSDPort.h \
    SourceOrchestrator.h \
    Tile.h \
    TilePort.h \
    uri.h \
    videowalllib.h \
    VideoWallLibBuilder.h

SOURCES += \
    Camera.cpp \
    CameraPort.cpp \
    Layout.cpp \
    LayoutPort.cpp \
    MQTTHandler.cpp \
    MQTTTopic.cpp \
    OSD.cpp \
    OSDDataDistributor.cpp \
    OSDText.cpp \
    OSDPort.cpp \
    SourceOrchestrator.cpp \
    Tile.cpp \
    TilePort.cpp \
    VideoWallLibBuilder.cpp \
    uri.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/VideoWallLib.Camera.MQTTTopic.xml \
    Templates/Models/VideoWallLib.Camera.xml \
    Templates/Models/VideoWallLib.CameraPort.xml \
    Templates/Models/VideoWallLib.Layout.xml \
    Templates/Models/VideoWallLib.LayoutPort.xml \
    Templates/Models/VideoWallLib.MQTTHandler.MQTTClient.xml \
    Templates/Models/VideoWallLib.MQTTHandler.xml \
    Templates/Models/VideoWallLib.MQTTTopic.xml \
    Templates/Models/VideoWallLib.OSD.OSDText.xml \
    Templates/Models/VideoWallLib.OSD.xml \
    Templates/Models/VideoWallLib.OSDDataDistributor.xml \
    Templates/Models/VideoWallLib.OSDText.xml \
    Templates/Models/VideoWallLib.OSDPort.xml \
    Templates/Models/VideoWallLib.PopulateComboBox_T.xml \
    Templates/Models/VideoWallLib.SourceOrchestrator.xml \
    Templates/Models/VideoWallLib.Tile.MQTTTopic.xml \
    Templates/Models/VideoWallLib.Tile.Models.MQTTTopic1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtBrightness1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtPanAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtPanSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtSource1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtTiltSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomAbs1.xml \
    Templates/Models/VideoWallLib.Tile.Models.mtZoomSpeed1.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextBC.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTL.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTL.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTR.xml \
    Templates/Models/VideoWallLib.Tile.xml \
    Templates/Models/VideoWallLib.TilePort.xml

load(cdp)