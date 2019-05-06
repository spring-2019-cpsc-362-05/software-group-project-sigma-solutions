#include "StaticVars.h"
#include "Card.h"
#include "Game.h"
#include "mainmenu.h"

#include <QStateMachine>
#include <QEventTransition>
#include <QPropertyAnimation>

//Game* game;
int main(int argc, char* argv[]) {

    QApplication a(argc, argv);
    mainMenu * menu = new mainMenu();
    menu->show();

//    game = new Game();
//    int numDecks = 4,
//        active = 127,
//        control = 85,
//        strategy = 1;
//    //Brandon's Menu Stuff
//    game->show();
//    game->start(numDecks, active, control, strategy);
//    game->run();

    return a.exec();
}
