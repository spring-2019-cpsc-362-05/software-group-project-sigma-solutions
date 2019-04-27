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

Table::~Table()
{
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
			std::cout << std::endl;
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
			players[i]->setPlayerPlaying();
			numPlaying++;
		}
	}
}

void Table::setStrategy(int _strategy) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (((_strategy >> i) & 1) == 1) {
			players[i]->setPlayerPlaying();
			numPlaying++;
		}
	}
}

void Table::initDeal() {
	for (int i = 0; i <= MAX_PLAYERS * 2; i++) {
		if (i == MAX_PLAYERS ) {
			dealer->dealCard(shoe->dealHidden());
		}
		else {
			if (players[i % (MAX_PLAYERS + 1)]->isPlaying())
				players[i % (MAX_PLAYERS + 1)]->dealCard(shoe->deal());
		}
	}
	dealer->dealCard(shoe->deal());
}

size_t Table::playRound() {
	size_t remainingCards = shoe->getSize();
	Card temp;

	std::cout << "Round " << round << ": " << remainingCards
		<< " cards remaining.\n" << std::string(57, '-') << std::endl;

	initDeal();
	print();

	busts = 0;
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying())
			playerTurn(i);
	}
	dealerTurn();

	std::cout << std::endl;
	printWinners();

	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		players[i]->reset();
	}
	dealer->reset();
	round++;
	return shoe->getSize();
}


void Table::offerInsurance() {
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			//Computer players take insurance half of the time.
			if (!players[i]->isControlled()) {
				if ((uni(rng) % 2) == 0) {
					players[i]->takeInsurance();
					std::cout << "\nPlayer " << players[i]->getPosition() 
						<< " takes insurance.";
				}
			}
			//Need to implement user control still
		}
	}
}

void Table::playerTurn(int p) {
	//Check up card
	int dealerShowing = dealer->getShowing();
	//Insurance only offered with Ace up card.
	if (dealerShowing == 1) {
		offerInsurance();
	}

	if (!dealer->hasBlackjack()) {
		//if (!players[p]->isControlled())
		computerTurn(p);
		//else
			//userTurn(p);
	}

	if (players[p]->getScore() > 21) {
		busts++;
	}
}

void Table::computerTurn(int p) {
	int dealerShowing = dealer->getShowing();
	char decision;
	bool turn = true;

	std::cout << std::endl;
	players[p]->print();

	if (players[p]->hasBlackjack()) {
		turn = false;
		std::cout << "\nPlayer " << players[p]->getPosition() << " has Blackjack!";
	}

	while (turn) {
		decision = (players[p]->isSoft() ?
			BASIC_STRAT_S[players[p]->getScore() - SOFT_MOD][dealerShowing - 1] :
			BASIC_STRAT_H[players[p]->getScore() - HARD_MOD][dealerShowing - 1]);

		switch (decision) {
		case 'D': //Double Down
			std::cout << "\nPlayer " << players[p]->getPosition() << " doubles down.\n";
			hit(p);
			std::cout << "\nPlayer " << players[p]->getPosition() << " has "
				<< players[p]->getScore() << ".";
			turn = false;
			break;
		case 'S': //Stand
			std::cout << "\nPlayer " << players[p]->getPosition() << " stands with "
				<< players[p]->getScore() << ".";
			turn = false;
			break;
		case 'H': //Hit
			std::cout << "\nPlayer " << players[p]->getPosition() << " hits.\n";
			turn = hit(p);
			break;
		default:
			std::cerr << "\nDecision " << decision << " not recognized.\n";
			turn = false;
			break;
		}
	}
}

void Table::userTurn(int p) {
}

void Table::dealerTurn() {
	if (busts < numPlaying) {
		int dealerScore = dealer->getScore();
		bool soft = dealer->isSoft();
		std::cout << "\n\nShowing Dealer's Hole Card:\n";
		dealer->showHoleCard();
		dealer->print();
		while (dealer->dealerHits()) {
			std::cout << "\nDealer hits.\n";
			dealer->dealCard(shoe->deal());
			dealer->print();
			if (dealer->getScore() > 21)
				std::cout << "\nDealer busted with " << dealer->getScore() << "!";
		}

		if (dealer->getScore() <= 21)
			std::cout << "\nDealer stands with " << dealer->getScore() << ".";
	}
	else
		std::cout << "Everyone busted. Dealer wins!\n";
}


bool Table::hit(int p) {
	players[p]->dealCard(shoe->deal());
	players[p]->print();
	if (players[p]->getScore() > 21) {
		std::cout << "\nPlayer " << players[p]->getPosition() << " Busted with " <<
			players[p]->getScore() << ".";
		return false;
	}
	else
		return true;
}

void Table::printWinners() const{
	std::cout << "\nResults:\n";
	int dealerScore = dealer->getScore();
	int score = 0;
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			if (dealer->hasBlackjack()) {
				if (players[i]->hasInsurance()) {
					std::cout << "\nPlayer " << players[i]->getPosition() 
						<< " has insurance."; //wins 2:1 insurance bet
				}
				else if (players[i]->hasBlackjack()) {
					std::cout << "\nPlayer " << players[i]->getPosition()
						<< " has Blackjack too and pushes."; //doesn't lose bet
				}
				else {
					std::cout << "\nPlayer " << players[i]->getPosition()
						<< " loses to Blackjack.";
				}
			}
			else {
				if (players[i]->hasInsurance()) {
					std::cout << "Player " << players[i]->getPosition()
						<< " loses insurance bet.\n";
				}
				if (dealerScore > 21) {
					if ((score = players[i]->getScore()) <= 21)
						if (players[i]->hasBlackjack()) {
							std::cout << "Player " << players[i]->getPosition()
								<< " wins with Blackjack!\n";
						}
						else {
							std::cout << "Player " << players[i]->getPosition()
								<< " wins from dealer bust!\n";
						}

					else
						std::cout << "Player " << players[i]->getPosition()
						<< " busted with " << score << "!\n";
				}
				else {
					if ((score = players[i]->getScore()) > dealerScore && score <= 21) {
						if (players[i]->hasBlackjack()) {
							std::cout << "Player " << players[i]->getPosition()
								<< " wins with Blackjack!\n";
						}
						else {
							std::cout << "Player " << players[i]->getPosition()
								<< " wins with " << score << "!\n";
						}
					}
					else if (score == dealerScore) {
						std::cout << "Player " << players[i]->getPosition()
							<< " pushes.\n";
					}
					else if (score > 21) {
						std::cout << "Player " << players[i]->getPosition()
							<< " busted with " << score << ".\n";
					}
					else {
						std::cout << "Player " << players[i]->getPosition()
							<< " loses with " << score << "!\n";
					}
				}
			}

		}
	}
}
