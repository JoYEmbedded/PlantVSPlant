#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QPainter>
#include "graphics/animation.h"
#include "player_id.h"
#include "platform.h"
#include "MY_DEF.h"
#include "Bullet/bullet.h"
#include "camera.h"
#include "graphics/particle.h"
#include "graphics/animation.h"

extern std::vector<Bullet*> bullet_list;
extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;
extern QImage img_1P_cursor;
extern QImage img_2P_cursor;

void sketch_img(const QImage& init_img, QImage& sketch_img);
class Player
{
public:
    Player(bool facing_right = true);
    ~Player();

    int HP = 100;
    int MP = 0;

    virtual void on_update(int delta, Camera& camera);
    virtual void on_draw(QPainter* widget_painter, const Camera& my_camera);
    virtual void on_input(QKeyEvent* event, KeyType key_type);
    void on_run(float distance);

    void set_id(PlayerID id);
    void set_position(int x, int y);
    QPoint get_position();
    QVector2D get_velocity();
    QVector2D get_shape();
    void set_velocity(QVector2D new_velocity);
    void make_invulnerable();

    int get_hp() const;
    int get_mp() const;
    virtual void on_attack();
    virtual void on_attack_ex();

    bool if_invulnerable();

    virtual void on_land();

    int last_hurt_direction;
protected:


    QPoint position;                //角色位置
    QVector2D velocity;
    QVector2D shape;                //角色形状尺寸

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;
    Animation animation_attack_ex_left;
    Animation animation_attack_ex_right;
    Animation animation_jump_effect;
    Animation animation_land_effect;


    Animation* current_animation = nullptr;     //当前正在播放的动画

    PlayerID id = PlayerID::P1;     //玩家序号ID

    bool is_move_left_btn_pressed = false;
    bool is_move_right_btn_pressed = false;
    bool is_shoot_btn_pressed = false;
    bool is_jump_btn_pressed = false;
    bool is_shoot_ex_btn_pressed = false;
    bool is_jump_effect_visible = false;
    bool is_land_effect_visible = false;
    bool is_die_animation_begin = false;
    QVector2D position_jump_effect;
    QVector2D position_land_effect;

    bool is_facing_right = true;        //角色是否朝向右侧

    int attack_cd = 500;
    bool can_attack = true;             //是否可以释放普通攻击
    Timer timer_attack_cd;              //普通攻击冷却定时器

    bool is_attacking_ex = false;       //是否正在释放特殊攻击

    bool is_invulnerable = false;           //角色是否处于无敌状态
    bool is_showing_sketch_frame = false;   //当前帧是否应该显示剪影
    Timer timer_invulnerable;               //无敌状态定时器
    Timer timer_invulnerable_blink;         //无敌状态闪烁定时器
    const float run_velocity = 0.55f;
    const float gravity = 1.6e-3f;
    const float jump_velocity = -0.65f;
    const int invulnerable_time = 750;
    QImage img_sketch;                      //动画帧剪影图片

    Timer timer_run_effect_generation;      //跑动特效粒子发射定时器
    Timer timer_die_effect_generation;      //死亡特效粒子发射定时器
    std::vector<Particle> particle_list;    //粒子对象

    virtual void on_jump();

    bool is_cursor_visible = true;
    Timer timer_cursor_visibility;

    /* 死亡动画控制 */



};

#endif // PLAYER_H
