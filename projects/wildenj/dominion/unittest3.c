/*
	Jason Wilden
	CS362 Assignment 3
	10/26/2018
	unittest3.c
	
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
    int i, j, l, m, n;
	int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int tmp = 0;
	struct gameState G, testG;
	time_t t;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// from: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	printf("----------------- Testing fullDeckCount() ----------------\n");
	
	for (n=0; n<10; n++)
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
		
		for (j=0; j<numPlayers; j++)
		{
			for (i=0; i<(treasure_map+1); i++)
			{
				//printf("%i\t%i\n",i, fullDeckCount(j,i, &testG));
				if (i==1)
					myAssert(3,fullDeckCount(j,i, &testG),1);
				if (i==4)
					myAssert(7,fullDeckCount(j,i, &testG),1);
			}
			//printf("HAND COUNT:%i\n",testG.handCount[j]);
			//printf("DECK COUNT:%i\n",testG.deckCount[j]);
			//printf("DISCARD COUNT:%i\n",testG.discardCount[j]);
			for (m=0; m<testG.handCount[j]; m++)
			{
				do
				{
					l = rand()%(treasure_map+1);
				} while (l==1 || l == 4);
				//printf("hand is:%i\n",testG.hand[j][m]);
				tmp = testG.hand[j][m];
				testG.hand[j][m] = l;
				myAssert(1,fullDeckCount(j,l, &testG),2);
				testG.hand[j][m] = tmp;
				//printf("TESTING:%i\t%i\n",l, fullDeckCount(j,l, &testG));
			}
			
			for (m=0; m<testG.deckCount[j]; m++)
			{
				do
				{
					l = rand()%(treasure_map+1);
				} while (l==1 || l == 4);
				//printf("deck is:%i\n",testG.deck[j][m]);
				tmp=testG.deck[j][m];
				testG.deck[j][m] = l;
				myAssert(1,fullDeckCount(j,l, &testG),3);
				testG.deck[j][m] = tmp;
				//printf("TESTING:%i\t%i\n",l, fullDeckCount(j,l, &testG));
			}
			
			for (m=0; m<testG.discardCount[j]; m++)
			{
				do
				{
					l = rand()%(treasure_map+1);
				} while (l==1 || l == 4);
				//printf("discard is:%i\n",testG.discard[j][m]);
				tmp = testG.discard[j][m];
				testG.discard[j][m] = l;
				myAssert(1,fullDeckCount(j,l, &testG),4);
				testG.discard[j][m] = tmp;
				//printf("TESTING:%i\t%i\n",l, fullDeckCount(j,l, &testG));
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

	printf("fullDeckCount() Tests Passed\n");

	return 0;
}


