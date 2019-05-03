#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene.h>
#include <QGraphicsView>
#include <QBrush>
#include <QImage>
#include "myrect.h"
#include "playingcard.h"
#include "card.h"

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    Card * card;
};

#endif // GAME_H
