#include "gamescene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene() {}

void GameScene::on_enter()
{
    qDebug("进入游戏局内场景");
    music_bgm_game.setAudioOutput(music_audio_output);
    music_bgm_game.play();

    pos_img_sky.setX((WINDOW_WIDTH - img_sky.width())/2);
    pos_img_sky.setY((WINDOW_HEIGHT - img_sky.height())/2);

    pos_img_hills.setX((WINDOW_WIDTH - img_hills.width())/2);
    pos_img_hills.setY((WINDOW_HEIGHT - img_hills.height())/2);

    platform_list.resize(4);

    Platform& large_platform = platform_list[0];
    large_platform.img = &img_platform_large;
    large_platform.render_position.setX(122);
    large_platform.render_position.setY(455);
    large_platform.shape.left = (float)large_platform.render_position.x() + 30;
    large_platform.shape.right = (float)large_platform.render_position.x() + large_platform.img->width() -30;
    large_platform.shape.y = (float)large_platform.render_position.y() + 60;

    Platform& small_platform_1 = platform_list[1];
    small_platform_1.img = &img_platform_small;
    small_platform_1.render_position.setX(175);
    small_platform_1.render_position.setY(360);
    small_platform_1.shape.left = (float)small_platform_1.render_position.x() + 40;
    small_platform_1.shape.right = (float)small_platform_1.render_position.x() + small_platform_1.img->width() - 40;
    small_platform_1.shape.y = (float)small_platform_1.render_position.y() + img_platform_small.height() / 2;

    Platform& small_platform_2 = platform_list[2];
    small_platform_2.img = &img_platform_small;
    small_platform_2.render_position.setX(855);
    small_platform_2.render_position.setY(360);
    small_platform_2.shape.left = (float)small_platform_2.render_position.x() + 40;
    small_platform_2.shape.right = (float)small_platform_2.render_position.x() + small_platform_2.img->width() - 40;
    small_platform_2.shape.y = (float)small_platform_2.render_position.y() + img_platform_small.height() / 2;

    Platform& small_platform_3 = platform_list[3];
    small_platform_3.img = &img_platform_small;
    small_platform_3.render_position.setX(515);
    small_platform_3.render_position.setY(225);
    small_platform_3.shape.left = (float)small_platform_3.render_position.x() + 40;
    small_platform_3.shape.right = (float)small_platform_3.render_position.x() + small_platform_3.img->width() - 40;
    small_platform_3.shape.y = (float)small_platform_3.render_position.y() + img_platform_small.height() / 2;
}

void GameScene::on_input(QKeyEvent* event, KeyType key_type)
{

}
void GameScene::on_update(int delta)
{
    qDebug("游戏正在运行...");
    player_1->on_update(delta);
    player_2->on_update(delta);
}

void GameScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    qDebug("游戏局内绘图内容");
    widget_painter->drawImage(pos_img_sky, img_sky);
    widget_painter->drawImage(pos_img_hills, img_hills);
    for(int i = 0; i < 4; i++)
    {
        platform_list[i].on_draw(widget_painter, camera);
    }

}

void GameScene::on_exit()
{
    qDebug("游戏局内退出");
}


