#include "animation.h"

// Animation::Animation(QPainter* widget_painter)
// {
//     painter = widget_painter;
// }

Animation::Animation()
{
    // painter = nullptr;
    timer = 0;
    idx_frame = 0;
}

Animation::~Animation()
{}

void Animation::reset()
{
    timer = 0;
    idx_frame = 0;
}

void Animation::set_atlas(Atlas* new_atlas)
{
    reset();
    m_atlas = new_atlas;
}

void Animation::set_loop(bool flag)
{
    is_loop = flag;
}

void Animation::set_interval(int ms)
{
    interval = ms;
}

int Animation::get_idx_frame()
{
    return idx_frame;
}

QImage& Animation::get_frame()
{
    return m_atlas->get_img(idx_frame);
}

bool Animation::check_finished()
{
    if(is_loop == true)
    {
        return false;
    }
    return (idx_frame == m_atlas->get_size() - 1);
}

void Animation::on_update(int delta)
{
    timer += delta;
    if (timer >= interval)
    {
        timer = timer - interval;
        idx_frame ++;
        if (idx_frame >= m_atlas->get_size())
        {
            idx_frame = is_loop ? 0 : (m_atlas->get_size()-1);
            if(!is_loop && callback)
            {
                callback();
            }
        }
    }
}

void Animation::on_draw(int x, int y, QPainter* widget_painter)
{

    // widget_painter->drawPixmap(QRect(500,200,300,400),QPixmap(":/static/resources/1P.png"));             //可画图
    widget_painter->drawImage(x,y, m_atlas->get_img(idx_frame));
}

void Animation::set_callback(std::function<void()> callback)
{
    this->callback = callback;
}

