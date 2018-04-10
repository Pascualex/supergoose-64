/** 
 * @brief It defines the inventory functions
 * @file inventory.c
 * @author Alejandro Pascual
 * @version 1.0 
 * @date 06-04-2018
 * @updated 07-04-2018
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdlib.h>
#include <stdio.h>
/*Own libraries*/
#include "../include/inventory.h"
#include "../include/set.h"

/*We define the Inventory structure with the different fields it will need*/
struct _Inventory {
    Set *objects_ids; /*A Set* to storage the Ids of the Objects*/
    int max_objects; /*An int that defines the capacity of the Inventory*/
};

/*The following function creates an Inventory with the passed int as its capacity*/
Inventory *inventory_create(int max_objects) {
    Inventory *inventory = NULL;

    if (max_objects < 0) return NULL;

    inventory = (Inventory *) malloc(sizeof (Inventory));
    if (inventory == NULL) return NULL;

    inventory->objects_ids = set_create();
    if (inventory->objects_ids == NULL) {
        free(inventory);
        return NULL;
    }

    if (max_objects <= SET_MAX_IDS) {
        inventory->max_objects = max_objects;
    } else {
        inventory->max_objects = SET_MAX_IDS;
    }

    return inventory;
}

/*The following function destroys the Inventory passed*/
STATUS inventory_destroy(Inventory *inventory) {

    if (inventory == NULL) return ERROR;

    if (inventory->objects_ids != NULL) set_destroy(inventory->objects_ids);

    free(inventory);

    return OK;
}

/*The following function adds the passed Id to the Set of the Inventory*/
STATUS inventory_add(Inventory *inventory, Id object_id) {

    if (inventory == NULL || inventory->objects_ids == NULL || object_id == NO_ID || set_get_ids_number(inventory->objects_ids) >= inventory->max_objects) return ERROR;

    return set_add(inventory->objects_ids, object_id);
}

/*The following function removes the passed Id from the Set of the Inventory*/
STATUS inventory_del(Inventory *inventory, Id object_id) {

    if (inventory == NULL || inventory->objects_ids == NULL || object_id == NO_ID) return ERROR;

    return set_del(inventory->objects_ids, object_id);
}

/*The following function sets the capacity of the Inventory*/
STATUS inventory_set_max_objects(Inventory *inventory, int max_objects) {

    if (inventory == NULL || max_objects < 0 || max_objects > SET_MAX_IDS) return ERROR;

    inventory->max_objects = max_objects;

    return OK;
}

/*The following function returns the Id of the specified position in the Set of the Inventory*/
Id inventory_get_object_id(Inventory *inventory, int position) {

    if (inventory == NULL || inventory->objects_ids == NULL || position < 0) return NO_ID;

    return set_get_id(inventory->objects_ids, position);
}

/*The following function returns the current number of Ids in the Set of the Inventory*/
int inventory_get_objects_number(Inventory *inventory) {

    if (inventory == NULL) return 0;

    return set_get_ids_number(inventory->objects_ids);
}

/*The following function returns the capacity of the Inventory*/
int inventory_get_max_objects(Inventory *inventory) {

    if (inventory == NULL) return 0;

    return inventory->max_objects;
}

/*The following function checks if the passed Id is on the Set of the Inventory*/
BOOL inventory_check_object(Inventory *inventory, Id object_id) {

    if (inventory == NULL || inventory->objects_ids == NULL || object_id == NO_ID) return FALSE;

    if (set_get_id_position(inventory->objects_ids, object_id) == -1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*The following function checks if the Set of the Inventory is empty*/
BOOL inventory_is_empty(Inventory *inventory) {

    if (inventory == NULL || inventory->objects_ids == NULL) return TRUE;

    if (set_is_empty(inventory->objects_ids)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*The following function checks if the Set of the Inventory is full*/
BOOL inventory_is_full(Inventory *inventory) {

    if (inventory == NULL || inventory->objects_ids == NULL) return TRUE;

    if (set_is_full(inventory->objects_ids) || set_get_ids_number(inventory->objects_ids) >= inventory->max_objects) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*The following function prints the content of the Set of the Inventory*/
STATUS inventory_print(Inventory *inventory) {
    int i;

    if (inventory == NULL) return ERROR;

    fprintf(stdout, "---> Inventory");

    if (inventory->objects_ids != NULL && inventory_is_empty(inventory) == FALSE) {
        fprintf(stdout, ":\n");
        for (i = 0; i < set_get_ids_number(inventory->objects_ids); i++) {
            fprintf(stdout, "----> Id: %ld \n", set_get_id(inventory->objects_ids, i));
        }
    } else {
        fprintf(stdout, " (Empty)\n");
    }

    return OK;
}
