#ifndef UTIL_H
#define UTIL_H
#include <QImage>
#include "./graphics/atlas.h"

void flip_img(QImage& img_flipped, const QImage& img_to_flip)
{
    QTransform transformer;
    transformer.scale(-1,1);
    img_flipped = img_to_flip.transformed(transformer);
}

void flip_atlas(Atlas& atlas_flipped, Atlas& atlas_to_flip)
{
    QTransform transformer;
    transformer.scale(-1,1);
    int length = atlas_to_flip.get_size();
    for (int i = 0; i < length; i++)
    {
        QImage& temp_img = atlas_to_flip.get_img(i);
        atlas_flipped.add_img(temp_img);
    }
    atlas_flipped.flip_atlas();
}

#endif // UTIL_H
