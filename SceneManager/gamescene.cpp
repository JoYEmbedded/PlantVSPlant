#include "gamescene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene() {}

void GameScene::on_enter()
{
    qDebug("进入游戏局内场景");
}

void GameScene::on_input()
{

}
void GameScene::on_update(int delta)
{
    qDebug("游戏正在运行...");
}

void GameScene::on_draw(QPainter* widget_painter)
{
    qDebug("游戏局内绘图内容");
}

void GameScene::on_exit()
{
    qDebug("游戏局内退出");
}
