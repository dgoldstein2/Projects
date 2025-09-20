/*
 * CSEN 79 Lab: Poker Statistics
 * Names: Dakota Goldstein and Kayla Malloy
 * Purpose: This file contains the function PokerHands which generates one sample hand for each rank.
 * It also contains PokerStats, which generates the statistics for each rank of poker.
 * In the main method, both pokerHands and pokerStats are called to test their functionality
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>
#include "card.h"
#include "deck.h"
#include "poker.h"



using namespace std;
using namespace csen79;


// Generate one sample hand for each rank
void pokerHands(Poker &poker) {
	/*
	 * Loop until you have found one of each rank.
	 * Print that "sample hand"
	 */
	
	Poker::Rank rank;
	//All integers are initialized for countersfor the switch to make break statements
	int fl = 0; //Flush
	int st = 0; //Straight
	int p = 0; //Pair
	int p2 = 0; //Two Pair
	int p3 = 0; //Triple
	int fh = 0; //Full House
	int Q = 0; //Quads
	int SFl = 0; //Straight Flush
	int hc = 0; //High Card
	bool done = false;
	int check = 0; //A counter to check to see if all ranks have a hand
	Deck deck = poker.getDeck();
	while(!done){
		deck.shuffle();
		poker.dealHand();
		rank = poker.rankHand();
		const Card* hand = poker.getHand();
		switch(rank){ //A switch that goes into each condition depending on the rank
			case Poker::Rank::POKER_HIGHCARD: //Each Case which corresponds to the rank of the hand
				if(hc > 0){ //Each one of these Pre statements check to see if a hand for this rank was already dealt
					break;
				}
				for(int i =0;i<5;i++){ //Prints out the Hand
					cout<<hand[i];
				}
				hc++;
				cout<< " high card" << endl;
				check++;
				break;
			case Poker::Rank::POKER_PAIR:
				if(p > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<< " pair"<< endl;
				p++;
				check++;
				break;
			case Poker::Rank::POKER_2_PAIR:
				if(p2 > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" two pair"<<endl;
				p2++;
				check++;
				break;
			case Poker::Rank::POKER_TRIPLE:
				if(p3 > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" triple"<<endl;
				p3++;
				check++;
				break;
			case Poker::Rank::POKER_STRAIGHT:
				if(st > 0){
				break;
				}
				
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" straight"<<endl;
				st++;
				check++;
				break;
			case Poker::Rank::POKER_FLUSH:
				if(fl > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" flush"<<endl;
				fl++;
				check++;
				break;
			case Poker::Rank::POKER_FULLHOUSE:
				if(fh > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" full house"<<endl;
				fh++;
				check++;
				break;
			case Poker::Rank::POKER_QUAD:
				if(Q > 0){					
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" quad"<<endl;
				Q++;
				check++;
				break;
			case Poker::Rank::POKER_STRAIGHT_FLUSH:
				if(SFl > 0){
					break;
				}
				for(int i =0;i<5;i++){
					cout<<hand[i];
				}
				cout<<" straight flush"<<endl;
				SFl++;
				check++;
				break;
			default:				
				break;
			

		}
		if(check == 9){ //Checks to see if all ranks have a hand 
			done = true;
		}
	}
}

// Collect statistics for each rank of Poker
void pokerStats(Poker &poker) {
	time_t tmark = clock();			// ready, get set, go!
	/*
	 * Do your thing here.
	 * This is supposed to be big loop that deal many many poker hands and collect the
	 * statistics for each rank.
	 * Once you believe the statistics are good.  Exit the loop.
	 * "tmark" then computes the number of "clock ticks" in your loop.
	 * You should convert that to human friendly units, such as "seconds"
	 * 
	 * Output your stats then, with the amount of time it took you collect the stats.
	 */
	float highCount; //counts for different types of ranks
	float straightFlushCount = 0;
	float flushCount = 0;
	float straightCount = 0;
	float pairCount = 0;
	float count2Pair = 0;
	float tripCount = 0;
	float quadCount = 0;
	float FHCount = 0;
	float howManyDeals = 0; //keeps track of how many deals made
	int stableCount = 0; //counts how many ranks are stable
	float highStat = 0; //keeps track of the stats per hand
	float SFStat = 0;
	float flushStat = 0; 
	float straightStat = 0; 
	float pairStat = 0;
	float twoPairStat = 0;
	float tripStat = 0;
	float quadStat = 0;
	float FHStat = 0;
	bool stable = false; //tracks if stats are stable
	float stabilityFactor = 0.0001; //differences between stats to see if stable
	Deck deck = poker.getDeck();
   do{
		stableCount = 0;
		deck.shuffle(); //generate new hand
		poker.dealHand();
		Poker::Rank rank;
		rank = poker.rankHand();
		const Card* hand = poker.getHand();
		howManyDeals++; //increment hand delt
		switch(rank){ //A switch that increments each count based on the highest possible rank it can be
			case Poker::Rank::POKER_STRAIGHT_FLUSH:
				straightFlushCount++;
				break;
			case Poker::Rank::POKER_QUAD:
				quadCount++;
				break;
			case Poker::Rank::POKER_FULLHOUSE:
				FHCount++;
				break;
			case Poker::Rank::POKER_FLUSH:
				flushCount++;
				break;
			case Poker::Rank::POKER_STRAIGHT:
				straightCount++;
				break;
			case Poker::Rank::POKER_TRIPLE:
				tripCount++;
				break;
			case Poker::Rank::POKER_2_PAIR:
				count2Pair++;
				break;
			case Poker::Rank::POKER_PAIR:
				pairCount++;
				break;
			case Poker::Rank::POKER_HIGHCARD:
				highCount++;
				break;
			default:				
				break;
		}
		if((int)howManyDeals % 100000 == 0){ //check for stability every 100,000 deals
			if((highCount/howManyDeals) - highStat < stabilityFactor){ //if the old stat and new stat differ by less than 0.001, the stat is stable
				stableCount++;
			}
			if((straightFlushCount/howManyDeals) - SFStat < stabilityFactor){
				stableCount++;
			}
			if((flushCount/howManyDeals) - flushStat < stabilityFactor){
				stableCount++;
			}
			if((straightCount/howManyDeals) - straightStat < stabilityFactor){
				stableCount++;
			}
			if((pairCount/howManyDeals) - pairStat < stabilityFactor){
				stableCount++;
			}
			if((count2Pair/howManyDeals) - twoPairStat < stabilityFactor){
				stableCount++;
			}
			if((tripCount/howManyDeals) - tripStat < stabilityFactor){
				stableCount++;
			}
			if((quadCount/howManyDeals) - quadStat < stabilityFactor){
				stableCount++;
			}
			if((FHCount/howManyDeals) - FHStat < stabilityFactor){
				stableCount++;
			}
			highStat = highCount/howManyDeals; //set up the new stats
			SFStat = straightFlushCount/howManyDeals;
			flushStat = flushCount/howManyDeals;
			straightStat = straightCount/howManyDeals;
			pairStat = pairCount/howManyDeals;
			twoPairStat = count2Pair/howManyDeals;
			tripStat = tripCount/howManyDeals;
			quadStat = quadCount/howManyDeals;
			FHStat = FHCount/howManyDeals; 
			if(stableCount == 9){ //if all hands are stable, the whole dataset is stable
				stable = true;
			}
		}
	}while(!stable);
	tmark = clock() - tmark;	// stop the clock
	double seconds = (double)tmark/ CLOCKS_PER_SEC; //convert the ticks to seconds
	//print information to screen
	cout << "Dealt " << (int)howManyDeals << " hands. Elpased Time: " << seconds << " seconds.\n";

	cout<< "Average "<< seconds/(howManyDeals/50000) << " seconds per 50k hands.\n";
	cout << "Straight Flush: \t" << (int)straightFlushCount << "   " << SFStat*100 << "%\n";
	cout << "Four of a Kind: \t" << (int)quadCount << "   " << quadStat*100 << "%\n";
	cout << "Full House:     \t" << (int)FHCount << "   " << FHStat*100 << "%\n";
	cout << "Flush:          \t" << (int)flushCount << "   " << flushStat*100 << "%\n";
	cout << "Straight:       \t" << (int)straightCount << "   " << straightStat*100 << "%\n";
	cout << "Triple:         \t" << (int)tripCount << "   " << tripStat*100 << "%\n";
	cout << "Two Pairs:      \t" << (int)count2Pair << "   " << twoPairStat*100 << "%\n";
	cout << "Pair:           \t" << (int)pairCount << "   " << pairStat*100 << "%\n";
	cout << "High Card:      \t" << (int)highCount << "   " << highStat*100 << "%\n";
}

int main(void) {
	Poker poker;
	cout << "Sample hand for each Rank:" << endl;
	pokerHands(poker);
	cout << endl << "Statistics:" << endl;
	pokerStats(poker);

	return EXIT_SUCCESS;
}
