#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "Shoe.h"
#include "DecisionButton.h"
#include "StaticVars.h"

class Table :  public QObject, public QGraphicsPixmapItem
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

    bool dealerBJ();
    void increaseBusts();
    int getBusts();

    int getRunningCount();
    int getTrueCount();

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

    Card* dealCard();

    DecisionButton* hitButton;
    DecisionButton* standButton;
    DecisionButton* ddButton;
    DecisionButton* splitButton;
    DecisionButton* betButton;

    DecisionButton* increaseBetButton;
    DecisionButton* decreaseBetButton;


    QGraphicsTextItem* mainMessageText;


    //GUI STUFF
    void updateMessage(const QString& str);
    void updateBetText();

    void activateDecisionButtons(bool canDD, bool canSplit);
    void deactivateDecisionButtons();

    void activateBettingButtons();
    void deactivateBettingButtons();

    void makeConnections();
    QString decisionToQString(char decision);

    void reset();

public slots:
    void userBetting();
    void userDeciding();

    void hitSlot();
    void standSlot();
    void ddSlot();
    void splitSlot();

    void betIncreaseSlot();
    void betDecreaseSlot();

    void transitionToDealPhase();
    void transitionToDecisionPhase();
    void transitionToBettingPhase();


signals:
    void UserBetSignal();
    void BetPhaseComplete();
    void DealingComplete();
    void UserDecisionSignal();
    void DecisionPhaseComplete();
    void RoundComplete();


private:
	Shoe* shoe;
    Player* dealer;
    size_t round;
    size_t numPlaying;
    size_t busts;
    std::vector<Player*> players;

    QGraphicsTextItem* userBetText;

};

#endif //TABLE_H
