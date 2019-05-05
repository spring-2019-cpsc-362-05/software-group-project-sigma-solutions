#include "DecisionButton.h"

DecisionButton::DecisionButton(QGraphicsItem* parent) : QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/graphics/other/button").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}


DecisionButton::DecisionButton(char c, QGraphicsItem* parent) : QGraphicsPixmapItem(parent){
    buttonText = new QGraphicsTextItem(parent);
    buttonText->setFont(QFont("Times", 16));
    buttonText->setDefaultTextColor(Qt::white);
    buttonText->setPos(0,0);
    setPixmap(QPixmap(":/graphics/other/button").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));

    if(c =='H' || c == 'h'){
        buttonText->setPlainText(QString("Hit"));
        buttonText->setZValue(1);
        qDebug() << "Creating hit button";
        setPos(BUTTON_XPOS[0], BUTTON_YPOS);
        buttonText->setPos(BUTTON_XPOS[0] + B_WIDTH/2 - buttonText->boundingRect().width()/2,
                BUTTON_YPOS + B_HEIGHT/2 - buttonText->boundingRect().height()/2);
    }
    else if(c =='S' || c == 's'){
        buttonText->setPlainText("Stand");
        buttonText->setZValue(1);
        qDebug() << "Creating stand button";
        setPos(BUTTON_XPOS[1], BUTTON_YPOS);
        buttonText->setPos(BUTTON_XPOS[1] + B_WIDTH/2 - buttonText->boundingRect().width()/2,
                BUTTON_YPOS + B_HEIGHT/2 - buttonText->boundingRect().height()/2);
    }
    else if(c =='d' || c == 'D'){
        setPixmap(QPixmap(":/graphics/other/button").scaled(B_WIDTH*2, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        buttonText->setPlainText(QString("Double Down"));
        buttonText->setZValue(1);
        qDebug() << "Creating DD button";
        setPos(BUTTON_XPOS[2], BUTTON_YPOS);
        buttonText->setPos(BUTTON_XPOS[2] + B_WIDTH - buttonText->boundingRect().width()/2,
                BUTTON_YPOS + B_HEIGHT/2 - buttonText->boundingRect().height()/2);
    }
    else if(c =='p' || c == 'P'){
        buttonText->setPlainText(QString("Split"));
        buttonText->setZValue(1);
        qDebug() << "Creating split button";
        setPos(BUTTON_XPOS[3], BUTTON_YPOS);
        buttonText->setPos(BUTTON_XPOS[3] + B_WIDTH/2 - buttonText->boundingRect().width()/2,
                BUTTON_YPOS + B_HEIGHT/2 - buttonText->boundingRect().height()/2);
    }

    setAcceptHoverEvents(true);

}


void DecisionButton::mousePressEvent(QGraphicsSceneMouseEvent* event){
    emit clicked();
}

void DecisionButton::mouseHoverEnterEvent(QGraphicsSceneHoverEvent* event){
    buttonText->setDefaultTextColor(Qt::red);
}

void DecisionButton::mouseHoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    buttonText->setDefaultTextColor(Qt::white);
}
