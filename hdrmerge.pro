TEMPLATE	= app
CONFIG		+= qt debug
QMAKE_CXXFLAGS_DEBUG	+= -O3
INCLUDEPATH	+= /usr/include/OpenEXR
LIBS		+= -ltiff -lpfs-1.2
HEADERS		+= Exposure.h
HEADERS		+= HdrMergeMainWindow.h
HEADERS		+= RenderThread.h
HEADERS		+= ImageControl.h
HEADERS		+= PreviewWidget.h
HEADERS		+= WhiteBalanceWidget.h
HEADERS		+= DraggableScrollArea.h
SOURCES		+= main.cpp
SOURCES		+= Exposure.cpp
SOURCES		+= HdrMergeMainWindow.cpp
SOURCES		+= RenderThread.cpp
SOURCES		+= ImageControl.cpp
SOURCES		+= PreviewWidget.cpp
SOURCES		+= WhiteBalanceWidget.cpp
SOURCES		+= DraggableScrollArea.cpp

TARGET = hdrmerge

