
#ifndef gamemusic_h
#define gamemusic_h

#include "raylib.h"
#include "engine.h"

class GameMusic
{
public:
    static bool sound_played;
    static bool end_sound_played;
    static float sound_volume;

    static void enableSound();
    static void disableSound();
    static void playPointedSound(Sound sound);
    static void playMainMusic(double &music_timer);
    static void pauseResumeSound(Sound sound);

    static Sound ship_interaction_sound;
    static Sound background_sound;
    static Sound game_start_sound;
    static Sound win_sound;
    static Sound lose_sound;
};

#endif // gamemusic_h
