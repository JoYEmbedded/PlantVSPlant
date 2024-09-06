#include "peabullet.h"

PeaBullet::PeaBullet()
{
    size.setX(64);
    size.setY(64);
    damage = 10;
    animation_break.set_atlas(&atlas_pea_break);
    animation_break.set_interval(100);
    animation_break.set_loop(false);
    animation_break.set_callback([&](){can_be_removed = true;});
}

void PeaBullet::on_collide()
{
    Bullet::on_collide();
    switch (rand()%3) {
    case 0:
        music_pea_break_1->play();
        break;
    case 1:
        music_pea_break_2->play();
        break;
    case 2:
        music_pea_break_3->play();
        break;
    }
}

void PeaBullet::on_update(int delta)
{
    position += velocity * (float)delta;
    if(!valid)
    {
        animation_break.on_update(delta);
    }
    if(check_if_exceed_screen())
    {
        can_be_removed = true;
    }
}

void PeaBullet::on_draw(QPainter* widget_painter, const Camera& camera)
{
    if(valid)
    {
        widget_painter->drawImage(QPoint(position.x(), position.y()),img_pea);
    }
    else
    {
        animation_break.on_draw(position.x(), position.y(), widget_painter);
    }
}
