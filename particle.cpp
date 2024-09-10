#include "particle.h"

Particle::Particle() {}

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
