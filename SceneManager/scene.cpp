#include "scene.h"

Scene::Scene()
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

void Scene::on_draw(QPainter* widget_painter)
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


