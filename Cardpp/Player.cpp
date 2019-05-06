#include "Player.h"
#include "Game.h"

extern Game* game;

Player::Player() : QObject(), QGraphicsPixmapItem()
{
	dealer = false;
	controlled = false;
	counting = false;
	insurance = false;
	position = 0;
	bank = DEFAULT_BANK;
	bet = DEFAULT_BET;
    std::vector<Hand*> hands;
}

Player::Player(const Player& p){
    dealer = p.isDealer();
    controlled = p.isControlled();
    counting = p.isCounting();
    insurance = p.hasInsurance();
    position = p.getPosition();
    bank = p.getBank();
    bet = p.getBet();
}

Player::Player(bool _dealer, int _position, QGraphicsItem* parent ): QGraphicsPixmapItem(parent)
{
    if(_dealer){
        setPos(PLAYER_XPOS[7],PLAYER_YPOS[7]);
    }
    else{
        setPos(PLAYER_XPOS[_position - 1],PLAYER_YPOS[_position-1]);
    }

    dealer = _dealer;
    controlled = false;
	insurance = false;
	playing = false;
	position = _position;
    bank = game->startBank;
    bet = game->minBet;
    std::vector<Hand*> hands;
    hands.push_back(new Hand(this));
    label = new QGraphicsTextItem(this);
    label->setPos(-5, -50);
    label->setDefaultTextColor(Qt::cyan);
    label->setFont(QFont("times", 16));
    bankLabel = new QGraphicsTextItem(this);
    bankLabel->setPos(-5, -30);
    bankLabel->setDefaultTextColor(QColor(255,195,0));
    bankLabel->setFont(QFont("times", 16));

    //label->drawText(static_cast<int>(x()), static_cast<int>(y())-10, "Player" + QString(_position));
}

void Player::setUserControlled() { controlled = true; }
void Player::activate() {playing = true;}
void Player::deactivate() { playing = false; }
void Player::setStrategy(bool _counting) { counting = _counting; }

void Player::takeInsurance(){
	insurance = true;
	bank -= (bet * 0.5);
}

bool Player::canDoubleDown(size_t h) const {
    return ((bank - bet >= 0.0) && hands[h]->canDoubleDown());
}
bool Player::canSplit(size_t h) const {
    return (bank >= static_cast<double>(bet) && hands[h]->canSplit());
}

Player::~Player()
{
}

void Player::draw(QGraphicsScene* _scene){
    qDebug() << "Added Player to scene.";
    _scene->addItem(this);
 //   for(size_t i = 0; i < hands.size(); i++){
//        hands[i]->draw(_scene);
 //   }
}

bool Player::isDealer() const {	return dealer;}
bool Player::isControlled() const { return controlled; }
bool Player::isPlaying() const { return playing; }
bool Player::isCounting() const { return counting; }
bool Player::hasInsurance() const { return insurance; }
size_t Player::getNumHands() const { return hands.size(); }
int Player::getScore(size_t i) const { return hands[i]->getScore(); }
int Player::getPosition() const { return position; }
double Player::getBank() const { return bank; }
int Player::getBet() const { return bet; }
bool Player::isSoft(size_t i) const { return hands[i]->isSoft(); }
std::string Player::collectWinnings(double winnings){
	std::ostringstream out;
	if (winnings > 0) {
		bank += winnings;
		out << " and receives $" << std::setprecision(2) << std::fixed << winnings;
	}
	return out.str();
}

Hand* Player::getHand(size_t i) { return hands[i]; }

void Player::takeBet(size_t h, int _bet){
    while (hands.size() < (h + 1)) {
        hands.push_back(new Hand(this));
    }
    bank -= _bet;
    hands[h]->addBet(bet);
    setBankLabel();
}

bool Player::dealerHits() const {
    if (hands[0]->getScore() < 22) {
        if (hands[0]->isSoft())
            return (hands[0]->getScore() <= 17);
		else
            return (hands[0]->getScore() < 17);
	}
	return false;
}

size_t Player::getShowing() const {
    return (hands[0]->getCard(1)->getIndex());
}

void Player::printHands() const {
    size_t len = getNumHands();
    for (size_t i = 0; i < len; i++) {
		printHand(i);
	}	
}

void Player::printHand(size_t i) const {
	std::cout << "\tHand" << ((hands.size() > 1) ?
		(" " + std::to_string(i + 1)) : "") << ":\t";
    hands[i]->print();
}

void Player::print() const {
	printPlayer();
	printHands();
}

void Player::printPlayer() const {
	if (!dealer) {
		std::cout << ((controlled) ? "H-" : "C-");
		std::cout << "Player " << position << " ($" << std::fixed << bank
			<< "): \n";
	}
	else
		std::cout << "Dealer:\n";
}

Card* Player::showHoleCard() {
    hands[0]->getCard(0)->showCard();
    updateScore(0, hands[0]->getCard(0));
    return hands[0]->getCard(0);
}

void Player::reset() {
    for (size_t i = 0; i < hands.size(); i++) {
        hands[i]->reset();
	}
	hands.clear();
	bet = DEFAULT_BET;
	insurance = false;
}


bool Player::split(size_t h, int _bet) {
    hands.push_back(hands[h]->split(this));
    hands.back()->addBet(_bet);
    for(size_t i = 0; i < hands.size(); i++){
        hands[i]->repositionCards();
    }
    repositionHands();
	recalculateScores();
	return true;
}

void Player::recalculateScores(){
    for (size_t i = 0; i < hands.size(); i++)
        hands[i]->recalculateScore();
}

void Player::dealCard(size_t h, Card* card) {
    while (hands.size() < (h + 1)) {
        createNewHand();
    }

    if (!card->isHidden())
        hands[h]->dealCard(card);
	else
        hands[h]->dealHidden(card);

    if(!dealer)
        repositionHands();
    else
        dealerPositionHand();
}

bool Player::updateScore(size_t i, Card* card) {
    return hands[i]->updateScore(card);
}

bool Player::hasBlackjack() const {
    return hands[0]->hasBlackjack();
}

void Player::setBet(int _bet) { bet = _bet; }

void Player::setBank(double _bank) { bank = _bank; }

void Player::dealerCheat() {
    hands[0]->setCard(0, new Card(10, 0));
    hands[0]->getCard(0)->hideCard();
    hands[0]->setCard(1, new Card(1, 0));
    hands[0]->recalculateScore();
}

void Player::setLabel(){
    label->setPlainText(QString("Player ") + QString::number(position));
}

void Player::setBankLabel(){
    bankLabel->setPlainText(QString("Bank $") + QString::number(bank));
}

void Player::repositionHands(){
    int yPos = 0;
    for(size_t i = 0; i < hands.size(); i++){
        yPos = (C_HEIGHT+10)*static_cast<int>(i);
        hands[i]->setPos(0, yPos);
    }
}


void Player::dealerPositionHand(){
    hands[0]->dealerPositionCards();
}


void Player::createNewHand(){
    Hand *temp = new Hand(this);
    int yPos = (C_HEIGHT+10)*static_cast<int>(hands.size());
    hands.push_back(temp);
    temp->setY(yPos);
    temp->repositionCards();
}

