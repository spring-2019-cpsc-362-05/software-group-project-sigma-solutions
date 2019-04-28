#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include "Shoe.h"
#include "Player.h"
#include "Table.h"

#include <random>

int main() {
	int numDecks = 8;

	std::cout.precision(2);

	Shoe* shoe = new Shoe(numDecks);
	//Shoe* shoe = new Shoe(Card(1, 0), 1000);
	shoe->shuffle(3);

	Card temp;
	int round = 1;
	size_t remainingCards = shoe->getSize();
	//active, control, strategy
	Table table(shoe, 255, 15, 255);
	size_t numPlaying = table.getNumPlaying();


	size_t cutCard = uni(rng);
	std::cout << "Cut Card: " << cutCard << std::endl;

	while (((remainingCards - (numPlaying + 1) * 3) > cutCard)
		&& table.getNumPlaying() > 0) {

		table.placeBets();
		if (table.getNumPlaying() > 0)
			remainingCards = table.playRound();
	}

	if (table.getNumPlaying() > 0) {
		std::cout << "Only " << remainingCards - cutCard << " cards until"
			<< " cut card. Ending game.\nFinal Score:\n" << std::string(57, '-') << std::endl;
		table.print();
	}
	else
		std::cout << "Everyone is out of money. Ending game.";

	table.~Table();
	return 0;
}