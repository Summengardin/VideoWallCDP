TYPE = application
PROJECTNAME = VWController

DEPS += canopenio cdplogger cdpmodel mqttio mqtttestlib operationutilities sequencer videowalllib

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

OTHER_FILES += scripts/apply_ufw_rules.sh

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true)

load(cdp)

ID = 106385972147399 # do not change
