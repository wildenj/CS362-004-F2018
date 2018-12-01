/*
	Jason Wilden
	CS362 Assignment 3
	10/26/2018
	unittest1.c
	
	code borrowed from example code provided
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int i, j, l;
	int tmp1, tmp2, tmp3, idx1=0, idx2=0, idx3=0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int test = 0;
	struct gameState G, testG;
	time_t t;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	// from: https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	printf("----------------- Testing isGameOver() ----------------\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	
	testG.supplyCount[province] = 1;
	test = isGameOver(&testG);
	if (test==0)
	{
		printf("Positive supply count passed\n");
	}
	myAssert(test, 0, 1);
	
	testG.supplyCount[province] = 0;
	test = isGameOver(&testG);
	if (test==1)
	{
		printf("Zero supply count passed\n");
	}	
	myAssert(test ,1, 2);
	
	for (l=0; l<10000; l++)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		idx1 = rand()%(treasure_map);
		do
		{
			idx2 = rand()%(treasure_map);
		} while (idx2 == idx1);
		
		do
		{
			idx3 = rand()%(treasure_map);
		} while ((idx3 == idx1) || (idx3 == idx2));
		
		
		tmp1 = testG.supplyCount[idx1];
		tmp2 = testG.supplyCount[idx2];
		tmp3 = testG.supplyCount[idx3];
		
		testG.supplyCount[idx1] = 1;
		testG.supplyCount[idx2] = 1;
		testG.supplyCount[idx3] = 1;
		
		j = 0;
		for (i = 0; i < (treasure_map); i++)
		{
		  if (testG.supplyCount[i] == 0)
		  {
			j++;
		  }
		}
		
		if (j==3)
		{
			printf("Supply count non zero test failed!\n");
		}
		test = isGameOver(&testG);
		
		myAssert(test, 0,3);
		myAssert(testG.handCount[thisPlayer] , G.handCount[thisPlayer], 3);
		myAssert(testG.deckCount[thisPlayer] , G.deckCount[thisPlayer], 3);
		myAssert(testG.whoseTurn , G.whoseTurn, 3);
		myAssert(testG.phase , G.phase, 3);
		myAssert(testG.numActions , G.numActions, 3);
		myAssert(testG.coins , G.coins, 3);
		myAssert(testG.numBuys , G.numBuys, 3);
				
		testG.supplyCount[idx1] = tmp1;
		testG.supplyCount[idx2] = tmp2;
		testG.supplyCount[idx3] = tmp3;
	}
	
	printf("Supply count non zero test passed\n");

	for (l=0; l<100; l++)
	{
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		idx1 = rand()%(treasure_map+1);
		do
		{
			idx2 = rand()%(treasure_map+1);
		} while (idx2 == idx1);
		
		do
		{
			idx3 = rand()%(treasure_map+1);
		} while ((idx3 == idx1) || (idx3 == idx2));
		
		tmp1 = testG.supplyCount[idx1];
		tmp2 = testG.supplyCount[idx2];
		tmp3 = testG.supplyCount[idx3];
		
		testG.supplyCount[idx1] = 0;
		testG.supplyCount[idx2] = 0;
		testG.supplyCount[idx3] = 0;
		
		j = 0;
		for (i = 0; i < (treasure_map+1); i++)
		{
		  if (testG.supplyCount[i] == 0)
		  {
			j++;
		  }
		}
		
		if (j!=3)
		{
			printf("Supply count zero test failed!\n");
		}
		test = isGameOver(&testG);
		if (test == 0)
			printf("test result:%i\t idx1:%i\t idx2:%i\t idx3:%i\n",test, idx1, idx2, idx3);
		
		myAssert(test, 1, 5);
		myAssert(testG.handCount[thisPlayer] , G.handCount[thisPlayer], 4);
		myAssert(testG.deckCount[thisPlayer] , G.deckCount[thisPlayer], 4);
		myAssert(testG.whoseTurn , G.whoseTurn, 4);
		myAssert(testG.phase , G.phase, 4);
		myAssert(testG.numActions , G.numActions, 4);
		myAssert(testG.coins , G.coins, 4);
		myAssert(testG.numBuys , G.numBuys, 4);
				
		testG.supplyCount[idx1] = tmp1;
		testG.supplyCount[idx2] = tmp2;
		testG.supplyCount[idx3] = tmp3;
	}
	
	printf("Supply count zero test passed\n");
	
	
	return 0;
}


