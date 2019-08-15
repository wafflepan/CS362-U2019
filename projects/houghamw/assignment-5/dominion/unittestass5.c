

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

void softAssert(int thing1,int thing2,char* declare,int mode){
if(mode==0){
if(thing1 == thing2){

printf("Assert Passed: %s\n",declare);
}
else{
printf("Assert Failed: %s\n",declare);
}
}
else{
  if(thing1>thing2){

    printf("Assert Passed (>): %s\n",declare);
    }
    else{
    printf("Assert Failed (>): %s\n",declare);
    }
}
}
int cardsfoundhand(int card,struct gameState state){
int j=0;
int count = 0;
for(j=0;j<state.handCount[state.whoseTurn];j++){
  if(state.hand[state.whoseTurn][j] == card){
    count++;
  }
}
  return count;
}
int cardsfounddeck(int card, struct gameState state){
  int j=0;
  int count = 0;
  for(j=0;j<state.deckCount[state.whoseTurn];j++){

    if(state.deck[state.whoseTurn][j] == card){
      count++;
    }
  }

}
int cardsfounddiscard(int card, struct gameState state){
  int j=0;
  int count = 0;
  for(j=0;j<state.discardCount[state.whoseTurn];j++){

    if(state.discard[state.whoseTurn][j] == card){
      count++;
    }
  }

}
int main() {

int i, n, r, p, deckCount, discardCount, handCount;

int seed = 1000;
int numPlayer = 2;
int maxBonus = 10;

int k[10] = {adventurer, council_room, feast, gardens, mine,
       remodel, smithy, village, baron, great_hall};

struct gameState G;

  r = initializeGame(numPlayer,k,seed,&G);

int startcoins = G.coins;
int testchoice = 1;

G.hand[G.whoseTurn][0] = 1;
G.hand[G.whoseTurn][1] = 1;
G.hand[G.whoseTurn][2] = 1;
G.hand[G.whoseTurn][3] = 1;
G.hand[G.whoseTurn][4] = 1;

//Test with all estates

//printf("Cards:\t");
for(i = 0;i<G.handCount[G.whoseTurn];i++){
  //printf(" %d,",G.hand[G.whoseTurn][i]);
}
//printf("\n");

int cardcheck = baronAct(testchoice,&G);
//printf("Cardcheck value: %d\n",cardcheck);
softAssert(G.coins,startcoins+4,"Coins added after estate sale",0);

//printf("Cards:\t");
for(i = 0;i<G.handCount[G.whoseTurn];i++){
//  printf(" %d,",G.hand[G.whoseTurn][i]);
}
//printf("\n");

r= initializeGame(numPlayer,k,seed,&G);

G.hand[G.whoseTurn][0] = 1;
G.hand[G.whoseTurn][1] = 2;
G.hand[G.whoseTurn][2] = 2;
G.hand[G.whoseTurn][3] = 2;
G.hand[G.whoseTurn][4] = 2;
//test with 1 estate at index 0

//printf("Cards:\t");
for(i = 0;i<G.handCount[G.whoseTurn];i++){
  //printf(" %d,",G.hand[G.whoseTurn][i]);
}
//printf("\n");

cardcheck = baronAct(testchoice,&G);
//printf("Cardcheck value: %d\n",cardcheck);
softAssert(G.coins,startcoins+4,"Coins added after estate sale (index 0)",0);

//printf("Cards:\t");
for(i = 0;i<G.handCount[G.whoseTurn];i++){
//  printf(" %d,",G.hand[G.whoseTurn][i]);
}
//printf("\n");

//printf("ESTATES CHECK: ----------------------------------------------------\n\n");

r= initializeGame(numPlayer,k,seed,&G);
G.hand[G.whoseTurn][0] = 2;
G.hand[G.whoseTurn][1] = 2;
G.hand[G.whoseTurn][2] = 2;
G.hand[G.whoseTurn][3] = 2;
G.hand[G.whoseTurn][4] = 2;
//Testing no estates

G.deck[G.whoseTurn][0]= 1;

//printf("Estates in discard: %d\n",(cardsfounddiscard(estate,G)));

//printf("Discard:\t");
for(i = 0;i<G.discardCount[G.whoseTurn];i++){
  //printf(" %d,",G.discard[G.whoseTurn][i]);
}
printf("\n");

int estatesbefore = cardsfounddiscard(estate,G);
cardcheck = baronAct(testchoice,&G);
//printf("Cardcheck value: %d\n",cardcheck);
softAssert(cardsfounddiscard(estate,G),estatesbefore,"Estate added",1);

//printf("Discard:\t");
for(i = 0;i<G.discardCount[G.whoseTurn];i++){
//  printf(" %d,",G.discard[G.whoseTurn][i]);
}
printf("\n");
//printf("Estates in discard: %d\n",(cardsfounddiscard(estate,G)));


}
