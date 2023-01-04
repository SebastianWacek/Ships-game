
#ifndef board_ships__operations_h
#define board_ships__operations_h

#include "board.h"
#include "ship.h"
#include "gamemusic.h"


//------------------------------------------------------------------------------------
// This file has been created due to significant problems
// when class Board and class Ship needs to work with each other
// This library connect this classes and allow to use those in functions ect.
//------------------------------------------------------------------------------------

bool clickOnBoard(Board gameBoard[][BOARD_SIZE], std::vector<Ship> &ship_collection);
bool computerIsShoothing(Board playerBoard[][BOARD_SIZE], std::vector<Ship> &ship_collection, std::vector<Board> &player_board_cover);
bool checkCollisionMouseShips(Vector2 vec, std::vector<Ship> &ship_collection, Board gameBoard[][BOARD_SIZE], Board considered_square);


#endif // board_ships__operations_h

