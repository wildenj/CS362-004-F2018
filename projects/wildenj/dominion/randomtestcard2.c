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
    int i, l, nTrials = 10000, trial=0;;
	int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int tmp, test;
	int handPos = 2, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState G, testG;
	time_t t;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// from: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	printf("----------------- Testing great_hall ----------------\n");
	for (trial=0; trial<nTrials; trial++)
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
		
		/*for (i=0; i<numPlayers-1; i++)
		{
			printf("deck count:%i\n",testG.deckCount[i]);
			for (m=0; m<testG.deckCount[i]; m++)
			{
				printf("Deck: %i\n",testG.deck[i][m]);
			}
			printf("hand count:%i\n",testG.handCount[i]);
			for (m=0; m<testG.handCount[i]; m++)
			{
				printf("Hand: %i\n",testG.hand[i][m]);
			}
			printf("discard count:%i\n",testG.discardCount[i]);
			for (m=0; m<testG.discardCount[i]; m++)
			{
				printf("discard: %i\n",testG.discard[i][m]);
			}
		}
		//testG.whoseTurn = 1;
		printf("handCount:%i\n",testG.handCount[thisPlayer]);
		printf("deckCount:%i\n",testG.deckCount[thisPlayer]);
		//*/
		
		//printf("count is:%i\n",fullDeckCount(thisPlayer, 0, &testG));
		
		

		
		
		//printf("handCount:%i\n",testG.handCount[thisPlayer]);
		//printf("deckCount:%i\n",testG.deckCount[thisPlayer]);
		
		/*for (i=0; i<numPlayers-1; i++)
		{
			printf("deck count:%i\n",testG.deckCount[i]);
			for (m=0; m<testG.deckCount[i]; m++)
			{
				printf("Deck: %i\n",testG.deck[i][m]);
			}
			printf("hand count:%i\n",testG.handCount[i]);
			for (m=0; m<testG.handCount[i]; m++)
			{
				printf("Hand: %i\n",testG.hand[i][m]);
			}
			printf("discard count:%i\n",testG.discardCount[i]);
			for (m=0; m<testG.discardCount[i]; m++)
			{
				printf("discard: %i\n",testG.discard[i][m]);
			}
		}
		//*/
		//myAssert(testG.handCount[thisPlayer] , G.handCount[thisPlayer], 7);
		//myAssert(testG.deckCount[thisPlayer] , G.deckCount[thisPlayer], 7);
		/*printf("handCount: %i\n",testG.handCount[thisPlayer]);
		printf("deckCount: %i\n",testG.deckCount[thisPlayer]);
		printf("discardCount: %i\n",testG.discardCount[thisPlayer]);
		printf("numActions: %i\n",testG.numActions);
		//*/
		tmp = testG.handCount[thisPlayer];
		test = testG.deckCount[thisPlayer];
		cardEffect(great_hall, choice1, choice2, choice3, &testG, handPos, &bonus);
		
		test--;
		myAssert(testG.numActions,2,1);
		myAssert(testG.handCount[thisPlayer], tmp,2);
		myAssert(testG.deckCount[thisPlayer], test,5);
		
		/*printf("handCount: %i\n",testG.handCount[thisPlayer]);
		printf("deckCount: %i\n",testG.deckCount[thisPlayer]);
		printf("discardCount: %i\n",testG.discardCount[thisPlayer]);
		printf("numActions: %i\n",testG.numActions);
		//*/
		//myAssert(testG.handCount[thisPlayer],testG.handCount[thisPlayer],1);
		//myAssert(testG.deckCount[thisPlayer],testG.deckCount[thisPlayer],2);
		myAssert(testG.whoseTurn , G.whoseTurn, 3);
		myAssert(testG.phase , G.phase, 4);
		myAssert(testG.coins , G.coins, 6);
		myAssert(testG.numBuys , G.numBuys, 7);
	}

	return 0;
}


