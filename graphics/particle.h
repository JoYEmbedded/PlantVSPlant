#ifndef PARTICLE_H
#define PARTICLE_H
#include "QVector2D"
#include "graphics/atlas.h"
#include "camera.h"
#include <QPainter>
class Particle
{
public:
    Particle();
    Particle(QVector2D position, Atlas* atlas, int lifespan);
    ~Particle() = default;

    void on_update(int delta, Camera& camera);
    void on_draw(QPainter* widget_paint, const Camera& camera) const;
    bool check_valid() const;

private:
    int timer = 0;      //  粒子动画播放定时器
    int lifespan = 0;    //单帧粒子动画持续时长
    int idx_frame = 0;
    QVector2D position;
    bool valid = true;
    Atlas* atlas = nullptr;

private:
    void set_atlas(Atlas* new_atlas);
    void set_position(const QVector2D& new_position);
    void set_lifespan(int ms);


};

#endif // PARTICLE_H
