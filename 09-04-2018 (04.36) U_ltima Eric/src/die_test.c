/*C libraries*/
#include <stdio.h>
/*Own libraries*/
#include "../include/die.h"

/*This entire module is used apart from the main program. It is used to test if the die is working correctly,
 *  by throwing the die repeteadly and checking if the values are normal or abnormal.*/
int main() {
    /*We create a die and seven different ints, one for loop purposes and the other six to count the different
     number of possibilities that are falling each time.*/
    Die *die = NULL;
    int i, a, b, c, d, e, f;
    die = die_create(1, 6);

    /*We print the die info one first time*/
    die_print(die);

    /*In this function we define the six possible cases of the die in variables so that we can add one to each
      value when its got in the loop that rolls dies.*/
    for (i=a=b=c=d=e=f=0; i < 100; i++) {
        printf("%d\t", die_get_value(die));
        switch (die_get_value(die)) {
            case 1: a++;
                break;
            case 2: b++;
                break;
            case 3: c++;
                break;
            case 4: d++;
                break;
            case 5: e++;
                break;
            case 6: f++;
                break;
        }
        die_roll(die);
    }
    /*Finally, we print the information got to see if the probability is correct. Once, we checked with 100 
     million rolls and it worked as a charm.*/
    printf("\n");
    die_print(die);
    printf("\n\n1: %d \t 2: %d \t 3: %d \t 4: %d \t 5: %d \t 6: %d\n", a, b, c, d, e, f);
    die_destroy(die);
    return 0;
}

