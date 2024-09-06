#ifndef PARTICLE_H
#define PARTICLE_H
#include "QVector2D"
#include "graphics/atlas.h"
class Particle
{
public:
    Particle();
    ~Particle() = default;

private:
    int timer = 0;      //  粒子动画播放定时器
    int lifespan = 0;    //单帧粒子动画持续时长
    int idx_frame = 0;
    QVector2D position;
    bool valid = true;
    Atlas* atlas = nullptr;
};

#endif // PARTICLE_H
