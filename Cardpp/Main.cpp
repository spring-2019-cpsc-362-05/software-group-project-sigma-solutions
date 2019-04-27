#include <iostream>
#include <vector>
#include <random>

#include "Shoe.h"
#include "Player.h"
#include "Table.h"

#include <random>

int main() {
	int numDecks = 10;

	Shoe* shoe = new Shoe(numDecks);
	shoe->shuffle(3);

	Card temp;
	int round = 1;
	size_t remainingCards = shoe->getSize();

	Table table(shoe, 255, 0, 255);
	size_t numPlaying = table.getNumPlaying();


	size_t cutCard = (numDecks * 52 * uni(rng)) / 100;
	std::cout << "Cut Card: " << cutCard << std::endl;

	while ((remainingCards - (numPlaying +1) * 3) > cutCard) {
		remainingCards = table.playRound();
	}

	std::cout << "Only " << remainingCards - cutCard << " cards until" 
		<< " cut card. Ending game.\n";
	table.~Table();
	return 0;
}