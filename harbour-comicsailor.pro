# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-comicsailor

CONFIG += sailfishapp

SOURCES += src/harbour-comicsailor.cpp \
    src/cs_curl.cpp \
    src/cs_json.cpp \
    src/comics.cpp \
    src/diesel.cpp \
    src/peebles.cpp \
    src/spiked.cpp \
    src/xkcd.cpp

OTHER_FILES += qml/harbour-comicsailor.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/harbour-comicsailor.changes.in \
    rpm/harbour-comicsailor.spec \
    rpm/harbour-comicsailor.yaml \
    harbour-comicsailor.desktop \
    qml/pages/About.qml \
    qml/pages/ComicModel.qml \
    qml/pages/ComicView.qml \
    qml/pages/InfoView.qml

# to disable building translations every time, comment out the
# following CONFIG line
# CONFIG += sailfishapp_i18n
# TRANSLATIONS += translations/comicsailor-de.ts

HEADERS += \
    src/common.h

unix:!macx: LIBS += -L$$PWD/../../../usr/lib/i386-linux-gnu/ -lcurl
