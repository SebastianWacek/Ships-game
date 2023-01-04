
#ifndef board_h
#define board_h

#include <vector>
#include "raylib.h"
#include "engine.h"
#include "textures.h"


class Board
{
public:
    int x, y, id;
    Rectangle square_collision_model;

    Board();
    Board(int x, int y, int id);


    static Rectangle player_board_collision_model;
    static Rectangle computer_board_collision_model;

    static Rectangle left_border_player, right_border_player, upper_border_player, lower_border_player;
    static Rectangle left_border_computer, right_border_computer, upper_border_computer, lower_border_computer;
/**@brief
* Funkcja inicjujaca plansze
**/
    static void initiate_board(Board newBoard[][BOARD_SIZE], int start_x, int start_y);
    /**@brief
* Funkcja rysujaca plansze
**/
    static void drawBoard(Board gameBoard[][BOARD_SIZE], Textures game_textures);
    /**@brief
* Funkcja rysujaca obramowania
**/
    static void drawBoardCover(std::vector <Board> board_cover, Textures game_textures);
/**@brief
* Funkcja rysujaca litery i liczby
**/
    static void drawLettersAndNumbers();
/**@brief
* Funkcja rysujaca granice planszy
**/
    static void drawBoardsLabels(Textures game_textures, Font font);
/**@brief
* Funkcja usuwajaca obramowanie statku po zjechaniu z niego myszka
**/
    static void disableSquaresAroundShip(Rectangle rec, Board gameBoard[][BOARD_SIZE]);


    static void TEST_draw_player_board_collision_model();
    static void TEST_draw_computer_board_collision_model();
    static void TEST_drawPlayerBoardCollisionBorders();
    static void TEST_drawComputerBoardCollisionBorders();




};



#endif // board_h
