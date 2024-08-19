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

    pos_img_1P_name.setX( pos_animation_1P.x());

    pos_img_1P_name.setY( pos_animation_1P.y() + 155 );

    pos_img_2P_name.setX( pos_animation_2P.x());

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
    animation_peashooter.on_update(delta);
    animation_sunflower.on_update(delta);
    choosing_background_scroll_offset_x += 5;
    if (choosing_background_scroll_offset_x >= img_peashooter_selector_background_left.width())
    {
        choosing_background_scroll_offset_x = 0;
    }
}

void ChoosingScene::on_draw(QPainter* widget_painter, const Camera& camera)
{
    QImage* img_p1_selector_background_shade = nullptr;
    QImage* img_p2_selector_background_shade = nullptr;

    widget_painter->drawImage(QPoint(0,0), img_selector_background);

    switch (player_type_1P) {
    case PlayerType::Peashooter:
        img_p2_selector_background_shade = &img_peashooter_selector_background_left;
        break;
    case PlayerType::Sunflower:
        img_p2_selector_background_shade = &img_sunflower_selector_background_left;
        break;
    default:
        break;
    }

    switch (player_type_2P) {
    case PlayerType::Peashooter:
        img_p1_selector_background_shade = &img_peashooter_selector_background_right;
        break;
    case PlayerType::Sunflower:
        img_p1_selector_background_shade = &img_sunflower_selector_background_right;
        break;
    default:
        break;
    }

    //绘制动态背景
    QImage cropped_img_p1_right = img_p1_selector_background_shade->copy(0, 0, img_p1_selector_background_shade->width() - choosing_background_scroll_offset_x, img_p1_selector_background_shade->height());
    QImage cropped_img_p1_left = img_p1_selector_background_shade->copy(0, 0, img_p1_selector_background_shade->width(), img_p1_selector_background_shade->height());
    widget_painter->drawImage(QPoint(choosing_background_scroll_offset_x,0), cropped_img_p1_right);
    widget_painter->drawImage(QPoint(choosing_background_scroll_offset_x - img_p1_selector_background_shade->width(),0), cropped_img_p1_left);
    QImage cropped_img_p2_left = img_p2_selector_background_shade->copy(choosing_background_scroll_offset_x,0,img_p2_selector_background_shade->width(),img_p2_selector_background_shade->height());
    QImage cropped_img_p2_right = img_p2_selector_background_shade->copy(0,0,img_p2_selector_background_shade->width(),img_p2_selector_background_shade->height());
    widget_painter->drawImage(QPoint(WINDOW_WIDTH - img_p2_selector_background_shade->width(),0),cropped_img_p2_left);
    widget_painter->drawImage(QPoint(WINDOW_WIDTH - choosing_background_scroll_offset_x,0),cropped_img_p2_right);

    widget_painter->drawImage(pos_img_1P, img_1P);
    widget_painter->drawImage(pos_img_2P, img_2P);
    widget_painter->drawImage(pos_img_1P_gravestone, img_gravestone_right);
    widget_painter->drawImage(pos_img_2P_gravestone, img_gravestone_left);

    widget_painter->drawImage(pos_img_1P_desc, img_1P_desc);
    widget_painter->drawImage(pos_img_2P_desc, img_2P_desc);
    widget_painter->drawImage(pos_img_tip, img_selector_tip);
    widget_painter->drawImage(pos_img_VS, img_vs);

    if(A_Pressed)
    {
        widget_painter->drawImage(pos_1P_selector_btn_left, img_1P_selector_btn_down_left);
    }
    else
    {
        widget_painter->drawImage(pos_1P_selector_btn_left, img_1P_selector_btn_idle_left);
    }
    if(D_Pressed)
    {
        widget_painter->drawImage(pos_1P_selector_btn_right, img_1P_selector_btn_down_right);
    }
    else
    {
        widget_painter->drawImage(pos_1P_selector_btn_right, img_1P_selector_btn_idle_right);
    }
    if(LeftArrow_Pressed)
    {
        widget_painter->drawImage(pos_2P_selector_btn_left, img_2P_selector_btn_down_left);
    }
    else
    {
        widget_painter->drawImage(pos_2P_selector_btn_left, img_2P_selector_btn_idle_left);
    }
    if(RightArrow_Pressed)
    {
        widget_painter->drawImage(pos_2P_selector_btn_right, img_2P_selector_btn_down_right);
    }
    else
    {
        widget_painter->drawImage(pos_2P_selector_btn_right, img_2P_selector_btn_idle_right);
    }

    switch (player_type_1P) {
    case PlayerType::Peashooter:
        animation_peashooter.on_draw(pos_animation_1P.x(), pos_animation_1P.y(), widget_painter);
        outtextxy_shaded(pos_img_1P_name.x(), pos_img_1P_name.y(), "豌豆射手", widget_painter);
        break;
    case PlayerType::Sunflower:
        animation_sunflower.on_draw(pos_animation_1P.x(), pos_animation_1P.y(), widget_painter);
        outtextxy_shaded(pos_img_1P_name.x(), pos_img_1P_name.y(), "向日葵", widget_painter);
    default:
        break;
    }

    switch (player_type_2P) {
    case PlayerType::Peashooter:
        animation_peashooter.on_draw(pos_animation_2P.x(), pos_animation_2P.y(), widget_painter);
        outtextxy_shaded(pos_img_2P_name.x(), pos_img_2P_name.y(), "豌豆射手", widget_painter);

        break;
    case PlayerType::Sunflower:
        animation_sunflower.on_draw(pos_animation_2P.x(), pos_animation_2P.y(), widget_painter);
        outtextxy_shaded(pos_img_2P_name.x(), pos_img_2P_name.y(), "向日葵", widget_painter);
    default:
        break;
    }
}

void ChoosingScene::on_input(QKeyEvent* event, KeyType key_type)
{
    if(key_type == KeyType::Press)
    {
        switch (event->key()) {
        case Qt::Key_A:
            A_Pressed = true;
            break;
        case Qt::Key_D:
            D_Pressed = true;
            break;
        case Qt::Key_Left:
            LeftArrow_Pressed = true;
            break;
        case Qt::Key_Right:
            RightArrow_Pressed = true;
            break;
        case Qt::Key_Enter:
            scene_manager->switch_to(SceneManager::SceneType::Game);
            break;
        default:
            break;
        }
    }

    if(key_type == KeyType::release)
    {
        switch (event->key()) {
        case Qt::Key_A:
            player_type_1P = PlayerType( ((int)player_type_1P - 1 + (int)PlayerType::Invalid)% (int)PlayerType::Invalid);
            A_Pressed = false;
            music_ui_switch.setAudioOutput(music_audio_output);
            music_ui_switch.setPosition(0);
            music_ui_switch.play();
            break;
        case Qt::Key_D:
            player_type_1P = PlayerType( ((int)player_type_1P + 1 + (int)PlayerType::Invalid)% (int)PlayerType::Invalid);
            D_Pressed = false;
            music_ui_switch.setAudioOutput(music_audio_output);
            music_ui_switch.setPosition(0);
            music_ui_switch.play();
            break;
        case Qt::Key_Left:
            player_type_2P = PlayerType( ((int)player_type_2P - 1 + (int)PlayerType::Invalid)% (int)PlayerType::Invalid);
            LeftArrow_Pressed = false;
            music_ui_switch.setAudioOutput(music_audio_output);
            music_ui_switch.setPosition(0);
            music_ui_switch.play();
            break;
        case Qt::Key_Right:
            player_type_2P = PlayerType( ((int)player_type_2P + 1 + (int)PlayerType::Invalid)% (int)PlayerType::Invalid);
            RightArrow_Pressed = false;
            music_ui_switch.setAudioOutput(music_audio_output);
            music_ui_switch.setPosition(0);
            music_ui_switch.play();
            break;
        case Qt::Key_Return:
            scene_manager->switch_to(SceneManager::SceneType::Game);
            break;
        case Qt::Key_Enter:
            scene_manager->switch_to(SceneManager::SceneType::Game);
            break;
        default:
            break;
        }
    }
}

void ChoosingScene::on_exit()
{
    // qDebug("choosing exit");

    switch (player_type_1P) {
    case PlayerType::Peashooter:
        player_1 = new PeashootPlayer();
        break;
    case PlayerType::Sunflower:
        player_1 = new SunflowerPlayer();
    default:
        break;
    }

    switch (player_type_2P) {
    case PlayerType::Peashooter:
        player_2 = new PeashootPlayer();
        break;
    case PlayerType::Sunflower:
        player_2 = new SunflowerPlayer();
    default:
        break;
    }

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

void ChoosingScene::outtextxy_shaded(int x, int y, QString string_line, QPainter* widget_painter)
{
    QFont font;
    font.setPointSize(24);
    font.setFamily("IPIX");
    widget_painter->setFont(font);
    QColor color(45, 45, 45);
    widget_painter->setPen(color);
    widget_painter->drawText(x+3, y+3, string_line);
    color.setRgb(255, 255, 255);
    widget_painter->setPen(color);

    widget_painter->drawText(x,y, string_line);
}
