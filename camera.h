#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include "timer.h"

class Camera
{
public:
    Camera();
    const QVector2D get_position() const;
    void set_position(QVector2D new_position);
    void reset();
    void on_update(int delta);
    void shake(float strength, int duration);

private:


    QVector2D m_position;               //摄像机位置
    Timer timer_shake;                  //摄像机抖动定时器
    bool is_shaking = false;            //摄像机是否在抖动
    float shaking_strength = 0;         //摄像机抖动幅度
};

#endif // CAMERA_H
