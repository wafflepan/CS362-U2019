#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"


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

int main(){

printf("Begin Test\n");

int k[10] = {adventurer, council_room, feast, gardens, mine,
       remodel, smithy, village, baron, great_hall};
       int i;
        int seed = 1000;
        int numPlayer = 2;
        int maxBonus = 10;
        int p, r, handCount;

struct state G;


    int maxHandCount = 5;



}
