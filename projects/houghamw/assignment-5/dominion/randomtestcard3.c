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
                    printf("Random test of Tribute effect\n");
    #endif
    for (random_itr = 0; random_itr < desired_cycles; random_itr++){

    int players = (rand() % 4) + 2;
      seed = rand();
      r = initializeGame(players,k,seed,&G);

      int randchoice1 = rand() %2;
      int randchoice2 = rand() %2;
int pl = 0;
for(pl = 0;pl < players;pl++){ //Randomize decks for all players
      G.deckCount[pl] = rand()%MAX_DECK;
      G.discardCount[pl] = rand()%MAX_DECK;
      G.handCount[pl] = rand()%MAX_HAND;

int playerhand = G.handCount[pl];
      for(playerhand=0;playerhand<G.handCount[pl];playerhand++){
        G.hand[pl][playerhand] = k[rand()%10];
      }
       playerhand = G.deckCount[pl];
            for(playerhand=0;playerhand<G.handCount[pl];playerhand++){
              G.deck[pl][playerhand] = k[rand()%10];
            }
             playerhand = G.discardCount[pl];
                  for(playerhand=0;playerhand<G.discardCount[pl];playerhand++){
                    G.discard[pl][playerhand] = k[rand()%10];
                  }
    }
    players = players-1;//Index fixing because im lazy
          G.whoseTurn = players;
int nextPlayer = players + 1;
if (nextPlayer > (G.numPlayers - 1)){
    nextPlayer = 0;
  }

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

      int cardcheck = tributeAct(&G);
      assert(cardcheck == 0);

int tributecards[2] = {-1,-1};
      //Testing against expected results

      if ((G.discardCount[nextPlayer] + G.deckCount[nextPlayer]) <= 1){ //If there's not enough cards for two

          if(G.deckCount[nextPlayer] > 0){
testassert(0,G.deckCount,0,"discard last card from deck");
          }
          else if(G.discardCount[nextPlayer] > 0){
              testassert(0,G.discardCount,0,"reshuffle discard into empty deck");
          }



  }
  else if(G.deckCount[nextPlayer] > 1){
int tributeitr;
int expectedactions=0;
int expectedcards=0;
int expectedcoins=0;
int lastcard = -1;
    for(tributeitr=0;tributeitr<2;tributeitr++){ //get both tribute cards, check what they are, calculate desired output
    int card = G.deck[nextPlayer][G.deckCount[nextPlayer]-tributeitr+1];
if(card<0 || card == lastcard){ //Ignore duplicate or invalid cards
  break;
}
if (card==copper || card==silver || card==gold){
  expectedcoins = expectedcoins + 2;
}
else if(card==estate||card==duchy||card==province||card==gardens||card==great_hall){
  expectedcards= expectedcards + 2;
}
else{

  expectedactions = expectedactions + 2;
}
lastcard = card;
  }

  #if (NOISY_TEST == 1)
  printf("Starting actions: %d\tStarting cards:%d\tStarting coins:%d\tNexplayer Deck:%d\tNextplayer Discard:%d\n",actionCount,handCount,coinCount,G.deckCount[nextPlayer],G.discardCount[nextPlayer]);
  printf("Expected actions: %d\tExpected cards:%d\tExpected coins:%d\n",actionCount + expectedactions,handCount + expectedcards,coinCount + expectedcoins);
  printf("Actual actions: %d\tActual cards:%d\tActual coins:%d\n",G.numActions,G.handCount[players],G.coins);
#endif
  testassert(actionCount + expectedactions,G.numActions,0,"actions increased from treasure card");
  testassert(handCount + expectedcards,G.handCount[players],0,"drew cards from victory card");
  testassert(coinCount + expectedcoins,G.coins,0,"number of coins increased from action card");
}
//card==copper||card==silver||card==gold
//card==estate||card==duchy||card==province||card==gardens||card==great_hall
//Treasure: Copper, silver, cold
//Victory: estate duchy province gardens great_hall

      #if (NOISY_TEST == 1)
                      printf("Random test of Tribute effect complete.\n");
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
