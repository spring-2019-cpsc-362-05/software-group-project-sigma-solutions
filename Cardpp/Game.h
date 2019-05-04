#ifndef GAME_H
#define GAME_H

#include "StaticVars.h"
#include "Card.h"
#include "Table.h"
#include "Shoe.h"
#include "Hand.h"
#include "Player.h"

class Game
{
public:
    Game();
    QGraphicsScene* scene;
    MainWindow* w;
    QGraphicsView* view;

    void run();

};

#endif // GAME_H
