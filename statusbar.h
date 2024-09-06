#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QPoint>
#include <QImage>
#include <QPainter>
class StatusBar
{
public:
    StatusBar();

    void set_avatar(QImage* img);
    void set_position(int x, int y);
    void set_HP(int val);
    void set_MP(int val);
    void on_draw(QPainter* widget_painter);
private:
    int HP = 0;
    int MP = 0;
    QPoint position = {0, 0};
    QImage* img_avatar = nullptr;

    const int width = 275;

};

#endif // STATUSBAR_H
