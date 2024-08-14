#include "scene.h"

Scene::Scene(QPainter* widget_painter) : painter(widget_painter)
{

}

Scene::~Scene()
{

}

void Scene::on_enter()
{
    qDebug("scene enter");

}

void Scene::on_update(int delta)
{
    qDebug("scene update");
}

void Scene::on_draw()
{
    qDebug("draw");
}

void Scene::on_input()
{
    qDebug("scene input");
}
void Scene::on_exit()
{
    qDebug("scene exit");
}
