/*
	Jason Wilden
	CS362 Assignment 3
	10/26/2018
	cardtest1.c
	
	some code borrowed from example code provided
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include "myAssert.h"

#define TESTCARD "steward"

int main() {
    int i, l;
	int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	time_t t;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// from: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	printf("----------------- Testing smithy ----------------\n");
	do
	{
		l = rand()%(treasure_map+1);
	} while (l<7 || l > 17);
	
	//printf("rand seed is:%i\n",l);
	for (i=0; i<10; i++)
	{
		k[i] = l + i;
		//printf("k is %i\n",k[i]);
	}
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//printf("handCount:%i\n",testG.handCount[thisPlayer]);
	//printf("deckCount:%i\n",testG.deckCount[thisPlayer]);
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
	
	myAssert(testG.handCount[thisPlayer],testG.handCount[thisPlayer]+2,1);
	myAssert(testG.deckCount[thisPlayer],testG.deckCount[thisPlayer]-3,2);
	
	//printf("handCount:%i\n",testG.handCount[thisPlayer]);
	//printf("deckCount:%i\n",testG.deckCount[thisPlayer]);
	
	//myAssert(testG.handCount[thisPlayer] , G.handCount[thisPlayer], 7);
	//myAssert(testG.deckCount[thisPlayer] , G.deckCount[thisPlayer], 7);
	myAssert(testG.whoseTurn , G.whoseTurn, 7);
	myAssert(testG.phase , G.phase, 7);
	myAssert(testG.numActions , G.numActions, 7);
	myAssert(testG.coins , G.coins, 7);
	myAssert(testG.numBuys , G.numBuys, 7);

	return 0;
}


