#include "Hand.h"


Hand::Hand(QGraphicsPixmapItem* parent) : QObject(), QGraphicsPixmapItem(parent)
{
	std::vector<Card> cards;
	score = 0;
	received = 0;
	bet = 0;
    handIndex = 0;

}

Hand::Hand(size_t index)
{
    std::vector<Card> cards;
    score = 0;
    received = 0;
    bet = 0;
    handIndex = index;
}


Hand::Hand(const Hand& _hand)
{
    std::vector<Card*> cards(_hand.cards);
    score = _hand.score;
    received = _hand.received;
    bet = _hand.bet;
}

Hand::~Hand()
{
}

void Hand::draw(QGraphicsScene* _scene){
    qDebug() << "Adding Hand to scene.";
    _scene->addItem(this);
    qDebug() << "Added Hand to scene.";
    for(size_t i = 0; i < cards.size(); i++){
        cards[i]->draw(_scene);
    }
}


size_t Hand::size() const { return cards.size(); }
int Hand::getBet() const { return bet; }

void Hand::incReceived() { received += 1; }
void Hand::addBet(int _bet) { bet += _bet; }

void Hand::print() const {
    size_t len = size();
    for (size_t i = 0; i < len; i++) {
        cards[i]->print();
		std::cout << "\t";
	}
	std::cout << "Score: " << score << "  Bet: " << bet << std::endl;
}
bool Hand::canSplit() const {
    return ((cards.size() == 2) && (cards[0]->getIndex() == cards[1]->getIndex()));
}

bool Hand::canDoubleDown() const {
	return (received == 0);
}

int Hand::getScore() const { return score; }

bool Hand::softenHand() {
    for (size_t i = 0; i < cards.size(); i++) {
        if (!cards[i]->isHidden()) {
            if (cards[i]->getValue() == 11) {
                return cards[i]->setAceSoft();
			}
		}
	}
	return false;
}

bool Hand::updateScore(Card* card) {
    if (card->getIndex() == 1) {
		if (score <= 10)
			score += 11;
		else
			score += 1;
	}
	else
        score += card->getValue();

	if (score > 21) {
		return softenHand();
	}
	return true;
}

bool Hand::isSoft() const {
    for (size_t i = 0; i < cards.size(); i++) {
        if (cards[i]->getValue() == 11)
			return true;
	}
	return false;
}


int Hand::recalculateScore() {
    int score = 0;
    for (size_t i = 0; i < cards.size(); i++) {
        if (!cards[i]->isHidden()) {
            if (cards[i]->getIndex() == 1) {
				if (score <= 10)
					score += 11;
				else
					score += 1;
			}
			else {
                score += cards[i]->getValue();
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
        && ((cards[0]->getValue() + cards[1]->getValue()) == 21));
}

void Hand::dealCard(Card* card) {
    Card* temp = new Card(card);
    temp->setPixmap(QPixmap(card->getCardImageFileName()));
    cards.push_back(temp);
    updateScore(temp);
    delete card;
    card = nullptr;
}

void Hand::dealHidden(Card* card) {
    Card* temp = new Card(card);
    temp->setPixmap(QPixmap(card->getCardImageFileName()));
    temp->hideCard();
    cards.push_back(temp);
    delete card;
    card = nullptr;
}

void Hand::reset() {
	cards.clear();
	score = 0;
	received = 0;
}

Hand* Hand::split() {
    Hand* newHand = new Hand(this);
    newHand->cards.push_back(cards.back());
	cards.pop_back();
	return newHand;
}

Card* Hand::getCard(size_t i){
	return cards[i];
}


void Hand::setCard(size_t i, Card* _card){
    Card* temp = cards[i];
    cards[i] = _card;
    delete temp;
    temp = nullptr;
}
