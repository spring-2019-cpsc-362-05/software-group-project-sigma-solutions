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
	int bet = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			bank = players[i]->getBank();
			bet = players[i]->getBet();
			if (bank >= bet)
				players[i]->takeBet(bet);
			else {
				std::cout << "Player " << players[i]->getPosition() << " only has $"
					<< std::fixed << bank << " and cannot bet $" << bet
					<< "\nThey have left the game.\n";
				players[i]->deactivate();
				numPlaying--;
			}
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
	int runningCount = shoe->getRunningCount();
	int trueCount = shoe->getTrueCount();

	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			//Computer players take insurance half of the time.
			if (!players[i]->isControlled()) {
				if ((uni(rng) % 2) == 0) {
					std::cout << "Player " << players[i]->getPosition()
						<< " takes insurance.\n";
					players[i]->takeInsurance();
				}
			}
			else {
				std::cout << "Running Count: " << ((runningCount > 0) ? "+" : "") << runningCount
					<< "\tTrue Count: " << ((trueCount > 0) ? "+" : "") << trueCount << std::endl;
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
		valid = false;
	}
}

void Table::playerTurn(int p) {

	if (!dealer->hasBlackjack()) {
		if (!players[p]->isControlled())
		computerTurn(p);
		else
			userTurn(p);
	}

	if (players[p]->getScore() > 21) {
		busts++;
	}
}

void Table::computerTurn(int p) {
	int dealerShowing = dealer->getShowing();
	double bank = players[p]->getBank();
	int bet = players[p]->getBet();
	char decision;
	bool turn = true;
	players[p]->print();

	if (players[p]->hasBlackjack()) {
		turn = false;
		std::cout << "Player " << players[p]->getPosition() << " has Blackjack!\n";
	}

	while (turn) {
		decision = (players[p]->isSoft() ?
			BASIC_STRAT_S[players[p]->getScore() - SOFT_MOD][dealerShowing - 1] :
			BASIC_STRAT_H[players[p]->getScore() - HARD_MOD][dealerShowing - 1]);

		if (decision == 'D' && !players[p]->canDoubleDown())
			decision = 'H';

		switch (decision) {
		case 'D': //Double Down

			std::cout << "Player " << players[p]->getPosition() << " doubles down.\n";
			players[p]->modBank(-1);
			players[p]->setBet(2 * bet);
			hit(p);
			std::cout << "Player " << players[p]->getPosition() << " has "
				<< players[p]->getScore() << ".\n";
			turn = false;
			break;
		case 'S': //Stand
			std::cout << "Player " << players[p]->getPosition() << " stands with "
				<< players[p]->getScore() << ".\n";
			turn = false;
			break;
		case 'H': //Hit
			std::cout << "Player " << players[p]->getPosition() << " hits.\n";
			turn = hit(p);
			break;
		default:
			std::cerr << "Decision " << decision << " not recognized.\n";
			turn = false;
			break;
		}
	}
}

void Table::userTurn(int p) {
	int dealerShowing = dealer->getShowing();
	double bank = players[p]->getBank();
	int bet = players[p]->getBet();
	int runningCount = 0,
		trueCount = 0;
	char decision;
	bool turn = true;
	bool valid = false;
	bool canDD;

	players[p]->print();

	if (players[p]->hasBlackjack()) {
		turn = false;
		std::cout << "Player " << players[p]->getPosition() << " has Blackjack!\n";
	}

	while (turn) {
		valid = false;
		runningCount = shoe->getRunningCount();
		trueCount = shoe->getTrueCount();
		canDD = players[p]->canDoubleDown();
		std::cout << "Running Count: " << ((runningCount > 0) ? "+" : "") << runningCount
			<< "\tTrue Count: " << ((trueCount > 0) ? "+" : "") << trueCount << std::endl;
		std::cout << "Player " << players[p]->getPosition() << " make a decision."
			<< "  (S = Stand" << ((canDD)? "  D = Double Down" : "")
			<<" H = Hit)  ==> ";
		while (!valid) {
			std::cin >> decision;
			decision = toupper(decision);

			if (decision == 'S' || decision == 'D' || decision == 'H')
				valid = true;
			else
				std::cout << "Please enter valid decision. S/D/H ==> ";
		}

		switch (decision) {
		case 'D': //Double Down
			std::cout << "Player " << players[p]->getPosition() << " doubles down.\n";
			players[p]->modBank(-1);
			players[p]->setBet(2 * bet);
			hit(p);
			std::cout << "Player " << players[p]->getPosition() << " has "
				<< players[p]->getScore() << ".\n";
			turn = false;
			break;
		case 'S': //Stand
			std::cout << "Player " << players[p]->getPosition() << " stands with "
				<< players[p]->getScore() << ".\n";
			turn = false;
			break;
		case 'H': //Hit
			std::cout << "Player " << players[p]->getPosition() << " hits.\n";
			turn = hit(p);
			break;
		default:
			std::cerr << "Decision " << decision << " not recognized.\n";
			turn = false;
			break;
		}
	}
}

void Table::dealerTurn() {
	int dealerScore = dealer->getScore();
	bool soft = dealer->isSoft();
	std::cout << "\nShowing Dealer's Hole Card:\n";
	Card temp = dealer->showHoleCard();
	shoe->updateCounts(temp);
	dealer->print();

	if (busts < numPlaying) {
		while (dealer->dealerHits()) {
			std::cout << "Dealer hits.\n";
			dealer->dealCard(shoe->deal());
			dealer->print();
			if (dealer->getScore() > 21)
				std::cout << "Dealer busted with " << dealer->getScore() << "!\n";
		}

		if (dealer->getScore() <= 21)
			std::cout << "Dealer stands with " << dealer->getScore() << ".\n";
	}
	else
		std::cout << "Everyone busted. Dealer wins!\n";
}


bool Table::hit(int p) {
	players[p]->dealCard(shoe->deal());
	players[p]->print();
	if (players[p]->getScore() > 21) {
		std::cout << "Player " << players[p]->getPosition() << " Busted with " <<
			players[p]->getScore() << ".\n";
		return false;
	}
	else
		return true;
}

void Table::printWinners() {
	std::cout << "\nResults:\n";
	int dealerScore = dealer->getScore();
	int score = 0;
	bool dealerBJ = dealer->hasBlackjack(),
		playerBJ = false,
		playerIns = false;
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (players[i]->isPlaying()) {
			playerBJ = players[i]->hasBlackjack();
			playerIns = players[i]->hasInsurance();
			if (dealerBJ) {
				if (playerBJ && playerIns) {
					std::cout << "Player " << players[i]->getPosition()
						<< " took even money.\n";
					players[i]->modBank(2);
				}
				else if (playerIns) {
					std::cout << "Player " << players[i]->getPosition()
						<< " has insurance.\n";
					players[i]->modBank(1);
				}
				else if (playerBJ) {
					std::cout << "Player " << players[i]->getPosition()
						<< " has Blackjack too and pushes.\n"; //doesn't lose bet
					players[i]->modBank(1);
				}
				else {
					std::cout << "Player " << players[i]->getPosition()
						<< " loses to Blackjack.\n";
				}
			}
			//Dealer does not have Blackjack
			else {
				if (playerIns) {
					std::cout << "Player " << players[i]->getPosition()
						<< " loses insurance bet.\n";
				}
				if (playerBJ) {
					std::cout << "Player " << players[i]->getPosition()
						<< " wins with Blackjack!\n";
					players[i]->modBank(2.5);
				}
				else if (dealerScore > 21) {
					if ((score = players[i]->getScore()) <= 21) {
						std::cout << "Player " << players[i]->getPosition()
							<< " wins from dealer bust!\n";
						players[i]->modBank(2);
					}
					else {
						std::cout << "Player " << players[i]->getPosition()
							<< " busted with " << score << "!\n";
					}
				}
				else {
					if ((score = players[i]->getScore()) > dealerScore && score <= 21) {
						std::cout << "Player " << players[i]->getPosition()
							<< " wins with " << score << "!\n";
						players[i]->modBank(2);
					}
					else if (score == dealerScore) {
						std::cout << "Player " << players[i]->getPosition()
							<< " pushes.\n";
						players[i]->modBank(1);
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
	std::cout << std::endl;
}