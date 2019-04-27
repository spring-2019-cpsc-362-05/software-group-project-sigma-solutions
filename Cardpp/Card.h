#pragma once
#include <iostream>
#include <vector>
#include <string>

static const std::vector<std::string> INDEX_STRS =
	{ "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
static const std::vector<std::string> SUIT_STRS =
	{ "Spades  ", "Hearts  ", "Diamonds", "Clubs   " };

class Card
{
public:
	Card();
	Card(int _index, int _suit);
	~Card();
	int getIndex() const;
	int getValue() const;
	int getSuit() const;
	int getCountValue() const;
	bool isHidden() const;
	void hideCard();
	void showCard();
	bool setAceSoft();
	void print() const;
private:
	//2-10 for number cards. Face Cards: A = 1, J = 11, Q = 12, K = 13
	int index;
	// 0 = Spades, 1 = Hearts, 2 = Diamonds, 3 = Clubs
	int suit;
	//face value for number cards, 10 for J-K, default 11 for A
	int value;
	//used for the Dealer's hole card
	bool hidden;

	int getValue(int index) const;
};

