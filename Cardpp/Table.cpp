#include "Table.h"
#include "Game.h"

extern Game* game;

Table::Table() : QObject(), QGraphicsPixmapItem()
{
}

Table::Table(Shoe* _shoe, int _active, int _control, int _strategy){
    round = 1;
	numPlaying = 0;
	shoe = _shoe;
    busts = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players.push_back(new Player(false, i+1, this));
    }
	setPlaying(_active);
	setPlayerControl(_control);
    setStrategy(_strategy);
    dealer = new Player(true, 0, this);
    setPixmap(QPixmap(":/graphics/other/table.png").scaled(T_WIDTH, T_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
    setPos(0,0);

    mainMessageText = new QGraphicsTextItem("", this);
    mainMessageText->setFont(QFont("Times", 25));
    mainMessageText->setDefaultTextColor(QColor(Qt::cyan));
    mainMessageText->setPos(W_WIDTH/2 - mainMessageText->boundingRect().width()/2,0);
}


void Table::makeConnections(){
    QObject::connect(this, SIGNAL(UserBetSignal()), this, SLOT(userBetting()));
    QObject::connect(this, SIGNAL(BetPhaseComplete()), this, SLOT(transitionToDealPhase()));
    QObject::connect(this, SIGNAL(DealingComplete()), this, SLOT(transitionToDecisionPhase()));
    QObject::connect(this, SIGNAL(UserDecisionSignal()), this, SLOT(userDeciding()));
}

Table::~Table(){
	while(!players.empty()) {
		delete players.back();
		players.pop_back();
	}
}

void Table::hitSlot(){
    qDebug() << "HIT!";
    game->userDecision = 'H';
}
void Table::standSlot(){
    qDebug() << "STAND!";
    game->userDecision = 'S';
}
void Table::ddSlot(){
    qDebug() << "DOUBLE DOWN!";
    game->userDecision = 'D';
}
void Table::splitSlot(){
    qDebug() << "SPLIT!";
    game->userDecision = 'P';
}

void Table::betIncreaseSlot(){
    if(game->action->getBank() >= (game->userBet + game->minBet)){
        qDebug() << "Bet Increase";
        game->userBet += game->minBet;
        userBetText->setPlainText(QString("$") + QString::number(game->userBet));
        userBetText->setPos(BUTTON_XPOS[4] + BUTTON_WIDTH - userBetText->boundingRect().width()/2,
                BUTTON_YPOS - userBetText->boundingRect().height());
    }
    else
        qDebug() << "No Bet Increase";
}
void Table::betDecreaseSlot(){
    if(game->minBet <= (game->userBet - game->minBet)){
        qDebug() << "Bet Decrease";
        game->userBet -= game->minBet;
        userBetText->setPlainText(QString("$") + QString::number(game->userBet));
        userBetText->setPos(BUTTON_XPOS[4] + BUTTON_WIDTH - userBetText->boundingRect().width()/2,
                BUTTON_YPOS - userBetText->boundingRect().height());
    }
    else
        qDebug() << "No Bet Decrease";
}


void Table::draw(QGraphicsScene* _scene){
    _scene->addItem(this);
    dealer->draw(_scene);
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        if(players[i]->isPlaying()){
            players[i]->draw(_scene);
        }
    }
}

size_t Table::getNumPlaying() const { return numPlaying; }
bool Table::dealerBJ(){return dealer->hasBlackjack();}
int Table::getRunningCount() {return shoe->getRunningCount();}
int Table::getTrueCount() {return shoe->getTrueCount();}


void Table::increaseBusts() {busts++;}

void Table::print() const {
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			players[i]->print();
		}
	}
	dealer->print();
	std::cout << std::endl;
}

void Table::setPlayerControl(int _control) {
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (((_control >> i) & 1) == 1)
			players[i]->setUserControlled();
	}
}

void Table::setPlaying(int _active) {
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (((_active >> i) & 1) == 1) {
			players[i]->activate();
            players[static_cast<size_t>(i)]->setLabel();
            players[static_cast<size_t>(i)]->setBankLabel();
			numPlaying++;
		}
	}
}

void Table::setStrategy(int _strategy) {
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (((_strategy >> i) & 1) == 1) {
			players[i]->setStrategy(true);
		}
	}
}

void Table::placeBets() {
    for(size_t i = 0; i < MAX_PLAYERS; i++){
        game->action = players[i];
        if(game->action->isPlaying()){
            if(game->action->isControlled()){
                emit UserBetSignal();
                qDebug() << "User Player " << game->action->getPosition() << "bets.";
            }
            else {
                game->action->takeBet(0, game->userBet);
                qDebug() << "Computer Player " << game->action->getPosition() << "bets.";
            }
        }
    }
    emit BetPhaseComplete();
}

void Table::userBetting(){
    QString str = QString("Player ") + QString::number(game->action->getPosition()) + QString(" place bet.");
    updateMessage(str);
    game->pause->exec();
    game->action->takeBet(0, game->userBet);
    game->userBet = game->minBet;
    updateBetText();
}

void Table::userDeciding(){
    game->pause->exec();
}

void Table::initDeal() {
	for (int i = 0; i <= MAX_PLAYERS * 2; i++) {
        if (i == MAX_PLAYERS ) {
            dealer->dealCard(0, shoe->dealHidden());
		}
		else {
            if (players[i % (MAX_PLAYERS + 1)]->isPlaying()){
                players[i % (MAX_PLAYERS + 1)]->dealCard(0, shoe->deal());
            }
		}
    }
    dealer->dealCard(0, shoe->deal());
}

size_t Table::playRound() {
    size_t remainingCards = shoe->getSize();

    initDeal();

    size_t dealerShowing = dealer->getShowing();
    bool dealerBJ = this->dealerBJ();
	//Insurance only offered with Ace up card.
    //if (dealerShowing == 1) {
    //	dealerBJ = offerInsurance();
    //}

	if (!dealerBJ) {
		busts = 0;
        for (size_t i = 0; i < MAX_PLAYERS; i++) {
			if (players[i]->isPlaying())
				playerTurn(i);
		}
		dealerTurn();

		printWinners();
	}
	else {
		std::cout << "\nShowing Dealer's Hole Card:\n";
        Card* temp = dealer->showHoleCard();
		shoe->updateCounts(temp);
		dealer->print();
		std::cout << "Dealer has Blackjack!\n";
		payInsurance();
	}

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		players[i]->reset();
	}
	dealer->reset();
	round++;
	return shoe->getSize();
}

bool Table::offerInsurance() {
	char choice = 0;
	bool valid = false;
	int bet;
	double bank;

    for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			bet = players[i]->getBet();
			bank = players[i]->getBank();
			if (bank >= (bet / 2)) {
				if (!players[i]->isControlled()) {
					if ((uni(rng) % 2) == 0) {
						std::cout << "Player " << players[i]->getPosition()
							<< " takes insurance.\n";
						players[i]->takeInsurance();
					}
					else {
						std::cout << "Player " << players[i]->getPosition()
							<< " declines insurance.\n";
					}
				}
				else {
					shoe->printCounts();
                    std::cout << "You should" << (insuranceRecommendation()? " " : "n't ")
						<< "take insurance.\n";
					std::cout << "Player " << players[i]->getPosition()
						<< " would you like insurance? Y/N ==> ";
					while (!valid) {
						std::cin >> choice;
						if (toupper(choice) == 'Y') {
							valid = true;
							players[i]->takeInsurance();
							std::cout << "Player " << players[i]->getPosition()
								<< " takes insurance.\n";
						}
						else if (toupper(choice) == 'N') {
							valid = true;
							std::cout << "Player " << players[i]->getPosition()
								<< " declines insurance.\n";
						}
						else {
							std::cout << "Please enter valid choice. Y/N ==> ";
						}
					}
				}
			}
			else {
				std::cout << "Player " << players[i]->getPosition()
					<< " can't afford insurance.\n";
			}
		}
		valid = false;
	}
    return dealer->getHand(0)->hasBlackjack();
}

void Table::playerTurn(size_t p) {
    for (size_t h = 0; h < players[p]->getNumHands(); h++) {
        if (!dealerBJ()) {
			if (!players[p]->isControlled())
				computerTurn(h, p);
			else
				userTurn(h, p);
		}

        if (players[p]->getHand(h)->getScore() > 21) {
			busts++;
		}
	}
}

void Table::computerTurn(size_t h, size_t p) {
	char decision;
	bool turn = true;

	players[p]->printHand(h);
    if (players[p]->getHand(h)->hasBlackjack()) {
		turn = false;
		std::cout << "Player " << players[p]->getPosition() << " has Blackjack!\n";
	}

	while (turn) {
		decision = basicStrategyDecision(h, p);
		turn = makeDecision(h, p, decision);
	}
}

char Table::basicStrategyDecision(size_t h, size_t p) const {
	char decision;
    size_t dealerShowing = dealer->getShowing();
	if (players[p]->canSplit(h)) {
        decision = BASIC_STRAT_SPLIT[players[p]->getHand(h)->getCard(0)->getIndex() - SPLIT_MOD][dealerShowing - SPLIT_MOD];
	}
    else if (players[p]->getHand(h)->size() == 1) {
        decision = BASIC_STRAT_H[players[p]->getHand(h)->getScore() - HARD_MOD][dealerShowing - 1];
	}
	else {
        decision = (players[p]->getHand(h)->isSoft() ?
            BASIC_STRAT_S[players[p]->getHand(h)->getScore() - SOFT_MOD][dealerShowing - 1] :
            BASIC_STRAT_H[players[p]->getHand(h)->getScore() - HARD_MOD][dealerShowing - 1]);
	}

	if (decision == 'D' && !players[p]->canDoubleDown(h))
		decision = 'H';

	return decision;
}

bool Table::makeDecision(size_t h, size_t p, char decision) {
	switch (decision) {
	case 'D': //Double Down
		std::cout << "Player " << players[p]->getPosition() << " doubles down.\n";
        return doubleDown(h, p);
	case 'S': //Stand
		std::cout << "Player " << players[p]->getPosition() << " stands with "
            << players[p]->getHand(h)->getScore() << ".\n";
        return false;
	case 'H': //Hit
		std::cout << "Player " << players[p]->getPosition() << " hits.\n";
        return hit(h, p);
	case 'P':
		std::cout << "Player " << players[p]->getPosition() << " splits.\n";
		return split(h, p);
	default:
		std::cerr << "Decision " << decision << " not recognized.\n";
        return false;
	}
}

void Table::userTurn(size_t h, size_t p) {
    bool turn = true,
        canDD = true,
        canSplit = true;
	
    if (players[p]->getHand(h)->hasBlackjack()) {
        turn = false;
	}

	while (turn) {
		canDD = players[p]->canDoubleDown(h);
        canSplit = players[p]->canSplit(h);

        QString recommendation = QString("RC = ") + QString::number(getRunningCount())
                + QString("TC = ") + QString::number(getTrueCount())
                + QString("We recomended Player ") + QString::number(players[p]->getPosition())
                + QString(" to ") + decisionToQString(decisionRecommendation(h, p));
        updateMessage(recommendation);

        activateDecisionButtons(canDD, canSplit);

        emit UserDecisionSignal();
        turn = makeDecision(h, p, game->userDecision);
        game->userDecision = 'N';
    }
}

void Table::dealerTurn() {
    std::cout << "\nShowing Dealer's Hole Card:\n";
    Card* temp = dealer->showHoleCard();
	shoe->updateCounts(temp);
    dealer->dealerPositionHand();
	dealer->print();

	if (busts < numPlaying) {
		while (dealer->dealerHits()) {
			std::cout << "Dealer hits.\n";
			dealer->dealCard(0, shoe->deal());
			dealer->printHand(0);
            if (dealer->getHand(0)->getScore() > 21)
                std::cout << "Dealer busted with " << dealer->getHand(0)->getScore() << "!\n";
		}

        if (dealer->getHand(0)->getScore() <= 21)
            std::cout << "Dealer stands with " << dealer->getHand(0)->getScore() << ".\n";
	}
	else
		std::cout << "Everyone busted. Dealer wins!\n";
}

bool Table::hit(size_t h, size_t p) {
	players[p]->dealCard(h, shoe->deal());
	players[p]->printHand(h);
    players[p]->getHand(h)->incReceived();
    if (players[p]->getHand(h)->getScore() >= 21) {
		return false;
	}
	else
		return true;
}

bool Table::doubleDown(size_t h, size_t p) {
	players[p]->takeBet(h, players[p]->getBet());
	hit(h, p);
	return false;
}

bool Table::split(size_t h, size_t p) {
    players[p]->split(h, players[p]->getBet());
	players[p]->printHand(h);
	return true;
}

void Table::printWinners() {
	std::cout << "\nResults:\n";
    int dealerScore = dealer->getHand(0)->getScore();
	int score = 0;
    bool dealerBJ = dealer->getHand(0)->hasBlackjack(),
		playerBJ = false,
		playerIns = false;
	int bet;
	double winnings;
    for (size_t p = 0; p < MAX_PLAYERS; p++) {
		if (players[p]->isPlaying()) {
            for(size_t h = 0; h < players[p]->getNumHands(); h++){
                bet = players[p]->getHand(h)->getBet();
				winnings = 0;
                playerBJ = players[p]->getHand(h)->hasBlackjack();
				//Dealer has uninsureable Blackjack
				if (dealerBJ) {
					if (playerBJ) {
						std::cout << "Player " << players[p]->getPosition()
							<< " has Blackjack too and pushes"; //doesn't lose bet
						winnings = bet;
					}
					else {
						std::cout << "Player " << players[p]->getPosition()
							<< " loses to Blackjack";
					}
				}
				//Dealer does not have Blackjack
				else {
					if (playerIns) {
						std::cout << "Player " << players[p]->getPosition()
							<< " loses insurance bet.\n";
					}
					if (playerBJ && players[p]->getNumHands() == 1) {
						std::cout << "Player " << players[p]->getPosition()
							<< " wins with Blackjack";
						winnings = bet * 2.5;
					}
					else if (dealerScore > 21) {
                        if ((score = players[p]->getHand(h)->getScore()) <= 21) {
							std::cout << "Player " << players[p]->getPosition()
								<< " wins from dealer bust";
							winnings = bet * 2;
						}
						else {
							std::cout << "Player " << players[p]->getPosition()
								<< " busted with " << score;
						}
					}
					else {
                        if ((score = players[p]->getHand(h)->getScore()) > dealerScore && score <= 21) {
							std::cout << "Player " << players[p]->getPosition()
								<< " wins with " << score;
							winnings = bet * 2;
						}
						else if (score == dealerScore) {
							std::cout << "Player " << players[p]->getPosition()
								<< " pushes";
							winnings = bet;
						}
						else if (score > 21) {
							std::cout << "Player " << players[p]->getPosition()
								<< " busted with " << score;
						}
						else {
							std::cout << "Player " << players[p]->getPosition()
								<< " loses with " << score;
						}
					}
				}
				std::cout << std::fixed
					<< players[p]->collectWinnings(winnings) 
					<< handInfoString(h, p) << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

//Insured Blackjack
void Table::payInsurance() {
	std::cout << "\nResults:\n";
	bool playerBJ = false,
		playerIns = false;
	int bet;
    double winnings = 0;

    for (size_t p = 0; p < MAX_PLAYERS; p++) {
		if (players[p]->isPlaying()) {
            for (size_t h = 0; h < players[p]->getNumHands(); h++) {
                bet = players[p]->getHand(h)->getBet();
				winnings = 0;
                playerBJ = players[p]->getHand(h)->hasBlackjack();
				playerIns = players[p]->hasInsurance();
				//Insured Blackjack
				if (playerBJ && playerIns) {
					std::cout << "Player " << players[p]->getPosition()
						<< " took even money.\n";
					winnings = bet * 2;
				}
				else if (playerIns) {
					std::cout << "Player " << players[p]->getPosition()
						<< " has insurance.\n";
					winnings = bet;
				}
				else if (playerBJ) {
					std::cout << "Player " << players[p]->getPosition()
						<< " has Blackjack too and pushes.\n";
					winnings = bet;
				}
				else {
					std::cout << "Player " << players[p]->getPosition()
						<< " loses to Blackjack.\n";
				}
			}
			std::cout << std::fixed
				<< players[p]->collectWinnings(winnings) << std::endl;
		}
	}
	std::cout << std::endl;
}

std::string Table::decisionMenu(bool canDD, bool canSplit) {
	std::string temp = "S = Stand  H = Hit  ";
	if (canDD)
		temp += "D = Double Down  ";
	if (canSplit)
		temp += "P = Split  ";
	temp += "==> ";
	return temp;
}

bool Table::validDecision(char decision, bool canDD, bool canSplit) {
	if (decision == 'S')
		return true;
	if (decision == 'D' && canDD)
		return true;
	if (decision == 'H')
		return true;
	if (decision == 'P' && canSplit)
		return true;
	return false;
}

std::string Table::handInfoString(size_t h, size_t p) {
	std::string temp = "";
	if (players[p]->getNumHands() > 1)
		temp += (" for Hand " + std::to_string(h + 1));
	temp += ".\t";
	return temp;
}

double Table::bettingRecommendation(size_t p) const {
	int trueCount = shoe->getTrueCount();
	double bank = players[p]->getBank();
	if (trueCount <= 1)
		return DEFAULT_BET;
	if(trueCount == 2)
		return (std::min(bank, DEFAULT_BET*2.0));
	if (trueCount == 3)
		return (std::min(bank, DEFAULT_BET*4.0));
	if (trueCount == 4)
		return (std::min(bank, DEFAULT_BET*8.0));

	return (std::min(bank, DEFAULT_BET*12.0));
}

bool Table::insuranceRecommendation() const {
	return (shoe->getTrueCount() >= 3);
}

char Table::decisionRecommendation(size_t h, size_t p) const {
	int score = players[p]->getScore(h);
    int dealerValue = dealer->getHand(h)->getCard(1)->getValue();
	int trueCount = shoe->getTrueCount();

	char decision = basicStrategyDecision(h, p);

	if (score == 16) {
		if (dealerValue == 9) {
			decision = ((trueCount >= 5) ? 'S' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 10) {
			decision = ((trueCount >= 0) ? 'S' : basicStrategyDecision(h, p));
		}
	}
	else if (score == 15) {
		if (dealerValue == 10) {
			decision = ((trueCount >= 4) ? 'S' : basicStrategyDecision(h, p));
		}
	}
	else if (score == 13) {
		if (dealerValue == 2) {
			decision = ((trueCount >= -1) ? 'S' : 'H');
		}
		else if (dealerValue == 3) {
			decision = ((trueCount >= -2) ? 'S' : 'H');
		}
	}
	else if (score == 12) {
		if (dealerValue == 2) {
			decision = ((trueCount >= 4) ? 'S' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 3) {
			decision = ((trueCount >= 2) ? 'S' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 4) {
			decision = ((trueCount >= 0) ? 'S' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 5) {
			decision = ((trueCount >= -1) ? 'S' : 'H');
		}
		else if (dealerValue == 6) {
			decision = ((trueCount >= -1) ? 'S' : 'H');
		}
	}
	else if (score == 11) {
		if (dealerValue == 11) {
			decision = ((trueCount >= 1) ? 'D' : basicStrategyDecision(h, p));
		}
	}
	else if (score == 10) {
		if (dealerValue == 10) {
			decision = ((trueCount >= 4) ? 'D' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 11) {
			decision = ((trueCount >= 4) ? 'D' : basicStrategyDecision(h, p));
		}
	}
	else if (score == 9) {
		if (dealerValue == 2) {
			decision = ((trueCount >= 1) ? 'D' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 7) {
			decision = ((trueCount >= 4) ? 'D' : basicStrategyDecision(h, p));
		}
	}
	else if (score == 20) {
		if (dealerValue == 5) {
			decision = ((trueCount >= 5) ? 'P' : basicStrategyDecision(h, p));
		}
		else if (dealerValue == 6) {
			decision = ((trueCount >= 5) ? 'P' : basicStrategyDecision(h, p));
		}
	}

	if (decision == 'D' && !players[p]->canDoubleDown(h))
		decision = 'H';

	if (decision == 'P' && !players[p]->canSplit(h))
		decision = basicStrategyDecision(h, p);

	return decision;
}

QString Table::decisionToQString(char decision){
    switch(decision){
    case 'H':
        return QString("Hit");
    case 'D':
        return QString("Double Down");
    case 'S':
        return QString("Stand");
    case 'P':
        return QString("Split");
    default:
        return QString("Something broke");
    }
}

//GUI STUFF

void Table::transitionToDealPhase(){
    deactivateBettingButtons();
    game->action = players[0];
}

void Table::transitionToDecisionPhase(){
}

void Table::activateBettingButtons(){
    betButton = new DecisionButton('b',this);
    increaseBetButton = new DecisionButton('i', this);
    decreaseBetButton = new DecisionButton('m', this);
    connect(betButton, SIGNAL(clicked()), game->pause, SLOT(quit()));
    connect(increaseBetButton, SIGNAL(clicked()), this, SLOT(betIncreaseSlot()));
    connect(decreaseBetButton, SIGNAL(clicked()), this, SLOT(betDecreaseSlot()));

    userBetText = new QGraphicsTextItem(QString("$") + QString::number(game->userBet), this);
    userBetText->setFont(QFont("Times", 30));
    userBetText->setDefaultTextColor(QColor(255,195,0));

    userBetText->setPos(BUTTON_XPOS[4] + BUTTON_WIDTH - userBetText->boundingRect().width()/2,
            BUTTON_YPOS - userBetText->boundingRect().height());
}

void Table::deactivateBettingButtons(){
    updateMessage("");
    game->pause->disconnect();
    game->scene->removeItem(betButton);
    delete betButton;
    betButton = nullptr;
    game->scene->removeItem(increaseBetButton);
    delete increaseBetButton;
    increaseBetButton = nullptr;
    game->scene->removeItem(decreaseBetButton);
    delete decreaseBetButton;
    decreaseBetButton = nullptr;
    game->scene->removeItem(userBetText);
    delete userBetText;
    userBetText = nullptr;
}


Card* Table::dealCard(){
    return shoe->deal();
}


void Table::activateDecisionButtons(bool canDD, bool canSplit){
    hitButton = new DecisionButton('h', this);
    connect(hitButton, SIGNAL(clicked()), this, SLOT(hitSlot()));
    connect(hitButton, SIGNAL(clicked()), game->pause, SLOT(quit()));
    standButton = new DecisionButton('s', this);
    connect(standButton, SIGNAL(clicked()), this, SLOT(standSlot()));
    connect(standButton, SIGNAL(clicked()), game->pause, SLOT(quit()));
    if(canDD){
        ddButton = new DecisionButton('d', this);
        connect(ddButton, SIGNAL(clicked()), this, SLOT(ddSlot()));
        connect(ddButton, SIGNAL(clicked()), game->pause, SLOT(quit()));
    }
    if(canSplit){
        splitButton = new DecisionButton('p', this);
        connect(splitButton, SIGNAL(clicked()), this, SLOT(splitSlot()));
        connect(splitButton, SIGNAL(clicked()), game->pause, SLOT(quit()));
    }
}

void Table::deactivateDecisionButtons(){
}

void Table::updateMessage(const QString& str){
    mainMessageText->setPlainText(str);
    mainMessageText->setPos(W_WIDTH/2 - mainMessageText->boundingRect().width()/2,0);
}

void Table::updateBetText(){
    QString str = QString("$") + QString::number(game->userBet);
    userBetText->setPlainText(str);
    userBetText->setPos(BUTTON_XPOS[4] + BUTTON_WIDTH - userBetText->boundingRect().width()/2,
            BUTTON_YPOS - userBetText->boundingRect().height());
}
