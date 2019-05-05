#include "StaticVars.h"
#include "Card.h"
#include "Game.h"

int main(int argc, char* argv[]) {

    QApplication a(argc, argv);
    static Game* game = new Game();

    game->run();
/*
	int numDecks = 4;

	std::cout.precision(2);

	Shoe* shoe = new Shoe(numDecks);
	//Shoe* shoe = new Shoe(Card(1, 0), 1000);
	shoe->shuffle(3);

    Card temp;
    size_t remainingCards = shoe->getSize();
    //active(1-127), control(0-127), strategy(0-127)
    Table table(shoe, 7, 0, 127);
    size_t numPlaying = table.getNumPlaying();


	int cutCard = uni(rng);
	std::cout << "Cut Card: " << cutCard << std::endl;

    while ((static_cast<int>(remainingCards) - (static_cast<int>(numPlaying) + 1) * 3) > cutCard
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
*/

    return a.exec();
}
