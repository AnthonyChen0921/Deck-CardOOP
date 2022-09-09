Lab 0: Cards and Decks
Authur: @Anthony Chen, @Yunlai Chen
Email: chenerdong@wustl.edu c.yunlai@wustl.edu
GitHub: @AnthonyChen0921 @yunlai-wustl

Description:
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


2. Second error is a linker error complained about the overloading of shift operator
    When I first came across the step 8, I haven't yet declare an overloading of shift operator for any deck (no shift operator declared for rank).
    / ----- code snippet that caused the error ----- /
        std::ostream &operator<<(std::ostream &os, const Card<R, S> &card)
        {
            os << card.rank << card.suit;
            return os;
        }

    >>>>>>>>>>>> Solution >>>>>>>>>>>>
    - comment out some code snippet that could potentially cause error to narrow down the error
    - sometime you have to look forward to several next steps



Test Case and Results: