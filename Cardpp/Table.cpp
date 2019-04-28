#include "Table.h"

Table::Table()
{
}

Table::Table(Shoe* _shoe, int _active, int _control, int _strategy) {
	round = 1;
	numPlaying = 0;
	shoe = _shoe;
	busts = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		players.push_back(new Player("computer", i+1));
	}
	setPlaying(_active);
	setPlayerControl(_control);
	dealer = new Player("dealer", 0);
}

Table::~Table(){
	while(!players.empty()) {
		delete players.back();
		players.pop_back();
	}
}

size_t Table::getNumPlaying() const { return numPlaying; }

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
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (((_control >> i) & 1) == 1)
			players[i]->setUserControlled();
	}
}

void Table::setPlaying(int _active) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (((_active >> i) & 1) == 1) {
			players[i]->activate();
			numPlaying++;
		}
	}
}

void Table::setStrategy(int _strategy) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (((_strategy >> i) & 1) == 1) {
			players[i]->setStrategy(true);
		}
	}
}

void Table::placeBets() {
	double bank = 0;
	int bet = DEFAULT_BET;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		shoe->printCounts();
		if (players[i]->isPlaying()) {
			bank = players[i]->getBank();
			if (bank < DEFAULT_BET){
				std::cout << "Player " << players[i]->getPosition() << " only has $"
					<< std::fixed << bank << " and cannot bet $" << bet
					<< "\nThey have left the game.\n";
				players[i]->deactivate();
				numPlaying--;
			}
			else {
				if (players[i]->isControlled()) {
					std::cout << "Player " << players[i]->getPosition()
						<< " choose bet amount. ==> ";
					do {
						std::cin >> bet;
						if (bank < bet) {
							std::cout << "You cannot afford that bet. Try again.  ==> ";
						}
						if (bet < DEFAULT_BET) {
							std::cout << "That is below minimum bet. Try again.  ==> ";
						}
					} while ((bank < bet) && (bet < DEFAULT_BET));
				}

				players[i]->setBet(bet);
				players[i]->takeBet(0, bet);
			}
		}
	}
}

void Table::initDeal() {
	for (int i = 0; i <= MAX_PLAYERS * 2; i++) {
		if (i == MAX_PLAYERS ) {
			dealer->dealCard(0, shoe->dealHidden());
		}
		else {
			if (players[i % (MAX_PLAYERS + 1)]->isPlaying())
				players[i % (MAX_PLAYERS + 1)]->dealCard(0, shoe->deal());
		}
	}
	dealer->dealCard(0, shoe->deal());
}

size_t Table::playRound() {
	size_t remainingCards = shoe->getSize();
	Card temp;

	std::cout << std::string(57, '-') << std::endl << "Round " << round 
		<< ": " << remainingCards << " cards remaining.\n" 
		<< std::string(57, '-') << std::endl;

	initDeal();
	//dealer->dealerCheat();
	print();
	
	//Check up card
	int dealerShowing = dealer->getShowing();
	//Insurance only offered with Ace up card.
	if (dealerShowing == 1) {
		offerInsurance();
	}

	busts = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying())
			playerTurn(i);
	}
	dealerTurn();

	printWinners();

	for (int i = 0; i < MAX_PLAYERS; i++) {
		players[i]->reset();
	}
	dealer->reset();
	round++;
	return shoe->getSize();
}

void Table::offerInsurance() {
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
}

void Table::playerTurn(int p) {
	for (int h = 0; h < players[p]->getNumHands(); h++) {
		players[p]->printPlayer();
		if (!dealer->hasBlackjack(0)) {
			if (!players[p]->isControlled())
				computerTurn(h, p);
			else
				userTurn(h, p);
		}

		if (players[p]->hand(h).getScore() > 21) {
			busts++;
		}
	}
}

void Table::computerTurn(int h, int p) {
	int dealerShowing = dealer->getShowing();
	char decision;
	bool turn = true;

	players[p]->printHand(h);
	if (players[p]->hand(h).hasBlackjack()) {
		turn = false;
		std::cout << "Player " << players[p]->getPosition() << " has Blackjack!\n";
	}

	while (turn) {
		if (players[p]->canSplit(h)) {
			decision =
				BASIC_STRAT_SPLIT[players[p]->hand(h)[0].getIndex() - SPLIT_MOD][dealerShowing - SPLIT_MOD];
		}
		else {
			decision = (players[p]->hand(h).isSoft() ?
				BASIC_STRAT_S[players[p]->hand(h).getScore() - SOFT_MOD][dealerShowing - 1] :
				BASIC_STRAT_H[players[p]->hand(h).getScore() - HARD_MOD][dealerShowing - 1]);
		}

		if (decision == 'D' && !players[p]->canDoubleDown(h))
			decision = 'H';

		turn = makeDecision(h, p, decision);
	}
}

bool Table::makeDecision(int h, int p, char decision) {
	switch (decision) {
	case 'D': //Double Down
		std::cout << "Player " << players[p]->getPosition() << " doubles down.\n";
		return doubleDown(h, p);
		break;
	case 'S': //Stand
		std::cout << "Player " << players[p]->getPosition() << " stands with "
			<< players[p]->hand(h).getScore() << ".\n";
		return false;
		break;
	case 'H': //Hit
		std::cout << "Player " << players[p]->getPosition() << " hits.\n";
		return hit(h, p);
		break;
	case 'P':
		std::cout << "Player " << players[p]->getPosition() << " splits.\n";
		return split(h, p);
	default:
		std::cerr << "Decision " << decision << " not recognized.\n";
		return false;
		break;
	}
}

void Table::userTurn(int h, int p) {
	char decision;
	bool turn = true,
		valid = false,
		canDD,
		canSplit;
	
	if (players[p]->hand(h).hasBlackjack()) {
		turn = false;
		std::cout << "Player " << players[p]->getPosition() << " has Blackjack!\n";
	}

	while (turn) {
		canDD = players[p]->canDoubleDown(h);
		canSplit = players[p]->canSplit(h);
		valid = false;
		players[p]->printHand(h);
		shoe->printCounts();
		std::cout << "Player " << players[p]->getPosition() << " make a decision"
			<< handInfoString(h, p) << decisionMenu(canDD, canSplit);
		while (!valid) {
			std::cin >> decision;
			decision = toupper(decision);
			valid = validDecision(decision, canDD, canSplit);
			if(!valid)
				std::cout << "Please enter valid decision.\t" 
				<< decisionMenu(canDD, canSplit);
		}

		turn = makeDecision(h, p, decision);
	}
	players[p]->print();
}

void Table::dealerTurn() {
	int dealerScore = dealer->hand(0).getScore();
	bool soft = dealer->hand(0).isSoft();
	std::cout << "\nShowing Dealer's Hole Card:\n";
	Card temp = dealer->showHoleCard();
	shoe->updateCounts(temp);
	dealer->print();

	if (busts < numPlaying) {
		while (dealer->dealerHits()) {
			std::cout << "Dealer hits.\n";
			dealer->dealCard(0, shoe->deal());
			dealer->printHand(0);
			if (dealer->hand(0).getScore() > 21)
				std::cout << "Dealer busted with " << dealer->hand(0).getScore() << "!\n";
		}

		if (dealer->hand(0).getScore() <= 21)
			std::cout << "Dealer stands with " << dealer->hand(0).getScore() << ".\n";
	}
	else
		std::cout << "Everyone busted. Dealer wins!\n";
}


bool Table::hit(int h, int p) {
	players[p]->dealCard(h, shoe->deal());
	players[p]->printHand(h);
	players[p]->hand(h).incReceived();
	if (players[p]->hand(h).getScore() > 21) {
		std::cout << "Player " << players[p]->getPosition() << " Busted with " <<
			players[p]->hand(h).getScore() << ".\n";
		return false;
	}
	else
		return true;
}

bool Table::doubleDown(int h, int p) {
	players[p]->takeBet(h, players[p]->getBet());
	hit(h, p);
	return false;
}

bool Table::split(int h, int p) {
	players[p]->split(h, players[p]->getBet());
	players[p]->printHand(h);
	return true;
}

void Table::printWinners() {
	std::cout << "\nResults:\n";
	int dealerScore = dealer->hand(0).getScore();
	int score = 0;
	bool dealerBJ = dealer->hand(0).hasBlackjack(),
		playerBJ = false,
		playerIns = false;
	int bet;
	double winnings;
	for (size_t p = 0; p < MAX_PLAYERS; p++) {
		if (players[p]->isPlaying()) {
			for(size_t h = 0; h < players[p]->getNumHands(); h++){
				bet = players[p]->hand(h).getBet();
				winnings = 0;
				playerBJ = players[p]->hand(h).hasBlackjack();
				playerIns = players[p]->hasInsurance();
				if (dealerBJ) {
					if (playerBJ && playerIns) {
						std::cout << "Player " << players[p]->getPosition()
							<< " took even money";
						winnings = bet * 2;
					}
					else if (playerIns) {
						std::cout << "Player " << players[p]->getPosition()
							<< " has insurance";
						winnings = bet;
					}
					else if (playerBJ) {
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
						if ((score = players[p]->hand(h).getScore()) <= 21) {
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
						if ((score = players[p]->hand(h).getScore()) > dealerScore && score <= 21) {
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