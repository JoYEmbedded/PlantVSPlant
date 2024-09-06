#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QMediaPlayer>
#include "qaudiooutput.h"
class MusicPlayer
{
public:
    MusicPlayer(QString music_url_string);
    ~MusicPlayer();

    void play();
    void stop();
    void set_loop(bool flag);

protected:
    QMediaPlayer* music_ptr;
    QAudioOutput* music_audio_output;


    bool end = false;
    bool loop = false;

protected:

    bool if_end();
};

#endif // MUSICPLAYER_H
