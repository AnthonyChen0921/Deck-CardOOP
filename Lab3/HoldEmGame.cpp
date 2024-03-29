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
        ifAllIn.push_back(false);
        scores.push_back(HoldEmGameInitialScore);
        chipsInPot.push_back(0);
        chipsCurrentRound.push_back(0);
        seats[players[i]]=i;
    }
    winnerName=players[bigblindInd];
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
    vector<vector<HoldEmPlayer>> vHoldEmPlayers;
    vector<HoldEmPlayer> maxPossibleCards;
    for (int i = 0; i < static_cast<int>(hands.size()); i++){
        //construct a cardset containing all cards in hand and board
        auto cardsInHand = hands[i];
        for(size_t j=0;j<board.getSize();j++){
            cardsInHand.addCard(board[j]);
        }
        int nc=cardsInHand.getSize();
        vector<HoldEmPlayer> p;
        for(int a=0;a<nc;a++){
            for(int b=a+1;b<nc;b++){
                for(int c=b+1;c<nc;c++){
                    for(int d=c+1;d<nc;d++){
                        for(int e=d+1;e<nc;e++){
                            CardSet<HoldEmRank, Suit> tmpHand;
                            tmpHand.addCard(cardsInHand[a]);
                            tmpHand.addCard(cardsInHand[b]);
                            tmpHand.addCard(cardsInHand[c]);
                            tmpHand.addCard(cardsInHand[d]);
                            tmpHand.addCard(cardsInHand[e]);
                            HoldEmPlayer tmpPlayer(players[i],tmpHand,HoldEmHandRank::undefined);
                            tmpPlayer.rank=holdem_hand_evaluation (tmpPlayer.hand);
                            p.push_back(tmpPlayer);
                        }
                    }
                }
            }
        }                  
        vHoldEmPlayers.push_back(p);
    }            
    //(1) add all cards from the common board of cards to the two cards (from the player's hand) in each element's CardSet and then 
    //(2) remove 0/1/2 cards from hand to make it
    for(size_t i=0;i<vHoldEmPlayers.size();i++){ 
        sort(vHoldEmPlayers[i].begin(),vHoldEmPlayers[i].end());
        maxPossibleCards.push_back(vHoldEmPlayers[i][vHoldEmPlayers[i].size()-1]);
    }

    //sort the vector and print out (from the highest ranked to the lowest) each player's name, 
    //card set (which includes the player's cards and the cards from the common board of cards), and hand rank at that point in the game.
    sort(maxPossibleCards.begin(),maxPossibleCards.end());
    cout<<"-------Print out from the highest ranked to the lowest player on the table and their cards:-------------"<<endl;
    for(int i=maxPossibleCards.size()-1;i>=0;i--){
        if( (!ifFold[seats[maxPossibleCards[i].name]])||ifAllIn[seats[maxPossibleCards[i].name]] ){
            cout << maxPossibleCards[i].name << " has "<< maxPossibleCards[i].rank<< endl;
            cout <<"card in "<< maxPossibleCards[i].name << "'s hand: " << endl;
            maxPossibleCards[i].hand.print(cout, GameRules::print_format_5);
        }   
    }
    for(int i=maxPossibleCards.size()-1;i>=0;i--){
        if(  (!ifFold[seats[maxPossibleCards[i].name]]) || (ifAllIn[seats[maxPossibleCards[i].name]])){
            winnerName = maxPossibleCards[i].name;
            break;
        }
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
        cout<<"---------------------------new Game start!-------------------"<<endl;
        // shuffle the deck
        bigblindInd=rand() % players.size();
        smallblindInd=(players.size()+bigblindInd-1)% players.size();
        cout<<"big blind:"<<players[bigblindInd]<<endl;
        cout<<"small blind:"<<players[smallblindInd]<<endl;

        deck.shuffle();
        int nfolded; //track the number of folded players
        // reset state
        state = HoldEmState::preflop;
              // deal cards to each player's hand
        deal();
        printPlayersHand();
        bet();
        
        nfolded = 0;
        for(auto b:ifFold){
            nfolded += b;
        }
        if(nfolded>=static_cast<int>(players.size()-1)){
            cout<<"only 1 player didn't fold his cards, ending the game..." <<endl;
        }
        else{

            state = HoldEmState::flop;
            // deal cards to the board in 3 rounds
            deal();
            printBoard("Flop: ");
            bet();
            evaluate();
        
            nfolded = 0;
            for(auto b:ifFold){
                nfolded += b;
            }
            if(nfolded>=static_cast<int>(players.size()-1)){
                cout<<"only 1 player didn't fold his cards, ending the game..." <<endl;
            }
            else{
                state = HoldEmState::turn;
                deal();
                printBoard("Turn: ");
                bet();
                evaluate();
                nfolded = 0;
                for(auto b:ifFold){
                    nfolded += b;
                }
                if(nfolded>=static_cast<int>(players.size()-1)){
                    cout<<"only 1 player didn't fold his cards, ending the game..." <<endl;
                }
                state = HoldEmState::river;
                deal();
                printBoard("River: ");
                bet();  
                evaluate();
            }
        }
        
        collectCardsFromPlayer();
        collectCardsFromBoard();
        cout<<"winner is "<<winnerName<<endl;
        resetChips();

        if (askEndGame() == message::quit_game){
            return message::end_game;
        }
        if(players.size()==1)
            return message::end_game;
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



void HoldEmGame::bet(){

    //store how many player has taken action after raise; 
    //if that == player size, end the round
    int playerNumber = players.size();
    int actedPlayer=0; //round before floop
    int currentRoundMaximumChip;
    
    int currentPlayerInd;
    int raiseChip;
    if(state==HoldEmState::preflop){
        //assume player 0 and player 1 are small blind and big blind;
        //automatically add bet for small and big blind
        chipsCurrentRound[smallblindInd]=1;
        chipsCurrentRound[bigblindInd]=2;
        scores[smallblindInd] -= 1;
        scores[bigblindInd] -= 2;
        raiseChip = 2;
        currentRoundMaximumChip=2;
        currentPlayerInd = bigblindInd+1;
    }
    if(state==HoldEmState::flop){
        raiseChip = 2;
        currentRoundMaximumChip=0;
        currentPlayerInd = bigblindInd+1;
    }
    if(state==HoldEmState::turn){
        raiseChip = 4;
        currentRoundMaximumChip=0;
        currentPlayerInd = bigblindInd+1;
    }
    if(state==HoldEmState::river){
        raiseChip = 4;
        currentRoundMaximumChip=0;
        currentPlayerInd = bigblindInd+1;
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
            auto playerAction = action(currentPlayerInd);
            std::cout<<players[currentPlayerInd]<<"'s turn, he chose ";
            if(playerAction==HoldEmAction::check){
                cout<<"check"<<std::endl;
            }
            if(playerAction==HoldEmAction::fold){
                cout<<"fold"<<std::endl;
                ifFold[currentPlayerInd]=true;
            }
            if(playerAction==HoldEmAction::call){
                if(currentRoundMaximumChip==0)
                    cout<<"check"<<endl;
                else
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
                    ifAllIn[currentPlayerInd]=true;
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
    cout<<"end betting round"<<endl;
    //clear chips in pot
    for(size_t i=0;i<chipsCurrentRound.size();i++){
        chipsInPot[i] += chipsCurrentRound[i];
        chipsCurrentRound[i] = 0;
    }


    cout<<"players not folded:"<<endl;
    for(size_t i=0;i<players.size();i++){
        if(!ifFold[i])
            cout<<players[i]<<endl;
    }
    cout<<endl;
    
    return;
}




HoldEmAction HoldEmGame::action(int PlayerInd){
    auto cardsInHand = hands[PlayerInd];

    //check if there is any raise by checking if any entry in chipsCurrentRound 
    // is above the initial chip
    bool ifRaise=false;
    for(auto i:chipsCurrentRound){
        if( ((state==HoldEmState::preflop) && (i>2)) || ((state!=HoldEmState::preflop) && (i>0))){
            ifRaise=true;
            break;
        }
    }

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
                    else{
                        if((!ifRaise)&&(PlayerInd==bigblindInd))
                            return HoldEmAction::check;
                        else
                            return HoldEmAction::call;                    }
                    }
            //a pair of others
            if((!ifRaise)&&(PlayerInd==bigblindInd))
                return HoldEmAction::check;
            else
                return HoldEmAction::call;
            }               

        //check if consective
        auto firstRand=cardsInHand[static_cast<int>(arrayIndex::firstCard)].rank;
        if(++firstRand == cardsInHand[static_cast<int>(arrayIndex::secondCard)].rank)
            return HoldEmAction::call;
        //check if same suit
        if(cardsInHand[static_cast<int>(arrayIndex::firstCard)].suit== cardsInHand[static_cast<int>(arrayIndex::secondCard)].suit)
            return HoldEmAction::call;    
        if((!ifRaise)&&(PlayerInd==bigblindInd))  
            return HoldEmAction::check;
        else
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
        if(ifRaise)  
            return HoldEmAction::fold;
        else   
            return HoldEmAction::check;    
    }
    if(state==HoldEmState::turn){
        //check if has straight
        if( (v[0]==v[1]-1 && v[0]==v[2]-2 && v[0]==v[3]-3 && v[0]==v[3]-4)||
            (v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-4 && v[1]==v[5]-5))
            return  HoldEmAction::call;
        //check if has three same rank
        bool hasThree=false;
        for(auto c:rankMap){
            if(c.second>=3){
                hasThree=true;
            }
        }
        if(hasThree){
            if(chipsCurrentRound[PlayerInd]==0)
                return HoldEmAction::raise;
            else
               return HoldEmAction::call;
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
        if(ifRaise)  
            return HoldEmAction::fold;
        else   
            return HoldEmAction::check;
    }
    if(state==HoldEmState::river){
        bool hasThree=false;
        bool hasPair=false;
        //check flush
        for(auto c:suitMap){
            if(c.second==5)
                return  HoldEmAction::raise;
        }
        //check fourofakind 
        for(auto c:rankMap){
            if(c.second==4)
                return  HoldEmAction::raise;
        }

        //check fullhouse 
        for(auto c:rankMap){
            if(c.second==3)
                hasThree=true;
            if(c.second==2)
                hasPair=true;
        }
        if(hasPair&&hasThree)
            return  HoldEmAction::raise;

        //check if has straight
        if( ( (v[0]==v[1]-1) && (v[0]==v[2]-2) && (v[0]==v[3]-3) && (v[0]==v[4]-4))||
            (v[1]==v[2]-1 && v[1]==v[3]-2 && v[1]==v[4]-3 && v[1]==v[5]-4)||
            (v[2]==v[3]-1 && v[2]==v[4]-2 && v[2]==v[5]-3 && v[2]==v[6]-4))
            return  HoldEmAction::raise;

        //check if has three same rank
        if(hasThree){
            if(chipsCurrentRound[PlayerInd]==0)
                return HoldEmAction::raise;
            else
               return HoldEmAction::call;
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
        if(ifRaise)  
            return HoldEmAction::fold;
        else   
            return HoldEmAction::check;
    }
    
    if(ifRaise)  
        return HoldEmAction::fold;
    else   
        return HoldEmAction::check;
}



void HoldEmGame::resetChips(){
    cout<<"----------------------------reseting the chips------------------------------------"<<endl;
    int winnerInd;
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        if(players[i]==winnerName)
            winnerInd = i;
    }
    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        ifFold[i]=false;
        ifAllIn[i]=false;
        scores[winnerInd] += chipsInPot[i];
        chipsInPot[i]=0;
        chipsCurrentRound[i]=0;
    }     

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        cout<<players[i]<< " has "<<scores[i]<< " chips after this game" <<endl;
    }

    for (int i = static_cast<int>(players.size())-1;i>=0;i--) {
        if(scores[i]==0){
            cout<<players[i] <<" has 0 score and will be kicked out of the game, he is No."
            << players.size() <<endl;
            kickplayer(i);
        }
    }
}

 void HoldEmGame::kickplayer(int i){
     players.erase(players.begin() + i);
     ifFold.erase(ifFold.begin() + i);
     ifAllIn.erase(ifAllIn.begin()+i);
     chipsCurrentRound.erase(chipsCurrentRound.begin() + i);
     chipsInPot.erase(chipsInPot.begin() + i);
     scores.erase(scores.begin() + i);
     hands.erase(hands.begin() + i);

 }