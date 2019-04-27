#pragma once
#include <vector>
#include <iostream>

#include "Player.h"
#include "Shoe.h"

#define MAX_PLAYERS 8

static const char BASIC_STRAT_H[18][13] = {
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H' },
	{ 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D' },
	{ 'H', 'H', 'H', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'S', 'S', 'S', 'S', 'S', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' }
};
static const int HARD_MOD = 4;

static const char BASIC_STRAT_S[9][13] = {
	{ 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'D', 'D', 'D', 'D', 'D', 'S', 'S', 'H', 'H', 'H', 'H', 'H' },
	{ 'S', 'S', 'S', 'S', 'S', 'D', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
};
static const int SOFT_MOD = 13;

class Table
{
public:
	Table();
	Table(Shoe* shoe, int _active, int _control, int _strategy);
	~Table();
	size_t getNumPlaying() const;
	void print() const;
	size_t playRound();
	void playerTurn(int p);
	void computerTurn(int p);
	void userTurn(int p);
	void offerInsurance();
	void dealerTurn();
	
private:
	Shoe* shoe;
	Player* dealer;
	std::vector<Player*> players;
	int round;
	size_t numPlaying;
	size_t busts;
	
	//8 digit bitwise number where 1 means user controlled/active
	void setPlayerControl(int _control);
	void setPlaying(int _active);
	void setStrategy(int _strategy);
	void initDeal();
	//returns false if player busts
	bool hit(int player);
	void printWinners() const;
};

