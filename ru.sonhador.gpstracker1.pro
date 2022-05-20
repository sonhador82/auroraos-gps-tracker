################################################################################
##
## Copyright (C) 2022 Open Mobile Platform LLC.
## Contact: https://community.omprussia.ru/open-source
##
################################################################################

TARGET = ru.sonhador.gpstracker1

CONFIG += \
    sailfishapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \
    src/mytrack.cpp \
    src/notif.cpp \
    src/statecontroller.cpp

HEADERS += \
    src/mytrack.h \
    src/notif.h \
    src/statecontroller.h

DISTFILES += \
    rpm/ru.sonhador.gpstracker1.spec \
    rpm/ru.sonhador.gpstracker1.yaml \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += sailfishapp_i18n

TRANSLATIONS += \
    translations/ru.sonhador.gpstracker1.ts \
    translations/ru.sonhador.gpstracker1-ru.ts \

QT += positioning dbus

LIBS += -lmlite5 -no-pie -lgpx

