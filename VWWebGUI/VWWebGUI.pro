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

ID = 221499101276363652754212 # do not change

FORMS += \
    Application/www/wasm/mainwidget.ui \
    Application/www/wasm/tile.ui \
    Application/www/wasm/ui/homepagewidget.ui \
    Application/www/wasm/ui/camerapagewidget.ui \
    Application/www/wasm/ui/tileconfigpagewidget.ui \
    Application/www/wasm/ui/tileconfiguratorpagewidget.ui \
    Application/www/wasm/ui/tilepagewidget.ui \
    Application/www/wasm/ui/elements/cameracontainer.ui \
    Application/www/wasm/ui/elements/menuwidget.ui \
    Application/www/wasm/ui/elements/camerapagewidget.ui \
    Application/www/wasm/ui/elements/osdcomboboxdialog.ui \
    Application/www/wasm/ui/elements/cameratable.ui \
    Application/www/wasm/ui/elements/osdcontainer.ui \
    Application/www/wasm/ui/elements/tilecontainer.ui \
    Application/www/wasm/ui/elements/cameracontainer.ui \
    Application/www/wasm/ui/elements/cameratable.ui \
    Application/www/wasm/ui/elements/tile.ui

RESOURCES += \
    resources.qrc
