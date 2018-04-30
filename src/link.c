/** 
 * @brief It defines the link functions
 * @file link.c
 * @author Victor Yrazusta
 * @version 1.0 
 * @date 
 * @updated 
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Own libraries*/
#include "../include/link.h"
#include "../include/game.h"

/*We define the Link structure with the different fields it will need*/
struct _Link {
    Id id; /*An Id with to distinguish this link from the others*/
    char name[MAX_NAME]; /*A string with the name of the Link*/
    Id space1, space2; /*Two Ids storing the Ids of the linked spaces*/
    LINK_STATUS status; /*The Link status, which will tell us if a link is closed or not*/
};

/*The following function is used to create (allocating memory) a link with the given Id. We will later define which spaces it ocnnects*/
Link *link_create(Id id) {
    Link *link;

    if (id == NO_ID || id < LINK_BASE_ID || id > LINK_BASE_ID+ID_RANGE) return NULL;

    link = (Link *) malloc(sizeof (Link));

    if (link == NULL) return NULL;

    link->id = id;
    link->space1 = NO_ID;
    link->space2 = NO_ID;
    link->status = OPEN;

    return link;
}

/*The following function is used to free the memory a link was using*/
STATUS link_destroy(Link *link) {

    if (link == NULL) return ERROR;

    free(link);

    return OK;
}

/*This function sets the name of a link*/
STATUS link_set_name(Link *link, char name[MAX_NAME]) {

    if (link == NULL || name == NULL) return ERROR;

    strcpy(link->name, name);

    return OK;
}

/*This functiond adds one space linked space to the given link*/
STATUS link_add_space(Link *link, Id id) {

    if (link == NULL || id == NO_ID || id < SPACE_BASE_ID || id > SPACE_BASE_ID+ID_RANGE) return ERROR;

    if (link->space1 == NO_ID) {
        link->space1 = id;
        return OK;
    } else {
        link->space2 = id;
        return OK;
    }

    return ERROR;
}

/*This function sets the status of a link, if open, closed, conditionally closed, etc. We can define more posibilities when needed with a few changes*/
STATUS link_set_status(Link *link, LINK_STATUS status) {

    if (link == NULL) return ERROR;

    link->status = status;

    return OK;
}

/*This function is used to get a links Id*/
Id link_get_id(Link *link) {

    if (link == NULL) return NO_ID;

    return link->id;
}

/*This function is used to get the name of a link*/
char *link_get_name(Link *link) {

    if (link == NULL) return NULL;

    return link->name;
}

/*This function receives a link and a spaces Id, so that it can give you the other 'end of the rope' (the space in the other side of the link)*/
Id link_get_other_side(Link *link, Id space) {

    if (link == NULL || space < SPACE_BASE_ID || space > SPACE_BASE_ID+ID_RANGE) return NO_ID;

    if (space == link->space1) return link->space2;
    if (space == link->space2) return link->space1;

    return NO_ID;
}

/*This function returns the status of the given link*/
LINK_STATUS link_get_status(Link *link) {

    if (link == NULL) return CLOSED;

    return link->status;
}

STATUS link_print(FILE *f, Link *link) {

    if (link == NULL) return ERROR;

    fprintf(f, "#l:%04ld|%s|", link->id - LINK_BASE_ID, link->name);

    if (link->space1 == NO_ID) {
        fprintf(f, "%04ld|", link->space1);
    } else {
        fprintf(f, "%04ld|", link->space1 - SPACE_BASE_ID);
    }

    if (link->space2 == NO_ID) {
        fprintf(f, "%04ld|", link->space2);
    } else {
        fprintf(f, "%04ld|", link->space2 - SPACE_BASE_ID);
    }

    fprintf(f, "%d|\n", link->status);

    return OK;
}
