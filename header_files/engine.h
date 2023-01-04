#ifndef engine_h
#define engine_h

#define SQUARE_BASIC_SIZE 50
#define BOARD_SIZE 10

#include "raylib.h"
#include "textures.h"
#include "gamemusic.h"

//---------------------------------------------------------------
// Declaration of global variables
//---------------------------------------------------------------
/**@brief
* Zmienna globalna okreslajaca tryb gry
**/
extern int GAMEMODE;
/**@brief
* Zmienna globalna okreslajaca punkty komputera
**/
extern int COMPUTER_POINTS;
/**@brief
* Zmienna globalna okreslajaca punkty gracza
**/
extern int PLAYER_POINTS;
/**@brief
* Zmienna globalna okreslajaca kolejnosc tur
**/
extern int WHOSE_TURN;
/**@brief
* Zmienna globalna sprawdzajaca, czy gra powinna byc zrestartowana
**/
extern bool SHOULD_GAME_BE_RESTARTED;
/**@brief
* Zmienna globalna sprawdzajaca, czy muzyka powinna zostac odtworzona
**/
extern bool SHOULD_MUSIC_PLAY;





//---------------------------------------------------------------
// Numeric types
//---------------------------------------------------------------

enum ID
{
    EMPTY_SQUARE = 0,
    LIGHTEN_SQUARE,
    TRANSPARENT_SQUARE,
    DISABLED_SQUARE,
    SHIP,
    PLAYER_SHIP_HIT,
    HORISONTAL,
    VERTICAL
};

enum PLAYERS {PLAYER, COMPUTER};
enum gamemode {BEGIN_MODE, PLAY_MODE, DEBUG_MODE};

class Engine
{
public:

};

void checkWinOrLose(Font font);
void drawScore(Textures game_textures);
void drawMessageBox(Textures game_textures, Font font, double &timer, int &computer_thinking_time);

#endif // engine_h
