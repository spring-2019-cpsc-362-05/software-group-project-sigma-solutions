#include "Hand.h"


Hand::Hand()
{
	std::vector<Card> cards;
	score = 0;
	received = 0;
	bet = 0;
}

Hand::~Hand()
{
}

int Hand::size() const { return static_cast<int>(cards.size()); }
int Hand::getBet() const { return bet; }

void Hand::incReceived() { received += 1; }
void Hand::addBet(int _bet) { bet += _bet; }

void Hand::print() const {
	int len = size();
	for (int i = 0; i < len; i++) {
		cards[i].print();
		std::cout << "\t";
	}
	std::cout << "Score: " << score << "  Bet: " << bet << std::endl;
}
bool Hand::canSplit() const {
	return ((cards.size() == 2) && (cards[0].getIndex() == cards[1].getIndex()));
}

bool Hand::canDoubleDown() const {
	return (received == 0);
}

int Hand::getScore() const { return score; }

bool Hand::softenHand() {
	for (int i = 0; i < cards.size(); i++) {
		if (!cards[i].isHidden()) {
			if (cards[i].getValue() == 11) {
				return cards[i].setAceSoft();
			}
		}
	}
	return false;
}

bool Hand::updateScore(Card card) {
	if (card.getIndex() == 1) {
		if (score <= 10)
			score += 11;
		else
			score += 1;
	}
	else
		score += card.getValue();

	if (score > 21) {
		return softenHand();
	}
	return true;
}

bool Hand::isSoft() const {
	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].getValue() == 11)
			return true;
	}
	return false;
}

int Hand::recalculateScore() {
	score = 0;
	for (int i = 0; i < cards.size(); i++) {
		if (!cards[i].isHidden()) {
			if (cards[i].getIndex() == 1) {
				if (score <= 10)
					score += 11;
				else
					score += 1;
			}
			else {
				score += cards[i].getValue();
			}
		}
	}

	while (isSoft() && score > 21) {
		softenHand();
	}

	return score;
}

bool Hand::hasBlackjack() const {
	return ((cards.size() == 2) 
		&& ((cards[0].getValue() + cards[1].getValue()) == 21));
}

void Hand::dealCard(Card card) {
	cards.push_back(card);
	updateScore(card);
}

void Hand::dealHidden(Card card) {
	cards.push_back(card);
}

void Hand::reset() {
	cards.clear();
	score = 0;
	received = 0;
}

Hand Hand::split() {
	Hand newHand;
	newHand.cards.push_back(cards.back());
	received = 0;
	cards.pop_back();
	return newHand;
}

Card& Hand::operator[](int i){
	return cards[i];
}

const Card& Hand::operator[](int i) const {
	return cards[i];
}