/** 
 * @brief It defines the space functions
 * @file space.c
 * @author Profesores PPROG
 * @version 3.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
#include "../include/types.h"
#include "../include/set.h"
#include "../include/space.h"

/*We define the Space structure as the following:*/
struct _Space {
    Id id; /*An Id to distinguish the space from other spaces or things*/
    char name[WORD_SIZE + 1]; /*A char used to name the space*/
    Id directions_ids[6];
    Set *objects_ids; /*A set to store the objects it has*/
    char **graphic_description; /*A graphic description to use in the graphic engine*/
    char **check_description; /*A field to store the information of the space and give it when asked playing.*/
};

/*This function is used to allocate memory for a space and create it with a given Id*/
Space *space_create(Id id) {
    int i;
    Space *new_space = NULL;
    DIRECTION direction;

    if (id == NO_ID) return NULL;

    new_space = (Space *) malloc(sizeof(Space));

    if (new_space == NULL) return NULL;

    new_space->objects_ids = set_create();

    if (new_space->objects_ids == NULL) {
        free(new_space);
        return NULL;
    }

    new_space->graphic_description = (char **) malloc(sizeof(char*)*MAX_GDESC_R);
    for (i = 0; i < MAX_GDESC_R; i++) {
        new_space->graphic_description[i] = (char *) malloc(sizeof(char)*MAX_GDESC_C);
        if (new_space->graphic_description[i] == NULL) {
            for (i = i - 1; i >= 0; i--) {
                free(new_space->graphic_description[i]);
            }
            free(new_space->graphic_description);
            set_destroy(new_space->objects_ids);
            free(new_space);
            return NULL;
        }
    }

    new_space->check_description = (char **) malloc(sizeof(char*)*MAX_CHECK_R);
    for (i = 0; i < MAX_CHECK_R; i++) {
        new_space->check_description[i] = (char *) malloc(sizeof(char)*MAX_CHECK_C);
        if (new_space->check_description[i] == NULL) {
            for (i = i - 1; i >= 0; i--) {
                free(new_space->check_description[i]);
            }
            for (i = 0; i < MAX_GDESC_R; i++) {
                free(new_space->graphic_description[i]);
            }
            free(new_space->graphic_description);
            free(new_space->check_description);
            set_destroy(new_space->objects_ids);
            free(new_space);
            return NULL;
        }
    }

    new_space->id = id;
    new_space->name[0] = '\0';

    for (direction = NORTH; direction <= BELOW; direction++) new_space->directions_ids[direction] = NO_ID;

    strcpy(new_space->graphic_description[0], "0000000");
    strcpy(new_space->graphic_description[1], "0000000");
    strcpy(new_space->graphic_description[2], "0000000");

    strcpy(new_space->check_description[0], "0000000");
    strcpy(new_space->check_description[1], "0000000");
    strcpy(new_space->check_description[2], "0000000");

    return new_space;
}

/*This function frees the allocated memory by a space*/
STATUS space_destroy(Space *space) {
    int i;

    if (space == NULL) return OK;

    if (space->objects_ids != NULL) set_destroy(space->objects_ids);

    if (space->graphic_description != NULL) {
        for (i = 0; i < MAX_GDESC_R; i++) {
            if (space->graphic_description[i] != NULL) free(space->graphic_description[i]);
        }
        free(space->graphic_description);
    }

    if (space->check_description != NULL) {
        for (i = 0; i < MAX_CHECK_R; i++) {
            if (space->check_description[i] != NULL) free(space->check_description[i]);
        }
        free(space->check_description);
        free(space);
    }

    return OK;
}

/*This function sets the space name*/
STATUS space_set_name(Space *space, char *name) {

    if (space == NULL || name == NULL) return ERROR;

    if (strcpy(space->name, name) == 0) return ERROR;

    return OK;
}

/*This function sets the northern Id of the space*/
STATUS space_set_direction(Space *space, DIRECTION direction, Id id) {

    if (space == NULL || id < LINK_BASE_ID || id >= LINK_BASE_ID + ID_RANGE) return ERROR;

    switch (direction) {
        case NORTH:
            space->directions_ids[0] = id;
            break;
        case WEST:
            space->directions_ids[1] = id;
            break;
        case SOUTH:
            space->directions_ids[2] = id;
            break;
        case EAST:
            space->directions_ids[3] = id;
            break;
        case ABOVE:
            space->directions_ids[4] = id;
            break;
        case BELOW:
            space->directions_ids[5] = id;
            break;
        default:
            return ERROR;
    }    

    return OK;
}

/*This function sets the graphic description of the space, to use it on the graphic engine*/
STATUS space_set_graphic_description(Space *space, char graphic_description[MAX_GDESC_R][MAX_GDESC_C]) {

    if (space == NULL || graphic_description == NULL) return ERROR;

    strcpy(space->graphic_description[0], graphic_description[0]);
    strcpy(space->graphic_description[1], graphic_description[1]);
    strcpy(space->graphic_description[2], graphic_description[2]);

    return OK;
}

/*This function sets the space description of the space, to use it on the graphic engine*/
STATUS space_set_check_description(Space *space, char check_description[MAX_CHECK_R][MAX_CHECK_C]) {
    int i;

    if (space == NULL || check_description == NULL) return ERROR;

    for (i = 0; i < MAX_CHECK_R; i++) {
        strcpy(space->check_description[i], check_description[i]);
    }

    return OK;
}

/*This function is used to add an object to the space set*/
STATUS space_add_object(Space *space, Id object_id) {

    if (space == NULL || object_id == NO_ID) return ERROR;

    return set_add(space->objects_ids, object_id);
}

/*This function is used to delete an object from the space set*/
STATUS space_del_object(Space *space, Id object_id) {

    if (space == NULL || object_id == NO_ID) return ERROR;

    return set_del(space->objects_ids, object_id);
}

/*This function returns the name of a space*/
const char *space_get_name(Space *space) {

    if (space == NULL) return NULL;

    return space->name;
}

/*This function gets the description of a space*/
char **space_get_check_description(Space *space) {

    if (space == NULL) return NULL;

    return space->check_description;
}

/*This function is used to get the id of a space*/
Id space_get_id(Space *space) {

    if (space == NULL) return NO_ID;

    return space->id;
}

/*This function is used to get the northern id of a space*/
Id space_get_direction(Space *space, DIRECTION direction) {

    if (space == NULL) return NO_ID;

    switch (direction) {
        case NORTH:
            return space->directions_ids[0];
            break;
        case WEST:
            return space->directions_ids[1];
            break;
        case SOUTH:
            return space->directions_ids[2];
            break;
        case EAST:
            return space->directions_ids[3];
            break;
        case ABOVE:
            return space->directions_ids[4];
            break;
        case BELOW:
            return space->directions_ids[5];
            break;
        default:
            return ERROR;
    }    

    return OK;
}

/*This function is used to get an object from the spaces set*/
Id space_get_object_id(Space *space, int position) {

    if (space == NULL || position < 0) return NO_ID;

    return set_get_id(space->objects_ids, position);
}

/*This function returns the number of objects there are in the spaces set*/
int space_get_objects_number(Space *space) {

    if (space == NULL) return 0;

    return set_get_ids_number(space->objects_ids);
}

/*This function is used to get the graphic description of a set to use it in the graphic engine later*/
char **space_get_graphic_description(Space *space) {

    if (space == NULL) return NULL;

    return space->graphic_description;
}

/*This function checks if the given object id is stored in the spaces set*/
BOOL space_check_object(Space *space, Id object_id) {

    if (space == NULL || object_id == NO_ID) return FALSE;

    if (set_get_id_position(space->objects_ids, object_id) == -1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/*This function returns if there are no objects in the space or not*/
BOOL space_is_empty(Space *space) {

    if (space == NULL) return TRUE;

    if (set_is_empty(space->objects_ids)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*This function returns if there is space or not to store another object*/
BOOL space_is_full(Space *space) {

    if (space == NULL) return TRUE;

    if (set_is_full(space->objects_ids)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*This function prints the space information for debuggin purposes*/
STATUS space_print(Space *space) {
    Id idaux = NO_ID;

    if (space == NULL) return ERROR;

    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

    idaux = space_get_direction(space, NORTH);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No north link.\n");
    }

    idaux = space_get_direction(space, WEST);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No west link.\n");
    }

    idaux = space_get_direction(space, SOUTH);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No south link.\n");
    }

    idaux = space_get_direction(space, EAST);
    if (NO_ID != idaux) {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No east link.\n");
    }

    set_print(space->objects_ids);

    fprintf(stdout, "---> Graphic description:\n");
    fprintf(stdout, "     %s\n", space->graphic_description[0]);
    fprintf(stdout, "     %s\n", space->graphic_description[1]);
    fprintf(stdout, "     %s\n", space->graphic_description[2]);

    return OK;
}
