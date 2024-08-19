#ifndef PLATFORM_H
#define PLATFORM_H
#include "camera.h"
#include <QPainter>

extern bool is_debug;

class Platform
{
public:
    Platform();
    ~Platform();

    struct CollisionShape
    {
        float y;
        float left, right;
    };

    CollisionShape shape;
    QImage* img = nullptr;
    QPoint render_position = {0, 0};

    void on_draw(QPainter* widget_painter, const Camera& camera);
};

#endif // PLATFORM_H
