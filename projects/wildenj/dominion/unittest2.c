/*
	Jason Wilden
	CS362 Assignment 3
	10/26/2018
	unittest2.c
	
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
	int test = 0;
	struct gameState G, testG;
	time_t t;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// from: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	printf("----------------- Testing supplyCount() ----------------\n");
	for (l=0; l<10; l++)
	{
		
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
		
		for (i=0; i<(treasure_map+1); i++)
		{
			//printf("%i\t%i\n",i, supplyCount(i, &testG));
		}
		
		test = supplyCount(0, &testG);
		myAssert(test, 10,1);
		
		for (i = 1; i < 4; i++)
		{
			test = supplyCount(i, &testG);
			myAssert(test, 8,2);
			//printf("%i\t%i\n",i,test);
		}
		
		test = supplyCount(4, &testG);
		myAssert(test, (60 - (7 * numPlayers)),3);
		
		test = supplyCount(5, &testG);
		myAssert(test, 40,4);
		
		test = supplyCount(6, &testG);
		myAssert(test, 30,5);

		for (i = 7; i < (treasure_map+1); i++)
		{
			test = supplyCount(i, &testG);
			if (numPlayers == 2 && (i==great_hall || i== gardens))
			{
				if (test != -1)
					myAssert(test,8,6);
				//printf("%i\ttest: %i\n",i,test);
			}
			else if (numPlayers != 2 &&(i==great_hall || i== gardens))
			{
				if (test != -1)
				myAssert(test,12,6);
				//printf("%i\ttest: %i\n",i,test);
			}
			else if (test == 10)
			{
				myAssert(test,10,6);
				//printf("%i\ttest: %i\n",i,test);
			}
			else 
			{
				myAssert(test,-1,6);
				//printf("%i\ttest: %i\n",i,test);
			}
		}
		
		myAssert(testG.handCount[thisPlayer] , G.handCount[thisPlayer], 7);
		myAssert(testG.deckCount[thisPlayer] , G.deckCount[thisPlayer], 7);
		myAssert(testG.whoseTurn , G.whoseTurn, 7);
		myAssert(testG.phase , G.phase, 7);
		myAssert(testG.numActions , G.numActions, 7);
		myAssert(testG.coins , G.coins, 7);
		myAssert(testG.numBuys , G.numBuys, 7);
	}
	printf("Supply Count Tests Passed\n");

	return 0;
}


