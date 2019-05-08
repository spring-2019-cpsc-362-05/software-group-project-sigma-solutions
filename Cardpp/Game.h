#ifndef GAME_H
#define GAME_H

#include "StaticVars.h"
#include "Card.h"
#include "Table.h"
#include "Shoe.h"
#include "Hand.h"
#include "Player.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent = nullptr);
    void start();
    void placeBets();
    void initDeal();

    bool makeDecision();
    void playRound();
    void playerTurn();
    void userTurn();
    void computerTurn();

    void wait(int msec);


    void run();
    bool dealerBJ();

    //variables
    QGraphicsScene* scene;
    Table* table;
    Shoe* shoe;
    Player* action;
    Hand* currentHand;
    int active;
    int control;
    int numDecks;
    int strategy;


    int minBet;
    double startBank;

    bool betPlaced;
    int userBet;
    char userDecision;

    QEventLoop* pause;

/*
    QStateMachine* machine;
    void buildMachine();
*/


};

#endif // GAME_H
