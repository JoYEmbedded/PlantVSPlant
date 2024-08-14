#ifndef SCENE_H
#define SCENE_H
#include <QDebug>
#include <QPainter>
class Scene
{


public:
    Scene(QPainter* widget_painter);
    ~Scene();

    virtual void on_enter();    //初始化场景
    virtual void on_update(int delta);   //处理数据
    virtual void on_draw();     //渲染绘图
    virtual void on_input();    //处理输入
    virtual void on_exit();     //退出场景


protected:
    QPainter* painter;
};

#endif // SCENE_H
