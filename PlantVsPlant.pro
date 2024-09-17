QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bullet/bullet.cpp \
    Bullet/peabullet.cpp \
    Bullet/sunbullet.cpp \
    Bullet/sunbulletex.cpp \
    Players/peashootplayer.cpp \
    Players/player.cpp \
    Players/sunflowerplayer.cpp \
    SceneManager/choosingscene.cpp \
    SceneManager/gamescene.cpp \
    SceneManager/menuscene.cpp \
    SceneManager/scene.cpp \
    SceneManager/scenemanager.cpp \
    camera.cpp \
    graphics/animation.cpp \
    graphics/atlas.cpp \
    graphics/particle.cpp \
    main.cpp \
    musicplayer.cpp \
    platform.cpp \
    statusbar.cpp \
    timer.cpp

HEADERS += \
    Bullet/bullet.h \
    Bullet/peabullet.h \
    Bullet/sunbullet.h \
    Bullet/sunbulletex.h \
    MY_DEF.h \
    Players/peashootplayer.h \
    Players/player.h \
    Players/player_id.h \
    Players/sunflowerplayer.h \
    SceneManager/choosingscene.h \
    SceneManager/gamescene.h \
    SceneManager/menuscene.h \
    SceneManager/scene.h \
    SceneManager/scenemanager.h \
    camera.h \
    graphics/animation.h \
    graphics/atlas.h \
    graphics/particle.h \
    musicplayer.h \
    platform.h \
    statusbar.h \
    timer.h \
    util.h

FORMS += \
    scenemanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
