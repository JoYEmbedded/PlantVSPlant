#ifndef ANIMATION_H
#define ANIMATION_H

#include "./graphics/atlas.h"
#include <QPainter>
#include "./SceneManager/scenemanager.h"
#include <QWidget>
#include <functional>

extern SceneManager* scene_manager;

class Animation
{
public:
    // Animation(QPainter* widget_painter);
    Animation();
    ~Animation();

    void set_interval(int ms);
    void reset();
    void set_loop(bool flag);
    void set_atlas(Atlas* new_atlas);
    int get_idx_frame();
    QImage& get_frame();
    bool check_finished();
    void on_update(int delta);
    void on_draw(int x, int y, QPainter* widget_painter);
    void set_callback(std::function<void()> callback);

private:
    int timer = 0;      //计时器
    int interval = 0;   //帧间隔
    int idx_frame = 0;  //帧索引
    bool is_loop = true;
    // QPainter* painter;
    Atlas* m_atlas;
    std::function<void()> callback;

};

#endif // ANIMATION_H
