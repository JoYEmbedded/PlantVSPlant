#include "statusbar.h"

StatusBar::StatusBar() {}

void StatusBar::set_HP(int val)
{
    HP = val;
}

void StatusBar::set_MP(int val)
{
    MP = val;
}

void StatusBar::set_position(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

void StatusBar::set_avatar(QImage* img)
{
    img_avatar = img;
}
void StatusBar::on_draw(QPainter* widget_painter)
{
    widget_painter->drawImage(position, *img_avatar);
    QColor black(5,5,5);
    widget_painter->setPen(black);
    widget_painter->setBrush(black);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 10,  width + 3 * 2, 36, 8, 8);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 45, width + 3 * 2, 38, 8, 8);

    QColor gray(67,47,47);
    widget_painter->setBrush(gray);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 10, width + 3, 33, 8, 8);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 45, width + 3, 36, 8, 8);

    float hp_bar_width = width * std::max(0, HP) / 100.0f;
    float mp_bar_width = width * std::min(100, MP) / 100.0f;

    QColor red(191,61,67);
    widget_painter->setBrush(red);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 10, (int)hp_bar_width + 3, 33, 8, 8);

    QColor blue(83,131,195);
    widget_painter->setBrush(blue);
    widget_painter->drawRoundedRect(position.x() + 100, position.y() + 45, (int)mp_bar_width + 3, 33, 8, 8);



}
