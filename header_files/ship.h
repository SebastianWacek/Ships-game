
#ifndef ship_h
#define ship_h

#include "raylib.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include "engine.h"
#include "gamemusic.h"
#include "textures.h"
#include "board.h"



class Ship
{
public:
    static int ship_counter;
    static int currently_moving_ship;
    int x, y, lives;
    int old_x, old_y, old_position;
    int size, position, ship_id;
    bool ship_can_be_moved = false;
    Rectangle ship_collision_model, ship_collision_model_2;


    Ship();
    Ship(int start_x, int start_y, int ship_size, int ship_position);

    static void drawShips(std::vector <Ship> ship_collection, Textures game_textures, int player);
    static void setShipsDefaultPositions(std::vector <Ship> &ship_collection);
    static void generateComputerShipsPositions(std::vector <Ship> &ship_collection);
    static bool checkCollisionRecShips(Rectangle rec, std::vector<Ship> ship_collection);
    static bool checkCollisionWithShipsAndBoard(std::vector <Ship> ship_collection, int ship_checked_id);
    static bool checkCollisionShipBoardBorders(Rectangle ship_collision_model);
    static void movePlayerShips(std::vector <Ship> *ship_collection);
    static void higlightChoosenShip(std::vector <Ship> *ship_collection);

    static void TEST_draw_ships_collision_models(std::vector <Ship> ship_collection);




    //void setShipOnBoard(Board gameBoard[][BOARD_SIZE]);
    void drawMyShip(Textures game_textures, int player);
    void moveShipByMouse(bool is_ship_colliding);
    void rotateShip();
    void updateShipCollisionModel_2();

};
#endif // ship_h
