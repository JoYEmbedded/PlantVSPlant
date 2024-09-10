#include "platform.h"

Platform::Platform() {}

Platform::~Platform(){}

void Platform::on_draw(QPainter* widget_painter, const Camera& camera)
{
    QVector2D pos_camera = camera.get_position();
    widget_painter->drawImage(QPoint(render_position.x() + pos_camera.x(), render_position.y() + pos_camera.y()), *img);
    if(is_debug)
    {
        QColor pen_color(3, 124, 214);
        QPen pen;
        pen.setColor(pen_color);
        pen.setWidth(5);
        widget_painter->setPen(pen);
        widget_painter->drawLine(QPoint(shape.left + pos_camera.x(), shape.y + pos_camera.y()), QPoint(shape.right + pos_camera.x(), shape.y + pos_camera.y()));
    }
}
