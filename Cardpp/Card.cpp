std::string Card::setCardImage(int index, int suit){
    std::string returnString  = ":/images/";
    
    //2-10 for number cards. Face Cards: A = 1, J = 11, Q = 12, K = 13
    // 0 = Spades, 1 = Hearts, 2 = Diamonds, 3 = Clubs
    
    std::string spades = "_of_spades.png";
    std::string hearts = "_of_hearts.png";
    std::string diamonds = "_of_diamonds.png";
    std::string clubs = "_of_clubs.png";
    
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
