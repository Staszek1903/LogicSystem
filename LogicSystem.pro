TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt


LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system


LIBS += -lentityx

SOURCES += main.cpp \
    containers/portnamescontainer.cpp \
    line.cpp \
    oopgui/textwindow.cpp \
    program.cpp \
    systems/rendersystem.cpp \
    systems/guisystem.cpp \
    mousehandler.cpp \
    creators/buttoncreator.cpp \
    creators/listcreator.cpp \
    creators/slidercreator.cpp \
    loaders/configparser.cpp \
    containers/drawcontainer.cpp \
    loaders/componentsloader.cpp \
    loaders/dirreader.cpp \
    systems/gatesguisystem.cpp \
    creators/circutcreator.cpp \
    containers/portscontainer.cpp \
    oopgui/configwindow.cpp \
    oopgui/bindbuttonwindow.cpp \
    systems/configwindowsystem.cpp \
    oopgui/button.cpp \
    systems/gatesprocessingsystem.cpp \
    loaders/gatesassembler.cpp \
    containers/memorycontainer.cpp \
    containers/namescontainer.cpp \
    oopgui/constwindow.cpp \
    loaders/savesloader.cpp \
    oopgui/ynwindow.cpp \
    oopgui/savewindow.cpp \
    oopgui/textinput.cpp \
    project_funcs.cpp \
    creators/configcreator.cpp \
    creators/wirecreator.cpp \
    oopgui/loadwindow.cpp \
    containers/projectdicontainer.cpp \
    frequencycontrol.cpp \
    oopgui/memorywindow.cpp \
    oopgui/scrollarea.cpp \
    oopgui/memorycontentgui.cpp \
    oopgui/bytegui.cpp \
    oopgui/fileselectwindow.cpp \
    oopgui/filelist.cpp \
    wireline.cpp

HEADERS += \
    components/partid.h \
    containers/portnamescontainer.h \
    line.h \
    oopgui/textwindow.h \
    program.h \
    systems/rendersystem.h \
    components/circcomponent.h \
    components/position.h \
    components/rectcomponent.h \
    components/text.h \
    components/mousebox.h \
    systems/guisystem.h \
    mousehandler.h \
    creators/buttoncreator.h \
    components/button.h \
    components/list.h \
    creators/listcreator.h \
    components/active.h \
    components/slider.h \
    creators/slidercreator.h \
    events/resizeevent.h \
    components/gui.h \
    components/screenresize.h \
    events/scrollevent.h \
    loaders/configparser.h \
    containers/drawcontainer.h \
    components/vertexarray.h \
    loaders/componentsloader.h \
    loaders/dirreader.h \
    events/buttonpushevent.h \
    systems/gatesguisystem.h \
    components/portarray.h \
    components/port.h \
    creators/circutcreator.h \
    containers/portscontainer.h \
    oopgui/configwindow.h \
    oopgui/bindbuttonwindow.h \
    components/configwindow.h \
    components/circuitbutton.h \
    containers/windowcreatecontainer.h \
    containers/containerscontainer.h \
    systems/configwindowsystem.h \
    events/configwindowcreateevent.h \
    oopgui/button.h \
    containers/additionalcontainer.h \
    events/keypushevent.h \
    components/line.h \
    components/led.h \
    systems/gatesprocessingsystem.h \
    components/wire.h \
    containers/instructioncontainer.h \
    loaders/gatesassembler.h \
    components/algorithm.h \
    containers/memorycontainer.h \
    components/memory.h \
    components/latch.h \
    components/probe.h \
    components/label.h \
    containers/namescontainer.h \
    components/constant.h \
    oopgui/constwindow.h \
    loaders/savesloader.h \
    components/yesnowindow.h \
    oopgui/ynwindow.h \
    oopgui/savewindow.h \
    oopgui/textinput.h \
    project_funcs.h \
    components/savedata.h \
    creators/configcreator.h \
    components/circuittypeindex.h \
    creators/wirecreator.h \
    components/loaddata.h \
    oopgui/loadwindow.h \
    containers/projectdicontainer.h \
    events/newdirevent.h \
    events/namechangeevent.h \
    components/selectarea.h \
    events/keyreleasedevent.h \
    components/disp7seg.h \
    frequencycontrol.h \
    components/startpoint.h \
    events/resetsequence.h \
    oopgui/memorywindow.h \
    oopgui/scrollarea.h \
    oopgui/memorycontentgui.h \
    events/mousescrollevent.h \
    oopgui/bytegui.h \
    oopgui/fileselectwindow.h \
    oopgui/filelist.h \
    vect.h \
    wireline.h
