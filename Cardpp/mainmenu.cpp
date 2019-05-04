#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "game.h"
#include <QObject>
#include <QString>
#include <QDebug>

Game * game;

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent), ui(new Ui::mainMenu) { ui->setupUi(this); }

mainMenu::~mainMenu() { delete ui; }

void mainMenu::on_buttonBox_accepted()
{
    game = new Game();
    game->show();
}

//UserControlled States
void mainMenu::on_player1UC_stateChanged(int arg1) { _player[0].userControlled = arg1;    qDebug() << "Player1UC: " << arg1;   }
void mainMenu::on_player2UC_stateChanged(int arg1) { _player[1].userControlled = arg1;    qDebug() << "Player2UC: " << arg1;   }
void mainMenu::on_player3UC_stateChanged(int arg1) { _player[2].userControlled = arg1;    qDebug() << "Player3UC: " << arg1;   }
void mainMenu::on_player4UC_stateChanged(int arg1) { _player[3].userControlled = arg1;    qDebug() << "Player4UC: " << arg1;   }
void mainMenu::on_player5UC_stateChanged(int arg1) { _player[4].userControlled = arg1;    qDebug() << "Player5UC: " << arg1;   }
void mainMenu::on_player6UC_stateChanged(int arg1) { _player[5].userControlled = arg1;    qDebug() << "Player6UC: " << arg1;   }

//Active States
void mainMenu::on_player1Active_stateChanged(int arg1) { _player[0].active = arg1;        qDebug() << "Player1A: " << arg1;   }
void mainMenu::on_player2Active_stateChanged(int arg1) { _player[1].active = arg1;        qDebug() << "Player2A: " << arg1;   }
void mainMenu::on_player3Active_stateChanged(int arg1) { _player[2].active = arg1;        qDebug() << "Player3A: " << arg1;   }
void mainMenu::on_player4Active_stateChanged(int arg1) { _player[3].active = arg1;        qDebug() << "Player4A: " << arg1;   }
void mainMenu::on_player5Active_stateChanged(int arg1) { _player[4].active = arg1;        qDebug() << "Player5A: " << arg1;   }
void mainMenu::on_player6Active_stateChanged(int arg1) { _player[5].active = arg1;        qDebug() << "Player6A: " << arg1;   }

//Game Options
void mainMenu::on_numberOfDecksSpinBox_valueChanged(int arg1) { _numberOfDecks = arg1;         qDebug() << "Decks: " << arg1;}
void mainMenu::on_startingBankSpinBox_valueChanged(int arg1) { _startBank = arg1;       qDebug() << "startBank: " << arg1;}
void mainMenu::on_minimumBetSpinBox_valueChanged(int arg1) { _minBet = arg1;            qDebug() << "MinBet: " << arg1;}

//Getter Functions
int mainMenu::getNumberOfDecks(){ return _numberOfDecks; }
int mainMenu::getStartBank(){ return _startBank; }
int mainMenu::getMinimumBet(){ return _minBet; }

unsigned long mainMenu::getPlayersActive() {
    for(size_t i = 0; i < 6; i++) {
        if(_player[i].active == 1)
            _playersActive.set(i,1);
    }
    return _playersActive.to_ulong();
}

unsigned long mainMenu::getPlayersUserControlled() {
    for(size_t i = 0; i < 6; i++) {
        if(_player[i].userControlled == 1)
            _playersUserControlled.set(i,1);
    }
    return _playersUserControlled.to_ulong();
}


