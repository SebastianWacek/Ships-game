
#include "../header_files/textures.h"
/**@brief
* Funkcja odpowiadajaca za pojawienie sie tekstur
**/
void Textures::loadTextures()
{
    background = LoadTexture("img/background.png");
    empty_square_texture = LoadTexture("img/square.png");
    lighten_square = LoadTexture("img/lighten_square.png");
    transparent_square = LoadTexture("img/transparent_square.png");
    disabled_square = LoadTexture("img/disabled_square.png");
    ship_texture = LoadTexture("img/ship.png");
    player_ship_texture = LoadTexture("img/player_ship_square.png");
    player_ship_texture_hit = LoadTexture("img/player_ship_square_hit.png");

    background_buttons = LoadTexture("img/scroll_background.png");
    play_button = LoadTexture("img/play_button.png");
    restart_button = LoadTexture("img/restart_button.png");
    quit_button = LoadTexture("img/quit_button.png");

    score_frame = LoadTexture("img/score_frame.png");
    board_label = LoadTexture("img/board_label.png");

    sound_enabled_button = LoadTexture("img/sound_enabled_button.png");
    sound_disabled_button = LoadTexture("img/sound_disabled_button.png");
}
/**@brief
* Funkcja odpowiadaj¹ca za znikniêcie tekstur
**/
void Textures::unloadTextures()
{
    UnloadTexture(background);
    UnloadTexture(empty_square_texture);
    UnloadTexture(lighten_square);
    UnloadTexture(disabled_square);
    UnloadTexture(transparent_square);
    UnloadTexture(ship_texture);
    UnloadTexture(player_ship_texture);
    UnloadTexture(player_ship_texture_hit);

    UnloadTexture(background_buttons);
    UnloadTexture(play_button);
    UnloadTexture(restart_button);
    UnloadTexture(quit_button);

    UnloadTexture(score_frame);
    UnloadTexture(board_label);

    UnloadTexture(sound_enabled_button);
    UnloadTexture(sound_disabled_button);
}
