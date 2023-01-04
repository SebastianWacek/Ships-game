
#include "../header_files/ship.h"

int Ship::ship_counter = 0;
int Ship::currently_moving_ship = -1;


Ship::Ship()
{
    x = 500;
    y = 500;
    old_x = x;
    old_y = y;
    size = 4;
    lives = size;
    position = VERTICAL;
    old_position = position;
    ship_id = ship_counter++;
    if(position == VERTICAL)
    {
        ship_collision_model = {(float)x, (float)y, (float)50, (float)(50 * size)};
        ship_collision_model_2 = {(float)(x - 25), (float)(y - 25), (float)150, (float)(50 * size + 100)};
    }
    else
    {
        ship_collision_model = {(float)x, (float)y, (float)(50 * size), (float)50};
        ship_collision_model_2 = {(float)(x - 25), (float)(y - 25), (float)(50 * size + 100), (float)150};
    }
}

Ship::Ship(int start_x, int start_y, int ship_size, int ship_position)
{
    x = start_x;
    y = start_y;
    old_x = x;
    old_y = y;
    size = ship_size;
    lives = size;
    position = ship_position;
    old_position = position;
    ship_id = ship_counter++;
    if(position == VERTICAL)
    {
        ship_collision_model = {(float)x, (float)y, (float)50, (float)(50 * size)};
        ship_collision_model_2 = {(float)(x - 25), (float)(y - 25), (float)100, (float)(50 * size + 50)};
    }
    else
    {
        ship_collision_model = {(float)x, (float)y, (float)(50 * size), (float)50};
        ship_collision_model_2 = {(float)(x - 25), (float)(y - 25), (float)(50 * size + 50), (float)100};
    }
}

//void Ship::setShipOnBoard(Board gameBoard[][BOARD_SIZE])
//{
//    for(int i = 0; i < BOARD_SIZE; i++)
//        for(int j = 0; j < BOARD_SIZE; j++)
//        {
//            if(gameBoard[i][j].x == x && gameBoard[i][j].y == y)
//                gameBoard[i][j].id = SHIP;
//        }
//}
/**@brief
* Funkcja rysujaca statki
**/
void Ship::drawShips(std::vector <Ship> ship_collection, Textures game_textures, int player)
{
    for(std::vector<Ship>::iterator it = ship_collection.begin(); it != ship_collection.end(); it++)
    {
        it ->drawMyShip(game_textures, player);
    }
}
/**@brief
* Funkcja rysujaca statki gracza
**/
void Ship::drawMyShip(Textures game_textures, int player)
{

    Texture2D ship_texture;

    if(player == PLAYER)
        ship_texture = game_textures.player_ship_texture;
    else
        ship_texture = game_textures.ship_texture;

    for(int i = 0; i < size; i++)
    {
        switch(position)
        {

        case HORISONTAL:
                DrawTexture(ship_texture, x + (SQUARE_BASIC_SIZE * i), y, RAYWHITE);
            break;
        case VERTICAL:
                DrawTexture(ship_texture, x, y + (SQUARE_BASIC_SIZE * i), RAYWHITE);
            break;
        default:
            break;
        }
    }
}
/**@brief
* Funkcja odpowiadajaca za przeciaganie statkow myszka
**/
void Ship::moveShipByMouse(bool is_ship_colliding)
{
    float ship_width, ship_hight;
    bool is_mouse_on_ship = false;

    if(position == HORISONTAL)  // jezeli statek jest poziomo to jego wysokosc to 50 a dlugosc 50 * size
    {
        ship_width = 50 * size;
        ship_hight = 50;
        ship_collision_model.width = ship_width;
        ship_collision_model.height = ship_hight;
    }
    else                        // jeżeli statek jest pionowo to jego wysokość to 50 * size a dlugosć 50
    {
        ship_width = 50;
        ship_hight = 50 * size;
        ship_collision_model.width = ship_width;
        ship_collision_model.height = ship_hight;
    }

    is_mouse_on_ship = CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)x, (float)y, ship_width, ship_hight});
    if(is_mouse_on_ship && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySoundMulti(GameMusic::ship_interaction_sound);
        currently_moving_ship = ship_id;
    }
    else if(currently_moving_ship == ship_id && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        rotateShip();
        DrawRectangleRec(ship_collision_model, (Color){ 230, 41, 55, 127});
        DrawRectangleRec(ship_collision_model_2, (Color){ 102, 191, 255, 127 });
        switch(position)
        {
        case HORISONTAL:
            DrawRectangle(x, y, ship_width, ship_hight, (Color){ 230, 41, 55, 127});
            x = GetMouseX() - (SQUARE_BASIC_SIZE/2) * size;
            y = GetMouseY() - (SQUARE_BASIC_SIZE/2);
            break;
        case VERTICAL:
            DrawRectangle(x, y, ship_width, ship_hight, (Color){ 230, 41, 55, 127});
            x = GetMouseX() - (SQUARE_BASIC_SIZE/2);
            y = GetMouseY() - (SQUARE_BASIC_SIZE/2) * size;
        default:
            break;
        }
    }
    else if(currently_moving_ship == ship_id && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        PlaySoundMulti(GameMusic::ship_interaction_sound);
        currently_moving_ship = -1;

        if(is_ship_colliding)
        {
            x = old_x;
            y = old_y;
            position = old_position;
        }
        else
        {
            x = (((x - 25)/50) * 50) + 50;
            y = (((y - 25)/50) * 50) + 50;
            old_x = x;
            old_y = y;
            old_position = position;
        }
    }

    ship_collision_model.x = x; // uaktualnianie pozycji modelu kolizyjnego statku
    ship_collision_model.y = y;
    updateShipCollisionModel_2();
}

/**@brief
* Funkcja odpowiadajaca za rotacje statkow
**/
void Ship::rotateShip()
{
    if(IsKeyPressed(KEY_R) && position == HORISONTAL)
    {
        PlaySoundMulti(GameMusic::ship_interaction_sound);
        position = VERTICAL;
    }
    else if(IsKeyPressed(KEY_R) && position == VERTICAL)
    {
        PlaySoundMulti(GameMusic::ship_interaction_sound);
        position = HORISONTAL;
    }
}
/**@brief
* Funkcja glowna
**/
void Ship::updateShipCollisionModel_2()
{
    ship_collision_model_2.x = x - 25;
    ship_collision_model_2.y = y - 25;
    if(position == VERTICAL)
    {
        ship_collision_model_2.width = 100;
        ship_collision_model_2.height = 50 * size + 50;
    }
    else
    {
        ship_collision_model_2.width = 50 * size + 50;
        ship_collision_model_2.height = 100;
    }
}

/**@brief
* Funkcja ustawiajaca statki na domyslnych pozycjach
**/
void Ship::setShipsDefaultPositions(std::vector <Ship> &ship_collection)
{
    ship_collection.push_back(Ship(250, 250, 1, VERTICAL));
    ship_collection.push_back(Ship(650, 250, 1, VERTICAL));
    ship_collection.push_back(Ship(200, 650, 1, VERTICAL));
    ship_collection.push_back(Ship(550, 600, 1, VERTICAL));


    ship_collection.push_back(Ship(650, 350, 2, VERTICAL));
    ship_collection.push_back(Ship(650, 600, 2, VERTICAL));
    ship_collection.push_back(Ship(300, 700, 2, HORISONTAL));


    ship_collection.push_back(Ship(250, 350, 3, HORISONTAL));
    ship_collection.push_back(Ship(200, 450, 3, VERTICAL));

    ship_collection.push_back(Ship(450, 400, 4, VERTICAL));

}

/**@brief
* Funkcja generujaca pozycje statkow przeciwnika
**/
void Ship::generateComputerShipsPositions(std::vector <Ship> &ship_collection)
{
    ship_collection.clear();
    int x, y, ship_size, position;
    Rectangle basic_collision_model;

    ship_size = 4;      //generowanie statkow o wielkosci 4
    for(int i = 0; i < 1; i++)
    {
        x = ((900 + rand()% 500) / 50) * 50;
        y = ((250 + rand()% 500) / 50) * 50;
        position = (VERTICAL - 1) + rand()% 2;

        if(position == VERTICAL)
            basic_collision_model = {(float)x, (float)y, 50, 200};
        else
            basic_collision_model = {(float)x, (float)y, 200, 50};


        if(Ship::checkCollisionRecShips(basic_collision_model, ship_collection) || Ship::checkCollisionShipBoardBorders(basic_collision_model))
            i--;
        else
            ship_collection.push_back(Ship(x, y, ship_size, position));
    }

    ship_size = 3;      //generowanie statkow o wielkosci 3
    for(int i = 0; i < 2; i++)
    {
        x = ((900 + rand()% 500) / 50) * 50;
        y = ((250 + rand()% 500) / 50) * 50;
        position = (VERTICAL - 1) + rand()% 2;

        if(position == VERTICAL)
            basic_collision_model = {(float)x, (float)y, 50, 150};
        else
            basic_collision_model = {(float)x, (float)y, 150, 50};


        if(Ship::checkCollisionRecShips(basic_collision_model, ship_collection) || Ship::checkCollisionShipBoardBorders(basic_collision_model))
            i--;
        else
            ship_collection.push_back(Ship(x, y, ship_size, position));
    }

    ship_size = 2;      //generowanie statkow o wielkosci 2
    for(int i = 0; i < 3; i++)
    {
        x = ((900 + rand()% 500) / 50) * 50;
        y = ((250 + rand()% 500) / 50) * 50;
        position = (VERTICAL - 1) + rand()% 2;

        if(position == VERTICAL)
            basic_collision_model = {(float)x, (float)y, 50, 100};
        else
            basic_collision_model = {(float)x, (float)y, 100, 50};


        if(Ship::checkCollisionRecShips(basic_collision_model, ship_collection) || Ship::checkCollisionShipBoardBorders(basic_collision_model))
            i--;
        else
            ship_collection.push_back(Ship(x, y, ship_size, position));
    }

    ship_size = 1;      //generowanie statkow o wielkosci 1
    for(int i = 0; i < 4; i++)
    {
        x = ((900 + rand()% 500) / 50) * 50;
        y = ((250 + rand()% 500) / 50) * 50;
        position = VERTICAL + rand()% 1;
        basic_collision_model = {(float)x, (float)y, 50, 50};
        if(Ship::checkCollisionRecShips(basic_collision_model, ship_collection))
            i--;
        else
            ship_collection.push_back(Ship(x, y, ship_size, position));
    }

}


/**@brief
* Funkcja sprawdzajaca kolizje pomiedzy statkami
**/
bool Ship::checkCollisionRecShips(Rectangle rec, std::vector<Ship> ship_collection)
{
    for(std::vector<Ship>::iterator it = ship_collection.begin(); it != ship_collection.end(); it++)
    {
        if(CheckCollisionRecs(rec, it ->ship_collision_model_2))
            return true;
    }
    return false;
}

//----------------------------------------
//
//----------------------------------------

/**@brief
* Funkcja sprawdzajaca kolizje pomiedzy statkami a granicami planszy
*@return Jezeli nie wystepuje kolizja statku z granica planszy funkcja konczy swoje dzialanie i zwraca false.
**/
bool Ship::checkCollisionShipBoardBorders(Rectangle ship_collision_model)
{

    bool is_ship_collide_with_left_border = CheckCollisionRecs(ship_collision_model, Board::left_border_computer);
    bool is_ship_collide_with_right_border = CheckCollisionRecs(ship_collision_model, Board::right_border_computer);
    bool is_ship_collide_with_upper_border = CheckCollisionRecs(ship_collision_model, Board::upper_border_computer);
    bool is_ship_collide_with_lower_border = CheckCollisionRecs(ship_collision_model, Board::lower_border_computer);

    if(is_ship_collide_with_left_border || is_ship_collide_with_right_border || is_ship_collide_with_upper_border || is_ship_collide_with_lower_border)
        return true;

    return false;

}
/**@brief
* Funkcja sprawdzajaca kolizje pomiedzy statkami a obramowaniem planszy
*@return Jezeli nie wystepuje kolizja statku z obramowaniem planszy funkcja konczy swoje działanie i zwraca false.
**/
bool Ship::checkCollisionWithShipsAndBoard(std::vector <Ship> ship_collection, int ship_checked_id)
{

    bool is_ships_collide = false;
    bool is_ship_on_board = true;
    bool is_ship_collide_with_left_border = false;
    bool is_ship_collide_with_right_border = false;
    bool is_ship_collide_with_upper_border = false;
    bool is_ship_collide_with_lower_border = false;

    for(std::vector<Ship>::iterator it = ship_collection.begin(); it != ship_collection.end(); it++)
    {
        is_ships_collide = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model, it -> ship_collision_model_2);
        is_ship_on_board = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model_2, Board::player_board_collision_model);

        is_ship_collide_with_left_border = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model_2, Board::left_border_player);
        is_ship_collide_with_right_border = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model_2, Board::right_border_player);
        is_ship_collide_with_upper_border = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model_2, Board::upper_border_player);
        is_ship_collide_with_lower_border = CheckCollisionRecs(ship_collection[ship_checked_id].ship_collision_model_2, Board::lower_border_player);


       if(ship_checked_id != it ->ship_id && (is_ships_collide == true || is_ship_on_board == false || is_ship_collide_with_left_border
            || is_ship_collide_with_right_border || is_ship_collide_with_upper_border || is_ship_collide_with_lower_border))
       {
            return true;
       }
    }
    return false;
}
/**@brief
* Funkcja odpowiadajaca za poruszanie statkami gracza
**/
void Ship::movePlayerShips(std::vector <Ship> *ship_collection)
{

    for(std::vector<Ship>::iterator it = ship_collection -> begin(); it != ship_collection -> end(); it++)
    {
            it ->moveShipByMouse(checkCollisionWithShipsAndBoard(*ship_collection, it ->ship_id));
    }
}

/**@brief
* Funkcja odpowiadajaca za podswietlenie statku, który jest aktualnie zaznaczony
**/
void Ship::higlightChoosenShip(std::vector <Ship> *ship_collection)
{
    for(std::vector<Ship>::iterator it = ship_collection -> begin(); it != ship_collection -> end(); it++)
    {
        if(CheckCollisionPointRec(GetMousePosition(), it ->ship_collision_model))
        {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
            DrawRectangleRec(it -> ship_collision_model, (Color){ 255, 203, 0, 127 });
            return;
            GameMusic::playPointedSound(GameMusic::ship_interaction_sound);

        }
        else if(GetMouseCursor() == MOUSE_CURSOR_RESIZE_ALL)
            SetMouseCursor(MOUSE_CURSOR_ARROW);
    }
}

void Ship::TEST_draw_ships_collision_models(std::vector <Ship> ship_collection)
{
    for(std::vector<Ship>::iterator it = ship_collection.begin(); it != ship_collection. end(); it++)
    {
        DrawRectangleRec(it ->ship_collision_model, (Color){ 230, 41, 55, 127});
        DrawRectangleRec(it ->ship_collision_model_2, (Color){ 102, 191, 255, 127 });
    }
}


