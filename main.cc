#include "/public/read.h"
#include "card_class.h"
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include "/public/colors.h"
#include <thread>
#include <chrono>
using namespace std;

Hand deck; // main game object
//function will retrive a card when they hit that follows the hit logic
void hit (Hand& h) {
 h.add_player_card();
   for (const Cards& card : h.get_player_hand()) { 
		cout << card;
	}
	 cout << "Total: " <<  h.total_player() << endl;
}
//function will retrive a card to the dealers deck that follows the stand logic
void stand (Hand &s) {
while (true) {
int x = s.total_dealer();
if (x <= 16) {
s.add_dealer_card();
cout << endl;
std::this_thread::sleep_for(std::chrono::seconds(2)); //this will pause the dealer printing for 2 seconds so the output all wont spew out at once
cout << CYAN << "Dealer Cards: " << WHITE  << endl;
    for (const Cards& card : s.get_dealer_hand()) {
		cout << card;
	}
 	 cout << "Total: " << s.total_dealer() << endl;
     }
else break;
   }
}

int main() {
system("figlet 'WELCOME TO BLACKJACK' | lolcat");
string name;
int balance = 100;
cout << "Please enter your name: " << endl;
getline(cin, name);
//main game loop
while (true) {
int wager = 0;
if (balance < 5) {
	cout << GREEN << name << WHITE <<" is BANKRUPT! The House Wins!" << endl;
	exit(0);
	}
if (balance > 1000) {
	cout << "JACKPOT!!" << GREEN << name << WHITE << " Has Brought Down The House!" << endl;
	exit(0);	
	}
cout << YELLOW << " - - - - - - - - - - - - - - - - - - - - - " << WHITE << endl;
cout << GREEN << name << WHITE << " how much do you want to wager? ($5 - $" << balance << ")" << endl;
cin >> wager;
if (!cin) { cout << RED << "Invalid Wager!" << WHITE << endl; exit(1); }
if ( wager < 5 or wager > balance){
	cout << RED << "Invalid Wager! Please enter a valid wager: " << WHITE << endl; 
	continue;
	}
	
cout << "Balance: $" << balance << " | Wager: " << wager << endl;
cout << GREEN << name << "'s cards: " << WHITE << endl;
deck.defualt_cards();//populates and shuffles the deck
for (const Cards& card : deck.get_player_hand()) {
		cout << card;
		}
	cout << "Total: " <<  deck.total_player() << endl << endl;
cout << CYAN << "Dealer Card: " << WHITE << endl;
for (const Cards& card : deck.get_dealer_hand()) {
	cout << card;
	}
cout << "Total: " <<  deck.total_dealer() << endl;
cout << endl;
//chrcking for possible natural blackjack
if (deck.check_blackjack(name, deck.get_player_vals(), deck.get_dealer_vals(), balance, wager)) {
	deck.clear_deck();
	continue;
	}
//HIT or STAND loop until someome wins 
while (true) {

string choice;
cout << GREEN << name << WHITE << ", do you want to 'HIT' or 'STAND'" << endl;
cin >> choice;
if (choice != "HIT" and  choice != "STAND") {
	cout << RED << "Invalid Input!" << WHITE << endl;
	cin.clear(); 
	cin.ignore();
	continue;
   }
	
if (choice == "HIT") {
cout << GREEN << name << "'s Cards: " << WHITE << endl;
	hit(deck);
	int x = deck.total_player();
    if (x > 21) {
		cout << GREEN << name << WHITE << " has busted!" << endl;
		balance = balance - wager;
		deck.clear_deck();
		break;
		}
	}	
else if (choice == "STAND") {
	cout << CYAN << "Dealer Cards: " << WHITE << endl;
	for (const Cards& card : deck.get_dealer_hand()) {
		cout << card;
		}
	cout << "Total: " << deck.total_dealer() << endl;
	stand(deck); //calling the stand function
	int dealer = deck.total_dealer();
	int player = deck.total_player();
    if (dealer == player and player == dealer) {
		cout << "PUSH, It's A Draw!" << endl;
		deck.clear_deck();
		break;
	}
	 if (dealer <= 21 and dealer > player) {
		cout << GREEN << name << WHITE << " has busted!" << endl;	
		balance = balance - wager;
		deck.clear_deck();
		break;
	}
    if (dealer > 21 and player < 21) {
		balance = balance + wager;
		cout << CYAN << "Dealer" << WHITE << " has busted" << endl;
		deck.clear_deck();
		break;
	  		}
	if (dealer <= 21 and player <= 21 and dealer < player and player > dealer) {
		cout << CYAN << "Dealer " << WHITE << " has busted" << endl;
		balance = balance + wager;
		deck.clear_deck();
		break;
	 	}
	}
}
	cout << "New Balance: $" << balance << endl;
  }
}
