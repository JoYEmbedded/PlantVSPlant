#include "scenemanager.h"
#include "ui_scenemanager.h"

SceneManager::SceneManager(QWidget *parent)
    : QWidget(parent)
    , painter(nullptr)
    , ui(new Ui::SceneManager)
{
    ui->setupUi(this);
    setFixedSize(1280,720);
    installEventFilter(this);
    time_manager.Init();
    connect(&timer,&QTimer::timeout,this, &SceneManager::update_logic);
    timer.setInterval(50);
    timer.start();

}

SceneManager::~SceneManager()
{
    delete ui;
}


void SceneManager::set_current_scene(Scene* scene)
{
    current_scene = scene;
    current_scene->on_enter();
}

void SceneManager::switch_to(SceneType scene_type)
{
    current_scene->on_exit();
    switch (scene_type) {
    case SceneType::Menu:
        current_scene = menu_scene;
        break;
    case SceneType::Choosing:
        current_scene = choosing_scene;
        break;
    case SceneType::Game:
        current_scene = game_scene;
        break;
    default:

        break;
    }
    current_scene->on_enter();
}

void SceneManager::input_process()
{

}

bool SceneManager::eventFilter(QObject* obj, QEvent* event)
{
    if(current_scene == menu_scene && event->type() == QEvent::KeyPress)
    {
        switch_to(SceneType::Choosing);
        return true;
    }
    else if(current_scene == choosing_scene)
    {
        return true;
    }
    QObject::eventFilter(obj, event);
    return false;
}


void SceneManager::update_logic()
{
    time_manager.UpdateTime();
    current_scene->on_update(time_manager.GetCurrentSecond());
    current_scene->on_draw();
    qDebug("update logic");
}

void SceneManager::paintEvent(QPaintEvent* event)
{

    painter = new QPainter(this);
    painter->drawPixmap(rect(),QPixmap(":/static/resources/1P.png"));
    painter->end();
}
