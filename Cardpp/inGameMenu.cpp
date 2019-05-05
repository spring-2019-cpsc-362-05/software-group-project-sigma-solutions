#include "inGameMenu.h"
#include "ui_inGameMenu.h"

Game * resetGame;

inGameMenu::inGameMenu(QWidget *parent) :
    QDialog(parent), ui(new Ui::inGameMenu) { ui->setupUi(this); }

inGameMenu::~inGameMenu() { delete ui; }

void inGameMenu::on_startNewGameButton_clicked()
{
    //TODO: Quit old game or Reset all variables

    //pass bitwise variables a, uc to new Table()
    ulong a, uc;
    a = getPlayersActive();
    uc = getPlayersUserControlled();

    if (_playerIsActive2)
    {
        QMessageBox::StandardButton prompt;
        prompt = QMessageBox::question(this, "New Game?",
                 "Are you sure you want to start a new game?  All previous progress will be lost.",
                 QMessageBox::Yes|QMessageBox::No);

        if (prompt == QMessageBox::Yes)
        {
              resetGame = new Game();
              resetGame->show();
        }
        close();
    } else
        QMessageBox::information(this, tr("Invalid Options"), tr("Activate at least 1 player to start."), QMessageBox::Ok);
}


//Active States
void inGameMenu::on_player1Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player1UC->setEnabled(true); }
    else {
        ui->player1UC->setEnabled(false);
        ui->player1UC->setChecked(false);
    }
    _player[0].active = arg1;
    qDebug() << "Player1A: " << arg1;
}
void inGameMenu::on_player2Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player2UC->setEnabled(true); }
    else {
        ui->player2UC->setEnabled(false);
        ui->player2UC->setChecked(false);
    }
    _player[1].active = arg1;
    qDebug() << "Player2A: " << arg1;
}
void inGameMenu::on_player3Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player3UC->setEnabled(true); }
    else {
        ui->player3UC->setEnabled(false);
        ui->player3UC->setChecked(false);
    }
    _player[2].active = arg1;
    qDebug() << "Player3A: " << arg1;
}
void inGameMenu::on_player4Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player4UC->setEnabled(true); }
    else {
        ui->player4UC->setEnabled(false);
        ui->player4UC->setChecked(false);
    }
    _player[3].active = arg1;
    qDebug() << "Player4A: " << arg1;
}
void inGameMenu::on_player5Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player5UC->setEnabled(true); }
    else {
        ui->player5UC->setEnabled(false);
        ui->player5UC->setChecked(false);
    }
    _player[4].active = arg1;
    qDebug() << "Player5A: " << arg1;
}
void inGameMenu::on_player6Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player6UC->setEnabled(true); }
    else {
        ui->player6UC->setEnabled(false);
        ui->player6UC->setChecked(false);
    }
    _player[5].active = arg1;
    qDebug() << "Player6A: " << arg1;
}
void inGameMenu::on_player7Active_stateChanged(int arg1) {
    if (arg1 == 2) { ui->player7UC->setEnabled(true); }
    else {
        ui->player7UC->setEnabled(false);
        ui->player7UC->setChecked(false);
    }
    _player[6].active = arg1;
    qDebug() << "Player7A: " << arg1;
}

//UserControlled States
void inGameMenu::on_player1UC_stateChanged(int arg1) { _player[0].userControlled = arg1;    qDebug() << "Player1UC: " << arg1;   }
void inGameMenu::on_player2UC_stateChanged(int arg1) { _player[1].userControlled = arg1;    qDebug() << "Player2UC: " << arg1;   }
void inGameMenu::on_player3UC_stateChanged(int arg1) { _player[2].userControlled = arg1;    qDebug() << "Player3UC: " << arg1;   }
void inGameMenu::on_player4UC_stateChanged(int arg1) { _player[3].userControlled = arg1;    qDebug() << "Player4UC: " << arg1;   }
void inGameMenu::on_player5UC_stateChanged(int arg1) { _player[4].userControlled = arg1;    qDebug() << "Player5UC: " << arg1;   }
void inGameMenu::on_player6UC_stateChanged(int arg1) { _player[5].userControlled = arg1;    qDebug() << "Player6UC: " << arg1;   }
void inGameMenu::on_player7UC_stateChanged(int arg1) { _player[6].userControlled = arg1;    qDebug() << "Player7UC: " << arg1;   }

//Game Options
void inGameMenu::on_numberOfDecksSpinBox_valueChanged(int arg1) { _numberOfDecks = arg1;    qDebug() << "Decks: " << arg1;}
void inGameMenu::on_startingBankSpinBox_valueChanged(int arg1) { _startBank = arg1;         qDebug() << "startBank: " << arg1;}
void inGameMenu::on_minimumBetSpinBox_valueChanged(int arg1) { _minBet = arg1;              qDebug() << "MinBet: " << arg1;}

//Getter Functions
int inGameMenu::getNumberOfDecks(){ return _numberOfDecks; }
int inGameMenu::getStartBank(){ return _startBank; }
int inGameMenu::getMinimumBet(){ return _minBet; }

unsigned long inGameMenu::getPlayersActive() {
    for(size_t i = 0; i < 7    ; i++) {
        if(_player[i].active == 2) {
            _playersActive.set(i,1);
            _playerIsActive2 = true;
        }
    }
    qDebug() << "_playersActiveBitset = " << _playersActive.to_ulong();
    return _playersActive.to_ulong();
}

unsigned long inGameMenu::getPlayersUserControlled() {
    for(size_t i = 0; i < 7; i++) {
        if(_player[i].userControlled == 2)
            _playersUserControlled.set(i,1);
    }
    qDebug() << "_playersUCBitset = " << _playersUserControlled.to_ulong();
    return _playersUserControlled.to_ulong();
}


void inGameMenu::on_exitGameButton_clicked()
{
    QMessageBox::StandardButton prompt;
      prompt = QMessageBox::question(this, "Quit?",
                "Are you sure you want to quit?  All game progress will be lost.",
                QMessageBox::Yes|QMessageBox::No);

      if (prompt == QMessageBox::Yes) QApplication::quit();
}

void inGameMenu::on_closeMenuButton_clicked() { close(); }

