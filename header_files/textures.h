
#ifndef textures_h
#define textures_h

#include "raylib.h"

class Textures
{
public:
    Texture2D background;
    Texture2D empty_square_texture;
    Texture2D lighten_square;
    Texture2D transparent_square;
    Texture2D disabled_square;
    Texture2D ship_texture;
    Texture2D player_ship_texture;
    Texture2D player_ship_texture_hit;

    Texture2D background_buttons;
    Texture2D play_button;
    Texture2D restart_button;
    Texture2D quit_button;

    Texture2D score_frame;
    Texture2D board_label;

    Texture2D sound_enabled_button;
    Texture2D sound_disabled_button;

    void loadTextures();
    void unloadTextures();

};

#endif // textures_h
