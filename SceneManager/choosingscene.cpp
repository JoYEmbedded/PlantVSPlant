#include "choosingscene.h"

ChoosingScene::ChoosingScene()
{

}

ChoosingScene::~ChoosingScene() {}

void ChoosingScene::on_enter()
{
    qDebug("choosing enter");
    animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
    animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
    animation_peashooter.set_interval(100);
    animation_sunflower.set_interval(100);

    static const int OFFSET_X = 50;
    pos_img_VS.setX((WINDOW_WIDTH - img_vs.width())/2);
    pos_img_VS.setY((WINDOW_HEIGHT - img_vs.height())/2);
    pos_img_tip.setX((WINDOW_WIDTH - img_selector_tip.width())/2);
    pos_img_tip.setY(WINDOW_HEIGHT - 125);
    pos_img_1P.setX((WINDOW_WIDTH / 2 - img_1P.width())/2 - OFFSET_X);
    pos_img_1P.setY(35);
    pos_img_2P.setX( WINDOW_WIDTH / 2+ (WINDOW_WIDTH / 2 - img_2P.width()) / 2 + OFFSET_X);
    pos_img_2P.setY(pos_img_1P.y());
    pos_img_1P_desc.setX( (WINDOW_WIDTH / 2 - img_1P_desc.width()) / 2 - OFFSET_X);
    pos_img_1P_desc.setY( WINDOW_HEIGHT - 150);
    pos_img_2P_desc.setX( WINDOW_WIDTH / 2 + ( WINDOW_WIDTH / 2 - img_2P_desc.width()) / 2 + OFFSET_X);

    pos_img_2P_desc.setY( pos_img_1P_desc.y() );

    pos_img_1P_gravestone.setX( (WINDOW_WIDTH / 2 - img_gravestone_right.width()) / 2 - OFFSET_X);

    pos_img_1P_gravestone.setY( pos_img_1P.y() + img_1P.height() + 35);

    pos_img_2P_gravestone.setX( WINDOW_WIDTH / 2 + ( WINDOW_WIDTH / 2 - img_gravestone_left.width()) / 2 + OFFSET_X);

    pos_img_2P_gravestone.setY( pos_img_1P_gravestone.y());

    pos_animation_1P.setX( (WINDOW_WIDTH / 2 - atlas_peashooter_idle_right.get_img(0).width()) / 2 - OFFSET_X);

    pos_animation_1P.setY( pos_img_1P_gravestone.y() + 80);

    pos_animation_2P.setX( WINDOW_WIDTH / 2 + ( WINDOW_WIDTH / 2 - atlas_peashooter_idle_right.get_img(0).width()) / 2 + OFFSET_X);

    pos_animation_2P.setY( pos_animation_1P.y());

    pos_img_1P_name.setY( pos_animation_1P.y() + 155 );

    pos_img_2P_name.setY( pos_img_1P_name.y());

    pos_1P_selector_btn_left.setX( pos_img_1P_gravestone.x() - img_1P_selector_btn_idle_left.width() );

    pos_1P_selector_btn_left.setY( pos_img_1P_gravestone.y() + (img_gravestone_right.height() - img_1P_selector_btn_idle_left.height()) / 2);

    pos_1P_selector_btn_right.setX( pos_img_1P_gravestone.x() + img_gravestone_right.width() );

    pos_1P_selector_btn_right.setY( pos_1P_selector_btn_left.y());

    pos_2P_selector_btn_left.setX( pos_img_2P_gravestone.x() - img_2P_selector_btn_idle_left.width());

    pos_2P_selector_btn_left.setY( pos_1P_selector_btn_left.y());

    pos_2P_selector_btn_right.setX( pos_img_2P_gravestone.x() + img_gravestone_left.width());

    pos_2P_selector_btn_right.setY( pos_1P_selector_btn_left.y());

}

void ChoosingScene::on_update(int delta)
{

}

void ChoosingScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    widget_painter->drawImage(QPoint(0,0), img_selector_background);
    widget_painter->drawImage(pos_img_1P, img_1P);
    widget_painter->drawImage(pos_img_2P, img_2P);
    widget_painter->drawImage(pos_img_1P_gravestone, img_gravestone_right);
    widget_painter->drawImage(pos_img_2P_gravestone, img_gravestone_left);

    widget_painter->drawImage(pos_img_1P_desc, img_1P_desc);
    widget_painter->drawImage(pos_img_2P_desc, img_2P_desc);
    widget_painter->drawImage(pos_img_tip, img_selector_tip);
    widget_painter->drawImage(pos_img_VS, img_vs);
}

void ChoosingScene::on_input()
{

}

void ChoosingScene::on_exit()
{
    qDebug("choosing exit");
    // music_ui_confirm.setAudioOutput(music_audio_output);
    // music_ui_confirm.play();
}

// bool ChoosingScene::eventFilter(QObject* obj, QEvent* event)
// {
//     if(event->type() == QEvent::KeyPress)
//     {
//         scene_manager->switch_to(SceneManager::SceneType::Game);
//         return true;
//     }
//     return false;
// }
