Lab 2: Evaluating and Ranking Hands
Authur: @Anthony Chen, @Yunlai Chen
Email: chenerdong@wustl.edu c.yunlai@wustl.edu
GitHub: @AnthonyChen0921 @yunlai-wustl

Description:
  This lab is intended to :
    using smart pointer templates with templates for safe memory management
    using copy construction to make a deep copy for a class template
    using sorting to put container elements into an order that can be evaluated
    matching different patterns in the elements in a container

How to run
    - Open up Commandline prompt, and type in
    - "module add gcc-8.3.0"
    - "make"
    - "./lab2 Pinochle player1 player2 player3 player4" (correct input exmaple)
    - "./lab2 HoldEm player1 player2 player3 player4 player5 player6" (correct input exmaple)
    - "./lab2 randomGame (incorrect input exmaple)



Errors and Warning jornals:

    1. 
    - Error: 
    CardSet_T.h:24:17: error: expected unqualified-id before ‘=’ token
     	CardSet() {}=default;
    
    - Solution:
    	CardSet()=default;

   2.
   - Error
	CardSet_T.h:38:12: error: need ‘typename’ before ‘std::vector<Card<R, S> >::iterator’ because ‘std::vector<Card<R, S> >’ is a dependent scope
	     static std::vector< Card<R, S> >::iterator getCard();
   - Solution
	         static typename std::vector< Card<R, S> >::iterator getCard();

   3.

   - error 
	In file included from lab2.cpp:14:
	PinochleGame.h: In static member function ‘static std::vector<CardSet<PinochleRank, Suit> >* PinochleGame::getHands()’:
	PinochleGame.h:53:31: error: cannot convert ‘std::vector<CardSet<PinochleRank, Suit> > PinochleGame::*’ to ‘std::vector<CardSet<PinochleRank, Suit> >*’ in return
         return &PinochleGame::hands;
                               ^~~~~
   - solution
	change from	static std::vector<CardSet<PinochleRank, Suit> > *getHands(){
	to		 static std::vector<CardSet<PinochleRank, Suit> > PinochleGame::*getHands(){

	

    4.
    -Error
    PinochleGame.cpp: In member function ‘void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit>&, std::vector<PinochleMelds>&)’:
    PinochleGame.cpp:177:31: error: invalid use of unary ‘*’ on pointer to member
     	auto cards=*(cs.getCards());
    -Solution
    
    5.
    -Error
    PinochleGame.cpp:179:52: error: no matching function for call to ‘sort(std::vector<Card<PinochleRank, Suit>, std::allocator<Card<PinochleRank, Suit> > >::iterator, std::vector<Card<PinochleRank, Suit>, std::allocator<Card<PinochleRank, Suit> > >::iterator, <unresolved overloaded function type>)’
         std::sort(cards.begin(),cards.end(),compareRank);
    -Solution
        std::sort(cards.begin(),cards.end(),compareRank<PinochleRank, Suit>);
    
     6.
     -Error
    HoldEmGame.cpp:243:68: error: ISO C++ forbids declaration of ‘operator<’ with no type [-fpermissive]
         friend operator<(const HoldEmPlayer &p1, const HoldEmPlayer &p2);
    
     -Solution
        friend bool operator<(const HoldEmPlayer &p1, const HoldEmPlayer &p2);
     
     7.
      -Error 
    error: non-static reference member ‘std::__cxx11::string& HoldEmGame::HoldEmPlayer::name’, can’t use default assignment operator
    
     -Solution
    We end up with a string rather than a string& since the string object will shallow copy the string and doesn't cost much more than a reference unless the string is changed (which it shouldn't need to be since player names are set at program invocation)
    
    change from 
    	std::string & name;
    to	
    	std::string name;
    	
    8.
    -warning
    
    In file included from HoldEmGame.cpp:8:
    HoldEmGame.h: In constructor ‘HoldEmGame::HoldEmPlayer::HoldEmPlayer(std::__cxx11::string, CardSet<HoldEmRank, Suit>, HoldEmHandRank)’:
    HoldEmGame.h:74:21: warning: ‘HoldEmGame::HoldEmPlayer::name’ will be initialized after [-Wreorder]
             std::string name;
                         ^~~~
    HoldEmGame.h:73:35: warning:   ‘CardSet<HoldEmRank, Suit> HoldEmGame::HoldEmPlayer::hand’ [-Wreorder]
             CardSet<HoldEmRank, Suit> hand;
                                       ^~~~
    HoldEmGame.cpp:279:1: warning:   when initialized here [-Wreorder]
     HoldEmGame::HoldEmPlayer::HoldEmPlayer(std::string n, CardSet<HoldEmRank, Suit> h, HoldEmHandRank r) : name(n), hand(h), rank(r) {}
     ^~~~~~~~~~
     
     -solution: The variable should appear in the same order as they appear in the class definition. 
     Changed from 
    		CardSet<HoldEmRank, Suit> hand;
            std::string name;
            HoldEmHandRank rank;
            HoldEmPlayer();
            HoldEmPlayer(std::string n, CardSet<HoldEmRank, Suit> c, HoldEmHandRank r);
     to
     		std::string name;
    		CardSet<HoldEmRank, Suit> hand;
            HoldEmHandRank rank;        
            HoldEmPlayer();
            HoldEmPlayer(std::string n, CardSet<HoldEmRank, Suit> c, HoldEmHandRank r


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

```
10: We defined a staitic hashmap 'points' (std::unordered_map<PinochleMelds,int> points) whose key is the PinochleMelds and
value is its points. Then we can access the points directly using [] operator (points[melds])

11: Check card in hand and return the approriate PinochleMelds it found. Here I used std::unordered_map <PinochleRank,std::unordered_map<Suit,int>> 
to store the card, and check from ace to jack. For each rank check if every suit appears twice, if not check if every rank appers more or equal than once.  
If no sixhundredqueens,sixtyqueens,fourhundredjacks or fortyjacks showed up, check doublepinochle and pinochle.

16: Defind less than opeator and compare two players.
	Compare the rank member, if the first player has bigger rank return true, if smaller return false, if equal we need to look at the cards.
	We sort the card first. 
	If straightflush, just compare rank of the smallest card of each player
	If fourofakind, just compare the rank of second card since that is for sure the rank occured four times
    If fullhouse or threeofakind, the 3th card would be definitely the one occured three times.
    If flush or xhigh, compare the maimum rank until they are not the same.
    If pair or two pair, compare the paired card rank then the single card rank. 
```





Test Case and Results:

    Case 1. only program name
    $ ./lab2 
    Usage: ./lab2 <Pinochle / HoldEm>  <4 players / 2-8 players>
    $ echo $?
    1
    
    1 correpons to 'error usage'
    
    Case 2. program name and invalid game name
    $ ./lab2 random
    Invalid Gamename
    Usage: ./lab2 <Pinochle / HoldEm>  <4 players / 2-8 players>
    $ echo $?
    1
    	
    Case 3. program name and valid game name (Pinochle), but invalid number of players
        > ./lab1 Pinochle player1 player2 player3
        Invalid number of players in Pinochle, must have exactly 4 players.
        For example: Pinochle player1 player2 player3 player4
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>
    
    Case 4. program name and valid game name (Pinochle), and valid number of players. I ran a lot of times and the results are correctly identified. There is also one case that eightykings and pinochle showed up in the same cardset, and it was also identified.
    
    ./lab2 Pinochle player1 player2 player3 player4
    ====================================================
    =                 PinochleGame                     =
    ====================================================
    Dealing cards...
    player1's hand: 
    K♥ Q♦ A♠ K♠ 
    A♥ A♣ 9♣ 10♣ 
    10♦ K♣ K♦ 9♦ 
    
    
    eightykings :80points
    
    player2's hand: 
    J♠ J♥ 9♣ Q♥ 
    9♦ A♥ 9♥ J♣ 
    10♣ 10♥ Q♣ J♠ 
    
    
    player3's hand: 
    Q♥ J♣ A♦ K♥ 
    K♣ Q♣ 10♥ K♠ 
    10♦ 9♠ Q♦ 9♥ 
    
    
    player4's hand: 
    J♦ A♣ A♦ 10♠ 
    9♠ A♠ 10♠ K♦ 
    J♦ Q♠ J♥ Q♠ 
    
    
    doublepinochle :300points
    
    
    Do you want to end the game? (y/n)
    n
    Dealing cards...
    player1's hand: 
    A♣ A♣ 10♥ 10♣ 
    K♠ 10♦ Q♠ 9♣ 
    J♣ 10♦ K♣ J♦ 
    
    
    pinochle :40points
    
    player2's hand: 
    J♠ Q♦ Q♦ 10♠ 
    J♦ 9♣ A♠ J♣ 
    K♥ 9♦ Q♥ Q♠ 
    
    
    pinochle :40points
    
    player3's hand: 
    10♣ A♥ A♥ 9♥ 
    A♠ Q♣ 9♦ K♠ 
    K♥ J♥ J♥ 9♥ 
    
    
    player4's hand: 
    K♦ 10♠ 9♠ A♦ 
    A♦ K♣ 9♠ Q♣ 
    J♠ K♦ Q♥ 10♥ 
    
    Do you want to end the game? (y/n)
    n
    Dealing cards...
    player1's hand: 
    J♠ J♦ K♣ A♠ 
    A♦ 10♠ A♦ K♠ 
    J♠ K♥ K♦ Q♠ 
    
    
    eightykings :80points
    
    pinochle :40points
    
    player2's hand: 
    9♣ J♥ A♣ J♣ 
    A♠ Q♦ K♦ 10♥ 
    J♥ A♥ 9♦ Q♣ 
    
    
    player3's hand: 
    9♠ 9♦ K♥ Q♥ 
    9♣ Q♣ 9♠ 10♥ 
    J♦ K♠ 10♦ Q♥ 
    
    
    player4's hand: 
    Q♦ 10♣ Q♠ A♣ 
    K♣ 10♠ 10♦ 9♥ 
    J♣ A♥ 9♥ 10♣ 
    
    
    Do you want to end the game? (y/n)
    n
    Dealing cards...
    player1's hand: 
    10♦ A♦ 10♣ A♥ 
    J♥ 10♥ 9♣ J♦ 
    J♣ 10♠ Q♥ Q♣ 
    
    
    player2's hand: 
    A♥ K♠ K♣ Q♠ 
    9♠ J♥ Q♥ K♥ 
    Q♠ Q♣ K♦ A♦ 
    
    
    eightykings :80points
    
    player3's hand: 
    J♠ 9♠ K♥ K♣ 
    Q♦ 9♥ J♦ A♠ 
    Q♦ A♠ 9♥ 10♠ 
    
    
    player4's hand: 
    K♦ A♣ 10♣ A♣ 
    10♥ 9♣ 10♦ 9♦ 
    J♣ 9♦ K♠ J♠ 
    
    
    Case 5. program name and valid game name (HoldEm), but invalid number of players
        > ./lab1 HoldEm playerA                          
        Invalid number of players in HoldEm, must have between 2 and 9 players.
        For example: HoldEm player1 player2
        Usage: ./lab1 <Pinochle / HoldEm>  <4 players / 2-8 players>
    
    Case 6. program name and valid game name (HoldEm), and valid number of players
    $ ./lab2 HoldEm player1 player2 player3 player4
    ====================================================
    =                 HoldEmGame                       =
    ====================================================
    player1's hand: 
    3♦ Q♥ 
    
    player2's hand: 
    Q♣ 6♣ 
    
    player3's hand: 
    A♥ A♣ 
    
    player4's hand: 
    9♥ 2♠ 
    
    Flop: 
    K♦ 9♦ 3♥ 
    
    -------Print out from the highest ranked to the lowest player and their cards:-------------
    player3 has pair
    card in player3's hand:   
    A♥ A♣ K♦ 9♦ 3♥ 
    
    player4 has pair
    card in player4's hand: 
    9♥ 2♠ K♦ 9♦ 3♥ 
    
    player1 has pair
    card in player1's hand: 
    3♦ Q♥ K♦ 9♦ 3♥ 
    
    player2 has xhigh
    card in player2's hand: 
    Q♣ 6♣ K♦ 9♦ 3♥ 
    
    Turn: 
    K♦ 9♦ 3♥ Q♠ 
    
    River: 
    K♦ 9♦ 3♥ Q♠ 2♦ 
    
    
    
    Do you want to end the game? (y/n)
    n
    player1's hand: 
    J♠ J♦ 
    
    player2's hand: 
    3♦ 7♣ 
    
    player3's hand: 
    Q♣ Q♦ 
    
    player4's hand: 
    10♦ K♠ 
    
    Flop: 
    7♦ 2♠ 3♥ 
    
    -------Print out from the highest ranked to the lowest player and their cards:-------------
    player2 has twopair
    card in player2's hand: 
    3♦ 7♣ 7♦ 2♠ 3♥ 
    
    player3 has pair
    card in player3's hand: 
    Q♣ Q♦ 7♦ 2♠ 3♥ 
    
    player1 has pair
    card in player1's hand: 
    J♠ J♦ 7♦ 2♠ 3♥ 
    
    player4 has xhigh
    card in player4's hand: 
    10♦ K♠ 7♦ 2♠ 3♥ 
    
    Turn: 
    7♦ 2♠ 3♥ 6♥ 
    
    River: 
    7♦ 2♠ 3♥ 6♥ 10♣ 
    
    
    Do you want to end the game? (y/n)
    n
    player1's hand: 
    5♣ 3♠ 
    
    player2's hand: 
    2♣ 10♣ 
    
    player3's hand: 
    A♣ 2♦ 
    
    player4's hand: 
    9♥ K♠ 
    
    Flop: 
    7♦ 6♠ 4♥ 
    
    -------Print out from the highest ranked to the lowest player and their cards:-------------
    player1 has straight
    card in player1's hand: 
    5♣ 3♠ 7♦ 6♠ 4♥ 
    
    player3 has xhigh
    card in player3's hand: 
    A♣ 2♦ 7♦ 6♠ 4♥ 
    
    player4 has xhigh
    card in player4's hand: 
    9♥ K♠ 7♦ 6♠ 4♥ 
    
    player2 has xhigh
    card in player2's hand: 
    2♣ 10♣ 7♦ 6♠ 4♥ 
    
    Turn: 
    7♦ 6♠ 4♥ 7♠ 
    
    River: 
    7♦ 6♠ 4♥ 7♠ 2♠ 
    
    
    Do you want to end the game? (y/n)
    n
    player1's hand: 
    K♣ 3♦ 
    
    player2's hand: 
    10♠ K♥ 
    
    player3's hand: 
    4♠ 2♣ 
    
    player4's hand: 
    9♣ J♠ 
    
    Flop: 
    Q♦ Q♣ 6♦ 
    
    -------Print out from the highest ranked to the lowest player and their cards:-------------
    player2 has pair
    card in player2's hand: 
    10♠ K♥ Q♦ Q♣ 6♦ 
    
    player1 has pair
    card in player1's hand: 
    K♣ 3♦ Q♦ Q♣ 6♦ 
    
    player4 has pair
    card in player4's hand: 
    9♣ J♠ Q♦ Q♣ 6♦ 
    
    player3 has pair
    card in player3's hand: 
    4♠ 2♣ Q♦ Q♣ 6♦ 
    
    Turn: 
    Q♦ Q♣ 6♦ 4♦ 
    
    River: 
    Q♦ Q♣ 6♦ 4♦ 6♣ 
    
    



