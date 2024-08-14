#include "atlas.h"

Atlas::Atlas() {}
Atlas::~Atlas() {}

void Atlas::load_from_file(QString path, int num)
{
    img_list.clear();
    img_list.resize(num);

    for (int i = 0; i < num; i++)
    {
        QString single_img_name = QString("%1%2").arg(path).arg(i+1);
        img_list[i].load(single_img_name);
    }
}

void Atlas::clear()
{
    img_list.clear();
}

int Atlas::get_size() const
{
    return (int)img_list.size();
}

QImage& Atlas::get_img(int index)
{
    if (index < 0 || index >= get_size())
    {
        throw std::out_of_range("index out of range");
    }
    return img_list[index];
}

void Atlas::add_img(const QImage& img)
{
    img_list.push_back(img);
}

void Atlas::flip_atlas()
{
    for (int i = 0; i < get_size(); i++)
    {
        QTransform flip_transform;
        flip_transform.scale(-1, 1);
        img_list[i] = img_list[i].transformed(flip_transform);
    }
}

