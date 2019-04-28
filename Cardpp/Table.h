#pragma once
#include <vector>
#include <iostream>
#include <sstream>

#include "Player.h"
#include "Shoe.h"

#define MAX_PLAYERS 8

static const char BASIC_STRAT_H[18][13] ={
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

static const char BASIC_STRAT_SPLIT[13][13] = {
	{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'H', 'H', 'H', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'H', 'H', 'H', 'H' },
	{ 'H', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'H', 'P', 'P', 'P', 'P', 'P', 'P', 'H', 'H', 'H', 'H', 'H', 'H' },
	{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
	{ 'S', 'P', 'P', 'P', 'P', 'P', 'S', 'P', 'P', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },	
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' },
	{ 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' }
};
static const int SPLIT_MOD = 1;


class Table
{
public:
	Table();
	Table(Shoe* shoe, int _active, int _control, int _strategy);
	~Table();
	int getNumPlaying() const;
	void print() const;
	int playRound();
	void playerTurn(int p);
	void computerTurn(int h, int p);
	void userTurn(int h, int p);
	bool offerInsurance();
	void dealerTurn();
	void placeBets();

	bool makeDecision(int h, int p, char decision);
	bool validDecision(char decision, bool canDD, bool canSplit);
	std::string decisionMenu(bool canDD, bool canSplit);
	std::string handInfoString(int h, int p);
	char basicStrategyDecision(int h, int p) const;
	
	double bettingRecommendation(int p) const;
	bool insuranceRecommendation(int p) const;
	char decisionRecommendation(int h, int p) const;

private:
	Shoe* shoe;
	Player* dealer;
	std::vector<Player*> players;
	int round;
	int numPlaying;
	int busts;
	
	//8 digit bitwise number where 1 means user controlled/active
	void setPlayerControl(int _control);
	void setPlaying(int _active);
	void setStrategy(int _strategy);
	void initDeal();
	//returns false if player busts
	bool hit(int h, int p);
	bool doubleDown(int h, int p);
	bool split(int h, int p);
	void printWinners();
	void payInsurance();


};

