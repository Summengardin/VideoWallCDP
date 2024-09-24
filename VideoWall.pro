CDPVERSION = 4.13
TYPE = system
load(cdp)

DISTFILES += $$files(*.xml, false)

SUBDIRS +=     VWController \
    VWGUI \
    VWWebGUI
