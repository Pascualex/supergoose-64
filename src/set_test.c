/** 
 * @brief It test the set functions
 * @file set_test.c
 * @author Eric Morales
 * @version 1.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include "../include/set.h"

#define OBJECT1 5

int main() {
    Set * set;
    int i;

    /*We wil check if the set works in normal cases (adding only one objectId and deleting it)*/

    printf("\n\nNormal cases:\n");

    set = set_create();

    set_print(set);

    printf("\nAdding one object...\n");
    set_add(set, OBJECT1);

    set_print(set);

    printf("\nDeleting one object...\n");
    set_del(set, OBJECT1);

    set_print(set);

    set_destroy(set);

    /*We wil check if the set works in extreme cases (adding more then the possible objectsId and deleting more than possible)*/

    printf("\n\nExtreme cases:\n");

    set = set_create();

    set_print(set);

    printf("\nAdding %d objects...\n", SET_MAX_IDS+1);
    for (i = 0; i < SET_MAX_IDS+1; i++) {
        set_add(set, i); /*It only allows 4 objects.*/
    }

    printf("Full: %d\n", (int) set_is_full(set));

    set_print(set);

    printf("\nDeletings %d objects...\n", SET_MAX_IDS + 1);
    for (i = 0; i < SET_MAX_IDS+1; i++) {
        set_del(set, i);
    }

    printf("Full: %d\n", (int) set_is_full(set));
    set_print(set);

    set_destroy(set);

    return 0;
}
