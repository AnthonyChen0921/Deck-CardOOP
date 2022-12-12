Lab 3: Finishing the Games
Authur: @Anthony Chen, @Yunlai Chen
Email: chenerdong@wustl.edu c.yunlai@wustl.edu
GitHub: @AnthonyChen0921 @yunlai-wustl

Description:
  This lab is intended to :
    using generic containers, iterators, and algorithms
    rotating indices to elements of containers among different combinations of them
    examining, ranking, and selecting different combinations of elements in containers
    tracking, tallying, and accumulating values based on those different combinations
    enforcing rules for how new values may be proposed and applied


How to run
    - Open up Commandline prompt, and type in
    - "module add gcc-8.3.0"
    - "make"
    - "./lab3 Pinochle PlayerA PlayerB PlayerC PlayerD" (correct input exmaple)
    - "./lab3 HoldEm player1 player2 player3 player4 player5 player6" (correct input exmaple)
    - "./lab3 randomGame (incorrect input exmaple)



Errors and Warning jornals:

    1. Pinochle Game bug fixed: 
        ======== determine the winner of the trick this round ========
        the index i should be used to access the vector of cards trick_cards_vector[i], not the index j.
        the index j should be used to access vector of players[j], not the index i.
    


Class Design:

    CardSet_T--------┬---- protected: vector<Card>
     |               |                        └----- template class Card_T
     |               |                                                 └----- member variable: Rank, Suit
     |               |
     |               └---- public: constructor: CardSet(), CardSet(const CardSet &cs),
     └------┐                      member function: print(), addCard(Card<R, S> c), CardSet::*getCardsPtr()
         public                    overloaded operator: operator>>, 
        inherited                  helper: is_empty(), getSize()       
     ┌------┘                      
     |
     |
    Deck-------------- public: constructor: Deck(),
     |                         member function: shuffle(), collect() 
     |
     └------┐
            ├-------- public inherited ------> PinochleDeck                                                   
            |                                      |                   
            |                                      ├----- public member: default constructor
            |                                      | 
            |                                      └----- overloaded operator: << (shift operator) 
            |                                                                  ++ (prefix increment operator)
            |
            └-------- public inherited ------> HoldEmDeck
                                                |                   
                                                ├----- public member: default constructor
                                                |
                                                └----- overloaded operator: << (shift operator) 
                                                                            ++ (prefix increment operator)


       Game--------┬---- protected: vector<string> players
        |          |                                 
        |          |
        |          └---- public: constructor: Game(),
        |                        pure virtual function: play(),
        └------┐                 helper: askEndGame() 
             public                     
            inherited 
           (interface)                       
               |
               ├-------- public inherited ------> PinochleGame
               |                                      |
               |                                      ├----- protected member: PinochleDeck deck
               |                                      |                        vector< CardSet<PinochleRank, Suit> > hands
               |                                      |                        deal()
               |                                      |                   
               |                                      ├----- public member: constructor PinochleGame(int argc, const char *argv[])
               |                                      |                     play()
               |                                      |                     
               |                                      └----- helper function: printPlayersHand()
               |                                                              collectCardsFromPlayer()
               |                                                               suit_independent_evaluation()
               |
               └-------- public inherited ------> HoldEmGame
                                                    |
                                                    ├----- protected member: HoldEmDeck deck
                                                    |                        vector< CardSet<HoldEmRank, Suit> > hands
                                                    |                        deal()
                                                    |                   
                                                    ├----- public member: constructor HoldEmGame(int argc, const char *argv[])
                                                    |                     play()
                                                    |                     evaluate()
                                                    └----- helper function: printPlayersHand()
                                                    |                        printBoard()
                                                    |                        collectCardsFromPlayer()
                                                    |                        collectCardsFromBoard()
                                                    |-----nested class: HoldEmPlayer


​                                                            
A comment for Pinochle:
    Neither of us had played Pinochle before, so we are somewhat confused about the detailed rules of the game (such as what should be played, what cannot be played in trick round if leading card is trumpsuit/nontrumpsuit). The rules from internet are also different from each other. Aside from playTrick part, everything else should be working fine. We are sorry for the difference between our implementation and the real game.


Design variation:

PinochleGame:
    12:
        BaseClass modification:
        - Added a removeCard(R r, S s) in CardSet_T template class.
        - Added a operator== in Card_T template class for iterator in remove function to compare.
        - Added a operator[] in CardSet_T template class for random accessing vector card.

        PinochleGame modification:
        - Added helper function findHighestRank/findLowestRank to find the highest/lowest rank in a cardset.
        - Added helper function findHighestRankwSuit/findLowestRankwSuit to find the highest/lowest rank according to given suit in a cardset.
        - Added PlayThisCard, calculateScore, findFirstPlayer, checkTrumpPlayed functions to maintain a good modularity.
        - Added bug fix function such as PrintMap, not used in final evaluation.

HoldEmGame:
    13: 
        We used a 2d vector. Outer dimension is number of player, inner dimension is possible card combination. In flop it only has 1 possible combination; for turn, 
        there are 4 possible combination; for river, it has 10 possible combination. 

        For each player at each round, we can call sort to sort the possible card combination of that player.




14: bet round Design

For simplification, the first and second player will be big and small blind by default

four functions: 
    bet(HoldEmState state)
        - round before floop; small and big blind are automatically bet; raise must be 2 chips larger than maximumChip
        - round after flop, raise must be 2 chips larger than maximumChip
        - round after turn, raise must be 4 chips larger than maximumChip
        - round after river, raise must be 4 chips larger than maximumChip


variable:

    HoldEmGame::status; player status, fold/check/gaming/
    vector<bool> ifFolded; store if player i fold his cards

    vector<int> scores; store the chips in each player hand, initialized as 60;
    vector<int> chipsInPot; keeps track of the current number of chips in the common "pot" of bets that have been made in previous betting rounds;
    vector<int> chipsCurrentRound; keeps track of how many chips each player has bet in the current round of betting;
    int currentRoundMaximumChip; store the maximum chip in current beting round
    int actedPlayer; store the number of players that makes an action; set as 0 at the beginning of each round or after one raised

function: 
    in each bet round,  while raise==0, loop over each player.
    For each player:
        1. check if they have folded, if folded or all in, continue to nextplayer.  
        2. For round after flop, if currentRoundMaximumChip==0, ask if choose to check;
           if check, set ifFolded[i] as true; moved to next player, otherwise ask for action;
        3. Ask which action the player choose to do:
            if fold: set ifFolded[i] to true, continue to next;
            if call: diff=currentRoundMaximumChip-chipsCurrentRound[i]; 
                     check if scores[i] is > diff. 
                        If yes substract diff from score and set chipsCurrentRound[i]=currentRoundMaximumChip
                        If not, set ifFolded[i] to true. Set scores[i]=0; and chipsCurrentRound[i]=scores[i]+chipsCurrentRound[i]
            if raise: add X to currentRoundMaximumChip; calculte difference between  
                      check if scores[i] is > diff. 
                        If yes substract diff from score and set chipsCurrentRound[i]=currentRoundMaximumChip
                        If not, set ifFolded[i] to true. Set scores[i]=0; and chipsCurrentRound[i]=scores[i]+chipsCurrentRound[i] 
        4.actedPlayer++; check if actedPlayer==number of players; 
                    if yes:  chipsCurrentRound are added to chipsInPot and set to 0; end
                    if not, continue to next player



15. AutoMaticBet design
    Since 'check' is a special case when maximumChip of that round is call, we didn't treat 'check'
    - new var: 
        enum class HoldEmGame::Action (fold/raise/call)

    - strategy function:
        HoldEmGame::Action(CardSet<HoldEmRank, Suit> hand[i], HoldEmState)
            input: current state and cardset of player i
            output: fold/raise/call
            if pre-flop state:
                - check if has a pair of Ace; if yes return raise
                - check if has a pair of king/queen/jack; 
                    if yes, return raise if chipsCurrentRound[i]==0 (check if this is the first bet); otherwise return call 
                - check if two cards in hand are consective/has pair/has same suit, return call
                - otherwise return fold    
            if flop state:
                - check if has three same rank; if yes return raise
                - check if has two pair; 
                    if yes, return raise if chipsCurrentRound[i]==0; otherwise return call 
                - check if has 4 consective ranks/has pair/has 4 same suit, return call
                - otherwise return fold 
            if turn state:
                - check if has straight(); if yes return raise
                - check if has three same ran
                     if yes, return raise if chipsCurrentRound[i]==0; otherwise return call 
                - check if hasPair/hasTwoPair/hasConsective(4)/hasSameSuit(Diamond/../../Spade, 4), return call
                - otherwise return fold 
            if river state:
                - check if has Straight; if yes return raise
                - check if has Three Same Rank 
                     if yes, return raise if chipsCurrentRound[i]==0; otherwise return call  
                - check if has Two Pair, return call
                - otherwise return fold 

16: We are running out of time so we only consider the case that there is no 
 indistinguishably best. In this case sum the chips in chipsInPot, 
 add it to the scores of winner and clear chipsInPot to 0. We do these steps in 
 resetChips.

When score[i]==0, we will call a member function kickplayer(int i);
this will remove the i th entry in:
    - player
    - ifFolded
    - chipsCurrentRound
    - chipsInPot
    - scores
    - hands
When the size of player is reduced to one, end the game



Test Case and Results:

1. Pinochle Game, Misdeal

    ==================== Test Case 1 ====================
    Rare Case: Misdeal

    Lab3 % ./lab3 Pinochle 1 2 3 4 
    ====================================================
    =                 PinochleGame                     =
    ====================================================
    Dealing cards...
    Trump suit is ♦
    1's hand: 
    A♣ Q♠ K♣ 10♦ 
    10♦ J♥ 10♣ 10♥ 
    9♦ 9♥ Q♦ A♠ 

    Melds: 
    dix :10points


    2's hand: 
    J♥ K♦ 9♣ K♦ 
    9♠ Q♠ J♠ 9♣ 
    K♥ 9♠ A♥ J♣ 

    No melds


    3's hand: 
    Q♣ K♥ A♦ A♣ 
    A♦ J♣ J♦ Q♥ 
    A♥ K♠ Q♥ J♠ 

    No melds


    4*'s hand: 
    10♥ 10♣ 10♠ 9♥ 
    10♠ K♣ Q♣ K♠ 
    J♦ A♠ Q♦ 9♦ 

    Melds: 
    dix :10points


    Team1:60 = bids1:10 + cardPoints1:50
    Team2:60 = bids2:10 + cardPoints2:50
    Misdeal
    Same bid score! Deal Again (Press any key)


2. Pinochle Game, Typical play round & Game Over:
    Dealing cards...
    Trump suit is ♥
    A*'s hand: 
    Q♦ 10♥ J♥ 9♣ 
    A♦ 9♠ A♣ Q♦ 
    A♠ 9♠ K♣ J♥ 

    No melds


    B's hand: 
    Q♥ K♥ A♥ A♥ 
    K♥ K♠ J♦ J♠ 
    10♠ J♣ A♠ 10♠ 

    No melds


    C's hand: 
    9♦ A♣ A♦ 9♦ 
    10♣ 10♦ 10♦ 9♥ 
    Q♣ K♦ Q♠ Q♠ 

    Melds: 
    dix :10points


    D's hand: 
    10♣ J♦ K♦ K♠ 
    Q♣ Q♥ J♠ K♣ 
    J♣ 10♥ 9♣ 9♥ 

    Melds: 
    dix :10points


    Team1:68 = bids1:10 + cardPoints1:58
    Team2:59 = bids2:10 + cardPoints2:49
    Team 1 wins the contract

    Team 1's bid goal: 10

    Team 2's bid goal: 10

    C has the highest bid and is the first player to play
    Turn 1 starts:
    C is the first player to play this round
    C plays A♦
    D plays J♦
    A plays Q♦
    B plays J♦
    C wins the trick in round 1 with A♦

    A♦ J♦ Q♦ J♦ 

    Turn 2 starts:
    C is the first player to play this round
    C plays A♣
    D plays 9♣
    A plays 9♣
    B plays J♣
    C wins the trick in round 2 with A♣

    A♣ 9♣ 9♣ J♣ 

    Turn 3 starts:
    C is the first player to play this round
    C plays 10♦
    D plays K♦
    A plays Q♦
    B plays A♠
    C wins the trick in round 3 with 10♦

    10♦ K♦ Q♦ A♠ 

    Turn 4 starts:
    C is the first player to play this round
    C plays 10♦
    D plays 10♥
    A plays A♦
    B plays A♥
    B wins the trick in round 4 with A♥

    10♦ 10♥ A♦ A♥ 

    Turn 5 starts:
    B is the first player to play this round
    B plays A♥
    C plays 9♥
    D plays 9♥
    A plays J♥
    B wins the trick in round 5 with A♥

    A♥ 9♥ 9♥ J♥ 

    Turn 6 starts:
    B is the first player to play this round
    B plays 10♠
    C plays Q♠
    D plays J♠
    A plays 9♠
    B wins the trick in round 6 with 10♠

    10♠ Q♠ J♠ 9♠ 

    Turn 7 starts:
    B is the first player to play this round
    B plays 10♠
    C plays Q♠
    D plays K♠
    A plays 9♠
    B wins the trick in round 7 with 10♠

    10♠ Q♠ K♠ 9♠ 

    Turn 8 starts:
    B is the first player to play this round
    B plays K♥
    C plays 9♦
    D plays Q♥
    A plays 10♥
    A wins the trick in round 8 with 10♥

    K♥ 9♦ Q♥ 10♥ 

    Turn 9 starts:
    A is the first player to play this round
    A plays A♠
    B plays J♠
    C plays 9♦
    D plays J♣
    A wins the trick in round 9 with A♠

    A♠ J♠ 9♦ J♣ 

    Turn 10 starts:
    A is the first player to play this round
    A plays A♣
    B plays K♠
    C plays Q♣
    D plays Q♣
    A wins the trick in round 10 with A♣

    A♣ K♠ Q♣ Q♣ 

    Turn 11 starts:
    A is the first player to play this round
    A plays K♣
    B plays K♥
    C plays 10♣
    D plays K♣
    B wins the trick in round 11 with K♥

    K♣ K♥ 10♣ K♣ 

    Turn 12 starts:
    B is the first player to play this round
    B plays Q♥
    C plays K♦
    D plays 10♣
    A plays J♥
    B wins the trick in round 12 with Q♥

    Q♥ K♦ 10♣ J♥ 

    Team 1 meets the contract bid
    ==============================
            Game Over!          
    Team 1 score: 1610
    Team 2 score: 1400
    Winner: Team 1
    ==============================

    3. ====================================================
=                 HoldEmGame                       =
====================================================
p1's hand: 
A♦ 7♥ 

p2's hand: 
6♠ 9♣ 

p3's hand: 
J♠ 7♠ 

p4's hand: 
8♠ 5♣ 

p5's hand: 
3♦ K♣ 

p6*'s hand: 
8♦ 2♣ 

p3's turn, chose call
p4's turn, chose fold
p5's turn, chose fold
p6's turn, chose fold
p1's turn, chose fold
p2's turn, chose fold
end betting round
players not folded:
p3

Flop: 
J♦ 2♥ K♥ 

p3's turn, chose check
end betting round
players not folded:
p3

-------Print out from the highest ranked to the lowest player and their cards:-------------
p5 has pair
card in p5's hand: 
3♦ K♣ J♦ 2♥ K♥ 

p3 has pair
card in p3's hand: 
J♠ 7♠ J♦ 2♥ K♥ 

p6 has pair
card in p6's hand: 
8♦ 2♣ J♦ 2♥ K♥ 

p1 has xhigh
card in p1's hand: 
A♦ 7♥ J♦ 2♥ K♥ 

p2 has xhigh
card in p2's hand: 
6♠ 9♣ J♦ 2♥ K♥ 

p4 has xhigh
card in p4's hand: 
8♠ 5♣ J♦ 2♥ K♥ 

Turn: 
J♦ 2♥ K♥ 6♥ 

p3's turn, chose check
end betting round
players not folded:
p3

-------Print out from the highest ranked to the lowest player and their cards:-------------
p5 has pair
card in p5's hand: 
3♦ K♣ J♦ 2♥ K♥ 

p3 has pair
card in p3's hand: 
J♠ 7♠ J♦ 2♥ K♥ 

p2 has pair
card in p2's hand: 
6♠ 9♣ 6♥ 2♦ ♣ 

p6 has pair
card in p6's hand: 
8♦ 2♣ 6♥ 2♦ ♣ 

p1 has xhigh
card in p1's hand: 
A♦ 7♥ J♦ 2♥ K♥ 

p4 has xhigh
card in p4's hand: 
8♠ 5♣ J♦ 2♥ K♥ 

59
58
60
60
60
60
River: 
J♦ 2♥ K♥ 6♥ 4♦ 


p3's turn, chose fold
end betting round
players not folded:

-------Print out from the highest ranked to the lowest player and their cards:-------------
p3 has twopair
card in p3's hand: 
J♠ 7♠ ♣ J♠ 7♠ 

p5 has pair
card in p5's hand: 
3♦ K♣ J♦ 2♥ K♥ 

p1 has pair
card in p1's hand: 
A♦ 7♥ ♣ ♣ 7♥ 

p2 has pair
card in p2's hand: 
6♠ 9♣ 6♥ 4♦ ♣ 

p6 has pair
card in p6's hand: 
8♦ 2♣ 2♣ ♣ ♣ 

p4 has xhigh
card in p4's hand: 
8♠ 5♣ ♣ ♣ 7♥ 

winner is p3
Do you want to end the game? (y/n)
