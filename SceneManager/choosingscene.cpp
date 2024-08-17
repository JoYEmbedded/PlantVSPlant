#include "choosingscene.h"

ChoosingScene::ChoosingScene()
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

void ChoosingScene::on_draw(QPainter* widget_painter, const Camera& camera)
{

}

void ChoosingScene::on_input()
{

}

void ChoosingScene::on_exit()
{
    qDebug("choosing exit");
}

// bool ChoosingScene::eventFilter(QObject* obj, QEvent* event)
// {
//     if(event->type() == QEvent::KeyPress)
//     {
//         scene_manager->switch_to(SceneManager::SceneType::Game);
//         return true;
//     }
//     return false;
// }
