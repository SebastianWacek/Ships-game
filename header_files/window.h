#ifndef window_h
#define window_h

#include "raylib.h"
#include <cmath>
#include "textures.h"
#include "gamemusic.h"
#include "engine.h"

class Window
{
public:
    double windowWidth, windowHeight;
    double scale;
    bool window_should_be_closed;
    //Texture2D background;

    Rectangle menu_background_rec, play_button_rec, restart_button_rec, quit_button_rec, sound_button_rec;

    Window();
    Window(double width, double height);

    void drawBackground(Textures game_textures);

    void initiateMenu();
    void drawMenu(Textures game_textures);
    void playOnButtonsSound();
    void drawPlayButton(Textures game_textures);
    void drawRestartButton(Textures game_textures);
    void drawQuitButton(Textures game_textures);
    void drawSoundButton(Textures game_textures);


};

#endif // window_h

