/* file:          marketQuantumFruit.c */
/* authors:       Wiebe Marten Wijnja (wiebemarten@gmx.com) */
/*                     Tomas Karamazen (t.j.karamazen@student.rug.nl) */
/* date:          11th Sep 2014 */
/* version:       2.010 */

/* How to buy exactly 100 fruits for 10000 cents of your preferred currency?. */
/* This program will try to give the answer by simply trying everything. IN A SMART AND HIGHLY EFFICIENT WAY! */

/* ************************************************************************** */
/* Version history: */
/*2.010(Quantum Fruit): New fast algorithm for the case where grapefruits and melons cost the same */

/*2.001: New comments, code style cleaning */

/*2.000(Funky Fruit): New, efficient algorithm added.*/

/* 1.060(Star Fruit): Replaced plural forms with a version that only adds an 's' add the end. Saves space.*/

/* 1.051: Increased readability of comments. */

/* 1.050(Dragon Fruit): Added a safeguard against negative number input, removed unused math.h. */

/* 1.000(Efficient Fruit): Added comments and slightly altered indentation. */

/* 0.006(Delicious Fruit): Inner for loop in combinations function replaced. */
/*                                     This significantly increased performance. */

/* 0.005 (Rotten Fruit): First version. */
/* ************************************************************************** */

/* Compiler parameters: */
/* gcc -ansi -Wall marketFinal.c -o marketFinal */

#include <stdio.h>
#include <stdlib.h>

/* Global fruit strings.
 * If you want to change the types of fruit, edit them here, and they will be changed throughout the whole program.
*/
const char* strOrange = "%d orange";
const char* strGrapeFruit = ", %d grapefruit";
const char* strMelon = ", %d melon";


int printCombination(int orangeCount, int grapeFruitCount, int melonCount);
int efficientCheck(int orangeCost, int grapeFruitCost, int melonCost);
int samePriceCheck(int orangeCost, int grapeFruitMelonCost);

int main(int argc, char** argv){
  int orangeCost = 0;
  int grapeFruitCost = 0;
  int melonCost = 0;

  /*Ask the user for the prices of the fruits. */
  printf("price of an orange: ");
  scanf("%d", &orangeCost);
  printf("price of a grapefruit: ");
  scanf("%d", &grapeFruitCost);
  printf("price of a melon: ");
  scanf("%d", &melonCost);

  /*Check for negative prices, as these would break the calculations, and also not make sense for the purpose of this program.
   * Die with an fun error message if these are found.
  */
  if(orangeCost < 0 || grapeFruitCost < 0 || melonCost < 0){
    printf("A world where you would earn money by buying fruit, would be a terrible world. All fruit farmers would have to file for bankruptcy!\n");
    return -1;
  }

  /*Decide between the more efficient algorithm that only works when grapeFruitCost and melonCost are not the same,
   * And the more expensive algorithm that always works.
   */
  if(grapeFruitCost==melonCost){
    samePriceCheck(orangeCost, grapeFruitCost);  
  }else{
    efficientCheck(orangeCost, grapeFruitCost, melonCost);
  }
  return 0;
}


/*decide whether to print the singular or plural form of the fruit names, depending on their quantity. 
 * Fruit Strings are stored as constants, for easy editing without digging through the source code.
*/
int printCombination(int orangeCount, int grapeFruitCount, int melonCount){
  printf(strOrange, orangeCount);
  if(orangeCount!=1){
    printf("s");
  }
  printf(strGrapeFruit, grapeFruitCount);
  if(grapeFruitCount!=1){
    printf("s");
  }
  printf(strMelon, melonCount);
  if(melonCount!=1){
    printf("s");
  }
  printf("\n");
  return 0;
}


/* Checks all options more efficiently, for inputs where the cost for grapefruits and melons is not the same.
* Only needs to iterate through 101 options, instead of 5151 and thus is much more efficient.
 */
int efficientCheck(int orangeCost, int grapeFruitCost, int melonCost){
  int orangeCount;
  int grapeFruitCount;
  int melonCount;

  int restFruit = 0;
  int restPrice = 0;
  /*Iterate through all oranges*/
  for(orangeCount = 0; orangeCount <= 100; orangeCount++){
    restFruit = 100-orangeCount; /*The amount of fruits still left, after we've purchased the oranges*/
    restPrice = 10000 - (orangeCount*orangeCost); /*The amount of money still left, after we've purchased the oranges*/
    grapeFruitCount = ( restPrice - (restFruit*melonCost) ) / (grapeFruitCost - melonCost); /*The amount of grapefruits we need to end up exactly at 100 fruits together with the melons. Math explanation is in the report.*/
    melonCount = restFruit - grapeFruitCount; /* melonCount is the fruit that is still left after this */
    
    
    /*grapeFruitCount and melonCount will return a value for each iteration of oranges, however:
     * a) Sometimes, the only way to end up at the total is by introducing negative amounts of fruits. Don't show these, by checking that both grapeFruitCount and melonCount are 0 or higher.
     * b) Sometimes, the only way to end up exactly at 10000 is by purchasing half fruits. 
     *      As we're using integer numbers, the way to check that this isn't happening, is by checking if the resulting fruits * their price is equal to the amount of money we've left.
    */
    if(grapeFruitCount >=0 && melonCount >=0 && (grapeFruitCount*grapeFruitCost + melonCount*melonCost)==restPrice){
      printCombination(orangeCount, grapeFruitCount, melonCount);
    }
  }
  
  return 0;
}

/* Checks all options more efficiently than the normal way, for all inputs where grapeFruitCost = melonCost
 * This is done by checking if the remaining price is fully divisible (remainder of 0) for a certain number of oranges.
 * Thus we don't have to loop through all grapefruits anymore.
 */
int samePriceCheck(int orangeCost, int grapeFruitMelonCost){
  int orangeCount;
  int grapeFruitCount;
  int melonCount;

  int restFruit = 0;
  int restPrice = 0;
  /*Iterate through all oranges*/
  for(orangeCount = 0; orangeCount <= 100; orangeCount++){
    restFruit = 100-orangeCount; /*The amount of fruits still left, after we've purchased the oranges*/
    restPrice = 10000 - (orangeCount*orangeCost); /*The amount of money still left, after we've purchased the oranges*/
    
    /* If this is fully divisible by the amount one piece of fruit costs
     * And ends up exactly dividing it by the number of fruits we ought to use to get to 100
     */
    if(restPrice % grapeFruitMelonCost == 0 && (restPrice / grapeFruitMelonCost) == restFruit){
      /*Then we iterate through all options between 0 and the amount of fruits that fit (restPrice / grapeFruitMelonCost) 
        * The amount of melons is always what's left of restFruit after subtracting the grapefruits.
        */
      for(grapeFruitCount = 0; grapeFruitCount <= (restPrice / grapeFruitMelonCost); grapeFruitCount++){
        melonCount = restFruit - grapeFruitCount; /* melonCount is the fruit that is still left after this */
        printCombination(orangeCount, grapeFruitCount, melonCount);
      }    
    }
  }
  
  return 0;
}
