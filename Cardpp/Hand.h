#pragma once
#include <vector>

#include "Card.h"
#include "StaticVars.h"

class Hand :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Hand(QGraphicsPixmapItem* parent);
    Hand(const Hand& _hand);
    Hand(size_t _index);
	~Hand();

    void draw(QGraphicsScene* _scene);

	void print() const;
	bool canSplit() const;
	bool canDoubleDown() const;
	int getScore() const;
	bool hasBlackjack() const;
	bool isSoft() const;
    size_t size() const;
	int getBet() const;

	bool softenHand();
    bool updateScore(Card* card);
	int recalculateScore();
    Hand* split();
	void reset();
    void dealCard(Card* card);
    void dealHidden(Card* card);
	void incReceived();
    void setIndex(size_t index);

    Card* getCard(size_t i);
    void setCard(size_t i, Card* _card);
    void addBet(int _bet);


private:
    std::vector<Card*> cards;
	int score;
	int received;
	int bet;
    size_t handIndex;
};

