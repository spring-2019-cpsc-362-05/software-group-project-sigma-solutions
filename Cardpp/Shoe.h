#ifndef SHOE_H
#define SHOE_H

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

#include "Card.h"
#include "Player.h"
#include "StaticVars.h"



class Shoe : public QGraphicsRectItem
{
public:
	Shoe();
	Shoe(int decks);
	//Fill a shoe with a number of the same card
    Shoe(Card* card, int num);
	~Shoe();
    size_t getSize() const;
	void print() const;
	void printCounts() const;
	int getRunningCount() const;
	int getTrueCount() const;

    void addCard(size_t index, size_t suit);
	void shuffle(int times);
    Card* deal();
    Card* dealHidden();
    void updateCounts(Card* c);

private:
    std::vector<Card*> cards;
	int runningCount;
	int trueCount;
};

#endif //SHOE_H
