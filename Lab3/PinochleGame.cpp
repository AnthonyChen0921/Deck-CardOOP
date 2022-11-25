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
    // initialize the trump suit to be undefined
    trump_suit = Suit::undefined;
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
    // get dealer cards pointer
    CardSet<PinochleRank, Suit> tmp(hands[dealer]);
    std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::*ptrToCards=CardSet<PinochleRank, Suit>::getCardsPtr();
    std::vector< Card<PinochleRank, Suit> > cards = tmp.*ptrToCards;

    // get dealer's last card suit
    trump_suit = cards.back().suit;
    cout << "Trump suit is " << trump_suit << endl;
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
        suit_independent_evaluation(hands[i], melds);
        suit_dependent_evaluation(hands[i], melds, trump_suit);
        if(melds.size() == 0){
            cout << "No melds" << endl << endl;
        }
        else{
            cout << "Melds: " << endl;
            for(auto m:melds){
                cout<<m<<endl;
            }
        }
        cout << endl;
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
        // declaring and intializing the vector of players' bids, and initiate a round of bidding by the players
        vector<unsigned int> bids(players.size(), 0);
        vector <unsigned int> scores(players.size()/2, 0);
        unsigned int contract = 0;
        vector <unsigned int> contractPoint(players.size()/2, 0);
        if(bid(bids, scores, contract) == message::misdeal){
            collectCardsFromPlayer();
            // ask to deal again
            cout << "Deal Again (Press any key)" << endl;
            char c;
            cin >> c;
            continue;
        } else{
        }
        // collect the cards from the players to the deck
        collectCardsFromPlayer();
        // ask the player want to end the game or not
        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
    }
}



int PinochleGame::bid(std::vector<unsigned int> &bids, std::vector<unsigned int> &scores, unsigned int &contract){
    // Each player should then store the value of their bid at the appropriate position in the bids vector
    // The first and third players are a team, and the second and fourth players are a team: the bids of the players on the same team should be added together and the team with the highest sum of their bids is awarded the contract for that deal; if both teams have the same combined bid score, however, a misdeal is declared and the cards are re-dealt from the same dealer position, the trump suit is again determined by the last card, and bidding is repeated again
    // Once a contract has been established, a separate running tally of points for the team that was awarded the contract should be initialized with the sum of the values of all the melds in both of their hands
    // for each player in turn should compute a value to bid based on the sum of the values of the melds in their hand
    // and the values of the cards in their hands, starting with the next player after the dealer, use %
    std::vector<PinochleMelds> melds;
    std::vector<unsigned int> cardPoints(players.size(), 0);
    int playerCount = 0;
    while (playerCount < static_cast<int>(players.size())){
        // modulous to get the next player
        int i = (dealer + playerCount + 1) % players.size();
        // get the melds of the player
        suit_independent_evaluation(hands[i], melds);
        suit_dependent_evaluation(hands[i], melds, trump_suit);
        for(auto m:melds){
            bids[i] += PinochleGame::points[m];
        }
        // get the points of the cards of the player
        cardPoints[i] = getCardPoints(hands[i]);
        melds.clear();
        playerCount++;
    }
    // The first and third players are a team, and the second and fourth players are a team: the bids of the players on the same team should be added together and the team with the highest sum of their bids is awarded the contract for that deal; if both teams have the same combined bid score, however, a misdeal is declared and the cards are re-dealt from the same dealer position, the trump suit is again determined by the last card, and bidding is repeated again
    unsigned int sum1 = bids[0] + bids[2] + cardPoints[0] + cardPoints[2];
    unsigned int sum2 = bids[1] + bids[3] + cardPoints[1] + cardPoints[3];
    cout << "sum1:" << sum1 << " bids1:" << bids[0] + bids[2] << " cardPoints1:" << cardPoints[0] + cardPoints[2] << endl;
    cout << "sum2:" << sum2 << " bids2:" << bids[1] + bids[3] << " cardPoints2:" << cardPoints[1] + cardPoints[3] << endl;
    if (sum1 > sum2){
        cout << "Team 1 wins the contract" << endl;
        contract = 1;
        scores[0] = bids[0] + bids[2];
    }
    else if (sum1 < sum2){
        cout << "Team 2 wins the contract" << endl;
        contract = 2;
        scores[1] = bids[1] + bids[3];
    }
    else{
        cout << "Misdeal" << endl;
        return message::misdeal;
    }
    // print points
    for (int i = 0; i < static_cast<int>(scores.size()); i++){
        cout << "Team " << i + 1 << " points: " << scores[i] << endl;
    }
    return message::SUCCESS;
}

/**
 * @brief getCardPoints() function compute the points of the cards in the hand
 * 
 * @param hand 
 * @return unsigned int 
 */
unsigned int PinochleGame::getCardPoints(const CardSet<PinochleRank, Suit> &hand){
    unsigned int cardPoints = 0;
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> m = convertCardSetToMap(hand);
    for(auto it = m.begin(); it != m.end(); it++){
        if(it->first == PinochleRank::ace){
            cardPoints += 11;
        }
        else if(it->first == PinochleRank::ten){
            cardPoints += 10;
        }
        else if(it->first == PinochleRank::king){
            cardPoints += 4;
        }
        else if(it->first == PinochleRank::queen){
            cardPoints += 3;
        }
        else if(it->first == PinochleRank::jack){
            cardPoints += 2;
        }
    }
    return cardPoints;
}



/**
 * @brief convert the CardSet to a map of rank and suit, sorted by rank and suit
 * 
 * @param cs 
 * @return std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> 
 */
std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> PinochleGame::convertCardSetToMap(const CardSet<PinochleRank, Suit> &cs){
    CardSet<PinochleRank, Suit> tmp(cs);
    std::vector< Card<PinochleRank, Suit> > CardSet<PinochleRank, Suit>::*ptrToCards=CardSet<PinochleRank, Suit>::getCardsPtr();
    std::vector< Card<PinochleRank, Suit> > cards = tmp.*ptrToCards;
    std::sort(cards.begin(),cards.end(),compareRank<PinochleRank, Suit>);
    std::sort(cards.begin(),cards.end(),compareSuit<PinochleRank, Suit>);

    //maintain a hashmap to check cards
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> m;
    for(auto c:cards)
        m[c.rank][c.suit]++;
    return m;
} 


/**
 * @brief suit_independent_evaluation() function 
 *          maintain a hashmap to store the number of cards
            start checking from ace to jack
 * @return 
 *              
 */void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit> &cs, std::vector<PinochleMelds> &melds){
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> m = convertCardSetToMap(cs);

    //check aces
    if(m[PinochleRank::ace][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ace][Suit::hearts]==static_cast<int>(cardNumber::pair))
        melds.push_back(PinochleMelds::thousandaces);
    else if(m[PinochleRank::ace][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::clubs]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::ace][Suit::hearts]==static_cast<int>(cardNumber::single))
        melds.push_back(PinochleMelds::hundredaces);
    
    //check king
    if(m[PinochleRank::king][Suit::spades]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::clubs]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::diamonds]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][Suit::hearts]==static_cast<int>(cardNumber::pair))
        melds.push_back(PinochleMelds::eighthundredkings);
    else if(m[PinochleRank::king][Suit::spades]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][Suit::clubs]==static_cast<int>(cardNumber::single) &&m[PinochleRank::king][Suit::diamonds]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][Suit::hearts]==static_cast<int>(cardNumber::single))
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



void PinochleGame::suit_dependent_evaluation(const CardSet<PinochleRank, Suit> &cs, std::vector<PinochleMelds> &melds, Suit s){
    std::unordered_map<PinochleRank,std::unordered_map<Suit,int> > m = convertCardSetToMap(cs);

    // check for insuitdoublerun
    if(m[PinochleRank::ace][s]==static_cast<int>(cardNumber::pair) && m[PinochleRank::ten][s]==static_cast<int>(cardNumber::pair) && m[PinochleRank::king][s]==static_cast<int>(cardNumber::pair) && m[PinochleRank::queen][s]==static_cast<int>(cardNumber::pair) && m[PinochleRank::jack][s]==static_cast<int>(cardNumber::pair)){
        melds.push_back(PinochleMelds::insuitdoublerun);
    }
    // check for insuitrun
    else if(m[PinochleRank::ace][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::ten][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::king][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::jack][s]==static_cast<int>(cardNumber::single)){
        melds.push_back(PinochleMelds::insuitrun);
    }
    // check for insuitmarriage
    else if(m[PinochleRank::king][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][s]==static_cast<int>(cardNumber::single)){
        melds.push_back(PinochleMelds::insuitmarriage);
    }
    // check for offsuitmarriage
    else if(m[PinochleRank::king][s]==static_cast<int>(cardNumber::single) && m[PinochleRank::queen][s]==static_cast<int>(cardNumber::single)){
        melds.push_back(PinochleMelds::offsuitmarriage);
    }
    // check for dix
    else if(m[PinochleRank::nine][s]==static_cast<int>(cardNumber::single)){
        melds.push_back(PinochleMelds::dix);
    }
}