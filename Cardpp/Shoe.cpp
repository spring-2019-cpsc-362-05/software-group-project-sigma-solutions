#include "Shoe.h"

Shoe::Shoe() : QGraphicsRectItem()
{
}

Shoe::~Shoe()
{
}

Shoe::Shoe(int decks) {
    for (size_t d = 0; d < static_cast<size_t>(decks); d++) {
        for (size_t s = 0; s < 4; s++) {
            for (size_t i = 1; i < 14; i++) {
				addCard(i, s);
			}
		}
	}
	runningCount = 0;
	trueCount = 0;
}

Shoe::Shoe(Card* card, int num) {
	for (int i = 0; i < num; i++)
		cards.push_back(card);
	runningCount = 0;
	trueCount = 0;
}



void Shoe::addCard(size_t index, size_t suit) {
    cards.push_back(new Card(index, suit));
}

size_t Shoe::getSize() const { return cards.size(); }
int Shoe::getRunningCount() const { return runningCount; }
int Shoe::getTrueCount() const { return trueCount; }


Card* Shoe::deal() {
    Card* temp = cards.back();
	updateCounts(temp);
	cards.pop_back();
	return temp;
}

Card* Shoe::dealHidden() {
    Card* temp = cards.back();
	cards.pop_back();
    temp->hideCard();
	return temp;
}

void Shoe::shuffle(int times) {
	for (int i = 0; i < times; i++) {
		std::shuffle(cards.begin(), cards.end(), rng);
	}
}

void Shoe::print() const {
    size_t len = getSize();
    for (size_t i = 0; i < len; i++) {
        cards[i]->print();
		std::cout << std::endl;
	}
}

void Shoe::printCounts() const {
	std::cout << "Running Count: " << ((runningCount > 0) ? "+" : "") << runningCount
		<< "\tTrue Count: " << ((trueCount > 0) ? "+" : "") << trueCount << std::endl;
}

void Shoe::updateCounts(Card* c) {
    runningCount += c->getCountValue();
    trueCount = runningCount / (static_cast<int>(cards.size() / 52));
}
