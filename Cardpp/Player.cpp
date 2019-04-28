#include "Player.h"

Player::Player()
{
	dealer = false;
	controlled = false;
	counting = false;
	insurance = false;
	position = 0;
	bank = DEFAULT_BANK;
	bet = DEFAULT_BET;
	std::vector<Hand> hands;
}

Player::Player(std::string playerType, int _position) {
	if (playerType.compare("dealer") == 0){
		dealer = true;
		controlled = false;
	}
	else if (playerType.compare("computer") == 0) {
		dealer = false;
		controlled = false;
	}
	else if (playerType.compare("user") == 0) {
		dealer = false;
		controlled = true;
	}
	else {
		dealer = false;
		controlled = false;
	}

	insurance = false;
	playing = false;
	position = _position;
	bank = DEFAULT_BANK;
	bet = DEFAULT_BET;
	std::vector<Hand> hands;
}

void Player::setUserControlled() { controlled = true; }
void Player::activate() {playing = true;}
void Player::deactivate() { playing = false; }
void Player::setStrategy(bool _counting) { counting = _counting; }

void Player::takeInsurance(){
	insurance = true;
	bank -= (bet * 0.5);
}

bool Player::canDoubleDown(size_t h) const {
	return ((bank - bet >= 0.0) && hands[h].canDoubleDown());
}
bool Player::canSplit(size_t h) const {
	return (bank >= (double)bet && hands[h].canSplit());
}

Player::~Player()
{
}

bool Player::isDealer() const {	return dealer;}
bool Player::isControlled() const { return controlled; }
bool Player::isPlaying() const { return playing; }
bool Player::isCounting() const { return counting; }
bool Player::hasInsurance() const { return insurance; }
size_t Player::getNumHands() const { return hands.size(); }
int Player::getScore(int i) const { return hands[i].getScore(); }
int Player::getPosition() const { return position; }
double Player::getBank() const { return bank; }
int Player::getBet() const { return bet; }
bool Player::isSoft(int i) const { return hands[i].isSoft(); }
std::string Player::collectWinnings(double winnings){
	std::ostringstream out;
	if (winnings > 0) {
		bank += winnings;
		out << " and receives $" << std::setprecision(2) << std::fixed << winnings;
	}
	return out.str();
}

Hand& Player::hand(size_t i) { return hands[i]; }

void Player::takeBet(size_t h, int _bet){
	if (hands.size() < (h + 1)) {
		hands.push_back(Hand());
	}
	bank -= bet;
	hands[h].addBet(bet);
	std::cout << "Player " << position << " bets $" << std::fixed << bet
		<< ". Bank is now $" << std::fixed << bank << std::endl;
}

bool Player::dealerHits() const {
	if (hands[0].getScore() < 22) {
		if (hands[0].isSoft())
			return (hands[0].getScore() <= 17);
		else
			return (hands[0].getScore() < 17);
	}
	return false;
}

int Player::getShowing() const {
	return (hands[0][0].getIndex());
}

void Player::printHands() const {
	size_t len = hands.size();
	for (size_t i = 0; i < len; i++) {
		printHand(i);
	}	
}

void Player::printHand(size_t i) const {
	std::cout << "\tHand" << ((hands.size() > 1) ?
		(" " + std::to_string(i + 1)) : "") << ":\t";
	hands[i].print();
}

void Player::print() const {
	printPlayer();
	printHands();
}

void Player::printPlayer() const {
	if (!dealer) {
		std::cout << ((controlled) ? "H-" : "C-");
		std::cout << "Player " << position << " ($" << std::fixed << bank
			<< "): \n";
	}
	else
		std::cout << "Dealer:\n";
}

Card Player::showHoleCard() {
	hands[0][0].showCard();
	updateScore(0, hands[0][0]);
	return hands[0][0];
}

void Player::reset() {
	for (size_t i = 0; i < hands.size(); i++) {
		hands[i].reset();
	}
	hands.clear();
	bet = DEFAULT_BET;
	insurance = false;
}


bool Player::split(size_t h, int _bet) {
	hands.push_back(hands[h].split());
	hands.back().addBet(_bet);
	recalculateScores();
	return true;
}

void Player::recalculateScores(){
	for (size_t i = 0; i < hands.size(); i++)
		hands[i].recalculateScore();
}

void Player::dealCard(int i, Card card) {
	if (hands.size() < (i + 1)) {
		hands.push_back(Hand());
	}

	if (!card.isHidden())
		hands[i].dealCard(card);
	else
		hands[i].dealHidden(card);
}

bool Player::updateScore(int i, Card card) {
	return hands[i].updateScore(card);
}

bool Player::hasBlackjack(int i) const {
	return hands[i].hasBlackjack();
}

void Player::setBet(int _bet) { bet = _bet; }

void Player::setBank(double _bank) { bank = _bank; }

void Player::dealerCheat() {
	hands[0][0] = Card(10, 0);
	hands[0][0].hideCard();
	hands[0][1] = Card(1, 0);
	hands[0].recalculateScore();
}
