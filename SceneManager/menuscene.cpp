#include "menuscene.h"

MenuScene::MenuScene()
{

}

void MenuScene::on_enter()
{
    qDebug("menu enter");
    animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
    animation_peashooter_run_right.set_interval(40);
    animation_peashooter_run_right.set_loop(true);
    qDebug("atlas init success");

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

void MenuScene::on_draw(QPainter* widget_painter)
{
    qDebug("menu draw");
    animation_peashooter_run_right.on_draw(100,100, widget_painter);
}

void MenuScene::on_input()
{
    qDebug("menu input");
}
void MenuScene::on_exit()
{
    qDebug("menu exit");
}

void MenuScene::paint(QPainter* widget_painter)
{
    // widget_painter->drawPixmap(QRect(100,200,300,400),QPixmap(":/static/resources/1P.png"));
    qDebug("begin animation draw");
    animation_peashooter_run_right.on_draw(100,200,widget_painter);

}
