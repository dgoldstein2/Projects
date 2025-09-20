/*
 * Dakota Goldstein & Kayla Malloy
 * dagoldstein@scu.edu & krmalloy@scu.edu
 * Purpose: This file implements shuffle and deal
 */
#include <iostream>

#include "card.h"
#include "deck.h"

namespace csen79 {
	// implement Fisher-Yates here
	void Deck::shuffle(void) {
		for (int i = CARDS_PER_DECK - 1; i > 0; i--) { 
         int j = rand() % (i + 1); //generates random number based on how many cards still need to be swapped
			Card temp = cards[i]; //swaps cards
			cards[i] = cards[j];
			cards[j] = temp;
    }
	}

	// deal out one card
	const Card &Deck::deal() {
	   if(CARDS_PER_DECK - getNext() < getGuard()){ //shuffles if cards in the deck is less than guard value 5
			shuffle();
			setNext(1); //sets next card in deal to be 1 because card 0 is being dealed
			return cards[0]; //return top of deck
		}
		int spot = getNext(); //get spot of "top" of deck
		setNext(spot+1); //set spot to next card
		return cards[spot]; //pop from top of deck
	}
}

