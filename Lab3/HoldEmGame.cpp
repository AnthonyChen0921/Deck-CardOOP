/*
    HoldEmGame.cpp
    Author: @Anthony Chen @Yunlai Chen
    Email: chenerdong@wustl.edu c.yunlai@wustl.edu
    Date: Sep 24, 2022
*/

#include "HoldEmGame.h"
#include <map>
#include <unordered_map>

using namespace std;

/**
 * @brief constructor: initialize the game and create cards to each player's hand and set ifFold of each player to false
 * 
 * @param argc the number of arguments
 * @param argv the arguments
 */
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop) {
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        hands.push_back(CardSet<HoldEmRank, Suit>());
        ifFold.push_back(false);
        scores.push_back(HoldEmGameInitialScore);
        chipsInPot.push_back(0);
        chipsCurrentRound.push_back(0);
    }
}

std::ostream &operator<<(std::ostream &os, const HoldEmHandRank &rank){
    //shifts an appropriate string for the label into the passed ostream and returns a reference to the ostream
    switch (rank){
        case HoldEmHandRank::xhigh:
            os<< "xhigh";
            break;
        case  HoldEmHandRank::pair:
            os<< "pair";
            break;
        case  HoldEmHandRank::twopair:
            os<< "twopair";
            break;
        case  HoldEmHandRank::threeofakind:
            os<< "threeofakind";
            break;
        case  HoldEmHandRank::straight:
            os<< "straight";
            break;
        case  HoldEmHandRank::flush:    
            os<< "flush";
            break;  
        case  HoldEmHandRank::fullhouse:    
            os<< "fullhouse";
            break;  
        case  HoldEmHandRank::fourofakind:
            os<< "fourofakind";
            break;
        case  HoldEmHandRank::straightflush:
            os<< "straightflush";
            break;
        case  HoldEmHandRank::undefined:
            os<< "undefined";
            break;
        default:
            os<< "undefined";
            break;
    }
    return os;   
}

/**
 * @brief deal() function: deal cards to each player's hand
 *         - deal cards to each player
 *         - increase the state to next state of the game after each round
 */
void HoldEmGame::deal() {
    switch (state) {
        // HoldEmState::preflop deal one card from the deck to each player's hand, 
        // and then deal a second card from the deck to each player's hand, 
        // and then increase the state to the next higher value
        case HoldEmState::preflop:
            for (int i = 0; i < static_cast<int>(players.size()); i++) {
                deck >> hands[(dealer + i + 1) % players.size()];
            }
            for (int i = 0; i < static_cast<int>(players.size()); i++) {
                deck >> hands[(dealer + i + 1) % players.size()];
            }
            break;
        // HoldEmState::flop deal three cards from the deck to the board
        case HoldEmState::flop:
            for (int i = 0; i < HoldEmGameRules::num_of_flop_cards; i++) {
                deck >> board;
            }
            break;
        // HoldEmState::turn deal one card from the deck to the board
        case HoldEmState::turn:
            deck >> board;
            break;
        // HoldEmState::river deal one card from the deck to the board
        case HoldEmState::river:
            deck >> board;
            break;
        // HoldEmState::undefined do nothing
        case HoldEmState::undefined:
            break;
    }
}

/**
 * @brief printPlayersHand() function print out the hands of each player
 * 
 */
void HoldEmGame::printPlayersHand(){
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
    }
}

/**
 * @brief collectCards() function collect the cards from the players to the deck
 * 
 */
void HoldEmGame::collectCardsFromPlayer() {
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        deck.collect(hands[i]);
    }
}

/**
 * @brief collectCardsFromBoard() function collect the cards from the board to the deck
 * 
 */
void HoldEmGame::collectCardsFromBoard() {
    deck.collect(board);
}

/**
 * @brief printBoard() function printout board cards
 * 
 */
void HoldEmGame::printBoard(string s) {
    cout << s << endl;
    board.print(cout, GameRules::print_format_5);
    cout << endl;
}



/**
 * @brief printBoard() function printout board cards
 * 
 */
void HoldEmGame::evaluate() {
    vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::*ptrToCards=CardSet<HoldEmRank, Suit>::getCardsPtr();
    auto cardsOnBoard = board.*ptrToCards;
    int ncard=cardsOnBoard.size();
    int nchoice;
    if(ncard==3)
        nchoice=1;
    if(ncard==4)
        nchoice=4;
    if(ncard==5)
        nchoice=10;
    
    vector<vector<HoldEmPlayer>> vHoldEmPlayers;
    vector<HoldEmPlayer> maxPossibleCards;
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        vector<HoldEmPlayer> p;
        for(int j=0;j<nchoice;j++){
            HoldEmPlayer tmpPlayer(players[i],hands[i], HoldEmHandRank::undefined);
            p.push_back(tmpPlayer);
        }
        vHoldEmPlayers.push_back(p);
    }            
    //(1) add all cards from the common board of cards to the two cards (from the player's hand) in each element's CardSet and then 
    //(2) remove 0/1/2 cards from hand to make it
    for(size_t i=0;i<vHoldEmPlayers.size();i++){ 
        for(size_t j=0;j<vHoldEmPlayers[0].size();j++){          
            //continous
            for(size_t k=j;k<j+3;k++){
                vHoldEmPlayers[i][j].hand.addCard(cardsOnBoard[k]);
            }
            vHoldEmPlayers[i][j].rank=holdem_hand_evaluation (vHoldEmPlayers[i][j].hand);
        }
        sort(vHoldEmPlayers[i].begin(),vHoldEmPlayers[i].end());
        maxPossibleCards.push_back(vHoldEmPlayers[i][nchoice-1]);
    }

    //sort the vector and print out (from the highest ranked to the lowest) each player's name, 
    //card set (which includes the player's cards and the cards from the common board of cards), and hand rank at that point in the game.
    sort(maxPossibleCards.begin(),maxPossibleCards.end());
    cout<<"-------Print out from the highest ranked to the lowest player and their cards:-------------"<<endl;
    for(int i=maxPossibleCards.size()-1;i>=0;i--){
        cout << maxPossibleCards[i].name << " has "<< maxPossibleCards[i].rank<< endl;
        cout <<"card in "<< maxPossibleCards[i].name << "'s hand: " << endl;
        maxPossibleCards[i].hand.print(cout, GameRules::print_format_5);
    }
}
  


/**
 * @brief play function: play the game
 * 
 * @return int possible return values: 
 *              message::end_game
 */
int HoldEmGame::play() {
    // repeat the following steps until the game is over:
    while (true) {
        // shuffle the deck
        deck.shuffle();

        // reset state
        state = HoldEmState::preflop;

              // deal cards to each player's hand
        deal();
        printPlayersHand();
        bet(state);
        
        state = HoldEmState::flop;
        // deal cards to the board in 3 rounds
        deal();
        printBoard("Flop: ");
        evaluate();
        bet(state);


        state = HoldEmState::turn;
        deal();
        printBoard("Turn: ");
        bet(state);

        state = HoldEmState::river;
        deal();
        printBoard("River: ");
        bet(state);

        collectCardsFromPlayer();
        collectCardsFromBoard();
        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
        resetChips();
    }
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> &cs){
    CardSet<HoldEmRank, Suit> tmp(cs);
    std::vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::*ptrToCards=CardSet<HoldEmRank, Suit>::getCardsPtr();
    std::vector<Card<HoldEmRank, Suit>> cards = tmp.*ptrToCards;
    std::sort(cards.begin(),cards.end(),compareRank<HoldEmRank, Suit>);
  
    
    //if cards !=5, return undefined
    if(cards.size()!= static_cast<int>(arrayIndex::HoldEmGameCardNumber))
        return HoldEmHandRank::undefined;
    //check flush
    bool flush=false;
    if (cards[static_cast<int>(arrayIndex::firstCard)].suit == cards[static_cast<int>(arrayIndex::secondCard)].suit && cards[static_cast<int>(arrayIndex::firstCard)].suit == cards[static_cast<int>(arrayIndex::thirdCard)].suit && cards[static_cast<int>(arrayIndex::firstCard)].suit == cards[static_cast<int>(arrayIndex::fourthCard)].suit && cards[static_cast<int>(arrayIndex::firstCard)].suit == cards[static_cast<int>(arrayIndex::fifthCard)].suit ){
        flush=true;
    }
    //check straight
    bool straight=false;
    auto firstRand=cards[static_cast<int>(arrayIndex::firstCard)].rank;
    if (++firstRand == cards[static_cast<int>(arrayIndex::secondCard)].rank && ++firstRand == cards[static_cast<int>(arrayIndex::thirdCard)].rank && ++firstRand == cards[static_cast<int>(arrayIndex::fourthCard)].rank&& ++firstRand == cards[static_cast<int>(arrayIndex::fifthCard)].rank){
        straight=true;
    }
    //straight and flush?
    if(straight && flush)
        return HoldEmHandRank::straightflush;
    else{
        //check fourofakind 
        if (cards[static_cast<int>(arrayIndex::secondCard)].rank == cards[static_cast<int>(arrayIndex::thirdCard)].rank && cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank && (cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank||cards[static_cast<int>(arrayIndex::fifthCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank))
            return HoldEmHandRank::fourofakind;
        //check full House
        if (cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank && cards[static_cast<int>(arrayIndex::fourthCard)].rank == cards[static_cast<int>(arrayIndex::fifthCard)].rank && (cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank||cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank))
            return HoldEmHandRank::fullhouse;
        //flush or straight
        if(flush)
            return HoldEmHandRank::flush;
        if(straight)
            return HoldEmHandRank::straight;
        //check threeofakind  
        if ((cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank && cards[static_cast<int>(arrayIndex::secondCard)].rank == cards[static_cast<int>(arrayIndex::thirdCard)].rank) 
            || (cards[static_cast<int>(arrayIndex::secondCard)].rank == cards[static_cast<int>(arrayIndex::thirdCard)].rank && cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank)
            || (cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank && cards[static_cast<int>(arrayIndex::fourthCard)].rank == cards[static_cast<int>(arrayIndex::fifthCard)].rank))
            return HoldEmHandRank::threeofakind;
        //check two pair
        if ((cards[static_cast<int>(arrayIndex::secondCard)].rank == cards[static_cast<int>(arrayIndex::thirdCard)].rank && cards[static_cast<int>(arrayIndex::fourthCard)].rank == cards[static_cast<int>(arrayIndex::fifthCard)].rank) 
            || (cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank && cards[static_cast<int>(arrayIndex::fourthCard)].rank == cards[static_cast<int>(arrayIndex::fifthCard)].rank)
            || (cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank && cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank))
            return HoldEmHandRank::twopair;
        //check pair
        if (cards[static_cast<int>(arrayIndex::firstCard)].rank == cards[static_cast<int>(arrayIndex::secondCard)].rank || cards[static_cast<int>(arrayIndex::secondCard)].rank == cards[static_cast<int>(arrayIndex::thirdCard)].rank 
            || cards[static_cast<int>(arrayIndex::thirdCard)].rank == cards[static_cast<int>(arrayIndex::fourthCard)].rank || cards[static_cast<int>(arrayIndex::fourthCard)].rank == cards[static_cast<int>(arrayIndex::fifthCard)].rank)
            return HoldEmHandRank::pair;
    }    
        
    return HoldEmHandRank::xhigh;
}

HoldEmGame::HoldEmPlayer::HoldEmPlayer(std::string n, CardSet<HoldEmRank, Suit> h, HoldEmHandRank r) : name(n), hand(h), rank(r) {}

bool operator<(const HoldEmGame::HoldEmPlayer &p1, const HoldEmGame::HoldEmPlayer &p2){
    if(static_cast<int>(p1.rank) < static_cast<int>(p2.rank))
        return true;
    if(static_cast<int>(p1.rank) > static_cast<int>(p2.rank))
        return false;

    //otherwise need to get the card set
    std::vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::*ptrToCards=CardSet<HoldEmRank, Suit>::getCardsPtr();
    std::vector<Card<HoldEmRank, Suit>> cards1 = p1.hand.*ptrToCards;
    std::sort(cards1.begin(),cards1.end(),compareRank<HoldEmRank, Suit>);
    std::vector<Card<HoldEmRank, Suit>> cards2 = p2.hand.*ptrToCards;
    std::sort(cards2.begin(),cards2.end(),compareRank<HoldEmRank, Suit>);

    //if strainght flush, just compare the 1st value
    if(p1.rank==HoldEmHandRank::straightflush)
        return (static_cast<int>(cards1[static_cast<int>(arrayIndex::firstCard)].rank) < static_cast<int>(cards2[static_cast<int>(arrayIndex::firstCard)].rank));
   
    //if fourofakind, compare the value occured 4 times
    if(p1.rank==HoldEmHandRank::fourofakind)
        return (static_cast<int>(cards1[static_cast<int>(arrayIndex::secondCard)].rank) < static_cast<int>(cards2[static_cast<int>(arrayIndex::secondCard)].rank));
    
    //if fullhouse or threeofakind, compare cards[2] which is always in the three 
    if(p1.rank==HoldEmHandRank::fullhouse || p1.rank==HoldEmHandRank::threeofakind)
        return (static_cast<int>(cards1[static_cast<int>(arrayIndex::thirdCard)].rank) < static_cast<int>(cards2[static_cast<int>(arrayIndex::thirdCard)].rank));
    
    //if, xhigh compare the maximum card
    if(p1.rank==HoldEmHandRank::xhigh){
        for(int i=static_cast<int>(arrayIndex::fifthCard);i>=0;i--){
            if(static_cast<int>(cards1[i].rank)<static_cast<int>(cards2[i].rank))
                return true;
        }
        return false;
    }
    //if staright, compare the minimum card
    if(p1.rank==HoldEmHandRank::straight)
        return (static_cast<int>(cards1[static_cast<int>(arrayIndex::firstCard)].rank) < static_cast<int>(cards2[static_cast<int>(arrayIndex::firstCard)].rank));
    
    //if pair search from maximum to minimum and store the paired/distinct ranks
    if(p1.rank==HoldEmHandRank::pair){
        //vRank1 and vRank2 to store the rank only showed once in cards1 and cards2
        std::vector<HoldEmRank> vRank1;
        std::vector<HoldEmRank> vRank2;
        //r1Paired and r2 paired to store the rank in pair of p1 and p2
        HoldEmRank r1Paired;
        HoldEmRank r2Paired;
        vRank1.push_back(cards1[static_cast<int>(arrayIndex::fifthCard)].rank);
        vRank2.push_back(cards2[static_cast<int>(arrayIndex::fifthCard)].rank);

        for(int i=arrayIndex::fourthCard;i>=0;i--){
            if(cards1[i].rank==cards1[i+1].rank){
                vRank1.pop_back();
                r1Paired=cards1[i].rank;
            }
            else
                vRank1.push_back(cards1[i].rank);
            if(cards2[i].rank==cards2[i+1].rank){
                vRank2.pop_back();
                r2Paired=cards2[i].rank;
            }
            else
                vRank2.push_back(cards2[i].rank);   
        }
        if(r1Paired==r2Paired){
            for(int i=0;i<3;i++){
                if(static_cast<int>(vRank1[i])<static_cast<int>(vRank2[i]))
                    return true;
                else{
                    if(static_cast<int>(vRank1[i])>static_cast<int>(vRank2[i]))
                    return false;
                }
            }
        }
        else
            return static_cast<int>(r1Paired)<static_cast<int>(r2Paired);
    } 
    //if twopair, similar with pair, search from maximum to minimum and store the 
    //paired ranks in vector and unpaired in a tmp variable
    if(p1.rank==HoldEmHandRank::twopair){
        //vRank1 and vRank2 to store the rank only showed once in cards1 and cards2
        std::vector<HoldEmRank> vRank1;
        std::vector<HoldEmRank> vRank2;
        //r1Paired and r2 paired to store the rank in pair of p1 and p2
        HoldEmRank r1Single;
        HoldEmRank r2Single;
        for(int i=4;i>=0;i--){
            if(i>0 && cards1[i].rank==cards1[i-1].rank){
                vRank1.push_back(cards1[i].rank);
            }
            else{
                if(i==4 || cards1[i].rank!=cards1[i+1].rank)
                    r1Single=cards1[i].rank;
            }
            if(i>0 && cards2[i].rank==cards2[i-1].rank){
                vRank2.push_back(cards2[i].rank);
            }
            else{
                if(i==4 || cards2[i].rank!=cards2[i+1].rank)
                    r2Single=cards2[i].rank;
            }  
        }
        for(int i=0;i<2;i++){
            if(static_cast<int>(vRank1[i])<static_cast<int>(vRank2[i]))
                return true;
            else{
                if(static_cast<int>(vRank1[i])>static_cast<int>(vRank2[i]))
                    return false;
            }
        }
        
        return static_cast<int>(r1Single)<static_cast<int>(r2Single);
    }
    return false;
}



void HoldEmGame::bet(HoldEmState state){

    //store how many player has taken action after raise; 
    //if that == player size, end the round
    int playerNumber = players.size();
    int actedPlayer=0; //round before floop
    int currentRoundMaximumChip;
    int initialChip;
    int currentPlayerInd;
    int raiseChip;
    int bigblindInd=1;
    int smallblindInd=0;
    if(state==HoldEmState::preflop){
        //assume player 0 and player 1 are small blind and big blind;
        //automatically add bet for small and big blind
        chipsCurrentRound[smallblindInd]=1;
        chipsCurrentRound[bigblindInd]=2;
        scores[smallblindInd] -= 1;
        scores[bigblindInd] -= 2;
        raiseChip = 2;
        currentRoundMaximumChip=2;
        initialChip=2;
        currentPlayerInd = bigblindInd+1;
    }
    if(state==HoldEmState::flop){
        raiseChip = 2;
        currentRoundMaximumChip=0;
        initialChip=0;
        currentPlayerInd = 2;
    }
    if(state==HoldEmState::turn){
        raiseChip = 4;
        currentRoundMaximumChip=0;
        initialChip=0;
        currentPlayerInd = 2;
    }
    if(state==HoldEmState::river){
        raiseChip = 4;
        currentRoundMaximumChip=0;
        initialChip=0;
        currentPlayerInd = 2;
    }


    while(actedPlayer<playerNumber){
        currentPlayerInd=currentPlayerInd%playerNumber;
        //check if folded
        if(ifFold[currentPlayerInd]){
            currentPlayerInd++;
            actedPlayer++;
            continue;
         }
        else{
            //check if there is any raise
            if(currentRoundMaximumChip==initialChip){
                std::cout<<"Player "<<currentPlayerInd<<"'s turn, check or not? y/n"<<std::endl;
                string input;
                cin >> input;
                if (input == "y" || input == "Y" || input == "yes" || input == "Yes"){
                    currentPlayerInd++;
                    actedPlayer++;
                    continue;
                }
            }
            auto playerAction = action(currentPlayerInd);
            std::cout<<"Player "<<currentPlayerInd<<"'s turn, chose ";

            if(playerAction==HoldEmAction::fold){
                cout<<"fold"<<std::endl;
                ifFold[currentPlayerInd]=true;
            }
            if(playerAction==HoldEmAction::call){
                cout<<"call"<<std::endl;
                int diff=currentRoundMaximumChip-chipsCurrentRound[currentPlayerInd];
                if(scores[currentPlayerInd]<diff){
                    ifFold[currentPlayerInd]=true;
                    chipsCurrentRound[currentPlayerInd] += scores[currentPlayerInd];
                    scores[currentPlayerInd]=0;
                }
                else{
                    chipsCurrentRound[currentPlayerInd] += diff;
                    scores[currentPlayerInd] -= diff;
                }
            }
            if(playerAction==HoldEmAction::raise){
                cout<<"raise"<<std::endl;
                currentRoundMaximumChip += raiseChip;
                int diff=currentRoundMaximumChip-chipsCurrentRound[currentPlayerInd];
                if(scores[currentPlayerInd]<diff){
                    ifFold[currentPlayerInd]=true;
                    chipsCurrentRound[currentPlayerInd] += scores[currentPlayerInd];
                    scores[currentPlayerInd]=0;
                }      
                else{
                    chipsCurrentRound[currentPlayerInd] += diff;
                    scores[currentPlayerInd] -= diff;
                }              
                actedPlayer=0;
            }
            currentPlayerInd++;
            actedPlayer++;
        }
    }
    //end the round
    cout<<"end betting round, current chips in pot"<<endl;
    for(int i=0;i<players.size();i++){
        chipsInPot[i] += chipsCurrentRound [i];
        chipsCurrentRound[i] = 0;
        cout<<"player "<<i<<":" <<chipsInPot[i]<<endl;
    }
    cout<<"players folded:"<<endl;
    for(int i=0;i<players.size();i++){
        if(ifFold[i])
            cout<<"player, "<<i<<endl;
    }
    cout<<endl;
    
    return;
}

void HoldEmGame::resetChips(){
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        ifFold[i]=false;
        chipsInPot[i]=0;
        chipsCurrentRound[i]=0;
        scores[i]=HoldEmGameInitialScore;
    }
}


HoldEmAction HoldEmGame::action(int PlayerInd){
    //preflop only check 2 cards in hand     
    auto cardsInHand = hands[PlayerInd];

    if(state==HoldEmState::preflop){
        //check a pair of ace
        if(static_cast<int>(cardsInHand[static_cast<int>(arrayIndex::firstCard)].rank)==static_cast<int>(Rank::ace)
            && static_cast<int>(cardsInHand[static_cast<int>(arrayIndex::secondCard)].rank)==static_cast<int>(Rank::ace))
            return HoldEmAction::raise;
        
        //check if pair 
        if(cardsInHand[static_cast<int>(arrayIndex::firstCard)].rank== cardsInHand[static_cast<int>(arrayIndex::secondCard)].rank){
            //if pair of j/q/k
            if( static_cast<int>(cardsInHand[static_cast<int>(arrayIndex::firstCard)].rank)>static_cast<int>(Rank::ten)  ){
                    if(chipsCurrentRound[PlayerInd]==0)
                        return HoldEmAction::raise;
                    else
                        return HoldEmAction::call;
            }
            //a pair of others
            return HoldEmAction::call;
        }        
        //check if consective
        auto firstRand=cardsInHand[static_cast<int>(arrayIndex::firstCard)].rank;
        if(++firstRand == cardsInHand[static_cast<int>(arrayIndex::secondCard)].rank)
            return HoldEmAction::call;
        //check if same suit
        if(cardsInHand[static_cast<int>(arrayIndex::firstCard)].suit== cardsInHand[static_cast<int>(arrayIndex::secondCard)].suit)
            return HoldEmAction::call;      
        return HoldEmAction::fold;   
    }    
    for(size_t i=0;i<board.getSize();i++){
        cardsInHand.addCard(board[i]);
    }
    std::map<int,int> rankMap;
    std::unordered_map<int,int> suitMap;
    std::vector<int> v;
    for(size_t i=0;i<cardsInHand.getSize();i++){
        rankMap[static_cast<int>(cardsInHand[i].rank)]++;
        suitMap[static_cast<int>(cardsInHand[i].suit)]++;
        v.push_back(static_cast<int>(cardsInHand[i].rank));
    }
    sort(v.begin(),v.end());


    if(state==HoldEmState::flop){
        //check if has three same rank
        for(auto c:rankMap){
            if(c.second>=3)
                return  HoldEmAction::raise;
        }
        for(auto c:rankMap){
            int npair=0;
            if(c.second==2)
                npair++;
            //check if has two pair
            if(npair==2){
                if(chipsCurrentRound[PlayerInd]==0)
                    return HoldEmAction::raise;
                else
                    return HoldEmAction::call;
            }
            //one pair
            if(npair==1){
                return HoldEmAction::call;
            }
        }
        //consective(4)
        if( (v[0]==v[1]-1 && v[0]==v[2]-2 && v[0]==v[3]-3)||(v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-4))
            return  HoldEmAction::call;
        // has 4 same suit       
        for(auto c:suitMap){
            if(c.second==4)
                return  HoldEmAction::call;
        }
        return HoldEmAction::fold;   
    }
    if(state==HoldEmState::turn){
        //check if has straight
        if( (v[0]==v[1]-1 && v[0]==v[2]-2 && v[0]==v[3]-3 && v[0]==v[3]-4)||
            (v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-4 && v[1]==v[5]-5))
            return  HoldEmAction::call;
        //check if has three same rank
        for(auto c:rankMap){
            if(c.second>=3){
                if(chipsCurrentRound[PlayerInd]==0)
                    return HoldEmAction::raise;
                else
                    return HoldEmAction::call;
            }
        }
        for(auto c:rankMap){
            int npair=0;
            if(c.second==2)
                npair++;
            //check if has two pair
            if(npair>=1){
                return HoldEmAction::call;
            }
        }
        //consective(4)
        sort(v.begin(),v.end());
        if( (v[0]==v[1]-1 && v[0]==v[2]-2 && v[0]==v[3]-3)||(v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-3)
            ||(v[2]==v[3]-1 && v[2]==v[4]-2 && v[2]==v[5]-3))
            return  HoldEmAction::call;
        // has 4 same suit       
        for(auto c:suitMap){
            if(c.second==4)
                return  HoldEmAction::call;
        }
        return HoldEmAction::fold;   
    }
    if(state==HoldEmState::river){
        //check if has straight
        if( (v[0]==v[1]-1 && v[0]==v[2]-2 && v[0]==v[3]-3 && v[0]==v[3]-4)||
            (v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-4 && v[1]==v[5]-5)||
            (v[2]==v[3]-1 && v[2]==v[4]-2 && v[2]==v[5]-4 && v[2]==v[6]-5))
            return  HoldEmAction::call;
        //check if has three same rank
        for(auto c:rankMap){
            if(c.second>=3){
                if(chipsCurrentRound[PlayerInd]==0)
                    return HoldEmAction::raise;
                else
                    return HoldEmAction::call;
            }
        }
        for(auto c:rankMap){
            int npair=0;
            if(c.second==2)
                npair++;
            //check if has two pair
            if(npair>1){
                return HoldEmAction::call;
            }
        }
        return HoldEmAction::fold;
    }
    
    return HoldEmAction::fold;

}
