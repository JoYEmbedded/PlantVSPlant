#include "musicplayer.h"


MusicPlayer::MusicPlayer(QString music_url_string)
{
    QUrl music_url = QUrl(music_url_string);
    music_ptr = new QMediaPlayer();
    music_audio_output = new QAudioOutput();
    music_ptr->setSource(music_url);
}

MusicPlayer::~MusicPlayer()
{
    delete music_audio_output;
    delete music_ptr;
}
void MusicPlayer::set_loop(bool flag)
{
    loop = flag;
    if(flag)
        music_ptr->setLoops(QMediaPlayer::Loops::Infinite);
}

bool MusicPlayer::if_end()
{
    return end;
}

void MusicPlayer::play()
{
    music_ptr->setAudioOutput(music_audio_output);
    music_ptr->setPosition(0);
    music_ptr->play();
}

void MusicPlayer::stop()
{
    music_ptr->stop();
}
