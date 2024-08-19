#include "scenemanager.h"
#include "ui_scenemanager.h"

SceneManager::SceneManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SceneManager)
{
    ui->setupUi(this);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // installEventFilter(this);
    timer.setInterval(20);
    connect(&timer,&QTimer::timeout,this, &SceneManager::update_logic);
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

// bool SceneManager::eventFilter(QObject* obj, QEvent* event)
// {
//     if(current_scene == menu_scene && event->type() == QEvent::KeyRelease)
//     {
//         switch_to(SceneType::Choosing);
//         return true;
//     }
//     if(current_scene == choosing_scene && event->type() == QEvent::KeyRelease)
//     {
//         current_scene->on_input(event);
//         // switch_to(SceneType::Game);
//         return true;
//     }
//     if(current_scene == game_scene && event->type() == QEvent::KeyRelease)
//     {
//         switch_to(SceneType::Menu);
//         return true;
//     }
//     QObject::eventFilter(obj, event);
//     return false;
// }

void SceneManager::keyReleaseEvent(QKeyEvent* event)
{
    if(current_scene == menu_scene )
    {
        switch_to(SceneType::Choosing);
    }
    if(current_scene == choosing_scene)
    {
        current_scene->on_input(event, Scene::KeyType::release);
        // switch_to(SceneType::Game);
    }
    if(current_scene == game_scene)
    {
        current_scene->on_input(event, Scene::KeyType::release);
        // switch_to(SceneType::Menu);

    }

}

void SceneManager::keyPressEvent(QKeyEvent* event)
{
    // if(current_scene == menu_scene )
    // {
    //     switch_to(SceneType::Choosing);
    // }
    if(current_scene == choosing_scene)
    {
        current_scene->on_input(event, Scene::KeyType::Press);
        // switch_to(SceneType::Game);
    }
    if(current_scene == game_scene)
    {
        current_scene->on_input(event, Scene::KeyType::Press);
    }

}

void SceneManager::update_logic()
{
    current_scene->on_update(timer.interval());      //长期时间
    // current_scene->on_draw(painter);
    this->repaint();
    // qDebug("update logic");
}

void SceneManager::paintEvent(QPaintEvent* event)
{

    QPainter my_painter(this);
    my_painter.begin(this);
    current_scene->on_draw(&my_painter, main_camera);

    // my_painter.drawPixmap(rect(),QPixmap(":/static/resources/1P.png"));
    my_painter.end();
}
