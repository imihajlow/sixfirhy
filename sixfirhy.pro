QT += quick
CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        tagprovider.cpp \
        PlistCpp/src/pugixml.cpp PlistCpp/src/PList.cpp PlistCpp/src/PlistDate.cpp
HEADERS += tagprovider.h
INCLUDEPATH += "PlistCpp/include" "PlistCpp/src"
RESOURCES += qml.qrc

!macx {
    error("This is a macOs application")
}
