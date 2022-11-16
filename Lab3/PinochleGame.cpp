/*
    PinochleGame.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 19, 2022
*/

#include "PinochleGame.h"

using namespace std;

/**
 * @brief constructor pass argc and argv to base class Game
 * 
 * @param argc the number of players
 * @param argv the name of players
 * 
 * @note A tutorial on how to call base class constructor: 
 * https://stackoverflow.com/questions/15777635/c-calling-base-class-constructors
 */
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv){
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        hands.push_back(CardSet<PinochleRank, Suit>());
    }
}

/**
 * @brief initialize static member points
 *              
 */
 std::unordered_map<PinochleMelds,int> PinochleGame::points = {
    {PinochleMelds::dix, 10},
    {PinochleMelds::offsuitmarriage, 20},
    {PinochleMelds::fortyjacks,40},
    {PinochleMelds::pinochle,40},
    {PinochleMelds::insuitmarriage,40},
    {PinochleMelds::sixtyqueens,60},
    {PinochleMelds::eightykings,80},
    {PinochleMelds::hundredaces,100},
    {PinochleMelds::insuitrun,150},
    {PinochleMelds::doublepinochle,300},
    {PinochleMelds::fourhundredjacks,400},
    {PinochleMelds::sixhundredqueens,600},
    {PinochleMelds::eighthundredkings,800},
    {PinochleMelds::thousandaces,1000},
    {PinochleMelds::insuitdoublerun,1500}
};
/**
 * @brief deal() function repeatedly shift cards to each player's hand, 3 at a time
 *        until the deck is empty
 * 
 */
void PinochleGame::deal(){
    // calculate number of cards to deal in a round
    size_t numCards = PinochleGameGameRules::packet_of_cards * players.size();
    // deal 3 cards to each player until the deck is empty
    cout << "Dealing cards..." << endl;
    while (deck.getSize() >= numCards){
        for (int i = 0; i < static_cast<int>(hands.size()); i++)
        {
            deck >> hands[(i + dealer + 1) % hands.size()];
            deck >> hands[(i + dealer + 1) % hands.size()];
            deck >> hands[(i + dealer + 1) % hands.size()];  
        }
    }
}


//define a left shift operator (operator<<) that takes a reference to an ostream and a const reference to a variable of the PinochleMelds enumerated type,which prints out an appropriate string for the name of the label and the points value associated with the label as an unsigned decimal integer (with a space in between them), and then returns a reference to the ostream that was passed to it.
std::ostream &operator<<(std::ostream &os, const PinochleMelds &pm){
    switch (pm)
    {
    case PinochleMelds::dix:
        os << "dix ";
        break;
    case PinochleMelds::offsuitmarriage:
        os << "offsuitmarriage ";
        break;
    case PinochleMelds::fortyjacks:
        os << "fortyjacks ";
        break;
    case PinochleMelds::pinochle:
        os << "pinochle ";
        break;
    case PinochleMelds::insuitmarriage:
        os << "insuitmarriage ";
        break;
    case PinochleMelds::sixtyqueens:
        os << "sixtyqueens ";
        break;
    case PinochleMelds::eightykings:
        os << "eightykings ";
        break;
    case PinochleMelds::hundredaces:
        os << "hundredaces ";
        break;
    case PinochleMelds::insuitrun:
        os << "insuitrun ";
        break;
    case PinochleMelds::doublepinochle:
        os << "doublepinochle ";
        break;
    case PinochleMelds::fourhundredjacks:
        os << "fourhundredjacks ";
        break;
    case PinochleMelds::sixhundredqueens:
        os << "sixhundredqueens ";
        break;
    case PinochleMelds::eighthundredkings:
        os << "eighthundredkings ";
        break;
    case PinochleMelds::thousandaces:
        os << "thousandaces ";
        break;
    case PinochleMelds::insuitdoublerun:
        os << "insuitdoublerun ";
        break;
    default:
        break;
    }
    os<<":"<<PinochleGame::points[pm] <<"points"<<endl;
    return os;
}

/**
 * @brief printPlayersHand() function print out the hands of each player and the melds
 * 
 */
void PinochleGame::printPlayersHand(){

    std::vector<PinochleMelds> melds;
    for (int i = 0; i < static_cast<int>(hands.size()); i++)
    {
        // if the player is the dealer, an asterisk (*) is added to the player's name
        if (i == static_cast<int>(dealer)){
            cout << players[i] << "*'s hand: " << endl;
        }
        else{
            cout << players[i] << "'s hand: " << endl;
        }
        hands[i].print(cout, GameRules::print_format_4);
        cout << endl;
        PinochleGame::suit_independent_evaluation(hands[i], melds);
        for(auto m:melds){
            cout<<m<<endl;
        }
        melds.clear();
    }

}

/**
 * @brief collectCards() function collect the cards from the players to the deck
 * 
 */
void PinochleGame::collectCardsFromPlayer(){
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        deck.collect(hands[i]);
    }
}



/**
 * @brief play() function 
 * 
 * @return possible return values: 
 *              message::end_game
 *              
 */
int PinochleGame::play(){
    while (true)
    {
        // shuffle the deck
        deck.shuffle();
        // deal the cards
        deal();
        // print out the hands of each player and melds
        printPlayersHand();
        // collect the cards from the players to the deck
        collectCardsFromPlayer();
        // ask the player want to end the game or not
        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
    }
}




/**
 * @brief suit_independent_evaluation() function 
 *          maintain a hashmap to store the number of cards
            start checking from ace to jack
 * @return 
 *              
 */void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit> &cs, std::vector<PinochleMelds> &melds){
    CardSet<PinochleRank, Suit> tmp(cs);
    std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::*ptrToCards=CardSet<PinochleRank, Suit>::getCardsPtr();
    std::vector<Card<PinochleRank, Suit>> cards = tmp.*ptrToCards;
    std::sort(cards.begin(),cards.end(),compareRank<PinochleRank, Suit>);
    std::sort(cards.begin(),cards.end(),compareSuit<PinochleRank, Suit>);
    
    //maintain a hashmap to check cards
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> m;
    for(auto c:cards)
        m[c.rank][c.suit]++;

    //check aces
    if(m[PinochleRank::ace][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::hearts]==static_cast<int>(cardNumber::pair))
        melds.push_back(PinochleMelds::thousandaces);
    else if(m[PinochleRank::ace][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::clubs]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::hearts]==static_cast<int>(cardNumber::single))
        melds.push_back(PinochleMelds::hundredaces);
    
    //check king
    if(m[PinochleRank::king][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::hearts]==static_cast<int>(cardNumber::pair))
        melds.push_back(PinochleMelds::eighthundredkings);
    else if(m[PinochleRank::king][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][Suit::clubs]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][Suit::hearts]==static_cast<int>(cardNumber::single))
        melds.push_back(PinochleMelds::eightykings);
    
    //check queen
    bool queenUsed=false;
    if(m[PinochleRank::queen][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::queen][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::queen][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::queen][Suit::hearts]==static_cast<int>(cardNumber::pair)){
        melds.push_back(PinochleMelds::sixhundredqueens);
        queenUsed = true;
        }
    else if(m[PinochleRank::queen][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][Suit::clubs]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][Suit::hearts]==static_cast<int>(cardNumber::single)){
        melds.push_back(PinochleMelds::sixtyqueens);
        queenUsed = true;
    }
       
    //check jack
    bool jackUsed=false;
    if(m[PinochleRank::jack][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::jack][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::jack][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::jack][Suit::hearts]==static_cast<int>(cardNumber::pair)){
        melds.push_back(PinochleMelds::fourhundredjacks);
        jackUsed=true;
    }
    else{
        if(m[PinochleRank::jack][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::jack][Suit::clubs]==static_cast<int>(cardNumber::single) && m[PinochleRank::jack][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::jack][Suit::hearts]==static_cast<int>(cardNumber::single)){
            melds.push_back(PinochleMelds::fortyjacks);
            jackUsed=true;
        }
    }    
    //if no queen and jack was used, check doublepinochle and pinochle 
    if( (!jackUsed) && (!queenUsed) ) {
            if(m[PinochleRank::jack][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::queen][Suit::spades]==static_cast<int>(cardNumber::pair))
                melds.push_back(PinochleMelds::doublepinochle);
            else if(m[PinochleRank::jack][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][Suit::spades]==static_cast<int>(cardNumber::single))
                melds.push_back(PinochleMelds::pinochle);
    }
       
}