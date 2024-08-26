#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QPainter>
#include "graphics/animation.h"
#include "player_id.h"
#include "platform.h"
#include "MY_DEF.h"
class Player
{
public:
    Player();
    ~Player();

    int HP = 100;
    int MP = 100;

    virtual void on_update(int delta);
    virtual void on_draw(QPainter* widget_painter);
    virtual void on_input(QKeyEvent* event, KeyType key_type);
    void on_run(float distance);

    void set_id(PlayerID id);
    void set_position(int x, int y);
    QPoint get_position();
    QVector2D get_velocity();
    QVector2D get_shape();
    void set_velocity(QVector2D new_velocity);


protected:
    QPoint position;                //角色位置
    QVector2D velocity;
    QVector2D shape;                //角色形状尺寸

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;

    Animation* current_animation = nullptr;     //当前正在播放的动画

    PlayerID id = PlayerID::P1;     //玩家序号ID

    bool is_move_left_btn_pressed = false;
    bool is_move_right_btn_pressed = false;
    bool is_shoot_btn_pressed = false;
    bool is_jump_btn_pressed = false;
    bool is_shoot_ex_btn_pressed = false;

    bool is_facing_right = true;        //角色是否朝向右侧

    const float run_velocity = 0.55f;
    const float gravity = 1.6e-3f;
    const float jump_velocity = -0.85f;

    virtual void on_jump();

};

#endif // PLAYER_H
