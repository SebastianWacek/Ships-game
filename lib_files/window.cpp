#include "../header_files/window.h"

Window::Window(double width, double height)
{
    this -> windowWidth = width;
    this -> windowHeight = height;
    this -> scale = sqrt((this -> windowHeight * this -> windowWidth) / (1920 * 1000));
    this -> window_should_be_closed = false;
    initiateMenu();
};

Window::Window()
{
    this -> windowWidth = 1280;
    this -> windowHeight = 720;
    this -> scale = sqrt((this -> windowHeight * this -> windowWidth) / (1920 * 1000));
    this -> window_should_be_closed = false;
    initiateMenu();
}

/**@brief
* Funkcja rysujaca tlo aplikacji
**/
void Window::drawBackground(Textures game_textures)
{
    DrawTexture(game_textures.background, 0, 0, RAYWHITE);
}
/**@brief
* Funkcja inicjujaca menu
**/
void Window::initiateMenu()
{
    menu_background_rec = {400, 20, 800, 140};
    play_button_rec = {400 + 115, 60, 160, 56};
    restart_button_rec = {400 + 115 + 160 + 45, 60, 160, 56};
    quit_button_rec = {400 + 480 + 45, 60, 160, 56};
    sound_button_rec = {50, 250, 60, 60};
}
/**@brief
* Funkcja rysujaca glowne menu
**/
void Window::drawMenu(Textures game_textures)
{
    DrawTexture(game_textures.background_buttons, 400, 20, RAYWHITE);
    drawPlayButton(game_textures);
    drawRestartButton(game_textures);
    drawQuitButton(game_textures);
    drawSoundButton(game_textures);
    playOnButtonsSound();
}

/**@brief
* Funkcja odpowiadajaca za obsluge dzwieku po najechaniu na przyciski
**/
void Window::playOnButtonsSound()
{
    Vector2 mouse_position = GetMousePosition();
    if(CheckCollisionPointRec(mouse_position, play_button_rec) || CheckCollisionPointRec(mouse_position, restart_button_rec)
       || CheckCollisionPointRec(mouse_position, quit_button_rec))
    {
        GameMusic::playPointedSound(GameMusic::ship_interaction_sound);
        GameMusic::disableSound();
    }
    else
        GameMusic::enableSound();
}
/**@brief
* Funkcja rysuj¹ca przycisk Play
**/
void Window::drawPlayButton(Textures game_textures)
{
    if(!CheckCollisionPointRec(GetMousePosition(), play_button_rec))   // 160 x 56 dimension of play_button
        {
            DrawTexture(game_textures.play_button, play_button_rec.x, play_button_rec.y, RAYWHITE);
        }
    else
    {

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawTexture(game_textures.play_button, play_button_rec.x + 5, play_button_rec.y + 5, GOLD);
        }
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            GAMEMODE = PLAY_MODE;
            SetSoundVolume(GameMusic::game_start_sound, 3);
            GameMusic::enableSound();
            GameMusic::playPointedSound(GameMusic::game_start_sound);
            GameMusic::disableSound();
        }
        else
            DrawTexture(game_textures.play_button, play_button_rec.x, play_button_rec.y, GOLD);

    }
}

/**@brief
* Funkcja rysujaca przycisk Restart
**/
void Window::drawRestartButton(Textures game_textures)
{
    if(!CheckCollisionPointRec(GetMousePosition(), restart_button_rec))   // 160 x 56 dimension of button
        {
            DrawTexture(game_textures.restart_button, restart_button_rec.x, restart_button_rec.y, RAYWHITE);
        }
    else
    {

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawTexture(game_textures.restart_button, restart_button_rec.x + 5, restart_button_rec.y + 5, GOLD);
            //GAMEMODE = PLAY_MODE;
        }
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            SHOULD_GAME_BE_RESTARTED = true;
        }
        else
            DrawTexture(game_textures.restart_button, restart_button_rec.x, restart_button_rec.y, GOLD);

    }
}
/**@brief
* Funkcja rysujuca przycisk Quit
**/
void Window::drawQuitButton(Textures game_textures)
{
    if(!CheckCollisionPointRec(GetMousePosition(), quit_button_rec))   // 160 x 56 dimension of button
        {
            DrawTexture(game_textures.quit_button, quit_button_rec.x, quit_button_rec.y, RAYWHITE);
        }
    else
    {

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            DrawTexture(game_textures.quit_button, quit_button_rec.x + 5, quit_button_rec.y + 5, GOLD);
        }
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            window_should_be_closed = true;
        }
        else
            DrawTexture(game_textures.quit_button, quit_button_rec.x, quit_button_rec.y, GOLD);
    }
}
/**@brief
* Funkcja rysujaca przycisk do obslugi dzwieku
**/
void Window::drawSoundButton(Textures game_textures)
{
    if(!CheckCollisionPointRec(GetMousePosition(), sound_button_rec))   // 160 x 56 dimension of button
        {
            if(SHOULD_MUSIC_PLAY == true)
                DrawTexture(game_textures.sound_enabled_button, sound_button_rec.x, sound_button_rec.y, RAYWHITE);
            else
                DrawTexture(game_textures.sound_disabled_button, sound_button_rec.x, sound_button_rec.y, RAYWHITE);
        }
    else
    {

        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if(SHOULD_MUSIC_PLAY == true)
                DrawTexture(game_textures.sound_enabled_button, sound_button_rec.x + 5, sound_button_rec.y + 5, GOLD);
            else
                DrawTexture(game_textures.sound_disabled_button, sound_button_rec.x + 5, sound_button_rec.y + 5, GOLD);
        }
        else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            SHOULD_MUSIC_PLAY = !SHOULD_MUSIC_PLAY;
            GameMusic::pauseResumeSound(GameMusic::background_sound);
        }
        else
        {
            if(SHOULD_MUSIC_PLAY == true)
                DrawTexture(game_textures.sound_enabled_button, sound_button_rec.x, sound_button_rec.y, GOLD);
            else
                DrawTexture(game_textures.sound_disabled_button, sound_button_rec.x, sound_button_rec.y, GOLD);
        }
    }
}
