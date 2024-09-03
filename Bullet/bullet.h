#ifndef BULLET_H
#define BULLET_H
#include <QVector2D>
#include <functional>
#include <QPainter>
#include "camera.h"
#include "Players/player_id.h"
#include "MY_DEF.h"

class Bullet
{
public:
    Bullet();
    ~Bullet();

    void set_damage(int new_damage);
    int get_damage() const;
    void set_position(float x, float y);
    const QVector2D& get_position() const;
    void set_size(float width, float height);
    const QVector2D& get_size();
    void set_velocity(float x, float y);
    void set_collide_target(PlayerID player_id);
    PlayerID get_collide_target() const;
    void set_callback(std::function<void()> callback);
    void set_valid(bool flag);
    bool get_valid() const;
    bool check_can_remove() const;
    virtual void on_collide();
    virtual bool check_collision(const QVector2D& other_position, const QVector2D& other_size);
    virtual void on_update(int delta);
    virtual void on_draw(QPainter* widget_painter, const Camera& camera);
protected:
    QVector2D size;                     //子弹尺寸
    QVector2D position;                 //子弹位置
    QVector2D velocity;                 //子弹速度
    int damage = 10;                    //子弹伤害
    bool valid = true;                  //子弹是否有效
    bool can_be_removed = false;        //子弹是否可以被移除
    std::function<void()> callback;
    PlayerID target_ID = PlayerID::P1;  //子弹目标玩家

    bool check_if_exceed_screen();
};

#endif // BULLET_H
