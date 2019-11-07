QT += quick
CONFIG += c++17

ICON = sixfirhy.icns

QMAKE_INFO_PLIST = Info.plist

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        tagprovider.cpp \
        PlistCpp/src/pugixml.cpp PlistCpp/src/PList.cpp PlistCpp/src/PlistDate.cpp \
    argsprovider.cpp \
    macapplication.cpp
HEADERS += tagprovider.h \
    argsprovider.h \
    macapplication.h
INCLUDEPATH += "PlistCpp/include" "PlistCpp/src"
RESOURCES += qml.qrc

!macx {
    error("This is a macOs application")
}
