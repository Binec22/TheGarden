#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "seller.h"
#include "arrow.h"

class Game
{
public:
    Game();
    void run();

private:
    RenderWindow window;
    View view;
    Input input;
    Player player;
    Seller seller;
    Break breaking;
    Utilitaire utilitaire;
    Calque calque1;
    Calque calque2;
    Calque calque3;
    Calque calque4;
    Clock gameClock;
    Arrow arrow;

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1440;
};

#endif