#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <bitset>

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
    unsigned long getPlayersActive();
    unsigned long getPlayersUserControlled();
    int getNumberOfDecks();
    int getStartBank();
    int getMinimumBet();

private slots:
    //UserControlled States
    void on_player1UC_stateChanged(int arg1);
    void on_player2UC_stateChanged(int arg1);
    void on_player3UC_stateChanged(int arg1);
    void on_player4UC_stateChanged(int arg1);
    void on_player5UC_stateChanged(int arg1);
    void on_player6UC_stateChanged(int arg1);

    //Active States
    void on_player1Active_stateChanged(int arg1);
    void on_player2Active_stateChanged(int arg1);
    void on_player3Active_stateChanged(int arg1);
    void on_player4Active_stateChanged(int arg1);
    void on_player5Active_stateChanged(int arg1);
    void on_player6Active_stateChanged(int arg1);

    //Game Options
    void on_numberOfDecksSpinBox_valueChanged(int arg1);
    void on_startingBankSpinBox_valueChanged(int arg1);
    void on_minimumBetSpinBox_valueChanged(int arg1);

    //Ok Box
    void on_buttonBox_accepted();

private:
    Ui::mainMenu *ui;
    std::bitset<6> _playersActive = 000000;
    std::bitset<6> _playersUserControlled = 000000;

    //Store player states
    struct player {
        int active, userControlled = false;
    } _player[6];

    //Store Game Option
    int _numberOfDecks, _startBank, _minBet;
};

#endif // MAINMENU_H
