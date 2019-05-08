#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <bitset>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include "Game.h"

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();

    //Getter functions
    int getPlayersActive();
    int getPlayersUserControlled();
    int getNumberOfDecks();
    int getStartBank();
    int getMinimumBet();

    //returns true if at least 1 active player
    bool checkActive();

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

    //Start Button
    void on_startButton_clicked();

private:
    Ui::mainMenu *ui;
    std::bitset<7> _playersActive = 000001;
    std::bitset<7> _playersUserControlled = 000001;

    //Store player states
    struct player {
        int active, userControlled = false;
    } _player[7];

    //Store Game Option
    int _numberOfDecks = 4, _startBank = 1000, _minBet = 5;
};

#endif // MAINMENU_H
