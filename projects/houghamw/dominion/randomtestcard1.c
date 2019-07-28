/* -----------------------------------------------------------------------
* Demonstration of how to write unit tests for dominion-base
* Include the following lines in your makefile:
*
* testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
*      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"



int testing_total_tests = 0;
int testing_successful_tests = 0;
int testing_failed_tests = 0;
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int printoutResults(){

  printf("Total Tests: %d\tPassed Tests: %d\tSuccess Rate:%2.2f%%\n",testing_total_tests,testing_successful_tests,100*((float)testing_successful_tests/(float)testing_total_tests));

}
int testassert(int a,int b,char printable[]){
//testing_total_tests++;
if(a==b){
  return 1;
}
else{
  #if (NOISY_TEST == 1)
    printf("Assert Failed: %s\n",printable);
  #endif
testing_failed_tests++;
  return 0;
}
}

int main() {
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10;
  int p, r, handCount;
  int bonus;
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
      coppers[i] = copper;
      silvers[i] = silver;
      golds[i] = gold;
    }
    int random_itr = 0;
    int desired_cycles = 9001;
    #if (NOISY_TEST == 1)
                    printf("Random test of Baron effect\n");
    #endif
    for (random_itr = 0; random_itr < desired_cycles; random_itr++){

      int players = rand() % 4;
      seed = rand();
      r = initializeGame(players,k,seed,&G);

      int randchoice1 = rand() %2;

      G.deckCount[players] = rand()%MAX_DECK;
      G.discardCount[players] = rand()%MAX_DECK;
      G.handCount[players] = rand()%MAX_DECK;

      handCount = G.handCount[players];
      int deckCount = G.deckCount[players];
      int buyCount = G.numBuys;
      int estateCount = supplyCount(estate,&G);
      int coinCount = G.coins;

    //  printf("initial buys: %d, estateCount: %d\n",buyCount,estateCount);

      if (seed %5 == 0){
        G.deckCount[players] = 0;
      }

      int cardcheck = cardEffectBaron(&G, randchoice1, players);
      assert(cardcheck == 0);

      //Testing against expected results
      testassert(buyCount+1,G.numBuys,"extra buy");
  //    printf("final buys: %d, final estateCount: %d\n",G.numBuys,supplyCount(estate,&G));
      if (randchoice1){ //Expect discard of estate if possible, gain gold.
        if(estateCount > 0){

          testassert(estateCount-1,supplyCount(estate,&G),"-1 estate in hand");
          testassert(coinCount+4,G.coins,"+4 coins from selling estate");
        }

      }


      #if (NOISY_TEST == 1)
                      printf("Random test of Baron effect complete.\n");
      #endif

      //     printf ("TESTING updateCoins():\n");
      //     for (p = 0; p < numPlayer; p++)
      //     {
      //         for (handCount = 1; handCount <= maxHandCount; handCount++)
      //         {
      //             for (bonus = 0; bonus <= maxBonus; bonus++)
      //             {
      // #if (NOISY_TEST == 1)
      //                 printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
      // #endif
      //                 int buynum = G.numBuys;
      //                 memset(&G, 23, sizeof(struct gameState));   // clear the game state
      //                 r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
      //                 G.handCount[p] = handCount;                 // set the number of cards on hand
      //
      //
      //
      //                 memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set random indexes and numbers of cards to estates
      //                 updateCoins(p, &G, bonus);
      // #if (NOISY_TEST == 1)
      //                 printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
      // #endif
      //                 assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct
      //             }
      //         }
      //     }
      //
      //     printf("All tests passed!\n");
  testing_total_tests++;
if(!testing_failed_tests){ //Must pass all asserts in this test to succeed
  testing_failed_tests = 0;
    testing_successful_tests++;
}
    }
    printoutResults();
      return 0;
  }
