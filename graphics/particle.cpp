#include "particle.h"

Particle::Particle() {}

Particle::Particle(QVector2D new_position, Atlas* new_atlas, int new_lifespan) : position(new_position), atlas(new_atlas), lifespan(new_lifespan)
{

}
void Particle::set_atlas(Atlas* new_atlas)
{
    atlas = new_atlas;
}

void Particle::set_position(const QVector2D& new_position)
{
    position.setX(new_position.x());
    position.setY(new_position.y());
}

void Particle::set_lifespan(int ms)
{
    lifespan = ms;
}

bool Particle::check_valid() const
{
    return valid;
}

void Particle::on_update(int delta, Camera& camera)
{
    timer += delta;
    if (timer >= lifespan)
    {
        timer = 0;
        idx_frame ++;
        if (idx_frame >= atlas->get_size())
        {
            idx_frame = atlas->get_size() - 1;
            valid = false;
        }
    }
}

void Particle::on_draw(QPainter* widget_painter, const Camera& camera) const
{
    widget_painter->drawImage(QPoint(position.x(), position.y()), atlas->get_img(idx_frame));
}
