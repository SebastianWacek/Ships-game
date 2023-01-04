#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>

#include "raylib.h"
#include "header_files/window.h"
#include "header_files/engine.h"
#include "header_files/textures.h"
#include "header_files/gamemusic.h"
#include "header_files/ship.h"
#include "header_files/board.h"
#include "header_files/board_ships_operations.h"



using namespace std;

/**@brief
* Funkcja glowna
**/
int main()
{
    srand(time(NULL));
    Window mainWindow = Window(1600, 900);
    InitWindow(mainWindow.windowWidth, mainWindow.windowHeight, "Statki");
    SetWindowIcon(LoadImage("ships_icon.png"));
    InitAudioDevice();

    Font BASIC_FONT = LoadFont("resources/fonts/romulus.png");


    Textures game_textures;             // ładowanie tekstur
    game_textures.loadTextures();

    Board playerBoard[BOARD_SIZE][BOARD_SIZE];
    Board opponentBoard[BOARD_SIZE][BOARD_SIZE];

    Board::initiate_board(playerBoard, 200, 250);
    Board::initiate_board(opponentBoard, 900, 250);


    vector <Ship> player_ships_collection;
    vector <Ship> computer_ships_collection;
    //-------------------------------------------------------------------------------------------
    // We will be drawing a 'hit' texture benaht the player ship square, which was hit
    //-------------------------------------------------------------------------------------------
    vector <Board> player_board_cover;

    Ship::setShipsDefaultPositions(player_ships_collection);
    Ship::generateComputerShipsPositions(computer_ships_collection);
    //PlaySound(GameMusic::background_sound);

    double timer_0 = 0;
    double music_timer = 0;
    int computer_thinking_time = GetRandomValue(2, 6);

    SetTargetFPS(60);
    while(!WindowShouldClose() && mainWindow.window_should_be_closed == false)
    {
        //-------------------------------------------------------------------------------------------
        // Music
        //-------------------------------------------------------------------------------------------
        GameMusic::playMainMusic(music_timer);



        BeginDrawing();

            //-------------------------------------------------------------------------------------------
            // Drawing background and menu, and message box
            //-------------------------------------------------------------------------------------------
            ClearBackground(WHITE);
            mainWindow.drawBackground(game_textures);
            mainWindow.drawMenu(game_textures);
            drawMessageBox(game_textures, BASIC_FONT, timer_0, computer_thinking_time);

            //-------------------------------------------------------------------------------------------
            // Possible game restart
            //-------------------------------------------------------------------------------------------
            if(SHOULD_GAME_BE_RESTARTED)
            {
                player_board_cover.clear();
                player_ships_collection.clear();
                computer_ships_collection.clear();

                Ship::ship_counter = 0;
                Ship::currently_moving_ship = -1;

                Board::initiate_board(playerBoard, 200, 250);
                Board::initiate_board(opponentBoard, 900, 250);

                Ship::setShipsDefaultPositions(player_ships_collection);
                Ship::generateComputerShipsPositions(computer_ships_collection);

                GameMusic::enableSound();
                GameMusic::end_sound_played = false;

                timer_0 = 0;

                GAMEMODE = BEGIN_MODE;
                COMPUTER_POINTS = 20;
                PLAYER_POINTS = 20;
                WHOSE_TURN = PLAYER;
                SHOULD_GAME_BE_RESTARTED = false;
            }


            //-------------------------------------------------------------------------------------------
            // Player board, ships and movement
            // Boards Numbers and Letters, Labels
            //-------------------------------------------------------------------------------------------
            Board::drawBoard(playerBoard, game_textures);
            Board::drawLettersAndNumbers();
            Board::drawBoardsLabels(game_textures, BASIC_FONT);
            Ship::drawShips(player_ships_collection, game_textures, PLAYER);
            if(GAMEMODE == BEGIN_MODE){
                //DrawText("Place your ships and pres PLAY to start the game.", 200, 170, 35, BLACK);
                //DrawTextEx(basic_font, "Place your ships and pres PLAY to start the game.", (Vector2){250.0, 170.0},30, 2, BLACK);
                Ship::higlightChoosenShip(&player_ships_collection);
                Ship::movePlayerShips(&player_ships_collection);
            }
            Board::drawBoardCover(player_board_cover, game_textures);

            //-------------------------------------------------------------------------------------------
            // We are drawing computer ships 'under' the computer board (ships are covered by board)
            //-------------------------------------------------------------------------------------------
            Ship::drawShips(computer_ships_collection, game_textures, COMPUTER);
            Board::drawBoard(opponentBoard, game_textures);



            //-------------------------------------------------------------------------------------------
            // Changing turns
            //-------------------------------------------------------------------------------------------
                switch(WHOSE_TURN)
                {
                case PLAYER:
                    if(GAMEMODE == PLAY_MODE && PLAYER_POINTS > 0 && COMPUTER_POINTS > 0){
                        if(clickOnBoard(opponentBoard, computer_ships_collection) == true)
                        {
                            timer_0 = 0;
                            computer_thinking_time = GetRandomValue(2, 6);
                        }
                    }
                    break;
                case COMPUTER:
                    if(timer_0 >= computer_thinking_time && PLAYER_POINTS > 0 && COMPUTER_POINTS > 0)
                    {
                        if(computerIsShoothing(playerBoard, player_ships_collection, player_board_cover) == true);
                            //WHOSE_TURN = PLAYER;
                        GameMusic::playPointedSound(GameMusic::ship_interaction_sound);
                        timer_0 = 0;
                    }
                    break;
                default:
                    WHOSE_TURN = PLAYER;
                    break;
                }

            //-------------------------------------------------------------------------------------------
            // Checking had we won or loose
            // Printing Player and Computer points
            //-------------------------------------------------------------------------------------------
            checkWinOrLose(BASIC_FONT);
            drawScore(game_textures);


            //-------------------------------------------------------------------------------------------
            //  DEBUG MODE FUNCTIONS:
            // 1. generating computer ships pressing T
            // 2. enter into DEBUG_MODE by pressing left ctrl + D
            // 3. WIN or LOSE instantly by presing W or L in DEBUG MODE
            //-------------------------------------------------------------------------------------------

            if(GAMEMODE == DEBUG_MODE)
            {
                // 1. generating computer ships pressing T
                if(IsKeyPressed(KEY_T))
                    Ship::generateComputerShipsPositions(computer_ships_collection);

                // 3. WIN instantly by presing W in DEBUG MODE
                if(IsKeyPressed(KEY_W)){
                    PLAYER_POINTS = 20;
                    COMPUTER_POINTS = 0;
                }

                // 3. LOSE instantly by presing L in DEBUG MODE
                if(IsKeyPressed(KEY_L)){
                    PLAYER_POINTS = 0;
                    COMPUTER_POINTS = 20;
                }
            }

            if(IsKeyPressed(KEY_D) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                if(GAMEMODE == BEGIN_MODE)
                    GAMEMODE = DEBUG_MODE;
                else
                {
                    SHOULD_GAME_BE_RESTARTED = true;
                }


            }
            //Board::TEST_draw_player_board_collision_model();
            //Board::TEST_drawPlayerBoardCollisionBorders();
            //Board::TEST_draw_computer_board_collision_model();
            //Board::TEST_drawComputerBoardCollisionBorders();
            //Ship::TEST_draw_ships_collision_models(computer_ships_collection);

        EndDrawing();

    }
    CloseAudioDevice();
    game_textures.unloadTextures();
    CloseWindow();

    return 0;
}
