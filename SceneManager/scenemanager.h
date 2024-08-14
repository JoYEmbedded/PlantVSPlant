#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"
#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include "timemanager.h"

extern Scene* menu_scene;       //此处思想很独特
extern Scene* game_scene;
extern Scene* choosing_scene;

namespace Ui {
class SceneManager;
}

class SceneManager : public QWidget
{
    Q_OBJECT

public:
    explicit SceneManager(QWidget *parent = nullptr);
    ~SceneManager();

    enum class SceneType
    {
        Menu,
        Choosing,
        Game
    };
    TimeManager time_manager;
    QPainter* painter;
    void set_current_scene(Scene* scene);
    void switch_to(SceneType);
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::SceneManager *ui;
    Scene* current_scene = nullptr;
    QTimer timer;


    bool eventFilter(QObject* obj, QEvent* event) override;
    void input_process();
    void update_logic();
};

#endif // SCENEMANAGER_H
