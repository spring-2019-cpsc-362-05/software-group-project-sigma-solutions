#include "Card.h"

Card::Card(QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent)
{
	index = 1;
	suit = 1;
	value = 1;
    hidden = false;
    setPixmap(QPixmap(CARD_BACK).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}

Card::Card(Card* card): QGraphicsPixmapItem(){
    index = card->getIndex();
    suit = card->getSuit();
    value = getValue(index);
    hidden = card->isHidden();
    setPixmap(QPixmap(getCardImageFileName()).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}

Card::Card(const Card& _card){
    index = _card.getIndex();
    suit = _card.getSuit();
    value = getValue(index);
    hidden = _card.isHidden();
    setPixmap(QPixmap(getCardImageFileName()).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}

void Card::addToScene(QGraphicsScene* scene){
    scene->addItem(this);
}


Card::Card(size_t _index, size_t _suit){
    index = _index;
    suit = _suit;
    value = getValue(_index);
    hidden = false;
    setPixmap(QPixmap(getCardImageFileName()).scaled(C_WIDTH, C_HEIGHT, Qt::IgnoreAspectRatio,Qt::FastTransformation));
}


void Card::draw(QGraphicsScene* _scene){
    qDebug() << "Drawing " << getCardImageFileName() << " to scene.";
    _scene->addItem(this);
}

Card Card::operator=(const Card& _card){
    return Card(_card);
}


size_t Card::getIndex() const { return index; }
size_t Card::getSuit() const { return suit; }
int Card::getValue() const  { return value; }
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

int Card::getValue(size_t index) const{
	if (index >= 2 && index <= 10)
        return static_cast<int>(index);
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


QString Card::getCardImageFileName(){
    if(!hidden)
        return QString::fromStdString(":/cards/cards/" + SUIT_STRS[suit] + "-"
                                      + INDEX_STRS[index]  + ".png");
    else {
        return CARD_BACK;
    }
}

