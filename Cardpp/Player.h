#pragma once

#include <string>
#include <vector>

#include "Card.h"

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
	int getPosition() const;
	int getBank() const;
	int getScore() const;
	bool isSoft() const;
	int getShowing() const;
	bool hasBlackjack() const;

	void print() const;
	void printHand() const;
		
	//resets for next round
	void reset();
	void dealCard(Card card);
	void showHoleCard();
	void setUserControlled();
	void setPlayerPlaying();
	void setStrategy(bool _counting);
	void takeInsurance();
	

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
	int bank;
	int score;

	bool updateScore(Card card);

};

