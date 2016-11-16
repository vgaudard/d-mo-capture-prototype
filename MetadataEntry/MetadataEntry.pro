QT       += core gui widgets

TARGET = MetadataEntry
TEMPLATE = app

defined(LEAP_SDK) {
}
else {
    LEAP_SDK = $$(HOME)/LeapDeveloperKit_v2/LeapSDK/
}

INCLUDEPATH += $$LEAP_SDK/include

QMAKE_CFLAGS +=  -std=c++11 -I$$LEAP_SDK/include
QMAKE_CXXFLAGS +=  -std=c++11 -I$$LEAP_SDK/include

OS = $$system(uname)
ARCH = $$system(uname -m)

equals (OS, Linux) {
    equals (ARCH, x86_64) {
        LIBS += "$$LEAP_SDK/lib/x64/libLeap.so"
        unix:QMAKE_RPATHDIR += "$$LEAP_SDK/lib/x64" 
    }
    else {
        LIBS += "$$LEAP_SDK/lib/x86/libLeap.so"
        unix:QMAKE_RPATHDIR += "$$LEAP_SDK/lib/x86" 
    }
}
else {
    # OS X
    LIBS += "$$LEAP_SDK/lib/libLeap.dylib"
}

SOURCES += main.cpp\
        mainwindow.cpp \
    metadatadialog.cpp \
    entry.cpp \
    entrylabel.cpp \
    ../dmo_prototype/PrototypeListener.cpp

HEADERS  += mainwindow.h \
    metadatadialog.h \
    entry.h \
    entrylabel.h \
    ../dmo_prototype/PrototypeListener.h

FORMS    += mainwindow.ui \
    metadatadialog.ui

compressTarget.target = compressGestures
compressTarget.commands = gzip -r gestures

decompressTarget.target = decompressGestures
decompressTarget.commands = gunzip -r gestures

QMAKE_EXTRA_TARGETS += compressTarget decompressTarget
