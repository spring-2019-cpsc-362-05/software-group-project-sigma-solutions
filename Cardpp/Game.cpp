#include "Game.h"

Game::Game()
{
    scene = new QGraphicsScene();
    w = new MainWindow();
    view = new QGraphicsView();
}


void Game::run(){
    w->resize(W_WIDTH,W_HEIGHT);

    int numDecks = 2;

    qDebug("Creating Shoe.");
    Shoe* shoe = new Shoe(numDecks);
    qDebug("Shoe successfully created.");
    //shoe->shuffle(3);
    qDebug("Shoe successfully shuffled.");
    size_t remainingCards = shoe->getSize();
    qDebug() << "Shoe has " << remainingCards << " cards.";
    //active(1-127), control(0-127), strategy(0-127)
    Table* table = new Table(shoe, 127, 0, 127);
    size_t numPlaying = table->getNumPlaying();
    qDebug() << "Table has " << numPlaying << " players.";

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


 //   table->initDeal();
 //   table->draw(scene);

    view->setScene(scene);
    view->setFixedSize(W_WIDTH, W_HEIGHT);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,W_WIDTH,W_HEIGHT);


    w->setCentralWidget(view);
    w->show();
}
