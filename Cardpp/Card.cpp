#include "Card.h"

#define INDEX_ERR 100

Card::Card()
{
	index = 1;
	suit = 1;
	value = 1;
	hidden = false;
}

Card::~Card()
{}


Card::Card(int _index, int _suit) {
	index = _index;
	suit = _suit;
	value = getValue(_index);
	hidden = false;
}

int Card::getIndex() const { return index; }
int Card::getValue() const  { return value; }
int Card::getSuit() const { return suit; }
bool Card::isHidden() const { return hidden; }
void Card::hideCard() { hidden = true; }
void Card::showCard() { hidden = false; }

void Card::print() const {
	if (!hidden)
		std::cout << INDEX_STRS[index] << "-" << SUIT_STRS[suit];
	else
		std::cout << "Hidden  ";
}

bool Card::setAceSoft() {
	if (index == 1) {
		value = 1;
		return true;
	}
	return false;
}

int Card::getValue(int index) const{
	if (index >= 2 && index <= 10)
		return index;
	else if (index >= 11 && index <= 13)
		return 10;
	else if (index == 1)
		return 11;
	else
		return INDEX_ERR;
}

int Card::getCountValue() const {
	if (index >= 2 && index <= 6)
		return 1;
	if (index == 1 || (index >= 10 && index <= 13))
		return -1;
	return 0;
}