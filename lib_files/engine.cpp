#include "../header_files/engine.h"


//---------------------------------------------------------------
// Definitions of global variables
//---------------------------------------------------------------


int GAMEMODE = BEGIN_MODE;
int COMPUTER_POINTS = 20;   // every square of a ship is a 'point'
int PLAYER_POINTS = 20;     // so 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1 = 20 points
int WHOSE_TURN = PLAYER;   // player has first move
bool SHOULD_GAME_BE_RESTARTED = false;
bool SHOULD_MUSIC_PLAY = true;





//---------------------------------------------------------------
// Definitions of functions
//---------------------------------------------------------------
/**@brief
* Funkcja sprawdzajaca koncowy wynik rozgrywki
**/
void checkWinOrLose(Font font)
{
    Rectangle message_frame = {30, 10, 340, 180};
    if(COMPUTER_POINTS <= 0)
    {
        if(GameMusic::end_sound_played == false){
            PlaySound(GameMusic::win_sound);
            GameMusic::end_sound_played = true;
        }
        DrawTextEx(font, "YOU WIN!", (Vector2){message_frame.x + 90, message_frame.y + 60}, 35, 2, YELLOW);
        DrawTextEx(font, "BRAVO!!", (Vector2){message_frame.x + 90, message_frame.y + 90}, 35, 2, YELLOW);
    }

    if(PLAYER_POINTS <= 0){
        if(GameMusic::end_sound_played == false){
            PlaySound(GameMusic::lose_sound);
            GameMusic::end_sound_played = true;
        }
        DrawTextEx(font, "YOU LOSE!", (Vector2){message_frame.x + 50, message_frame.y + 45}, 30, 1, RED);
        DrawTextEx(font, "BETTER LUCK", (Vector2){message_frame.x + 50, message_frame.y + 75}, 30, 1, RED);
        DrawTextEx(font, "NEXT TIME...!!", (Vector2){message_frame.x + 50, message_frame.y + 105}, 30, 1, RED);
    }
}
/**@brief
* Funkcja wyswietlajaca punkty gracza i komputera
**/
void drawScore(Textures game_textures)
{
    DrawTexture(game_textures.score_frame, 1230, 10, RAYWHITE);
    DrawText(TextFormat("PLAYER: %d", PLAYER_POINTS), 1280, 60, 32, BLACK);
    DrawText(TextFormat("COMPUTER: %d", COMPUTER_POINTS), 1280, 100, 32, BLACK);
}
/**@brief
* Funkcja odpowiadajaca za wyswietlanie polecen i wskazowek dla gracza przed rozpoczeciem oraz w trakcie gry
**/
void drawMessageBox(Textures game_textures, Font font, double &timer, int &computer_thinking_time)
{
    Rectangle message_frame = {30, 10, 340, 180};
    DrawTexture(game_textures.score_frame, message_frame.x, message_frame.y, RAYWHITE);
    if(GAMEMODE == BEGIN_MODE)
    {
        DrawTextEx(font, "Place your ships", (Vector2){message_frame.x + 50, message_frame.y + 40}, 30, 1, BLACK);
        DrawTextEx(font, "and press 'PLAY'", (Vector2){message_frame.x + 50, message_frame.y + 70}, 30, 1, BLACK);
        DrawTextEx(font, "Press R to rotate", (Vector2){message_frame.x + 50, message_frame.y + 100}, 30, 1, BLACK);
    }
    else if(GAMEMODE == PLAY_MODE){
        switch(WHOSE_TURN)
        {
        case PLAYER:
            if(PLAYER_POINTS > 0 && COMPUTER_POINTS > 0){
            DrawTextEx(font, "Your turn ", (Vector2){message_frame.x + 50, message_frame.y + 75}, 35, 2, BLACK);
            if(timer < 1)
            {
            DrawTextEx(font, ".", (Vector2){message_frame.x + 230, message_frame.y + 75}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else if(timer < 2){
                DrawTextEx(font, "..", (Vector2){message_frame.x + 230, message_frame.y + 75}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else if(timer < 3){
                DrawTextEx(font, "...", (Vector2){message_frame.x + 230, message_frame.y + 75}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else
                timer = 0;
            }
            break;
        case COMPUTER:
            if(PLAYER_POINTS > 0 && COMPUTER_POINTS > 0){
            DrawTextEx(font, "Computer is", (Vector2){message_frame.x + 60, message_frame.y + 50}, 35, 1, BLACK);
            DrawTextEx(font, "thinking", (Vector2){message_frame.x + 60, message_frame.y + 80}, 35, 1, BLACK);
            if(timer < 1)
            {
                DrawTextEx(font, ".", (Vector2){message_frame.x + 190, message_frame.y + 80}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else if(timer < 2){
                DrawTextEx(font, "..", (Vector2){message_frame.x + 190, message_frame.y + 80}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else if(timer < 3){
               DrawTextEx(font, "...", (Vector2){message_frame.x + 190, message_frame.y + 80}, 40, 4, BLACK);
                timer += GetFrameTime();
            }
            else if(computer_thinking_time >= 0)
            {
                computer_thinking_time -= 3;
                timer = 0;
            }
            else
            {
                // zerowanie timer
                timer = 0;
            }
            }
            break;
        default:
            break;
        }
    }
}

