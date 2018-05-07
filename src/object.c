/** 
 * @brief It defines the object functions
 * @file object.c
 * @author 
 * @version 1.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdarg.h>
/*Own libraries*/
#include "../include/types.h"
#include "../include/object.h"

/*We define the object structure as the following:*/
struct _Object {
    Id id; 						/*An Id to tell apart from other objects and things*/
    wchar_t name[WORD_SIZE]; 	/*A string with the objects name*/
    wchar_t **check;			/*A longer wchar_t with the description of the object*/
    wchar_t **alt_check;		/*A longer wchar_t with the alternative description of the object*/
    Id location; 				/*An Id with the space its being located*/
    TAG object_tags[MAX_TAGS];	/*An array of tags that define the propierties of the object*/
    int num_tags; 				/*A number that indicates the number of tags*/
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

    newObject->check = (wchar_t **) malloc(sizeof(wchar_t*)*MAX_TDESC_R);

    for (i = 0; i < MAX_TDESC_R; i++) {
        newObject->check[i] = (wchar_t *) malloc(sizeof(wchar_t)*MAX_TDESC_C);
        if (newObject->check[i] == NULL) {
            for (i = i-1; i >= 0; i--) {
                free(newObject->check[i]);
            }
            free(newObject->check);
            free(newObject);
            return NULL;
        }
    }

	newObject->alt_check = (wchar_t **) malloc(sizeof(wchar_t*)*MAX_TDESC_R);

    for (i = 0; i < MAX_TDESC_R; i++) {
        newObject->alt_check[i] = (wchar_t *) malloc(sizeof(wchar_t)*MAX_TDESC_C);
        if (newObject->alt_check[i] == NULL) {
            for (i = i-1; i >= 0; i--) {
                free(newObject->alt_check[i]);
            }
            free(newObject->alt_check);
            free(newObject->check);
            free(newObject);
            return NULL;
        }
    }

    for (i = 0; i < MAX_TAGS; i++) {
        newObject->object_tags[i] = NO_TAG;
    }
    newObject->num_tags = 0;

    return newObject;
}

/*This function is used to free the memory allocated by an object*/
STATUS object_destroy(Object *object) {
    int i;

    if (object == NULL) return ERROR;

    if (object->check != NULL) {
        for (i = 0; i < MAX_TDESC_R; i++) {
            if (object->check[i] != NULL) free(object->check[i]);
        }
        free(object->check);
    }

    if (object->alt_check != NULL) {
        for (i = 0; i < MAX_TDESC_R; i++) {
            if (object->alt_check[i] != NULL) free(object->alt_check[i]);
        }
        free(object->alt_check);
    }

    free(object);

    return OK;
}

/*The following function is used to set the name of an object*/
STATUS object_set_name(Object *object, wchar_t *name) {

    if (object == NULL || name == NULL || wcscpy(object->name, name) == 0 || wcscmp(name, L"space") == 0) return ERROR;

    return OK;
}

/*The following function is used to set the description of an object*/
STATUS object_set_check(Object *object, wchar_t check[MAX_TDESC_R][MAX_TDESC_C]) {
    int i;

    if (object == NULL || check == NULL) return ERROR;

    for (i = 0; i < MAX_TDESC_R; i++) {
        wcscpy(object->check[i], check[i]);
    }

    return OK;
}

/*The following function is used to set the alternative description of an object*/
STATUS object_set_alt_check(Object *object, wchar_t alt_check[MAX_TDESC_R][MAX_TDESC_C]) {
    int i;

    if (object == NULL || alt_check == NULL) return ERROR;

    for (i = 0; i < MAX_TDESC_R; i++) {
        wcscpy(object->alt_check[i], alt_check[i]);
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
const wchar_t *object_get_name(Object *object) {

    if (object == NULL) return NULL;

    return object->name;
}

/*The following function returns a wchar_t with the description of the given object*/
wchar_t **object_get_check(Object *object) {

    if (object == NULL) return NULL;

    return object->check;
}

/*The following function returns a wchar_t with the alternative description of the given object*/
wchar_t **object_get_alt_check(Object *object) {

    if (object == NULL) return NULL;

    return object->alt_check;
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

STATUS object_add_tags(Object *object, int num_tags, ...) {
    TAG object_tags[MAX_TAGS];
    va_list object_tags_list;
    int i;

    if (object == NULL || num_tags == 0 || object->num_tags+num_tags > MAX_TAGS) return ERROR;

    va_start(object_tags_list, num_tags);

    for (i = 0; i < num_tags; i++) {        /*We retrieve the information of all the tags passed*/
        object_tags[i] = va_arg(object_tags_list, TAG);
    }

    for (i = 0; i < num_tags; i++) {
    	if (!object_check_tag(object, object_tags[i])) {
    		object->object_tags[object->num_tags] = object_tags[i];
    		object->num_tags++;
    	}
    }

    va_end(object_tags_list);

    return OK;
}

TAG *object_get_tags(Object *object) {
    
    if (object == NULL) return NULL;

    return object->object_tags;
}

int object_get_tags_number(Object *object) {
    
    if (object == NULL) return 0;

    return object->num_tags;
}

BOOL object_check_tag(Object *object, TAG object_tag) {
    int i;

    if (object == NULL) return FALSE;

    for (i = 0; i < object->num_tags; i++) {
        if (object_tag == object->object_tags[i]) return TRUE;
    }

    return FALSE;
}

STATUS object_remove_tag(Object *object, TAG object_tag) {
	int i, j;

	if (object == NULL || !object_check_tag(object, object_tag)) return ERROR;

	i = 0;
	while (1) {
		if (i > MAX_TAGS) return ERROR;

		if (object_tag == object->object_tags[i]) {
			for (j = i; j < object->num_tags; j++) {
				object->object_tags[j] = object->object_tags[j+1];
			}
			object->object_tags[j] = NO_TAG;
			object->num_tags--;
			return OK;
		}
		i++;
	}

	return ERROR;
}

/*It prints all the object data.*/
STATUS object_print(FILE *f, Object *object) {
    TAG *object_tags = NULL;
    int num_tags, i;

    if (object == NULL) return ERROR;

    object_tags = object_get_tags(object);
    if (object_tags == NULL) return ERROR;

    num_tags = object_get_tags_number(object);

    fwprintf(f, L"#o:%04ld|%-8S|%04ld|", object->id - OBJECT_BASE_ID, object->name, object->location);
    fwprintf(f, L"%S|%S|%S|%S|%S|%S|", object->check[0], object->check[1], object->check[2], object->alt_check[0], object->alt_check[1], object->alt_check[2]);

    for (i = 0; i < num_tags; i++) {
        if (object_tags[i] != NO_TAG){
            fwprintf(f, L"%d|", object_tags[i]);
        }
    }
    fwprintf(f, L"\n");
    
    return OK;
}