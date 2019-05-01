#include "game.h"

Game::Game(QWidget *parent) {

    //Create Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1200,600);
    setBackgroundBrush(QBrush(QImage(":/images/table.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,600);

    //Create item to put in scene
    rect = new MyRect();
    rect->setRect(0,0,100,100);  //set width x height

    card = new Card();
    card->setPos(x()+150,y()+150);

    //add item to scene
    scene->addItem(rect);
    scene->addItem(card);

    //make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();


    show();
}
