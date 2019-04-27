#include "Shoe.h"

Shoe::Shoe()
{
}

Shoe::~Shoe()
{
}

Shoe::Shoe(int decks) {

	for (int d = 0; d < decks; d++) {
		for (int s = 0; s < 4; s++) {
			for (int i = 1; i < 14; i++) {
				addCard(i, s);
			}
		}
	}
}

void Shoe::addCard(int index, int suit) {
	cards.push_back(Card(index, suit));
}

size_t Shoe::getSize() const { return cards.size(); }

Card Shoe::deal() {
	Card temp = cards.back();
	cards.pop_back();
	return temp;
}

Card Shoe::dealHidden() {
	Card temp = deal();
	temp.hideCard();
	return temp;
}

void Shoe::shuffle(int times) {
	for (int i = 0; i < times; i++) {
		std::shuffle(cards.begin(), cards.end(), rng);
	}
}

void Shoe::print() const {
	size_t len = cards.size();
	for (size_t i = 0; i < len; i++) {
		cards[i].print();
		std::cout << std::endl;
	}
}