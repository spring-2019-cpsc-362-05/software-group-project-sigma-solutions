#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "Game.h"

extern Game* game;

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent), ui(new Ui::mainMenu) { ui->setupUi(this); }

mainMenu::~mainMenu() { delete ui; }

void mainMenu::on_startButton_clicked()
{
    qDebug() << "Active: " << game->active;
    qDebug() << "Controlled: " << game->control;
    qDebug() << "numDecks: " << game->numDecks;
    qDebug() << "Starting Bank: $" << game->startBank;
    qDebug() << "Minimum Bet: $" << game->minBet;

    game->active = getPlayersActive();
    game->control = getPlayersUserControlled();
    game->numDecks = getNumberOfDecks();
    game->startBank = getStartBank();
    game->minBet = getMinimumBet();

    qDebug() << "Active: " << game->active;
    qDebug() << "Controlled: " << game->control;
    qDebug() << "numDecks: " << game->numDecks;
    qDebug() << "Starting Bank: $" << game->startBank;
    qDebug() << "Minimum Bet: $" << game->minBet;

    if (checkActive())
    {
        game->show();
        game->start();
        game->run();
        close(); //close menu window

    } else {
        QMessageBox::information(this, tr("Invalid Options"), tr("Activate at least 1 player to start."), QMessageBox::Ok);
    }
}

//Active States
void mainMenu::on_player1Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player1UC->setEnabled(true); }
    else {
        ui->player1UC->setEnabled(false);
        ui->player1UC->setChecked(false);
    }
    _player[0].active = arg1;
}

void mainMenu::on_player2Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player2UC->setEnabled(true); }
    else {
        ui->player2UC->setEnabled(false);
        ui->player2UC->setChecked(false);
    }
    _player[1].active = arg1;

}

void mainMenu::on_player3Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player3UC->setEnabled(true); }
    else {
        ui->player3UC->setEnabled(false);
        ui->player3UC->setChecked(false);
    }
    _player[2].active = arg1;

}

void mainMenu::on_player4Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player4UC->setEnabled(true); }
    else {
        ui->player4UC->setEnabled(false);
        ui->player4UC->setChecked(false);
    }
    _player[3].active = arg1;
}

void mainMenu::on_player5Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player5UC->setEnabled(true); }
    else {
        ui->player5UC->setEnabled(false);
        ui->player5UC->setChecked(false);
    }
    _player[4].active = arg1;
}

void mainMenu::on_player6Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player6UC->setEnabled(true); }
    else {
        ui->player6UC->setEnabled(false);
        ui->player6UC->setChecked(false);
    }
    _player[5].active = arg1;
}
void mainMenu::on_player7Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player7UC->setEnabled(true); }
    else {
        ui->player7UC->setEnabled(false);
        ui->player7UC->setChecked(false);
    }
    _player[6].active = arg1;
}

//UserControlled States
void mainMenu::on_player1UC_stateChanged(int arg1) { _player[0].userControlled = arg1; }
void mainMenu::on_player2UC_stateChanged(int arg1) { _player[1].userControlled = arg1; }
void mainMenu::on_player3UC_stateChanged(int arg1) { _player[2].userControlled = arg1; }
void mainMenu::on_player4UC_stateChanged(int arg1) { _player[3].userControlled = arg1; }
void mainMenu::on_player5UC_stateChanged(int arg1) { _player[4].userControlled = arg1; }
void mainMenu::on_player6UC_stateChanged(int arg1) { _player[5].userControlled = arg1; }
void mainMenu::on_player7UC_stateChanged(int arg1) { _player[6].userControlled = arg1; }

//Game Options
void mainMenu::on_numberOfDecksSpinBox_valueChanged(int arg1) { _numberOfDecks = arg1; }
void mainMenu::on_startingBankSpinBox_valueChanged(int arg1){
    _startBank = arg1;
    int betMax = arg1 / 10 - ((arg1 / 10) % 5);
    ui->minimumBetSpinBox->setRange(5, betMax);
}

void mainMenu::on_minimumBetSpinBox_valueChanged(int arg1) { _minBet = arg1; }

//Getter Functions
int mainMenu::getNumberOfDecks(){ return _numberOfDecks; }
int mainMenu::getStartBank(){ return _startBank; }
int mainMenu::getMinimumBet(){ return _minBet; }
int mainMenu::getPlayersActive() {
    for(size_t i = 0; i < 7; i++) {
        if(_player[i].active == 2) {
            _playersActive.set(i,1);
        }
    }
    return int(_playersActive.to_ulong());
}
int mainMenu::getPlayersUserControlled() {
    for(size_t i = 0; i < 7; i++) {
        if(_player[i].userControlled == 2)
            _playersUserControlled.set(i,1);
    }
    return int(_playersUserControlled.to_ulong());
}


//returns true if at least 1 active player
bool mainMenu::checkActive(){
    return (_playersActive.to_ulong() != 0);
}
