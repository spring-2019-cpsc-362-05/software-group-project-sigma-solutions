#include "card.h"
#include <QDebug>

#define INDEX_ERR 100

Card::Card()
{
    index = 1;
    suit = 1;
    value = 1;
    hidden = false;
    imageFilePath = "";
    
    //QT - 500, 726
    // draw graphics
    setPixmap((QPixmap(":/images/ace_of_spades.png")).scaledToHeight(150,Qt::FastTransformation));
}

Card::~Card()
{}


Card::Card(int _index, int _suit) {
    index = _index;
    suit = _suit;
    value = getValue(_index);
    hidden = false;
    imageFilePath = getCardImagePath(index, suit);
    //void setCardImage(imageFilePath);
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
QString Card::getCardImagePath(int index, int suit){
    QString returnString  = ":/images/";
    
    //2-10 for number cards. Face Cards: A = 1, J = 11, Q = 12, K = 13
    // 0 = Spades, 1 = Hearts, 2 = Diamonds, 3 = Clubs
    
    QString spades = "_of_spades.png";
    QString hearts = "_of_hearts.png";
    QString diamonds = "_of_diamonds.png";
    QString clubs = "_of_clubs.png";
    
    switch (index)
    {
        case 1: returnString += "ace";  break;
        case 2: returnString += "2";    break;
        case 3: returnString += "3";    break;
        case 4: returnString += "4";    break;
        case 5: returnString += "5";    break;
        case 6: returnString += "6";    break;
        case 7: returnString += "7";    break;
        case 8: returnString += "8";    break;
        case 9: returnString += "9";    break;
        case 10:returnString += "10";   break;
        case 11:returnString += "king"; break;
        case 12:returnString += "queen";break;
        case 13:returnString += "king"; break;
        default:
            qDebug("Error in Card.cpp -> Expected Card index 1-13");
    }
    switch (suit) {
        case 0: returnString += spades;   break;
        case 1: returnString += hearts;   break;
        case 2: returnString += diamonds; break;
        case 3: returnString += clubs;    break;
        default:
            qDebug("Error in Card.cpp -> Expected Card suit 0-3");
    }
    return returnString;
}

void setCardImage(QString filepath) {
    //this->setPixmap(QPixmap(filepath)).scaledToHeight(150,Qt::FastTransformation));
}
