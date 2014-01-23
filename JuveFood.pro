# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed

TARGET = JuveFood
CONFIG += sailfishapp
QT += network
INCLUDEPATH += src/

SOURCES += src/Juvefood.cpp \
    src/kitchen.cpp \
    src/foodAPI.cpp \
    src/helperFunctions.cpp \
    src/foodParser.cpp \
    src/httpEngine.cpp \
    src/settings.cpp

OTHER_FILES += qml/Juvefood.qml \
    qml/cover/CoverPage.qml \
    Juvefood.desktop \
    qml/pages/Settings.qml \
    qml/pages/MenuPage.qml \
    qml/pages/helper.js \
    rpm/Juvefood.spec \
    rpm/Juvefood.yaml \
    qml/pages/About.qml

HEADERS += \
    src/kitchen.h \
    src/foodAPI.h \
    src/helperFunctions.h \
    src/foodParser.h \
    src/httpEngine.h \
    src/settings.h


