QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testcrypto.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../softcrypto/release/ -lsoftcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../softcrypto/debug/ -lsoftcrypto
else:unix: LIBS += -L$$OUT_PWD/../softcrypto/ -lsoftcrypto

INCLUDEPATH += $$PWD/../softcrypto
DEPENDPATH += $$PWD/../softcrypto
