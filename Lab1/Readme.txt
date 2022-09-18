Lab 0: Cards and Decks
Authur: @Anthony Chen, @Yunlai Chen
Email: chenerdong@wustl.edu c.yunlai@wustl.edu
GitHub: @AnthonyChen0921 @yunlai-wustl

Description:
    This lab is basic oop design for cards and decks. In particular, for HoldEmDeck and PinochleDeck. 
    In the lab, we overload the operator, introducing class template, using new gen c++ feature.
    Also we practice oop design, using inheritance and polymorphism.

    How to run
    - Open up Commandline prompt, and type in
    - "module add gcc-8.3.0"
    - "make"
    - "./lab0"



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


    2. 
        


Class Design:
    Deck ┬-------- public inherited ------> PinochleDeck
         |                                |
         |                                ├----- private member: vector<Card>
         |                                |                               └----- template class Card_T
         |                                |                                                       └----- member variable: Rank, Suit
         |                                |                   
         |                                ├----- public member: default constructor, print()
         |                                | 
         |                                └----- overloaded operator: << (shift operator) 
         |                                                            ++ (prefix increment operator)
         |
         |
         └-------- public inherited ------> HoldEmDeck
                                            |
                                            ├----- private member: vector<Card>
                                            |                               └----- template class Card_T
                                            |                                                       └----- member variable: Rank, Suit
                                            |                   
                                            ├----- public member: default constructor, print()
                                            |
                                            └----- overloaded operator: << (shift operator) 
                                                                        ++ (prefix increment operator)

    PinochleDeck default constructor: 
        - each card has a rank and a suit
        - initialize the vector<Card> with 48 cards
        - rank: Ace, Nine, Ten, Jack, Queen, King
        - suit: Clubs, Diamonds, Hearts, Spades
        - pushback twice card when in for loop


    HoldEmDeck default constructor:
        - each card has a rank and a suit
        - initialize the vector<Card> with 52 cards
        - rank: Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
        - suit: Clubs, Diamonds, Hearts, Spades
        - pushback once card when in for loop



Design variation:
 


Test Case and Results:
