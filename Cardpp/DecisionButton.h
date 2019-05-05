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
    void mouseHoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void mouseHoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:
    void clicked();
private:
    QGraphicsTextItem* buttonText;

};

#endif // DECISIONBUTTON_H
