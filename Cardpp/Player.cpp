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
	score = 0;
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
	score = 0;
}

void Player::setUserControlled() { controlled = true; }
void Player::activate() {playing = true;}
void Player::deactivate() { playing = false; }
void Player::setStrategy(bool _counting) { counting = _counting; }
void Player::takeInsurance(){
	insurance = true;
	modBank(-0.5);
}


bool Player::canDoubleDown() const {
	return (bank >= bet && hand.size() == 2);
}

Player::~Player()
{
}

bool Player::isDealer() const {	return dealer;}
bool Player::isControlled() const { return controlled; }
bool Player::isPlaying() const { return playing; }
bool Player::isCounting() const { return counting; }
bool Player::hasInsurance() const { return insurance; }
size_t Player::getHandSize() const { return hand.size(); }
int Player::getScore() const { return score; }
int Player::getPosition() const { return position; }
int Player::getBank() const { return bank; }
int Player::getBet() const { return bet; }
void Player::takeBet(int bet) { bank -= bet; }

bool Player::isSoft() const {
	for (size_t i = 0; i < hand.size(); i++) {
		if (hand[i].getValue() == 11)
			return true;
	}
	return false;
}

bool Player::dealerHits() const {
	if (score < 22) {
		if (isSoft())
			return (score <= 17);
		else
			return (score < 17);
	}
	return false;
}

int Player::getShowing() const {
	return hand[1].getIndex();
}

void Player::printHand() const {
	size_t len = hand.size();
	for (size_t i = 0; i < len; i++) {
		hand[i].print();
		std::cout << "\t";
	}
	std::cout << "Score: " << score << std::endl;
}

void Player::print() const {
	if (!dealer) {
		std::cout << ((controlled)? "H-" : "C-");
		std::cout << "Player " << position << " ($" << std::fixed << bank
			<< "): \t";
	}
	else
		std::cout << "\t       Dealer:\t";
	printHand();
}


Card Player::showHoleCard() {
	hand[0].showCard();
	updateScore(hand[0]);
	return hand[0];
}

void Player::reset() {
	hand.clear();
	score = 0;
	bet = DEFAULT_BET;
	insurance = false;
}

void Player::dealCard(Card card) {
	if (!card.isHidden())
		updateScore(card);
	hand.push_back(card);
}

bool Player::updateScore(Card card) {
	if (card.getIndex() == 1) {
		if (score <= 10)
			score += 11;
		else
			score += 1;
	}
	else
		score += card.getValue();

	if (score > 21) {
		size_t i = 0;
		bool softened = false;
		while(!softened && i < hand.size()) {
			softened = hand[i++].setAceSoft();
			if (softened) {
				score -= 10;
				return true;
			}
		}
		return false;
	}
	return true;
}

bool Player::hasBlackjack() const {
	if (hand.size() == 2) {
		if ((hand[0].getValue() + hand[1].getValue()) == 21)
			return true;
	}
	return false;
}


void Player::modBank(double mod) {
	bank += (mod * bet);
	std::string str = ((mod >= 0) ? " receives $" : " pays $");
	std::cout << "Player " << position << str << std::fixed << abs((mod*bet))
		<< ". Bank is now $" << std::fixed << bank << std::endl;
}

void Player::setBet(int _bet) { bet = _bet; }

void Player::setBank(double _bank) { bank = _bank; }

void Player::dealerCheat() {
	hand[0] = Card(10, 0);
	hand[0].hideCard();
	hand[1] = Card(1, 0);
	score = 11;
}