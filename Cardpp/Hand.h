#pragma once
#include <vector>

#include "Card.h"

class Hand
{
public:
	Hand();
	~Hand();

	void print() const;
	bool canSplit() const;
	bool canDoubleDown() const;
	int getScore() const;
	bool hasBlackjack() const;
	bool isSoft() const;
	size_t size() const;
	int getBet() const;

	bool softenHand();
	bool updateScore(Card card);
	int recalculateScore();
	Hand split();
	void reset();
	void dealCard(Card card);
	void dealHidden(Card card);
	void incReceived();

	Card& operator[](size_t i);
	const Card& operator[](size_t i) const;
	void addBet(int _bet);

private:
	std::vector<Card> cards;
	int score;
	int received;
	int bet;
};

