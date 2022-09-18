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
        Lab0 % make
        g++ -o lab0 -DUNIX   -Wall -W -g -std=c++17 -DTEMPLATE_HEADERS_INCLUDE_SOURCE Suit.cpp lab0.cpp PinochleDeck.cpp HoldEmDeck.cpp 
        In file included from lab0.cpp:12:
        In file included from ./PinochleDeck.h:11:
        ./Card_T.h:15:8: error: redefinition of 'Card'
        struct Card
            ^
        ./Card_T.h:15:8: note: previous definition is here
        struct Card
            ^
        In file included from lab0.cpp:13:
        In file included from ./HoldEmDeck.h:11:
        ./Card_T.h:15:8: error: redefinition of 'Card'
        struct Card
            ^
        ./Card_T.h:15:8: note: previous definition is here
        struct Card
            ^
        2 errors generated.
        make: *** [lab0] Error 1

        >>>>>>>>>>>> Solution >>>>>>>>>>>>
        - added IFDEF guard to Card_T.h


    2. 
        Lab0 % make
        g++ -o lab0 -DUNIX   -Wall -W -g -std=c++17 -DTEMPLATE_HEADERS_INCLUDE_SOURCE Suit.cpp lab0.cpp PinochleDeck.cpp HoldEmDeck.cpp 
        In file included from lab0.cpp:11:
        In file included from ./Card_T.h:34:
        ./Card_T.cpp:21:8: error: invalid operands to binary expression ('std::ostream' (aka 'basic_ostream<char>') and 'const Rank')
            os << card.rank << card.suit;
            ~~ ^  ~~~~~~~~~
        lab0.cpp:42:40: note: in instantiation of function template specialization 'operator<<<Rank, Suit>' requested here
            cout << "Card is initialized to: " << c << endl;

        >>>>>>>>>>>> Thought >>>>>>>>>>>>
        When we first came across the step 8, I haven't yet declare an overloading of shift operator for any deck (no shift operator declared for rank).
        / ----- code snippet that caused the error ----- /
            std::ostream &operator<<(std::ostream &os, const Card<R, S> &card)
            {
                os << card.rank << card.suit;
                return os;
            }

    >>>>>>>>>>>> Solution >>>>>>>>>>>>
    - comment out some code snippet that could potentially cause error to narrow down the error
    - sometime you have to look forward to several next steps


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
    1.
        In step 7, where the lab0 says: 
        "That shift operator should insert a string corresponding to the suit ("C" for clubs, "D" for diamonds, "H" for hearts, "S" spades, or "?" for undefined) into the ostream and then return a reference to that same ostream."

        Instead of using C, D, H, S, 
        We use unicode icon ♣, ♦, ♥, ♠, ? for the suits.
        A useful website for unicode icon: https://en.wikipedia.org/wiki/Playing_cards_in_Unicode



Test Case and Results:
    // We develop a main function to test the code according to the lab instruction
    // The main function is in lab0.cpp

    The whole output of the test case is as follows:
    ============================
    Test Suit's shift operator<<
    ============================
    Suit::clubs: ♣
    Suit::diamonds: ♦
    Suit::hearts: ♥
    Suit::spades: ♠
    Suit::undefined: ?


    =======================================
    Test Suit's prefix increment operator++
    =======================================
    Suit is initialized to: ♣
    Prefix increment ++s return: ♦


    =========================================
    Test PinochleDeck's rank shift operator<<
    =========================================
    PinochleRank::nine: 9
    PinochleRank::jack: J
    PinochleRank::queen: Q
    PinochleRank::king: K
    PinochleRank::undefined: ?


    =========================================
    Test HoldEmDeck's rank shift operator<<
    =========================================
    HoldEmRank::two: 2
    HoldEmRank::three: 3
    HoldEmRank::four: 4
    HoldEmRank::five: 5
    HoldEmRank::undefined: ?


    ====================================================
    Test PinochleDeck's rank prefix increment operator++
    ====================================================
    PinochleRank is initialized to: 9
    Prefix increment ++r return: J


    ====================================================
    Test HoldEmDeck's rank prefix increment operator++
    ====================================================
    HoldEmRank is initialized to: 2
    Prefix increment ++h return: 3

    
    ==============================================================
    Test PinochleDeck Class default constructor and print function
    ==============================================================
    Printing PinochleDeck pd: 9♣ 9♣ 9♦ 9♦ 9♥ 9♥ 9♠ 9♠ J♣ J♣ J♦ J♦ J♥ J♥ J♠ J♠ Q♣ Q♣ Q♦ Q♦ Q♥ Q♥ Q♠ Q♠ K♣ K♣ K♦ K♦ K♥ K♥ K♠ K♠ 10♣ 10♣ 10♦ 10♦ 10♥ 10♥ 10♠ 10♠ A♣ A♣ A♦ A♦ A♥ A♥ A♠ A♠ 
    
    
    
    =============================================================
    Test HoldEmDeck Class default constructor and print function
    =============================================================
    Printing HoldEmDeck hd: 2♣ 2♦ 2♥ 2♠ 3♣ 3♦ 3♥ 3♠ 4♣ 4♦ 4♥ 4♠ 5♣ 5♦ 5♥ 5♠ 6♣ 6♦ 6♥ 6♠ 7♣ 7♦ 7♥ 7♠ 8♣ 8♦ 8♥ 8♠ 9♣ 9♦ 9♥ 9♠ 10♣ 10♦ 10♥ 10♠ J♣ J♦ J♥ J♠ Q♣ Q♦ Q♥ Q♠ K♣ K♦ K♥ K♠ A♣ A♦ A♥ A♠ 