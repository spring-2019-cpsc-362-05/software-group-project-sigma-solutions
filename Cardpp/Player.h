#pragma once

#include <string>
#include <vector>
#include <iomanip>

#include "Card.h"

#define DEFAULT_BET 100
#define DEFAULT_BANK 1000

class Player
{
public:
	Player();
	Player(std::string playerType, int _position);
	~Player();

	bool isDealer() const;
	bool isControlled() const;
	bool isPlaying() const;
	bool isCounting() const;
	bool hasInsurance() const;
	bool dealerHits() const;
	bool canDoubleDown() const;
	int getPosition() const;
	size_t getHandSize() const;
	int getBank() const;
	int getBet() const;
	int getScore() const;
	bool isSoft() const;
	int getShowing() const;
	bool hasBlackjack() const;
	void takeBet(int bet);

	void print() const;
	void printHand() const;
		
	//resets for next round
	void reset();
	void dealCard(Card card);
	Card showHoleCard();
	void setUserControlled();
	void activate();
	void deactivate();
	void setStrategy(bool _counting);
	void takeInsurance();
	void modBank(double mod);
	void setBet(int _bet);
	void setBank(double _bank);
	
	void dealerCheat();
private:
	//True if player is a dealer
	bool dealer;
	//True if user is controlling player
	bool controlled;
	//True if player at this position is active
	bool playing;
	//True if counting, False if basic strat (Only used by CPU Players)
	bool counting;
	bool insurance;
	//Position on the table
	int position;
	std::vector<Card> hand;
	double bank;
	int bet;
	int score;

	bool updateScore(Card card);
};

