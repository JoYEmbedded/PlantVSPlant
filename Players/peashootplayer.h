#ifndef PEASHOOTPLAYER_H
#define PEASHOOTPLAYER_H
#include "player.h"

class PeashootPlayer : public Player
{
public:
    PeashootPlayer();
    ~PeashootPlayer();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input();

private:

};

#endif // PEASHOOTPLAYER_H
