#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "game.h"

Game * game;

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_buttonBox_accepted()
{
    game = new Game();
    game->show();
}
