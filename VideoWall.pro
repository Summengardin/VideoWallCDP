CDPVERSION = 5.0
TYPE = system
load(cdp)

DISTFILES += $$files(*.xml, false)

SUBDIRS +=     VWController \
    VWGUI \
    VWWebGUI
