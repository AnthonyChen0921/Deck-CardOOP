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
    - "./lab3 Pinochle player1 player2 player3 player4" (correct input exmaple)
    - "./lab3 HoldEm player1 player2 player3 player4 player5 player6" (correct input exmaple)
    - "./lab3 randomGame (incorrect input exmaple)



Errors and Warning jornals:

    1. 
    

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



Design variation:

PinochleGame:
Added a remove(R r, S s) in CardSet_T template class.
Added a operator== in Card_T template class for iterator in remove function to compare.



Test Case and Results:

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
