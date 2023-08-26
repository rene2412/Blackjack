#include "/public/read.h"
#include <deque>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "/public/colors.h"
#include <algorithm>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
class Cards {
private: 
	//member vars
	 std::string face;
	 std::string suit;
	int val = 0;
public:
	//def constructor
	Cards() : face(""), suit(""), val(0) {}
	// 3 paramter construcutor
	Cards(const std::string& f, const std::string& s, int v = 0) : face(f), suit(s), val(v) {}
	//getters
	std::string get_face() const { return face; }
	std::string get_suit() const { return suit; }
	int get_val() const { return val; }
	//setter
	void set_val(int v) { val = v; }
	// friend overload function that replaces cout, returns the output stream
		friend std::ostream& operator<< (std::ostream& outs, const Cards &card) {
			return outs << card.get_face() << " of " << card.get_suit() << std::endl;
	}
};

class Deck {
private:
	std::deque<Cards> deck; //holds the 52 deck of cards
public:
	 std::vector<std::string> faces = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; 
	 std::vector<std::string> suits = {"Spades", "Clubs", "Hearts", "Diamond"};

	// 1 parameter construtor 
	Deck(const std::deque<Cards> d) : deck(d) {}
	//copy constructor
	Deck(const Deck& temp) : deck(temp.deck) {} 
	//deque getter
	const std::deque<Cards>& get_deck() const { return deck; }
    // default constructor that populates the cards and reshuffles them 	
	Deck() {
		for (const std::string& suit : suits) {
			int value = 1;
			for (const std::string &face : faces) {
				Cards temp(face, suit);
				if (value > 10) value = 10;
				temp.set_val(value == 1 ? 11 : value);
				value++;
				deck.push_back(temp);	
				}	
			}
			  srand(time(0));
			  random_shuffle(deck.begin(), deck.end());
		}
	//Cards objecy function that gets the first card then pops it to move to the next
	Cards draw() {
		Cards temp = deck.front();
		deck.pop_front();
		return temp;
	}
};

class Hand {
private:
	std::vector<Cards> player; //holds the players cards
	std::vector<Cards> dealer; //holds the dealers cards
	std::vector<int> player_values; //holds the players vals
	std::vector<int> dealer_values; //holds dealer vals
public:
	//def constrcutor
	Hand() : player(), dealer(), player_values(), dealer_values() {}
	//4 parameter constrcutor
	Hand(std::vector<Cards>& player_hand, std::vector<Cards>& dealer_hand, std::vector<int> player_vals, 
         std::vector<int> dealer_vals) : player(player_hand), dealer(dealer_hand), player_values(player_vals), dealer_values(dealer_vals) {}
	//getters for the dealers and players cards and values
	 std::vector<Cards>& get_player_hand()  { return player; }	
	 std::vector<Cards>& get_dealer_hand()  { return dealer; }
	 std::vector<int>& get_player_vals()    { return player_values; }
	 std::vector<int>& get_dealer_vals()    { return dealer_values; }
	
	   Deck x;
		//functiom that will draw the first 2 cards to player and dealer
		void defualt_cards() {
		for (int i = 0; i < 2; i++) {
			Cards curr_card = x.draw();
			player.push_back(curr_card);
			player_values.push_back(curr_card.get_val());	
			}
		for (int i = 0; i < 1; i++) {
			Cards curr_card = x.draw();
			dealer.push_back(curr_card);
			dealer_values.push_back(curr_card.get_val());
			}
		}
		//function that will push back a player card by 1
		void add_player_card() {
			Cards tmp = x.draw();
			player.push_back(tmp);
			player_values.push_back(tmp.get_val());
		}
	//function that will push back a dealers card by 1
		void add_dealer_card() { 
			Cards tmp = x.draw();
			dealer.push_back(tmp);
			dealer_values.push_back(tmp.get_val());
		}

	//function to return the total value of the players currents hand
	int total_player() {
		int total = 0;
		for (auto x : player_values) {
			total = total + x;
		}
		return total;	
	}	
	//function to return the total value of the dealers current hand
	int total_dealer() {
		int total = 0;
		for (auto x : dealer_values) {
			total = total + x;
		}
		return total;
	}
	//function that clears all the data sets to start a new game
	void clear_deck() {
		get_player_hand().clear();
		get_player_vals().clear();	
		get_dealer_hand().clear();
		get_dealer_vals().clear();
	}
	
//boolean function that will check if natural blackjack occured
bool check_blackjack(const std::string& name, const std::vector<int>& p, const std::vector<int>& d,  int& balance, int& wager) {
	int i = 0;
	int j = 0;

	for (auto x : p) {
		i = i + x;
	}
	for (auto x : d) {
		j = j + x;
	}
	if (i == 21 and j != 21) {
		std::cout << GREEN << name << WHITE << " Has Drawn A Natural BlackJack" << std::endl;
		std::cout << "Payout is 150%!" << std::endl;
		balance = balance + wager * 1.5;
		return true;
	}
	else return false;
	}
};
