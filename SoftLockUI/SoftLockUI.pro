QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        fileobject.cpp \
        main.cpp \
        qcryptoadaptor.cpp

RESOURCES += qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../softcrypto/release/ -lsoftcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../softcrypto/debug/ -lsoftcrypto
else:unix: LIBS += -L$$OUT_PWD/../softcrypto/ -lsoftcrypto

INCLUDEPATH += $$PWD/../softcrypto
DEPENDPATH += $$PWD/../softcrypto
DISTFILES += \
    test

HEADERS += \
    fileobject.h \
    qcryptoadaptor.h
