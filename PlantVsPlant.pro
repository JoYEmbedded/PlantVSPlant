QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SceneManager/choosingscene.cpp \
    SceneManager/gamescene.cpp \
    SceneManager/menuscene.cpp \
    SceneManager/scene.cpp \
    SceneManager/scenemanager.cpp \
    animation.cpp \
    graphics/atlas.cpp \
    main.cpp \
    timemanager.cpp

HEADERS += \
    SceneManager/choosingscene.h \
    SceneManager/gamescene.h \
    SceneManager/menuscene.h \
    SceneManager/scene.h \
    SceneManager/scenemanager.h \
    animation.h \
    graphics/atlas.h \
    timemanager.h \
    util.h

FORMS += \
    scenemanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
