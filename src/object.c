/** 
 * @brief It defines the object functions
 * @file object.c
 * @author 
 * @version 1.0 
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
#include "../include/object.h"

/*We define the object structure as the following:*/
struct _Object {
    Id id; /*An Id to tell apart from other objects and things*/
    char name[WORD_SIZE + 1]; /*A string with the objects name*/
    char **check; /*A longer char with the description of the object*/
    Id location; /*An Id with the space its being located*/
    TAG tags[MAX_TAGS]; /*A array of tags that define the propierties of the object*/
    unsigned int num_tags; /*A number that indicates the number of tags*/
};

/*This function is used to allocate memory and create an object with the given Id*/
Object *object_create(Id id) {
    int i;

    Object *newObject = NULL;

    newObject = (Object *) malloc(sizeof(Object));

    if (newObject == NULL) return NULL;

    newObject->id = id;
    newObject->name[0] = '\0';
    newObject->location = NO_ID;

    newObject->check = (char **) malloc(sizeof(char*)*MAX_CHECK_R);

    for (i = 0; i < MAX_CHECK_R; i++) {
        newObject->check[i] = (char *) malloc(sizeof(char)*MAX_CHECK_C);
        if (newObject->check[i] == NULL) {
            for (i = i-1; i >= 0; i--) {
                free(newObject->check[i]);
            }
            free(newObject->check);
            free(newObject);
            return NULL;
        }
    }

    for (i = 0; i < MAX_TAGS; i++) {
        newObject->tags[i] = NO_TAG;
    }
    newObject->num_tags = 0;

    object_add_tags(newObject, 1, VISIBLE);

    return newObject;
}

/*This function is used to free the memory allocated by an object*/
STATUS object_destroy(Object *object) {
    int i;

    if (object == NULL) return ERROR;

    if (object->check != NULL) {
        for (i = 0; i < MAX_CHECK_R; i++) {
            if (object->check[i] != NULL) free(object->check[i]);
        }
        free(object->check);
    }
    free(object);

    return OK;
}

/*The following function is used to set the name of an object*/
STATUS object_set_name(Object *object, char *name) {

    if (object == NULL || name == NULL || strcpy(object->name, name) == 0 || strcmp(name, "space") == 0) return ERROR;

    return OK;
}

/*The following function is used to set the description of an object*/
STATUS object_set_check(Object *object, char check[MAX_CHECK_R][MAX_CHECK_C]) {
    int i;

    if (object == NULL || check == NULL) return ERROR;

    for (i = 0; i < MAX_CHECK_R; i++) {
        strcpy(object->check[i], check[i]);
    }

    return OK;
}

/*The next function sets the location of the given object with the given Id*/
STATUS object_set_location(Object *object, Id location) {

    if (object == NULL || location == NO_ID) return ERROR;

    object->location = location;

    return OK;
}

/*The following object returns the name of an object*/
const char *object_get_name(Object *object) {

    if (object == NULL) return NULL;

    return object->name;
}

/*The following function returns a char with the information of the given object*/
char **object_get_check(Object *object) {

    if (object == NULL) return NULL;

    return object->check;
}

/*This function gets an Id from an object and gives it back to the program*/
Id object_get_id(Object *object) {

    if (object == NULL) return NO_ID;

    return object->id;
}

/*This function gets the location of an object*/
Id object_get_location(Object *object) {

    if (object == NULL) return NO_ID;

    return object->location;
}

/*This function is used for debugging purposes. It prints all the object data.*/
STATUS object_print(Object *object) {

    if (object == NULL) return ERROR;

    fprintf(stdout, "--> Object (Id: %ld; Name: %s; Location: %ld)\n", object->id, object->name, object->location);

    return OK;
}

STATUS object_add_tags(Object *object, int num_tags, ...) {
    TAG tags[MAX_TAGS];
    va_list tags_list;
    int i;

    if (object == NULL || num_tags == 0 || object->num_tags+num_tags >= MAX_TAGS) {
        return ERROR;
    }

    va_start(tags_list, num_tags);

    for (i = 0; i < num_tags; i++) {        /*We retrieve the information of all the tags passed*/
        tags[i] = va_arg(tags_list, TAG);
    }

    for (i = object->num_tags; i < object->num_tags+num_tags; i++) {
        object->tags[i] = tags[i-object->num_tags];
    }

    object->num_tags = object->num_tags+num_tags;

    va_end(tags_list);

    return OK;
}

TAG *object_get_tags(Object *object) {
    
    if (object == NULL) {
        return NULL;
    }

    return object->tags;
}

unsigned int object_get_tags_number(Object *object) {
    
    if (object == NULL) {
        return 0;
    }

    return object->num_tags;
}

BOOL object_is(Object *object, TAG tag) {
    int i;

    if (object == NULL) {
        return FALSE;
    }

    for (i = 0; i < object->num_tags; i++) {
        if (tag == object->tags[i]) {
            return TRUE;
        }
    }

    return FALSE;
}