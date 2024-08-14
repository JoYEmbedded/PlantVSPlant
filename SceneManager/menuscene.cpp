#include "menuscene.h"

MenuScene::MenuScene(QPainter* widget_painter) : Scene(widget_painter), animation_peashooter_run_right(widget_painter)
{

}

void MenuScene::on_enter()
{
    qDebug("menu enter");
    animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
    animation_peashooter_run_right.set_interval(75);
    animation_peashooter_run_right.set_loop(true);

}

bool MenuScene::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        scene_manager->switch_to(SceneManager::SceneType::Menu);
        return true;
    }
    return false;
}

void MenuScene::on_update(int delta)
{
    qDebug("menu update");
    animation_peashooter_run_right.on_update(delta);
}

void MenuScene::on_draw()
{
    qDebug("menu draw");
    animation_peashooter_run_right.on_draw(100,100);

}

void MenuScene::on_input()
{
    qDebug("menu input");
}
void MenuScene::on_exit()
{
    qDebug("menu exit");
}
