/** 
 * @brief It defines the set functions
 * @file set.c
 * @author 
 * @version 1.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*Own libraries*/
#include "../include/set.h"

/*We define the set structure as the following:*/
struct _Set {
    Id ids[SET_MAX_IDS]; /*The bunch of objects ids the set will be managing (maybe not objects)*/
    int ids_number; /*The number of ids the set has*/
};

/*This function allocates memory for a set and returns it*/
Set *set_create() {
    Set *set = NULL;
    int i;

    set = (Set *) malloc(sizeof (Set));
    if (set == NULL) {
        return ERROR;
    }

    for (i = 0; i < SET_MAX_IDS; i++) {
        set->ids[i] = NO_ID;
    }
    set->ids_number = 0;

    return set;
}

/*This function frees the memory allocated by a set*/
STATUS set_destroy(Set *set) {

    if (set == NULL) {
        return ERROR;
    }

    free(set);

    return OK;
}

/*This function is used to add an object to a set, given an id*/
STATUS set_add(Set *set, Id id) {

    if (set == NULL || id == NO_ID || set_is_full(set) == TRUE) {
        return ERROR;
    }

    if (set_get_id_position(set, id) != NOT_FOUND) {
        return ERROR;
    }

    set->ids[set->ids_number] = id;
    set->ids_number++;

    return OK;
}

/*The following function is used to delete a given id from the set*/
STATUS set_del(Set *set, Id id) {
    int id_position, i;

    if (set == NULL || id == NO_ID || set_is_empty(set) == TRUE) {
        return ERROR;
    }

    id_position = set_get_id_position(set, id);

    if (id_position == NOT_FOUND) {
        return ERROR;
    }

    for (i = id_position; i < set->ids_number - 1; i++) {
        set->ids[i] = set->ids[i + 1];
    }

    set->ids[i] = NO_ID;
    set->ids_number--;

    return OK;
}

/*This function returns the Id from a set, given a set and a position*/
Id set_get_id(Set *set, int id_position) {

    if (set == NULL || id_position < 0 || id_position >= set->ids_number) {
        return NO_ID;
    }

    return set->ids[id_position];
}

/*This function gets the Id position of a given Id in a set*/
int set_get_id_position(Set *set, Id id) {
    int i;

    if (set == NULL || id == NO_ID) {
        return NOT_FOUND;
    }

    for (i = 0; i < set->ids_number; i++) {
        if (set->ids[i] == id) {
            return i;
        }
    }

    return NOT_FOUND;
}

/*This function gets the number of ids of a given set*/
int set_get_ids_number(Set *set) {

    if (set == NULL) {
        return 0;
    }

    return set->ids_number;
}

/*This function returns a boolean telling if the set is or isnt empty*/
BOOL set_is_empty(Set *set) {

    if (set->ids_number == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*So does this one, but telling if its full or not*/
BOOL set_is_full(Set *set) {

    if (set->ids_number >= SET_MAX_IDS) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*This function prints he set information for debugging purposes*/
STATUS set_print(Set *set) {
    int i;

    if (set == NULL) {
        return ERROR;
    }

    fprintf(stdout, "---> Set (Number of ids: %d)", set->ids_number);

    if (set->ids_number != 0) {
        fprintf(stdout, ":\n");
    } else {
        fprintf(stdout, "\n");
    }

    for (i = 0; i < set->ids_number; i++) {
        fprintf(stdout, "    Id %d: %ld\n", i + 1, set->ids[i]);
    }

    return OK;
}
