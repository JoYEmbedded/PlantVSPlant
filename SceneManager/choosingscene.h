#ifndef CHOOSINGSCENE_H
#define CHOOSINGSCENE_H

#include "scene.h"
#include "scenemanager.h"
#include "./graphics/animation.h"
#include "MY_DEF.h"
extern QImage img_vs;
extern QImage img_1P;                                  //1P文本图片
extern QImage img_2P;                                  //2P文本图片
extern QImage img_1P_desc;                             //1P键位描述图片
extern QImage img_2P_desc;                             //2P键位描述图片
extern QImage img_gravestone_left;                     //朝向左的墓碑图片
extern QImage img_gravestone_right;
extern QImage img_selector_tip;                        //选角界面提示信息文本图片
extern QImage img_selector_background;                 //选角界面背景图
extern QImage img_1P_selector_btn_idle_left;           //1P向左选择按钮默认状态图片
extern QImage img_1P_selector_btn_idle_right;
extern QImage img_1P_selector_btn_down_left;           //1P向左选择按钮按下状态图片
extern QImage img_1P_selector_btn_down_right;
extern QImage img_2P_selector_btn_idle_left;           //2P向左选择按钮默认状态图片
extern QImage img_2P_selector_btn_idle_right;
extern QImage img_2P_selector_btn_down_left;           //2P向左选择按钮按下状态图片
extern QImage img_2P_selector_btn_down_right;
extern QImage img_peashooter_selector_background_left; //选角界面朝向左的豌豆射手背景图片
extern QImage img_peashooter_selector_background_right;
extern QImage img_sunflower_selector_background_left;  //选角界面朝向左的向日葵背景图片
extern QImage img_sunflower_selector_background_right;
extern Atlas atlas_peashooter_idle_left;               //豌豆射手朝向左的默认动画图集
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;

extern QMediaPlayer music_bgm_game;
extern QMediaPlayer music_ui_confirm;
extern QAudioOutput* music_audio_output;

extern SceneManager* scene_manager;
class ChoosingScene : public Scene
{
public:
    ChoosingScene();
    ~ChoosingScene();

    void on_enter();
    void on_update(int delta);
    void on_draw(QPainter* widget_painter, const Camera& camera);
    void on_input(QEvent* event);
    void on_exit();

private:
    enum class PlayerType
    {
        Peashooter = 0,
        Sunflower,
        Invalid
    };

    QPoint pos_img_VS = {0, 0};
    QPoint pos_img_tip = {0, 0};
    QPoint pos_img_1P = {0, 0};
    QPoint pos_img_2P = {0, 0};
    QPoint pos_img_1P_desc = {0, 0};
    QPoint pos_img_2P_desc = {0, 0};
    QPoint pos_img_1P_name = {0, 0};
    QPoint pos_img_2P_name = {0, 0};
    QPoint pos_animation_1P = {0, 0};
    QPoint pos_animation_2P = {0, 0};
    QPoint pos_img_1P_gravestone = {0, 0};
    QPoint pos_img_2P_gravestone = {0, 0};
    QPoint pos_1P_selector_btn_left = {0, 0};
    QPoint pos_2P_selector_btn_left = {0, 0};
    QPoint pos_1P_selector_btn_right = {0, 0};
    QPoint pos_2P_selector_btn_right = {0, 0};

    Animation animation_peashooter;
    Animation animation_sunflower;
    PlayerType player_type_1P = PlayerType::Peashooter;     //1P角色类型
    PlayerType player_type_2P = PlayerType::Sunflower;      //2P角色类型

    int choosing_background_scroll_offset_x = 0;

private:
    void outtextxy_shaded(int x, int y, QString string_line, QPainter* widget_painter);
};

#endif // CHOOSINGSCENE_H
