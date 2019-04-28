#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Card.h"
#include "Hand.h"

#define DEFAULT_BET 5
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
	bool canDoubleDown(size_t h) const;
	bool canSplit(size_t h) const;
	int getPosition() const;
	size_t getNumHands() const;
	double getBank() const;
	int getBet() const;
	int getScore(int i) const;
	void recalculateScores();
	bool isSoft(int i) const;
	int getShowing() const;
	bool hasBlackjack(int i) const;

	Hand& hand(size_t i);
	bool split(size_t h, int _bet);

	void print() const;
	void printPlayer() const;
	void printHands() const;
	void printHand(size_t i) const;
		
	//resets for next round
	void reset();
	void dealCard(int i, Card card);
	Card showHoleCard();
	void setUserControlled();
	void activate();
	void deactivate();
	void setStrategy(bool _counting);
	void takeInsurance();
	void setBet(int _bet);
	void setBank(double _bank);
	void takeBet(size_t h, int _bet);
	std::string collectWinnings(double _bet);
	
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
	std::vector<Hand> hands;
	double bank;
	int bet;

	bool updateScore(int i, Card card);
};

