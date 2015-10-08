#include <iostream>
#include <string>
#include <stdlib.h> //random number generator
#include <time.h>
#include <array>

using namespace std;

class Deck{

	private:
		//generating deck
		int fullDeck [52][2];
		int cardSuit = 0; //value from 0 to 13
		int cardValue = 1;
		int returnSuit = 0;
		int returnValue = 0;

		//other functions
		int cardsRemaining = 52;
		int deckIndex = 0;
		string cardString = "";

		//spades hearts clubs diamonds : 0 1 2 3
		//gereates the deck in the form [{1,0},{2,0},{3,0},{4,0}...{12,3},{13,3}]
		int generateDeck(){
			for (int i = 0; i < 52; i ++){
				fullDeck[i][0] = cardValue;
				fullDeck[i][1] = cardSuit;
				cardValue ++;
				if (cardValue > 13){
					cardValue = 1;
					cardSuit++;
				}				
			}
			return 0;
		};

		//deletes a card from the fullDeck array given an index for which card to delete
		void deleteCard(int deckIndex){
			for (int x = deckIndex; x < cardsRemaining-1; x ++){
				fullDeck[x][0] = fullDeck[x+1][0];
				fullDeck[x][1] = fullDeck[x+1][1];
			}
			fullDeck[cardsRemaining-1][0] = 0;
			fullDeck[cardsRemaining-1][1] = 0;
		}

		//prints out all the cards in the deck in a 52x2 array. Used for trouble shooting
		void printDeck(){
			for (int i = 0; i < 52; i++){
				cout << fullDeck[i][0] << " ";
				cout << fullDeck[i][1] << endl;
			}
		}

	public:
		Deck(){
			srand(time(0));
			generateDeck();
		};

		//calling the drawCard function will return a string with the card value from 1-13, 1 being ace 13 being king
		//followed by an underscore, and the suit value, 0,1,2,3 representing diamonds, spades, hearts clubs
		//will return "No cards left in deck" string when all 52 cards have been drawn
		//jokers are not incuded in the deck

		string drawCard(){
			if (cardsRemaining > 0 ){
				deckIndex = (rand()%cardsRemaining)+1;
				returnValue = fullDeck[deckIndex-1][0];
				returnSuit = fullDeck[deckIndex-1][1];
				cardString = to_string(returnValue) + "_" + to_string(returnSuit);
				deleteCard(deckIndex-1);
				cardsRemaining--;
				return (cardString);
			}
			else
				return "No cards left in deck";
		};

		//getters
		int getCardsRemaining(){
			return cardsRemaining;
		}


};

// main program 

void hitMe(int player);
void printHand();
void recalculateHandTotal();

int dealerTotalValue = 0;
int dealerTotalSuit = 0;
int dealerCardCounter = 0;
int dealerHand [5] = {0};
int dealerHandSuit [5] = {0};

int playerTotalValue = 0;
int playerTotalSuit = 0;
int playerCardCounter = 0;
int playerHand [5] = {0};
int playerHandSuit [5] = {0};

int newCardValue = 0;
int newCardSuit = 0;

Deck deck;

string drawnCard = "";
string userInput = "";

bool compare = true;

int main(){

	cout << "Blackjack" << endl;
    
    //deals two cards to each player
	hitMe(0);
	hitMe(0);
	hitMe(1);
	hitMe(1);

	while(userInput != "stand"){

		cout << "Here are your cards: "<< endl;
		printHand();
		cout << endl;
		//winning/losing conditions
		if (playerCardCounter == 5 && playerTotalValue <= 21){
			cout << "You win! More than 5 cards!";
			compare = false;
			break;
		}
		if (playerTotalValue > 21){
			cout << "Total over 21, you lose :(" << endl;
			compare = false;
			break;
		}
		cout << "What do you want to do? ";
		getline (cin,userInput);

		while(userInput != "stand" && userInput != "hit me" && userInput != "hit"){
			cout << "Invalid Input" << endl;
			getline (cin,userInput);
		}

		if (userInput == "hit me" || userInput == "hit"){
			hitMe(1);
		}
		recalculateHandTotal();
	}
	if(compare == true){
		while((playerCardCounter > 2 && dealerTotalValue < 17)|| dealerTotalValue <= 13){
			hitMe(0);
			cout << "Dealer hits!" << endl;
			recalculateHandTotal();
		}
		if(dealerTotalValue < playerTotalValue && playerTotalValue <= 21){
			cout << "You win! Dealer has a total of " << dealerTotalValue << " and you have a total of " << playerTotalValue << "."<< endl;
		}
		else if(dealerTotalValue > 21){
			cout << "Dealer bust with "<< dealerTotalValue << ". You win!" << endl;
		}
		else{
			cout << "You lose! Dealer has a total of " << dealerTotalValue << " and you have a total of " << playerTotalValue << "."<< endl;
		}
	}
	cout <<endl<< "Game over"; 
	return 0;
}

void hitMe(int player){

	int value = 0;
	int suit = 0;

	drawnCard = deck.drawCard();

	if(drawnCard.length() == 3){
		suit = (int)drawnCard.back()-'0';
    	value = stoi(drawnCard.substr(0,1));
	}
	else{
		suit = (int)drawnCard.back()-'0';
    	value = stoi(drawnCard.substr(0,2));
	}

	if (value == 11 || value == 12 || value == 13){
		value = 10;
	}

	if (player == 0){
		dealerHand[dealerCardCounter] = value;
		dealerHandSuit[dealerCardCounter] = suit;
		dealerCardCounter ++;
	}
	else{
		playerHand[playerCardCounter] = value;
		playerHandSuit[playerCardCounter] = suit;
		playerCardCounter ++;
	}
}

void recalculateHandTotal(){
	dealerTotalValue = 0;
	playerTotalValue = 0;
	for (int i = 0; i < 5; ++i)
	{
		dealerTotalValue += dealerHand[i];
		playerTotalValue += playerHand[i];
	}
}

void printHand(){
	for(int i = 0 ; i < playerCardCounter ; i ++){
		cout << "  _________ " << endl;
		cout << " /         \\" << endl;
		if (playerHand[i] < 10){
			cout << "|" << playerHand[i] << "          |" << endl;
		}
		else
			cout << "|" << playerHand[i] << "         |" << endl;

		if (playerHandSuit[i] == 0){
			cout << "|           |" << endl;
			cout << "|    /\\     |" << endl;
			cout << "|   <  >    |" << endl;
			cout << "|    \\/     |" << endl;
			cout << "|           |" << endl;

		}
		if (playerHandSuit[i] == 1){
			cout << "|     _     |" << endl;
			cout << "|    (_)    |" << endl;
			cout << "|   (_)_)   |" << endl;
			cout << "|    /_\\    |" << endl;
			cout << "|           |" << endl;
		}
		if (playerHandSuit[i] == 2){
			cout << "|    _ _    |" << endl;
			cout << "|   / ^ \\   |" << endl;
			cout << "|   \\   /   |" << endl;
			cout << "|    \\ /    |" << endl;
			cout << "|     `     |" << endl;

		}
		if (playerHandSuit[i] == 3){
			cout << "|     ,     |" << endl;
			cout << "|    / \\    |" << endl;
			cout << "|   (_ _)   |" << endl;
			cout << "|    /_\\    |" << endl;
			cout << "|           |" << endl;
		}

		if (playerHand[i] < 10){
			cout << "|          "<< playerHand[i] << "|" << endl;
		}
		else
			cout << "|         "<< playerHand[i] << "|" << endl;

		cout << " \\_________/" << endl << endl;

	}
}


//10 0 20 20