#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include "Card.h"

static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(15, 30);

class Shoe
{
public:
	Shoe();
	Shoe(int decks);
	~Shoe();
	size_t getSize() const;
	void print() const;


	void addCard(int index, int suit);
	void shuffle(int times);
	Card deal();
	Card dealHidden();
private:
	std::vector<Card> cards;
};

