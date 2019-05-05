#ifndef INGAMEMENU_H
#define INGAMEMENU_H

#include <QDialog>
#include <bitset>
#include "game.h"
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class inGameMenu;
}

class inGameMenu : public QDialog
{
    Q_OBJECT

public:
    explicit inGameMenu(QWidget *parent = nullptr);
    ~inGameMenu();

    //Getter functions
    unsigned long getPlayersActive();
    unsigned long getPlayersUserControlled();
    int getNumberOfDecks();
    int getStartBank();
    int getMinimumBet();

private slots:
    //Active States
    void on_player1Active_stateChanged(int arg1);
    void on_player2Active_stateChanged(int arg1);
    void on_player3Active_stateChanged(int arg1);
    void on_player4Active_stateChanged(int arg1);
    void on_player5Active_stateChanged(int arg1);
    void on_player6Active_stateChanged(int arg1);
    void on_player7Active_stateChanged(int arg1);

    //UserControlled States
    void on_player1UC_stateChanged(int arg1);
    void on_player2UC_stateChanged(int arg1);
    void on_player3UC_stateChanged(int arg1);
    void on_player4UC_stateChanged(int arg1);
    void on_player5UC_stateChanged(int arg1);
    void on_player6UC_stateChanged(int arg1);
    void on_player7UC_stateChanged(int arg1);

    //Game Options
    void on_numberOfDecksSpinBox_valueChanged(int arg1);
    void on_startingBankSpinBox_valueChanged(int arg1);
    void on_minimumBetSpinBox_valueChanged(int arg1);

    //Buttons
    void on_exitGameButton_clicked();
    void on_closeMenuButton_clicked();
    void on_startNewGameButton_clicked();

private:
    Ui::inGameMenu *ui;
    std::bitset<7> _playersActive = 000000;
    std::bitset<7> _playersUserControlled = 000000;
    bool _playerIsActive = false;
    //Store player states in struct arry of 7
    struct player {
        int active, userControlled = false;
    } _player[7];

    //Store Game Option
    int _numberOfDecks, _startBank, _minBet;
};

#endif // INGAMEMENU_H
