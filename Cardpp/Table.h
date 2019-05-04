#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "Shoe.h"
#include "StaticVars.h"

class Table :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
	Table();
    Table(Shoe* shoe, int _active, int _control, int _strategy);
	~Table();

    void draw(QGraphicsScene* _scene);

    size_t getNumPlaying() const;
	void print() const;
    size_t playRound();
    void playerTurn(size_t p);
    void computerTurn(size_t h, size_t p);
    void userTurn(size_t h, size_t p);
	bool offerInsurance();
	void dealerTurn();
	void placeBets();

    bool makeDecision(size_t h, size_t p, char decision);
	bool validDecision(char decision, bool canDD, bool canSplit);
	std::string decisionMenu(bool canDD, bool canSplit);
    std::string handInfoString(size_t h, size_t p);
    char basicStrategyDecision(size_t h, size_t p) const;
	
    double bettingRecommendation(size_t p) const;
    bool insuranceRecommendation() const;
    char decisionRecommendation(size_t h, size_t p) const;
    //7 digit bitwise number where 1 means user controlled/active
    void setPlayerControl(int _control);
    void setPlaying(int _active);
    void setStrategy(int _strategy);
    void initDeal();
    //returns false if player busts
    bool hit(size_t h, size_t p);
    bool doubleDown(size_t h, size_t p);
    bool split(size_t h, size_t p);
    void printWinners();
    void payInsurance();

private:
	Shoe* shoe;
	Player* dealer;
	std::vector<Player*> players;
    size_t round;
    size_t numPlaying;
    size_t busts;
};

#endif //TABLE_H
