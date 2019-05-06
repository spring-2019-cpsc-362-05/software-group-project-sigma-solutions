#include "DecisionButton.h"

DecisionButton::DecisionButton(QGraphicsItem* parent) : QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/graphics/other/button").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
    buttonChar = '\0';
}


DecisionButton::DecisionButton(char c, QGraphicsItem* parent) : QGraphicsPixmapItem(parent){
    buttonChar = c;
    if(buttonChar =='H' || buttonChar == 'h'){
        setPixmap(QPixmap(":/graphics/other/hitButton.png").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[0], BUTTON_YPOS);
    }
    else if(buttonChar =='S' || buttonChar == 's'){
        setPixmap(QPixmap(":/graphics/other/standButton.png").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[1], BUTTON_YPOS);
    }
    else if(buttonChar =='d' || buttonChar == 'D'){
        setPixmap(QPixmap(":/graphics/other/ddButton.png").scaled(B_WIDTH*2, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        qDebug() << "Creating DD button";
        setPos(BUTTON_XPOS[2], BUTTON_YPOS);
    }
    else if(buttonChar =='p' || buttonChar == 'P'){
        setPixmap(QPixmap(":/graphics/other/splitButton.png").scaled(B_WIDTH, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[3], BUTTON_YPOS);
    }
    else if(buttonChar =='b' || buttonChar == 'b'){
        setPixmap(QPixmap(":/graphics/other/betButton.png").scaled(B_WIDTH*2, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[4], BUTTON_YPOS);
    }
    else if(buttonChar =='i' || buttonChar == 'I'){
        setPixmap(QPixmap(":/graphics/other/incrementButton.png").scaled(B_WIDTH/2, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[4]-B_WIDTH/2, BUTTON_YPOS);
    }
    else if(buttonChar =='m' || buttonChar == 'M'){
        setPixmap(QPixmap(":/graphics/other/decrementButton.png").scaled(B_WIDTH/2, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
        setPos(BUTTON_XPOS[4]+2*B_WIDTH, BUTTON_YPOS);
    }
    setAcceptHoverEvents(true);
}


void DecisionButton::mousePressEvent(QGraphicsSceneMouseEvent* event){
    emit clicked();
}

void DecisionButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    QString str = QString("");
    int width = B_WIDTH;
    if(buttonChar == 'h' || buttonChar == 'H'){
        str = QString(":/graphics/other/hitButtonHover.png");
    }
    else if(buttonChar == 's' || buttonChar == 'S'){
        str = QString(":/graphics/other/standButtonHover.png");
    }
    else if(buttonChar == 'd' || buttonChar == 'D'){
        str = QString(":/graphics/other/ddButtonHover.png");
        width *= 2;
    }
    else if(buttonChar == 'p' || buttonChar == 'P'){
        str = QString(":/graphics/other/splitButtonHover.png");
    }
    else if(buttonChar == 'i' || buttonChar == 'I'){
        str = QString(":/graphics/other/incrementButtonHover.png");
        width /= 2;
    }
    else if(buttonChar == 'm' || buttonChar == 'M'){
        str = QString(":/graphics/other/decrementButtonHover.png");
        width /= 2;
    }
    else if(buttonChar == 'b' || buttonChar == 'b'){
        str = QString(":/graphics/other/betButtonHover.png");
        width *= 2;
    }

    setPixmap(QPixmap(str).scaled(width, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}

void DecisionButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    QString str = QString("");
    int width = B_WIDTH;
    if(buttonChar == 'h' || buttonChar == 'H'){
        str = QString(":/graphics/other/hitButton.png");
    }
    else if(buttonChar == 's' || buttonChar == 'S'){
        str = QString(":/graphics/other/standButton.png");
    }
    else if(buttonChar == 'd' || buttonChar == 'D'){
        str = QString(":/graphics/other/ddButton.png");
        width *= 2;
    }
    else if(buttonChar == 'p' || buttonChar == 'P'){
        str = QString(":/graphics/other/splitButton.png");
    }
    else if(buttonChar == 'i' || buttonChar == 'I'){
        str = QString(":/graphics/other/incrementButton.png");
        width /= 2;
    }
    else if(buttonChar == 'm' || buttonChar == 'M'){
        str = QString(":/graphics/other/decrementButton.png");
        width /= 2;
    }
    else if(buttonChar == 'b' || buttonChar == 'b'){
        str = QString(":/graphics/other/betButton.png");
        width *= 2;
    }


    setPixmap(QPixmap(str).scaled(width, B_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}
