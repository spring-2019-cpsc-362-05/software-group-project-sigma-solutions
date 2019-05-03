#include "game.h"

Game::Game(QWidget *parent) {
    
    
    //GRAPHICS
    //Create Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,600);
    setBackgroundBrush(QBrush(QImage(":/images/table.png")));
    
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,600);
    
    card = new Card();
    card->setPos(x()+150,y()+150);
    
    //add item to scene
    scene->addItem(card);
    
    show();
}
