#ifndef DECISIONBUTTON_H
#define DECISIONBUTTON_H

#include "StaticVars.h"

class DecisionButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    DecisionButton(QGraphicsItem* parent = nullptr);

    DecisionButton(char c, QGraphicsItem* parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();
private:
    char buttonChar;

};

#endif // DECISIONBUTTON_H
