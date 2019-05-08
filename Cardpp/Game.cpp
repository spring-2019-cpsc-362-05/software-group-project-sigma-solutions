#include "Game.h"

Game::Game(QWidget* parent) : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(W_WIDTH, W_HEIGHT);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,W_WIDTH, W_HEIGHT);
    setScene(scene);

    active = 1;
    control = 1;
    strategy = 1;
    numDecks = 4;

    shoe = nullptr;
    table = nullptr;
    action = nullptr;
    currentHand = nullptr;

    pause = new QEventLoop();
}

void Game::start(){
    userBet  = minBet;
    betPlaced = false;

    userDecision = '\0';

    shoe = new Shoe(numDecks);
    table = new Table(shoe, active, control, strategy);
    scene->addItem(table);
}

void Game::run(){
    size_t remainingCards = shoe->getSize();
    size_t numPlaying = table->getNumPlaying();
    int cutCard = uni(rng);

    table->activateBettingButtons();
    table->makeConnections();

    while ((static_cast<int>(remainingCards) - (static_cast<int>(numPlaying) + 1) * 3) > cutCard
        && table->getNumPlaying() > 0)
    {
        table->placeBets();
        if (table->getNumPlaying() > 0)
            remainingCards = table->playRound();
    }
        QString endStr;
    if (table->getNumPlaying() > 0) {
         endStr = QString("Only ")+ QString::number(remainingCards - cutCard)
                 + QString(" cards until cut card. Ending game.");
    }
    else
        endStr = QString("Everyone is out of money. Ending game.");

    table->updateMessage(endStr);
}

void Game::wait(int msec){
    qDebug() << "Waiting for " << msec << " miliseconds.";
    QTimer::singleShot(msec, pause, SLOT(quit()));
    pause->exec();

}

/*

void Game::userBetting(){
    QString str = QString("Player ") + QString::number(action->getPosition()) + QString(" place bet.");
    table->mainMessageText->setPlainText(str);
    table->mainMessageText->setPos(W_WIDTH/2 - table->mainMessageText->boundingRect().width()/2,0);
    pause->exec();
    action->takeBet(0, userBet);
    userBet = minBet;
    table->updateBetText();
}

void Game::userDeciding(){
    QString str = QString("RC: ") + QString::number(table->getTrueCount())
            + QString(" TC ") + QString::number(table->getTrueCount())
            + QString(" Player ") + QString::number(action->getPosition());
    //TODO Add recomended action to this string.

    table->mainMessageText->setPlainText(str);
    table->mainMessageText->setPos(W_WIDTH/2 - table->mainMessageText->boundingRect().width()/2,0);
    pause->exec();
    action->takeBet(0, userBet);
    makeDecision(
    table->updateBetText();
}

bool Game::dealerBJ(){
    return table->dealerBJ();
}


void Game::buildMachine(){


    machine = new QStateMachine();
    QState* player = new QState();
    QState* computer = new QState();

    player->addTransition(table->betButton, SIGNAL(clicked()), computer);
    computer->addTransition(table->betButton, SIGNAL(clicked()), player);

    QObject::connect(player, SIGNAL(entered()), table, SLOT(enterPlayerTurn()));
    QObject::connect(player, SIGNAL(exited()), table, SLOT(exitPlayerTurn()));

    machine->addState(player);
    machine->addState(computer);


    machine->setInitialState(player);
    machine->start();
}
*/


/* Deal entire deck
   int xPos = 0,
    yPos = 0;
    std::vector<Card*> cards;
    for(size_t i = 0; i < 52; i ++){
        if(i % 13 == 0){
            xPos = 0;
            yPos += C_HEIGHT+1;
        }
       cards.push_back(new Card(shoe->deal()));
       cards[i]->setPos(xPos, yPos);
       cards[i]->draw(scene);
       xPos += (C_WIDTH+2);
    }
*/
