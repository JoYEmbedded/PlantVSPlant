#ifndef PEASHOOTPLAYER_H
#define PEASHOOTPLAYER_H
#include "player.h"

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;

class PeashootPlayer : public Player
{
public:
    PeashootPlayer();
    ~PeashootPlayer();

    void on_update(int delta);
    void on_draw(QPainter* widget_painter);
    void on_input(QKeyEvent* event, KeyType key_type);

private:

};

#endif // PEASHOOTPLAYER_H
