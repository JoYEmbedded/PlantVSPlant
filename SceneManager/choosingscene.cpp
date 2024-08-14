#include "choosingscene.h"

ChoosingScene::ChoosingScene(QPainter* widget_painter) : Scene(widget_painter)
{

}

ChoosingScene::~ChoosingScene() {}

void ChoosingScene::on_enter()
{
    qDebug("choosing enter");
}

void ChoosingScene::on_update(int delta)
{

}

void ChoosingScene::on_draw()
{

}

void ChoosingScene::on_input()
{

}

void ChoosingScene::on_exit()
{
    qDebug("choosing exit");
}
