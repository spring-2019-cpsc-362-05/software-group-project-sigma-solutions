#ifndef CARD_H
#define CARD_H

#include "StaticVars.h"

class Card :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Card(QGraphicsItem* parent = nullptr);
    Card(const Card& _card);
    Card(Card* card);
    Card(size_t _index, size_t _suit);
    Card operator=(const Card& _card);
    size_t getIndex() const;
    size_t getSuit() const;
    int getValue() const;
    int getCountValue() const;
    bool isHidden() const;
    void hideCard();
    void showCard();
    bool setAceSoft();
    void print() const;
    void draw(QGraphicsScene* _scene);

    QString getCardImageFileName();
    void addToScene(QGraphicsScene* scene);

private:
    //2-10 for number cards. Face Cards: A = 1, J = 11, Q = 12, K = 13
    size_t index;
    // 0 = Spades, 1 = Hearts, 2 = Diamonds, 3 = Clubs
    size_t suit;
    //face value for number cards, 10 for J-K, default 11 for A
    int value;
    //used for the Dealer's hole card
    bool hidden;

    int getValue(size_t index) const;
};


#endif // CARD_H
