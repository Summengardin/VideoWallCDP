TYPE = guiapplication
PROJECTNAME = VWGUI

DEPS += \

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

OTHER_FILES += \
    Application/mainwidget.ui \
    Application/qt.conf

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true)

load(cdp)

ID = 608813418082871587539167 # do not change

FORMS += \
    Application/camera.ui
