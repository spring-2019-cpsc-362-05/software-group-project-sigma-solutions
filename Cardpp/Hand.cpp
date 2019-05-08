#include "Hand.h"
#include "Game.h"

extern Game* game;

Hand::Hand(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent)
{
    std::vector<Card*> cards;
	score = 0;
	received = 0;
	bet = 0;
    handIndex = 0;

    scoreLabel = new QGraphicsTextItem(this);
    scoreLabel->setPos(0,0);
    scoreLabel->setDefaultTextColor(Qt::red);
    scoreLabel->setFont(QFont("Times", 20, QFont::Bold));
    scoreLabel->setZValue(1);

    //setPixmap(QPixmap(QString(":/graphics/other/hand.png")).scaled(P_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}

Hand::Hand(size_t index)
{
    std::vector<Card*> cards;
    score = 0;
    received = 0;
    bet = 0;
    handIndex = index;
    scoreLabel = new QGraphicsTextItem(this);
    scoreLabel->setPos(0,0);
    scoreLabel->setDefaultTextColor(Qt::red);
    scoreLabel->setFont(QFont("Times", 20, QFont::Bold));
    scoreLabel->setZValue(1);
    //setPixmap(QPixmap(QString(":/graphics/other/hand.png")).scaled(P_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}


Hand::Hand(const Hand& _hand)
{
    std::vector<Card*> cards(_hand.cards);
    score = _hand.score;
    received = _hand.received;
    bet = _hand.bet;
    scoreLabel = new QGraphicsTextItem(this);
    scoreLabel->setPos(0,0);
    scoreLabel->setDefaultTextColor(Qt::red);
    scoreLabel->setFont(QFont("Times", 20, QFont::Bold));
    scoreLabel->setZValue(1);

    //setPixmap(QPixmap(QString(":/graphics/other/hand.png")).scaled(P_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
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
    repositionScore();
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
    score = 0;
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
    repositionScore();

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
    Card* temp = new Card(card, this);
    setPixmap(QPixmap(card->getCardImageFileName()).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
    cards.push_back(temp);
    updateScore(temp);
    int xPos = (static_cast<int>(cards.size())-1)*C_WIDTH/3;
    temp->setX(xPos);
    repositionScore();
    delete card;
    card = nullptr;
}

void Hand::dealHidden(Card* card) {
    Card* temp = new Card(card, this);
    temp->hideCard();
    setPixmap(QPixmap(card->getCardImageFileName()).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
    cards.push_back(temp);
    int xPos = (static_cast<int>(cards.size())-1)*C_WIDTH/3;
    temp->setX(xPos);
    repositionScore();
    delete card;
    card = nullptr;
}

void Hand::reset() {
    for(size_t i = 0; i < cards.size(); i++)
        game->scene->removeItem(cards[i]);
    scoreLabel->setPlainText("");
	cards.clear();
	score = 0;
	received = 0;
}

Hand* Hand::split(QGraphicsPixmapItem* parent) {
    Hand* newHand = new Hand(parent);
    Card* oldCard = cards.back();
    Card* newCard = new Card(oldCard, newHand);
    newHand->cards.push_back(newCard);
    qDebug() << "The New Hand's score is: " << newHand->recalculateScore();
    cards.pop_back();
    qDebug() << "The Old Hand's score is: " << recalculateScore();
    delete oldCard;
    oldCard = nullptr;
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


void Hand::repositionCards(){
    for(size_t i = 0; i < cards.size(); i++){
        cards[i]->setPos(0, (C_WIDTH/3)*static_cast<int>(i));
    }
    repositionScore();
}

void Hand::repositionScore(){
    scoreLabel->setPlainText(QString::number(score));
    int xPos = C_WIDTH + C_WIDTH/3*static_cast<int>(cards.size()-1);
    scoreLabel->setPos(xPos-15, -5);
}


void Hand::dealerPositionCards(){
    for(size_t i = 0; i < cards.size(); i++){
        cards[i]->setX((C_WIDTH+5)*static_cast<int>(i));
        dealerPositionScore();
    }
}
void Hand::dealerPositionScore(){
    scoreLabel->setPlainText(QString::number(score));
    int xPos = (C_WIDTH+5)*static_cast<int>(cards.size());
    scoreLabel->setPos(xPos-15, -5);
}
