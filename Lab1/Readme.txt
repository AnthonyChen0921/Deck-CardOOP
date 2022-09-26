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
               |                                      ├----- protected member: PinochleDeck deck
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
                                                    ├----- protected member: HoldEmDeck deck
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

    Situation
        When designing PinochleGame.cpp deal() funtion, 

    Task:
        given the task that we need to push a packet of cards (3 cards at a time) to player's hand,

    Problem:
        If the card has only 2 left in the deck, dealling 3 cards at a time will cause the deck to be empty, throwing an error.

    We have 3 options:
    Code:
        // calculate number of cards to deal in a round
        size_t numCards = PinochleGameGameRules::packet_of_cards * players.size();
        // deal 3 cards to each player until the deck is empty
        cout << "Dealing cards..." << endl;
        while (deck.getSize() >= numCards){
            for (int i = 0; i < static_cast<int>(hands.size()); i++)
            {
                deck >> hands[i];
                deck >> hands[i];
                deck >> hands[i];  
                // Problem: currently if the deck has 2 cards left, shifting 3 cards will be unsafe, cauing runtime error

                // Solution1: add size() function in the deck class to check the size of the deck
                //             -- result: the deck will have 2 cards leftover
                // Accpted

                // Solution2: use try catch block to catch the runtime error and break the loop
                //             -- result: the deck will have all cards on player's hand but unevenly distributed
                // Infeasible, rejected

                // Solution3: deal with the number of the card before call deal() function, and make sure the number of the card is divisible by 3
                //             -- result: the deck will have 2 cards leftover, add helper function, complicated
                // Feasible, rejected
            }
        }

    Action: 
        1. added getSize() function in CardSet_T class to check the size of the deck
        2. Calculate the number of cards to deal in a round, and make sure the number of the card is divisible by 3 

    Result:
        Problem solved, if the cards cannot be deal evenly in the last round, the leftover cards will be left in the deck.
 


Test Case and Results:

    Case 1. only program name
        > ./lab1
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>

    Case 2. program name and invalid game name
        > ./lab1 random
        Invalid Gamename
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>

    Case 3. program name and valid game name (Pinochle), but invalid number of players
        > ./lab1 Pinochle player1 player2 player3
        Invalid number of players in Pinochle, must have exactly 4 players.
        For example: Pinochle player1 player2 player3 player4
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>

    Case 4. program name and valid game name (Pinochle), and valid number of players
        > ./lab1 Pinochle player1 player2 player3 player4
        ====================================================
        =                 PinochleGame                     =
        ====================================================
        Dealing cards...
        player1's hand: 
        A♦ 9♠ Q♦ 10♣ 
        Q♠ Q♣ Q♥ A♠ 
        9♣ J♦ 9♥ 10♦ 


        player2's hand: 
        9♠ J♥ K♣ K♥ 
        10♥ J♣ A♥ A♦ 
        10♠ K♣ A♣ J♥ 


        player3's hand: 
        10♦ Q♦ Q♠ 9♣ 
        K♥ 10♥ 9♦ A♠ 
        A♥ K♦ 10♣ J♦ 


        player4's hand: 
        J♠ J♣ 10♠ 9♦ 
        K♠ Q♣ A♣ K♠ 
        K♦ Q♥ 9♥ J♠ 


        Do you want to end the game? (y/n)

        // if the user enter y, the game will end
        // if the user enter n, the game will continue and every card will be collected
        // and starts off a new round with a new deck (shuffled)

    Case 5. program name and valid game name (HoldEm), but invalid number of players
        > ./lab1 HoldEm playerA                          
        Invalid number of players in HoldEm, must have between 2 and 9 players.
        For example: HoldEm player1 player2
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>

    Case 6. program name and valid game name (HoldEm), and valid number of players
        > ./lab1 HoldEm playerA PlayerB playerC PlayerD
        ====================================================
        =                 HoldEmGame                       =
        ====================================================
        playerA's hand: 
        8♣ 5♦ 

        PlayerB's hand: 
        2♦ 9♦ 

        playerC's hand: 
        5♣ J♥ 

        PlayerD's hand: 
        6♠ K♣ 

        Flop: 
        2♠ 8♥ 7♦ 

        Turn: 
        2♠ 8♥ 7♦ J♦ 

        River: 
        2♠ 8♥ 7♦ J♦ 4♥ 


        Do you want to end the game? (y/n)

// entered n, the game will continue and every card will be collected from both the players and the board
        n
        playerA's hand: 
        Q♣ K♦ 

        PlayerB's hand: 
        J♠ Q♠ 

        playerC's hand: 
        6♥ A♥ 

        PlayerD's hand: 
        10♣ 9♦ 

        Flop: 
        2♠ K♥ 10♦ 

        Turn: 
        2♠ K♥ 10♦ 9♠ 

        River: 
        2♠ K♥ 10♦ 9♠ 5♦ 


        Do you want to end the game? (y/n)

