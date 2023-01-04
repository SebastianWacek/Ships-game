
#include "../header_files/board.h"


//---------------------------------------------------------------
// Definitions of static variables from class Board
//---------------------------------------------------------------


Rectangle Board::player_board_collision_model = {230, 280, SQUARE_BASIC_SIZE * 10 - 60, SQUARE_BASIC_SIZE * 10 - 60};
Rectangle Board::computer_board_collision_model = {900, 250, SQUARE_BASIC_SIZE * 10, SQUARE_BASIC_SIZE * 10}; //930, 280, -60, -60


Rectangle Board::left_border_player = {150, 200, 1, 600};
Rectangle Board::right_border_player = {750, 200, 1, 600};
Rectangle Board::upper_border_player = {150, 200, 600, 1};
Rectangle Board::lower_border_player = {150, 800, 600, 1};

Rectangle Board::left_border_computer = {875, 200, 1, 600};
Rectangle Board::right_border_computer = {1425, 200, 1, 600};
Rectangle Board::upper_border_computer = {850, 225, 600, 1};
Rectangle Board::lower_border_computer = {850, 775, 600, 1};




Board::Board(){};
Board::Board(int x, int y, int id)
{
    this -> x = x;
    this -> y = y;
    this -> id = id;
}

//---------------------------------------------------------------
// Definitions of functions
//---------------------------------------------------------------



void Board::TEST_draw_player_board_collision_model()
{
    DrawRectangleRec(Board::player_board_collision_model, (Color){ 0, 228, 48, 64 });
}

void Board::TEST_draw_computer_board_collision_model()
{
    DrawRectangleRec(Board::computer_board_collision_model, (Color){ 0, 228, 48, 64 });
}

void Board::TEST_drawPlayerBoardCollisionBorders()
{
    DrawRectangleRec(Board::left_border_player, YELLOW);
    DrawRectangleRec(Board::right_border_player, YELLOW);
    DrawRectangleRec(Board::upper_border_player, YELLOW);
    DrawRectangleRec(Board::lower_border_player, YELLOW);
}

void Board::TEST_drawComputerBoardCollisionBorders()
{
    DrawRectangleRec(Board::left_border_computer, YELLOW);
    DrawRectangleRec(Board::right_border_computer, YELLOW);
    DrawRectangleRec(Board::upper_border_computer, YELLOW);
    DrawRectangleRec(Board::lower_border_computer, YELLOW);
}

void Board::initiate_board(Board newBoard[][BOARD_SIZE], int start_x, int start_y)
{
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            newBoard[i][j].id = EMPTY_SQUARE;
            newBoard[i][j].x = start_x + 50 * j;
            newBoard[i][j].y = start_y + 50 * i;

            // 49 x 49 are a dimension of collision box, because if it will be 50,
            // it will be possible to click two squares in the same time
            newBoard[i][j].square_collision_model = {(float)newBoard[i][j].x, (float)newBoard[i][j].y, 49, 49};
        }
}

void Board::drawBoard(Board gameBoard[][BOARD_SIZE], Textures game_textures)
{

    //----------------------------------------------------------------------------------
    // If we are in debug mode, we use transparent squares to see the ships
    //----------------------------------------------------------------------------------
    if(GAMEMODE == DEBUG_MODE)
        game_textures.empty_square_texture = game_textures.transparent_square;

    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            switch(gameBoard[i][j].id)
            {
            case EMPTY_SQUARE:
                DrawTexture(game_textures.empty_square_texture, gameBoard[i][j].x, gameBoard[i][j].y, RAYWHITE);
                break;
            case LIGHTEN_SQUARE:
                DrawTexture(game_textures.lighten_square, gameBoard[i][j].x, gameBoard[i][j].y, RAYWHITE);
                break;
            case TRANSPARENT_SQUARE:
                DrawTexture(game_textures.transparent_square, gameBoard[i][j].x, gameBoard[i][j].y, RAYWHITE);
                break;
            case DISABLED_SQUARE:
                DrawTexture(game_textures.disabled_square, gameBoard[i][j].x, gameBoard[i][j].y, RAYWHITE);
                break;
            case SHIP:
                DrawTexture(game_textures.ship_texture, gameBoard[i][j].x, gameBoard[i][j].y, RAYWHITE);
            default:
                break;
            }
        }
}

void Board::drawBoardCover(std::vector <Board> board_cover, Textures game_textures)
{
    for(std::vector<Board>::iterator it = board_cover.begin(); it != board_cover.end(); it++)
    {
        switch(it -> id)
            {
            case EMPTY_SQUARE:
                DrawTexture(game_textures.empty_square_texture, it -> x, it -> y, RAYWHITE);
                break;
            case LIGHTEN_SQUARE:
                DrawTexture(game_textures.lighten_square, it -> x, it -> y, RAYWHITE);
                break;
            case TRANSPARENT_SQUARE:
                DrawTexture(game_textures.transparent_square, it -> x, it -> y, RAYWHITE);
                break;
            case DISABLED_SQUARE:
                DrawTexture(game_textures.disabled_square, it -> x, it -> y, RAYWHITE);
                break;
            case SHIP:
                DrawTexture(game_textures.ship_texture, it -> x, it -> y, RAYWHITE);
            case PLAYER_SHIP_HIT:
                DrawTexture(game_textures.player_ship_texture_hit, it -> x, it -> y, RAYWHITE);
            default:
                break;
            }
    }
}

void Board::drawLettersAndNumbers()
{
    Color basic_color = BLACK;

    //-----------------------------------------------
    // drawing numbers
    //-----------------------------------------------
    for(int i = 0; i < 10; i++)
    {

        DrawText(TextFormat("%d", i + 1), 160, 255 + i * 50, 40, basic_color);
    }

    for(int i = 0; i < 10; i++)
    {

        DrawText(TextFormat("%d", i + 1), 860, 255 + i * 50, 40, basic_color);
    }


    //-----------------------------------------------
    // drawing letters
    //-----------------------------------------------
     for(int i = 0; i < 10; i++)
    {

        DrawText(TextFormat("%c", 64 + i + 1), 210 + i * 50, 210, 40, basic_color);
    }

     for(int i = 0; i < 10; i++)
    {

        DrawText(TextFormat("%c", 64 + i + 1), 910 + i * 50, 210, 40, basic_color);
    }
}

void Board::drawBoardsLabels(Textures game_textures, Font font)
{
    Vector2 player_board_label, computer_board_label;
    player_board_label = {305, 790};
    computer_board_label = {990, 790};
    Color color = BLACK;

    DrawTexture(game_textures.board_label, 250, 760, RAYWHITE);
    DrawTextEx(font, "PLAYER  BOARD", player_board_label, 36, 2, color);

    DrawTexture(game_textures.board_label, 950, 760, RAYWHITE);
    DrawTextEx(font, "COMPUTER  BOARD", computer_board_label, 36, 1, color);
}

void Board::disableSquaresAroundShip(Rectangle rec, Board gameBoard[][BOARD_SIZE])
{
    //----------------------------------------------------------------------------------
    // If we destroyed the ship, we disable squares around it
    //----------------------------------------------------------------------------------
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(CheckCollisionRecs(rec, gameBoard[i][j].square_collision_model) && gameBoard[i][j].id != TRANSPARENT_SQUARE)
                gameBoard[i][j].id = DISABLED_SQUARE;
        }
}


