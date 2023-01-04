
#include "../header_files/gamemusic.h"

bool GameMusic::sound_played = false;
bool GameMusic::end_sound_played = false;
float GameMusic::sound_volume = 1;

Sound GameMusic::ship_interaction_sound  = LoadSound("sounds/ship_interaction_sound.mp3");
Sound GameMusic::background_sound  = LoadSound("sounds/background_sound.mp3");
Sound GameMusic::game_start_sound = LoadSound("sounds/game_start_sound.mp3");
Sound GameMusic::win_sound = LoadSound("sounds/win_sound.mp3");
Sound GameMusic::lose_sound = LoadSound("sounds/lose_sound.mp3");
/**@brief
* Funkcja wlaczajaca muzyke
**/
void GameMusic::enableSound()
{
    if(sound_played == true)
        GameMusic::sound_played = false;
}
/**@brief
* Funkcja wylaczajaca muzyke
**/
void GameMusic::disableSound()
{
    if(sound_played == false)
        GameMusic::sound_played = true;
}
/**@brief
* Funkcja odtwarzajaca dzwiek
**/
void GameMusic::playPointedSound(Sound sound)
{
    if(sound_played == false)
        PlaySoundMulti(sound);
}
/**@brief
* Funkcja wylczajaca muzykê w menu glownym
**/
void GameMusic::playMainMusic(double &music_timer)
{
    //float sound_volume = 1;

    if(!IsSoundPlaying(GameMusic::background_sound) && SHOULD_MUSIC_PLAY == true)
    {
        PlaySound(GameMusic::background_sound);
    }

    float volume_change_time = 0.05;

    switch(GAMEMODE)
        {
        case BEGIN_MODE:
            if(GameMusic::sound_volume < 0.9){
                    music_timer += GetFrameTime();
                if(music_timer > volume_change_time){
                    GameMusic::sound_volume += 0.01;
                    music_timer = 0;
                }
            }
            SetSoundVolume(GameMusic::background_sound, GameMusic::sound_volume);
            break;
        case PLAY_MODE:
            if(GameMusic::sound_volume > 0.4){
                    music_timer += GetFrameTime();
                if(music_timer > volume_change_time){
                    GameMusic::sound_volume -= 0.01;
                    music_timer = 0;
                }
            }
            SetSoundVolume(GameMusic::background_sound, GameMusic::sound_volume);
            break;
        case DEBUG_MODE:
        default:
            SetSoundVolume(GameMusic::background_sound, 0);
            break;
        }
}

/**@brief
* Funkcja pauzujaca muzyke
**/
void GameMusic::pauseResumeSound(Sound sound)
{
    if(IsSoundPlaying(sound))
        PauseSound(sound);
    else
        ResumeSound(sound);
}



