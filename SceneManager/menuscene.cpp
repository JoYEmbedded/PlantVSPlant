#include "menuscene.h"

MenuScene::MenuScene()
{

}

void MenuScene::on_enter()
{
    qDebug("menu enter");
    animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
    animation_peashooter_run_right.set_interval(80);
    animation_peashooter_run_right.set_loop(true);
    // animation_peashooter_run_right.set_callback(
    //     []()
    //     {
    //         scene_manager->switch_to(SceneManager::SceneType::Game);
    //     }
    //     );

    timer.set_wait_time(1000);
    timer.set_one_shot(false);
    timer.set_callback(
        []()
        {
            qDebug("shot");
        });
    // qDebug("atlas init success");
    camera.shake(10,350);
    music_bgm_menu.setAudioOutput(music_audio_output);
    music_bgm_menu.play();

}



void MenuScene::on_update(int delta)
{
    // qDebug("menu update");
    animation_peashooter_run_right.on_update(delta);        //短期时间
    camera.on_update(delta);                                //短期时间
    timer.on_update(delta);                                 //短期时间
}

void MenuScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    // qDebug("menu draw");
    const QVector2D pos_camera = camera.get_position();
    animation_peashooter_run_right.on_draw((int)(100 - pos_camera.x()),(int)(100 - pos_camera.y()), widget_painter);
    widget_painter->drawImage(QPoint(0,0), img_menu_background);
}

void MenuScene::on_input()
{
    qDebug("menu input");
}
void MenuScene::on_exit()
{
    qDebug("menu exit");
    music_bgm_menu.stop();
    music_ui_confirm.setAudioOutput(music_audio_output);
    music_ui_confirm.play();
}

void MenuScene::paint(QPainter* widget_painter)
{
    // widget_painter->drawPixmap(QRect(100,200,300,400),QPixmap(":/static/resources/1P.png"));
    qDebug("begin animation draw");
    animation_peashooter_run_right.on_draw(100,200,widget_painter);

}
