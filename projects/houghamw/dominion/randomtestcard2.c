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
int testassert(int a,int b,int mode,char printable[]){
  //testing_total_tests++;
if(mode == 0){
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
else if(mode == 1){
  if(a<b){
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
    int maxHandCount = 6;
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
                    printf("Random test of Minion effect\n");
    #endif
    for (random_itr = 0; random_itr < desired_cycles; random_itr++){

    int players = (rand() % 4) + 2;
      seed = rand();
      r = initializeGame(players,k,seed,&G);

      int randchoice1 = rand() %2;
      int randchoice2 = rand() %2;
int pl = 0;
for(pl = 0;pl <= players;pl++){ //Randomize decks for all players
      G.deckCount[pl] = rand()%MAX_DECK;
      G.discardCount[pl] = rand()%MAX_DECK;
      G.handCount[pl] = rand()%MAX_HAND;

    }
    players = players-1;//Index fixing because im lazy
          G.whoseTurn = players;



      handCount = G.handCount[players];
      int randHandPos = 0;
      if(handCount > 0){
        randHandPos = rand()%handCount;
      }
      int deckCount = G.deckCount[players];
      int buyCount = G.numBuys;
      int estateCount = supplyCount(estate,&G);
      //G.coins = rand()%10;
      int coinCount = G.coins;
      int actionCount = G.numActions;

    //  printf("initial buys: %d, estateCount: %d\n",buyCount,estateCount);

      if (seed %10 == 0){
        G.deckCount[players] = 0;
      }
      //

      int cardcheck = cardEffectMinion(&G, randchoice1, randchoice2, players,randHandPos);
      assert(cardcheck == 0);

      //Testing against expected results
      testassert(actionCount+1,G.numActions,0,"extra action");
  //    printf("final buys: %d, final estateCount: %d\n",G.numBuys,supplyCount(estate,&G));
  if (randchoice1){
    testassert(coinCount+2,G.coins,0,"add 2 coins");
  }
      else if (randchoice2){ //Expect discard of estate if possible, gain gold.

          testassert(4,numHandCards(&G),0,"End up with 4 cards");
          for (i = 0; i < G.numPlayers; i++)
        {
            testassert(G.handCount[i],5,1,"All players with 5+ cards redraw to 4");
          }



      }


      #if (NOISY_TEST == 1)
                      printf("Random test of Minion effect complete.\n");
      #endif
      testing_total_tests++;
      if(!testing_failed_tests){
        testing_failed_tests = 0;
          testing_successful_tests++;
      }
    }
    printoutResults();
      return 0;
  }
