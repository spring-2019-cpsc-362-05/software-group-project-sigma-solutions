#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

#include "Card.h"
#include "Player.h"

static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(75, 125);

class Shoe
{
public:
	Shoe();
	Shoe(int decks);
	//Fill a shoe with a number of the same card
	Shoe(Card card, int num);
	~Shoe();
	size_t getSize() const;
	void print() const;
	void printCounts() const;
	int getRunningCount() const;
	int getTrueCount() const;

	void addCard(int index, int suit);
	void shuffle(int times);
	Card deal();
	Card dealHidden();
	void updateCounts(Card c);
private:
	std::vector<Card> cards;
	int runningCount;
	int trueCount;
};

