CONFIG -= qt

TEMPLATE = lib
DEFINES += SOFTCRYPTO_LIBRARY

CONFIG += c++11

SOURCES += \
    softcrypto.cpp

HEADERS += \
    softcrypto_global.h \
    softcrypto.h
    LIBS += -lssl \
            -lcrypto
# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
