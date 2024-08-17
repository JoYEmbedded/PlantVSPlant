#ifndef SCENE_H
#define SCENE_H
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include "camera.h"

class Scene
{


public:
    Scene();
    ~Scene();

    virtual void on_enter();    //初始化场景
    virtual void on_update(int delta);   //处理数据
    virtual void on_draw(QPainter* widget_painter, const Camera& camera);     //渲染绘图
    virtual void on_input();    //处理输入
    virtual void on_exit();     //退出场景
protected:
    Camera camera;

private:
    // virtual bool eventFilter(QObject* obj, QEvent* event);
};

#endif // SCENE_H
