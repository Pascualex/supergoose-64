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
#include <stdarg.h>
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
    char **basic_description; /*A field to store the basic information of the space.*/
    char **check_description; /*A field to store the information of the space and give it when asked playing.*/
    TAG space_tags[MAX_TAGS]; /*An array of tags that define the propierties of the space*/
    int num_tags; /*A number that indicates the number of tags*/
};

/*This function is used to allocate memory for a space and create it with a given Id*/
Space *space_create(Id id) {    
    Space *space = NULL;
    DIRECTION direction;
    int i;

    if (id == NO_ID) return NULL;

    space = (Space *) malloc(sizeof(Space));

    if (space == NULL) return NULL;

    space->objects_ids = set_create();

    if (space->objects_ids == NULL) {
        free(space);
        return NULL;
    }

    space->graphic_description = (char **) malloc(sizeof(char*)*MAX_GDESC_R);
    for (i = 0; i < MAX_GDESC_R; i++) {
        space->graphic_description[i] = (char *) malloc(sizeof(char)*MAX_GDESC_C);
        if (space->graphic_description[i] == NULL) {
            for (i = i - 1; i >= 0; i--) {
                free(space->graphic_description[i]);
            }
            free(space->graphic_description);
            set_destroy(space->objects_ids);
            free(space);
            return NULL;
        }
    }

    space->basic_description = (char **) malloc(sizeof(char*)*MAX_TDESC_R);
    for (i = 0; i < MAX_TDESC_R; i++) {
        space->basic_description[i] = (char *) malloc(sizeof(char)*MAX_TDESC_C);
        if (space->basic_description[i] == NULL) {
            for (i = i - 1; i >= 0; i--) {
                free(space->basic_description[i]);
            }
            for (i = 0; i < MAX_GDESC_R; i++) {
                free(space->graphic_description[i]);
            }
            free(space->graphic_description);
            free(space->basic_description);
            set_destroy(space->objects_ids);
            free(space);
            return NULL;
        }
    }

    space->check_description = (char **) malloc(sizeof(char*)*MAX_TDESC_R);
    for (i = 0; i < MAX_TDESC_R; i++) {
        space->check_description[i] = (char *) malloc(sizeof(char)*MAX_TDESC_C);
        if (space->check_description[i] == NULL) {
            for (i = i - 1; i >= 0; i--) {
                free(space->check_description[i]);
            }
            for (i = 0; i < MAX_TDESC_R; i++) {
                free(space->basic_description[i]);
            }
            for (i = 0; i < MAX_GDESC_R; i++) {
                free(space->graphic_description[i]);
            }
            free(space->graphic_description);
            free(space->check_description);
            set_destroy(space->objects_ids);
            free(space);
            return NULL;
        }
    }

    space->id = id;
    space->name[0] = '\0';

    for (direction = NORTH; direction <= BELOW; direction++) space->directions_ids[direction] = NO_ID;

    strcpy(space->graphic_description[0], "NO_GDES");
    strcpy(space->graphic_description[1], "NO_GDES");
    strcpy(space->graphic_description[2], "NO_GDES");

    strcpy(space->basic_description[0], "No basic description.");
    strcpy(space->basic_description[1], "No basic description.");
    strcpy(space->basic_description[2], "No basic description.");

    strcpy(space->check_description[0], "No check description.");
    strcpy(space->check_description[1], "No check description.");
    strcpy(space->check_description[2], "No check description.");

    space->num_tags = 0;

    for (i = 0; i < MAX_TAGS; i++) {
    	space->space_tags[i] = NO_TAG;
    }

    return space;
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

    if (space->basic_description!= NULL) {
        for (i = 0; i < MAX_TDESC_R; i++) {
            if (space->basic_description[i] != NULL) free(space->basic_description[i]);
        }
        free(space->basic_description);
    }

    if (space->check_description != NULL) {
        for (i = 0; i < MAX_TDESC_R; i++) {
            if (space->check_description[i] != NULL) free(space->check_description[i]);
        }
        free(space->check_description);        
    }

    free(space);

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

/*This function sets the basic description of the space, to use it on the graphic engine*/
STATUS space_set_basic_description(Space *space, char basic_description[MAX_TDESC_R][MAX_TDESC_C]) {
    int i;

    if (space == NULL || basic_description == NULL) return ERROR;

    for (i = 0; i < MAX_TDESC_R; i++) {
        strcpy(space->basic_description[i], basic_description[i]);
    }

    return OK;
}

/*This function sets the check description of the space, to use it on the graphic engine*/
STATUS space_set_check_description(Space *space, char check_description[MAX_TDESC_R][MAX_TDESC_C]) {
    int i;

    if (space == NULL || check_description == NULL) return ERROR;

    for (i = 0; i < MAX_TDESC_R; i++) {
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

/*This function is used to get the graphic description of a set to use it in the graphic engine later*/
char **space_get_graphic_description(Space *space) {

    if (space == NULL) return NULL;

    return space->graphic_description;
}

/*This function gets the basic description of a space*/
char **space_get_basic_description(Space *space) {

    if (space == NULL) return NULL;

    return space->basic_description;
}

/*This function gets the check description of a space*/
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
            return NO_ID;
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

STATUS space_add_tags(Space *space, int num_tags, ...) {
    TAG space_tags[MAX_TAGS];
    va_list space_tags_list;
    int i;

    if (space == NULL || num_tags <= 0 || space->num_tags+num_tags > MAX_TAGS) return ERROR;

    va_start(space_tags_list, num_tags);

    for (i = 0; i < num_tags; i++) {        
        space_tags[i] = va_arg(space_tags_list, TAG);
    }

    for (i = 0; i < num_tags; i++) {
    	if (space_check_tag(space, space_tags[i]) == FALSE) {
    		space->space_tags[space->num_tags] = space_tags[i];
    		space->num_tags++;
    	}
    }

    va_end(space_tags_list);

    return OK;
}

BOOL space_check_tag(Space *space, TAG space_tag) {
    int i;

    if (space == NULL) return TRUE;

    for (i = 0; i < space->num_tags; i++) {
        if (space_tag == space->space_tags[i]) return TRUE;
    }

    return FALSE;
}

STATUS space_remove_tags(Space *space, int num_tags, ...) {
	TAG space_tags[MAX_TAGS];
	va_list space_tags_list;
	int i, j, k;

	if (space == NULL || num_tags <= 0) return ERROR;

	va_start(space_tags_list, num_tags);

    for (i = 0; i < num_tags; i++) {        
        space_tags[i] = va_arg(space_tags_list, TAG);
    }

    for (i = 0; i < num_tags; i++) {
		for (j = 0; j < space->num_tags; j++) {
			if (space_tags[i] == space->space_tags[j]) {
				for (k = j; k < space->num_tags-1; k++) {
					space->space_tags[k] = space->space_tags[k+1];
				}				
				space->space_tags[k] = NO_TAG;
				space->num_tags--;
				return OK;
			}
		}
	}

	return ERROR;
}

TAG *space_get_tags(Space *space) {
    
    if (space == NULL) return NULL;

    return space->space_tags;
}

int space_get_tags_number(Space *space) {
    
    if (space == NULL) return 0;

    return space->num_tags;
}

STATUS space_print(FILE *f, Space *space) {
    TAG *space_tags = NULL;
    int num_tags, i;

    if (space == NULL) return ERROR;

    space_tags = space_get_tags(space);
    if (space_tags == NULL) return ERROR;

    num_tags = space_get_tags_number(space);

    fprintf(f, "#s:%04ld|%-8s|",    space->id - SPACE_BASE_ID, space->name);

    for (i = 0; i < 6; i++) {
        if (space_get_direction(space, i) != NO_ID) {
            fprintf(f, "%02ld|", space_get_direction(space, i) - LINK_BASE_ID);
        } else {
            fprintf(f, "%02ld|", space_get_direction(space, i));
        }
    }

    fprintf(f, "%s|%s|%s|%s|%s|%s|%s|%s|%s|",   space->graphic_description[0],
                                                space->graphic_description[1],
                                                space->graphic_description[2],
                                                space->basic_description[0],
                                                space->basic_description[1],
                                                space->basic_description[2],
                                                space->check_description[0],
                                                space->check_description[1],
                                                space->check_description[2]);

    for (i = 0; i < num_tags; i++) {
        if (space_tags[i] != NO_TAG){
    	   fprintf(f, "%d|", space_tags[i]);
        }
    }
    fprintf(f, "\n");

    return OK;
}