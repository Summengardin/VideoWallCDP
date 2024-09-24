TYPE = application
PROJECTNAME = VWWebGUI

DEPS += cdp_wasm

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true)

load(cdp)

ID = 1676865642602372093446207 # do not change

FORMS += \
    Application/cameraweb.ui
