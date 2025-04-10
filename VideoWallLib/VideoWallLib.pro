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
    OSD.h \
    OSDText.h \
    OSDPort.h \
    SourceOrchestrator.h \
    Tile.h \
    TilePort.h \
    videowalllib.h \
    VideoWallLibBuilder.h

SOURCES += \
    Camera.cpp \
    CameraPort.cpp \
    Layout.cpp \
    LayoutPort.cpp \
    MQTTHandler.cpp \
    OSD.cpp \
    OSDText.cpp \
    OSDPort.cpp \
    SourceOrchestrator.cpp \
    Tile.cpp \
    TilePort.cpp \
    VideoWallLibBuilder.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/VideoWallLib.Camera.xml \
    Templates/Models/VideoWallLib.CameraPort.xml \
    Templates/Models/VideoWallLib.Layout.xml \
    Templates/Models/VideoWallLib.LayoutPort.xml \
    Templates/Models/VideoWallLib.MQTTHandler.MQTTClient.xml \
    Templates/Models/VideoWallLib.MQTTHandler.xml \
    Templates/Models/VideoWallLib.OSD.OSDText.xml \
    Templates/Models/VideoWallLib.OSD.xml \
    Templates/Models/VideoWallLib.OSDText.xml \
    Templates/Models/VideoWallLib.OSDPort.xml \
    Templates/Models/VideoWallLib.SourceOrchestrator.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextBC.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTL.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTL.xml \
    Templates/Models/VideoWallLib.Tile.OSDTextTR.xml \
    Templates/Models/VideoWallLib.Tile.xml \
    Templates/Models/VideoWallLib.TilePort.xml

load(cdp)