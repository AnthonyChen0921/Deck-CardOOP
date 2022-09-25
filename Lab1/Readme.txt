Lab 1: Players, Hands, and Games
Authur: @Anthony Chen, @Yunlai Chen
Email: chenerdong@wustl.edu c.yunlai@wustl.edu
GitHub: @AnthonyChen0921 @yunlai-wustl

Description:
    This lab is one step further for the oop design for cards and decks. In particular, for HoldEmDeck and PinochleDeck. 
    In the lab, we modified the class struture of the Deck and CardSet_T, and added a new abstract class called Game.
    We improved the code reusability and readability by moving common method and class variable from HoldEmDeck and PinochleDeck to CardSet_T.

    How to run
    - Open up Commandline prompt, and type in
    - "module add gcc-8.3.0"
    - "make"
    - "./lab1 Pinochle player1 player2 player3 player4" (correct input exmaple)
    - "./lab1 HoldEm player1 player2 player3 player4 player5 player6" (correct input exmaple)
    - "./lab1 randomGame (incorrect input exmaple)



Errors and Warning jornals:

    1. 
    - Error:
            Lab1 % make
            g++ -o lab1 -DUNIX   -Wall -W -g -std=c++17 -DTEMPLATE_HEADERS_INCLUDE_SOURCE Suit.cpp lab1.cpp PinochleDeck.cpp HoldEmDeck.cpp 
            In file included from lab1.cpp:12:
            In file included from ./PinochleDeck.h:9:
            In file included from ./Deck.h:35:
            ./Deck.cpp:27:13: error: too many arguments to function call, expected 0, have 3
                shuffle(CardSet<R,S>::cards.begin(), CardSet<R,S>::cards.end(), generator);
                ~~~~~~~ ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            lab1.cpp:96:8: note: in instantiation of member function 'Deck<PinochleRank, Suit>::shuffle' requested here
                pd.shuffle();
                ^
            ./Deck.h:30:10: note: 'shuffle' declared here
                void shuffle();
                    ^
            In file included from lab1.cpp:12:
            In file included from ./PinochleDeck.h:9:
            In file included from ./Deck.h:35:
            ./Deck.cpp:27:13: error: too many arguments to function call, expected 0, have 3
                shuffle(CardSet<R,S>::cards.begin(), CardSet<R,S>::cards.end(), generator);
                ~~~~~~~ ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            lab1.cpp:104:8: note: in instantiation of member function 'Deck<HoldEmRank, Suit>::shuffle' requested here
                hd.shuffle();
                ^
            ./Deck.h:30:10: note: 'shuffle' declared here
                void shuffle();
                    ^
            2 errors generated.
            make: *** [lab1] Error 1


    - Solution:
        The error is caused by using std namespace.
        When using using std namespace in the whole cpp file, shuffle function will be called from class declaration for some reason.
        The solution is to remove using std namespace, and use std::shuffle instead.


        


Class Design:

    CardSet_T--------┬---- protected: vector<Card>
     |               |                        └----- template class Card_T
     |               |                                                 └----- member variable: Rank, Suit
     |               |
     |               └---- public: constructor: CardSet(), 
     └------┐                      member function: print(), 
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
               |                                      ├----- protected member: PinochleDeck Deck
               |                                      |                        vector< CardSet<PinochleRank, Suit> > hands
               |                                      |                        deal()
               |                                      |                   
               |                                      ├----- public member: constructor PinochleGame(int argc, const char *argv[])
               |                                      |                     play()
               |                                      | 
               |                                      └----- helper function: printPlayersHand()
               |                                                              collectCardsFromPlayer()
               |
               └-------- public inherited ------> HoldEmGame
                                                    |
                                                    ├----- protected member: HoldEmDeck Deck
                                                    |                        vector< CardSet<HoldEmRank, Suit> > hands
                                                    |                        deal()
                                                    |                   
                                                    ├----- public member: constructor HoldEmGame(int argc, const char *argv[])
                                                    |                     play()
                                                    | 
                                                    └----- helper function: printPlayersHand()
                                                                            printBoard()
                                                                            collectCardsFromPlayer()
                                                                            collectCardsFromBoard()


                                                            



Design variation:
 


Test Case and Results:
