#include "../header_files/board_ships_operations.h"

/**@brief
* Funkcja obslugujaca zdarzenie klikania w pola na planszy
*@return jezeli klikniecie nastepuje poza granicami planszy, funkcja zwraca false, wartosc true zwraca,
 kiedy po nie trafieniu w statek nastepuje tura komputera, w przeciwnym wypadku zwraca false i konczy swoje dzialanie
**/
bool clickOnBoard(Board gameBoard[][BOARD_SIZE], std::vector<Ship> &ship_collection)
{

    //-------------------------------------------------------------------------------------------
    // This helps to optimize the game
    //-------------------------------------------------------------------------------------------
    if(CheckCollisionPointRec(GetMousePosition(), Board::computer_board_collision_model) == false)
        return false;

    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(CheckCollisionPointRec(GetMousePosition(), gameBoard[i][j].square_collision_model))
            {
                if(gameBoard[i][j].id == EMPTY_SQUARE)
                    gameBoard[i][j].id = LIGHTEN_SQUARE;

                if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    GameMusic::playPointedSound(GameMusic::ship_interaction_sound);
                    if(checkCollisionMouseShips(GetMousePosition(), ship_collection, gameBoard, gameBoard[i][j]))
                    {
                        if(gameBoard[i][j].id != TRANSPARENT_SQUARE)
                        {
                            gameBoard[i][j].id = TRANSPARENT_SQUARE;
                            COMPUTER_POINTS--;
                            return true;
                        }
                    }
                    else if(gameBoard[i][j].id != DISABLED_SQUARE)
                    {
                        gameBoard[i][j].id = DISABLED_SQUARE;
                        //-------------------------------------------------
                        //  If player missed, then it's computer turn
                        //-------------------------------------------------
                        WHOSE_TURN = COMPUTER;
                        return true;
                    }
                }
            }
            else
            {
                if(gameBoard[i][j].id == LIGHTEN_SQUARE)
                    gameBoard[i][j].id = EMPTY_SQUARE;

            }
        }

    return false;
}


//----------------------------------------------
// This function is called after mouse click
//----------------------------------------------
/**@brief
* Funkcja sprawdzaj¹ca "kolizjê" statku z kursorem myszy
**/
bool checkCollisionMouseShips(Vector2 vec, std::vector<Ship> &ship_collection, Board gameBoard[][BOARD_SIZE], Board considered_square)
{
    for(std::vector<Ship>::iterator it = ship_collection.begin(); it != ship_collection.end(); it++)
    {
        if(CheckCollisionPointRec(vec, it ->ship_collision_model))
        {
            if(considered_square.id != TRANSPARENT_SQUARE)
            {
                it ->lives--;
                if(it ->lives <= 0)
                    Board::disableSquaresAroundShip(it ->ship_collision_model_2, gameBoard);
            }

            return true;
        }
    }
    return false;
}

/**@brief
* Funkcja odpowiadajaca za strzaly komputera
**/
bool computerIsShoothing(Board playerBoard[][BOARD_SIZE], std::vector<Ship> &ship_collection, std::vector<Board> &player_board_cover)
{

    int i, shoot_x, shoot_y;
    int shoot_x_rounded, shoot_y_rounded;
    Vector2 computer_shoot;
    bool shooted_the_same_place = false;
    bool do_break;

    //-------------------------------------------------------------------------
    // Here we make sure, that computer won't shoot in the same place again
    //-------------------------------------------------------------------------
    do{
        i = 0;
        do_break = false;
        shooted_the_same_place = false;
        shoot_x = 201 + rand() % 499;
        shoot_y = 251 + rand() % 499;

        shoot_x_rounded = (shoot_x / 50) * 50;
        shoot_y_rounded = (shoot_y / 50) * 50;

        //for(int i = 0; i < BOARD_SIZE; i++)
        while(i < BOARD_SIZE || do_break == false)
        {
            for(int j = 0; j < BOARD_SIZE; j++)
            {
                if(playerBoard[i][j].x == shoot_x_rounded && playerBoard[i][j].y == shoot_y_rounded){
                    if(playerBoard[i][j].id == TRANSPARENT_SQUARE || playerBoard[i][j].id == DISABLED_SQUARE){
                        shooted_the_same_place = true;
                        do_break = true;
                        break;
                    }
                    else
                    {
                        do_break = true;
                        break;
                    }
                }
            }
            i++;
        }

    }while(shooted_the_same_place == true);

    computer_shoot = {(float)shoot_x, (float)shoot_y};

    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            //checkCollisionMouseShips(computer_shoot, ship_collection, playerBoar, Board[i][j]);
            if(CheckCollisionPointRec(computer_shoot, playerBoard[i][j].square_collision_model))
            {

                if(checkCollisionMouseShips(computer_shoot, ship_collection, playerBoard, playerBoard[i][j]))
                {
                    if(playerBoard[i][j].id != TRANSPARENT_SQUARE)
                    {
                        playerBoard[i][j].id = TRANSPARENT_SQUARE;
                        PLAYER_POINTS--;
                        player_board_cover.push_back(Board(shoot_x_rounded, shoot_y_rounded, PLAYER_SHIP_HIT));
                        return true;
                    }
                }
                else
                {
                    playerBoard[i][j].id = DISABLED_SQUARE;
                    //-------------------------------------------------
                    //  If computer missed, then it's player turn
                    //-------------------------------------------------
                    WHOSE_TURN = PLAYER;
                    return true;
                }
            }
        }


    return false;
}
