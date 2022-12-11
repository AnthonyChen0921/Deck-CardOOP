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
        unsigned int contract = 0;
        vector<unsigned int> bids(players.size(), 0); // bids of each player
        vector <unsigned int> scores(players.size()/2, 0); // tally the scores of each team to see if team meets the contract

        // bid round
        if(bid(bids, scores, contract) == message::misdeal){
            collectCardsFromPlayer();
            // ask to deal again
            cout << "Same bid score! Deal Again (Press any key)" << endl;
            char c;
            cin >> c;
            continue;
        } 

        // play tricks round
        playTricks(bids, scores, contract);
        
        // collect the cards from the players to the deck
        collectCardsFromPlayer();
        // ask the player want to end the game or not
        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
    }
}

void PinochleGame::playTricks(std::vector<unsigned int> &bids, std::vector<unsigned int> &scores, unsigned int &contract){
    // repeatedly have each player in turn, initially starting with the player on the team that was awarded the contract whose bid was higher (or if the team members' bids were the same, is the earlier of them in the list of players that was passed to the program), move a card from their hand into an (initially empty) CardSet for that "trick" in the game:
    // the player who moves the first card into the trick is the "leader" of that trick
    int first_player = findFirstPlayer(bids, contract);
    // initialize a vector of CardSet to store the cards of each trick
    CardSet<PinochleRank, Suit> trick;
    // declare first player
    cout << players[first_player] << " has the highest bid and is the first player to play" << endl;
    // repeatedly have each player in turn, move a card from their hand to the trick, untill all cards are played
    int turn = 0;
    while (turn < PinochleGameGameRules::num_of_turns){
        cout << "Turn " << turn+1 << " starts:" << endl;
        cout << players[first_player] << " is the first player to play this round" << endl;
        int player_count = 0;
        CardSet<PinochleRank, Suit> trick_thisRound;
        while (player_count < PinochleGameGameRules::num_of_players){
            int i = (first_player + player_count) % PinochleGameGameRules::num_of_players;
            // Get the hand of the current player
            std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map = convertCardSetToMap(hands[i]);
            Suit trick_suit = Suit::undefined;
            PinochleRank trick_rank = PinochleRank::undefined;
            // printMap(map);
            if(i == first_player){
                // find the highest card in the hand and play it to the trick
                PinochleRank highest_rank = findHighestRank(map);
                // find the suit of the highest card
                Suit highest_suit = findHighestSuit(map, highest_rank);
                // if there is a card of the trump suit of that highest rank that card should be played; otherwise the card of that highest rank that is of the highest non-trump suit should be played
                if (map[highest_rank].find(trump_suit) != map[highest_rank].end()){
                    highest_suit = trump_suit;
                }
                // move the card from the hand to the trick
                cout << players[i] << " plays " << Card<PinochleRank, Suit>(highest_rank, highest_suit) << endl;
                trick_suit = highest_suit;
                trick_rank = highest_rank;
                map[highest_rank][highest_suit]--;
                hands[i].removeCard(highest_rank, highest_suit);
                trick_thisRound.addCard(Card<PinochleRank, Suit>(highest_rank, highest_suit));
            }
            // Every player after that must follow suit, by playing a card of the same suit that was led, if they can:
            // 1. If a card of the trump suit was led, if the player has a trump card that is higher in rank than any other card of the trump suit that has been played so far in that trick, the player's highest card in the trump suit should be played; otherwise the player should play their lowest ranked card of the trump suit if they have one, and if not should play their lowest ranked card of any non-trump suit
            // 2. If a non-trump suit was led, and the player has a card of that suit, then if no trump cards have been played so far in that trick, and they have a higher card in the suit that was led than any other card of that suit so far in the trick, they should play the highest card they have in the suit that was led
            // 3. If a non-trump suit was led, and the player has a card of that suit, but a trump card or a higher card than they have in the suit that was led has been played so far in that trick, they should play their lowest ranked card of the suit that was led
            // 4. If a player does not have a card of the non-trump suit that was led, then if they have a trump card that is higher in rank than any other trump card that has been played, they should play their highest ranked trump card; otherwise they should play the lowest ranked card of any non-trump suit
            else if (i != first_player){
                Suit first_suit = trick_suit;
                PinochleRank first_rank = trick_rank;

                PinochleRank highest_rank = findHighestRank(map);
                Suit highest_suit = findHighestSuit(map, highest_rank);
                // if there is a card of the trump suit of that highest rank that card should be played; otherwise the card of that highest rank that is of the highest non-trump suit should be played
                if (map[highest_rank].find(trump_suit) != map[highest_rank].end()){
                    highest_suit = trump_suit;
                }
                // if the first card is a trump card
                if (first_suit == trump_suit){
                    // if the player has a trump card that is higher in rank than any other card of the trump suit that has been played so far in that trick, the player's highest card in the trump suit should be played
                    if (map[highest_rank].find(trump_suit) != map[highest_rank].end() && highest_rank > first_rank){
                        cout << players[i] << " plays " << Card<PinochleRank, Suit>(highest_rank, highest_suit) << endl;
                        map[highest_rank][highest_suit]--;
                        hands[i].removeCard(highest_rank, highest_suit);
                        trick_thisRound.addCard(Card<PinochleRank, Suit>(highest_rank, highest_suit));
                    }
                    // otherwise the player should play their lowest ranked card of the trump suit if they have one, and if not should play their lowest ranked card of any non-trump suit
                    else{
                        // find the lowest card in the hand and play it to the trick
                        PinochleRank lowest_rank = findLowestRank(map);
                        // find the suit of the lowest card
                        Suit lowest_suit = findLowestSuit(map, lowest_rank);
                        // if there is a card of the trump suit of that lowest rank that card should be played; otherwise the card of that lowest rank that is of the lowest non-trump suit should be
                        if (map[lowest_rank].find(trump_suit) != map[lowest_rank].end()){
                            lowest_suit = trump_suit;
                        }
                        cout << players[i] << " plays " << Card<PinochleRank, Suit>(lowest_rank, lowest_suit) << endl;
                        map[lowest_rank][lowest_suit]--;
                        hands[i].removeCard(lowest_rank, lowest_suit);
                        trick_thisRound.addCard(Card<PinochleRank, Suit>(lowest_rank, lowest_suit));
                    }
                }
                // if the first card is not a trump card
                else if (first_suit != trump_suit){
                    // if the player has a card of that suit, then if no trump cards have been played so far in that trick, and they have a higher card in the suit that was led than any other card of that suit so far in the trick, they should play the highest card they have in the suit that was led
                    if (map[highest_rank].find(first_suit) != map[highest_rank].end() && highest_rank > first_rank){
                        cout << players[i] << " plays " << Card<PinochleRank, Suit>(highest_rank, highest_suit) << endl;
                        map[highest_rank][highest_suit]--;
                        hands[i].removeCard(highest_rank, highest_suit);
                        trick_thisRound.addCard(Card<PinochleRank, Suit>(highest_rank, highest_suit));
                    }
                    // if the player has a card of that suit, but a trump card or a higher card than they have in the suit that was led has been played so far in that trick, they should play their lowest ranked card of the suit that was led
                    else if (map[highest_rank].find(first_suit) != map[highest_rank].end() && highest_rank <= first_rank){
                        // find the lowest card in the hand and play it to the trick
                        PinochleRank lowest_rank = findLowestRank(map);
                        // find the suit of the lowest card
                        Suit lowest_suit = findLowestSuit(map, lowest_rank);
                        // if there is a card of the trump suit of that lowest rank that card should be played; otherwise the card of that lowest rank that is of the lowest non-trump suit should be
                        if (map[lowest_rank].find(first_suit) != map[lowest_rank].end()){
                            lowest_suit = first_suit;
                        }
                        cout << players[i] << " plays " << Card<PinochleRank, Suit>(lowest_rank, lowest_suit) << endl;
                        map[lowest_rank][lowest_suit]--;
                        hands[i].removeCard(lowest_rank, lowest_suit);
                        trick_thisRound.addCard(Card<PinochleRank, Suit>(lowest_rank, lowest_suit));
                    }
                    // if a player does not have a card of the non-trump suit that was led,
                    else if (map[highest_rank].find(first_suit) == map[highest_rank].end()){
                        // if the player has a trump card, they should play their highest ranked trump card
                        if (map[highest_rank].find(trump_suit) != map[highest_rank].end()){
                            cout << players[i] << " plays " << Card<PinochleRank, Suit>(highest_rank, highest_suit) << endl;
                            map[highest_rank][highest_suit]--;
                            hands[i].removeCard(highest_rank, highest_suit);
                            trick_thisRound.addCard(Card<PinochleRank, Suit>(highest_rank, highest_suit));
                        }
                        // otherwise they should play their lowest ranked card of any non-trump suit
                        else{
                            // find the lowest card in the hand and play it to the trick
                            PinochleRank lowest_rank = findLowestRank(map);
                            // find the suit of the lowest card
                            Suit lowest_suit = findLowestSuit(map, lowest_rank);
                            // if there is a card of the trump suit of that lowest rank that card should be played; otherwise the card of that lowest rank that is of the lowest non-trump suit should be
                            if (map[lowest_rank].find(first_suit) != map[lowest_rank].end()){
                                lowest_suit = first_suit;
                            }
                            cout << players[i] << " plays " << Card<PinochleRank, Suit>(lowest_rank, lowest_suit) << endl;
                            map[lowest_rank][lowest_suit]--;
                            hands[i].removeCard(lowest_rank, lowest_suit);
                            trick_thisRound.addCard(Card<PinochleRank, Suit>(lowest_rank, lowest_suit));
                        }
                    }
                }
            }
            player_count++;
        }
        
        // print out the trick
        trick_thisRound.print(cout, print_format_4);

        // extract the cards in the trick_thisRound into a vector
        vector<Card<PinochleRank, Suit>> trick_cards_vector;
        for (int i = 0; i < static_cast<int>(trick_thisRound.getSize()); i++){
            trick_cards_vector.push_back(trick_thisRound[i]);
        }

        bool trump_played = false;
        // check if trump was played
        for (int i = 0; i < static_cast<int>(trick_cards_vector.size()); i++){
            if (trick_cards_vector[i].suit == trump_suit){
                trump_played = true;
            }
        }
        // determine the winner of the trick this round
        // If trump was played, the player who first played the highest-ranked card of the trump suit wins the trick; otherwise if trump was not played, the player who first played the highest-ranked card of the suit that was led wins the trick -- if a trick has two cards of the same highest rank (e.g., both tens) of the trump suit, or of the suit that was led if no trump was played, the player who played the first of those cards wins the trick.
        if (trump_played){
            std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map = convertCardSetToMap(trick_thisRound);
            // find the highest card in the hand and play it to the trick
            PinochleRank highest_rank = findHighestRank(map);

            // find the player who played the highest card
            for (int i = 0; i < static_cast<int>(trick_cards_vector.size()); i++){
                if (trick_cards_vector[i].rank == highest_rank && trick_cards_vector[i].suit == trump_suit){
                    first_player = i;
                    cout << players[i] << " wins the trick in round " << turn+1 << endl << endl;
                    break;
                }
            }
        } 
        // if trump was not played
        else{
            std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map = convertCardSetToMap(trick_thisRound);
            // find the highest card in the hand and play it to the trick
            PinochleRank highest_rank = findHighestRank(map);
            // find the suit of the highest card
            Suit highest_suit = findHighestSuit(map, highest_rank);
            // find the player who played the highest card
            for (int i = 0; i < static_cast<int>(trick_cards_vector.size()); i++){
                if (trick_cards_vector[i].rank == highest_rank && trick_cards_vector[i].suit == highest_suit){
                    first_player = i;
                    cout << players[i] << " wins the trick in this round" << endl;
                    break;
                }
            }
        }


        // push trick_thisRound to trick
        for (int i = 0; i < static_cast<int>(trick_thisRound.getSize()); i++){
            trick_thisRound >> trick;
        }

        turn++;
    }
    // collect the cards from the trick
    deck.collect(trick);
}



PinochleRank PinochleGame::findHighestRank(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map){
    // find the highest card in the hand and play it to the trick
    PinochleRank highest_rank = PinochleRank::nine;
    for(auto m:map){
        if(m.first > highest_rank){
            highest_rank = m.first;
        }
    }
    return highest_rank;
}

Suit PinochleGame::findHighestSuit(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, PinochleRank &highest_rank){
    // find the suit of the highest card
    Suit highest_suit = Suit::clubs;
    for(auto m:map[highest_rank]){
        if(m.first > highest_suit){
            highest_suit = m.first;
        }
    }
    return highest_suit;
}

PinochleRank PinochleGame::findLowestRank(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map){
    // find the lowest card in the hand and play it to the trick
    PinochleRank lowest_rank = PinochleRank::ace;
    for(auto m:map){
        if(m.first < lowest_rank){
            lowest_rank = m.first;
        }
    }
    return lowest_rank;
}

Suit PinochleGame::findLowestSuit(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> &map, PinochleRank &lowest_rank){
    // find the suit of the lowest card
    Suit lowest_suit = Suit::spades;
    for(auto m:map[lowest_rank]){
        if(m.first < lowest_suit){
            lowest_suit = m.first;
        }
    }
    return lowest_suit;
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
    cout << "Team1:" << sum1 << " = bids1:" << bids[0] + bids[2] << " + cardPoints1:" << cardPoints[0] + cardPoints[2] << endl;
    cout << "Team2:" << sum2 << " = bids2:" << bids[1] + bids[3] << " + cardPoints2:" << cardPoints[1] + cardPoints[3] << endl;
    if (sum1 > sum2){
        cout << "Team 1 wins the contract" << endl << endl;
        contract = 1;
        scores[0] = bids[0] + bids[2];
    }
    else if (sum1 < sum2){
        cout << "Team 2 wins the contract" << endl << endl;
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

void printMap(std::unordered_map<PinochleRank,std::unordered_map<Suit,int>> map){
    for(auto m:map){
        cout << m.first << ": ";
        for(auto n:m.second){
            cout << n.first << " " << n.second << " ";
        }
        cout << endl;
    }
}

int PinochleGame::findFirstPlayer(std::vector<unsigned int> &bids, unsigned int &contract){
    // find the first player with the greatest bid in bids in which winning the contract
    if(contract == 1){
        if(bids[0] >= bids[2]){
            return 0;
        }
        return 2;
    } else if(contract == 2){
        if(bids[1] >= bids[3]){
            return 1;
        }
        return 3;
    }
    return 0;
}