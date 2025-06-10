TYPE = application
PROJECTNAME = VWWebGUI

DEPS += cdp_wasm

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true) \ 
    $$files(Application/images/*, true) 

load(cdp)

ID = 1676865642602372093446207 # do not change

FORMS += \
    Application/Application/cameracontainer.ui \
    Application/cameraweb.ui \
    Application/www/wasm/Application/camera.ui \
    Application/www/wasm/Application/menuwidget.ui \
    Application/www/wasm/elements/camera.ui \
    Application/www/wasm/mainwidget.ui \
    Application/www/wasm/tile.ui \
    Application/www/wasm/ui/Application/camerapagewidget.ui \
    Application/www/wasm/ui/camerapagewidget.ui \
    Application/www/wasm/ui/elements/Application/cameratable.ui \
    Application/www/wasm/ui/elements/Application/osdcontainer.ui \
    Application/www/wasm/ui/elements/Application/tilecontainer.ui \
    Application/www/wasm/ui/elements/OSDPopUp.ui \
    Application/www/wasm/ui/elements/cameracontainer.ui \
    Application/www/wasm/ui/elements/cameratable.ui \
    Application/www/wasm/ui/elements/tile.ui \
    Application/www/wasm/ui/homepagewidget.ui \
    Application/www/wasm/ui/tileconfigpagewidget.ui \
    Application/www/wasm/ui/tileconfiguratorpagewidget.ui \
    Application/www/wasm/ui/tilepagewidget.ui

RESOURCES += \
    resources.qrc
