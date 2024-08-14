#ifndef ATLAS_H
#define ATLAS_H
#include <vector>
#include <QImage>
#include <stdexcept>
class Atlas
{
public:
    Atlas();
    ~Atlas();

    void load_from_file(QString path, int num);
    void clear();

    int get_size() const;
    QImage& get_img(int index);
    void add_img(const QImage& img);
    void flip_atlas();


private:
    std::vector<QImage> img_list;

};

#endif // ATLAS_H
