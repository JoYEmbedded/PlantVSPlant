#include "platform.h"

Platform::Platform() {}

Platform::~Platform(){}

void Platform::on_draw(QPainter* widget_painter, const Camera& camera)
{
    widget_painter->drawImage(QPoint(render_position.x(), render_position.y()), *img);
    if(is_debug)
    {
        QColor pen_color(3, 124, 214);
        QPen pen;
        pen.setColor(pen_color);
        pen.setWidth(5);
        widget_painter->setPen(pen);
        widget_painter->drawLine(QPoint(shape.left, shape.y), QPoint(shape.right, shape.y));
    }
}
