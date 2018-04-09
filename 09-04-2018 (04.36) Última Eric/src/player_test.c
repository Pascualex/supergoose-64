/** 
 * @brief It tests player module
 * @file player_test.c
 * @author Eric Morales
 * @version 1.0 
 * @date 08-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/player.h"
#include "../include/player_test.h"
#include "../include/test.h"

#define MAX_TESTS 40

/*
 * Main function for PLAYER unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 */

int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_player_create();
    if (all || test == 2) test2_player_create();
    if (all || test == 3) test1_player_set_name();
    if (all || test == 4) test2_player_set_name();
    if (all || test == 5) test3_player_set_name();
    if (all || test == 6) test1_player_set_graphic_description();
    if (all || test == 7) test2_player_set_graphic_description();
    if (all || test == 8) test3_player_set_graphic_description();
    if (all || test == 9) test1_player_set_location();
    if (all || test == 10) test2_player_set_location();
    if (all || test == 11) test3_player_set_location();
    if (all || test == 12) test1_player_get_name();
    if (all || test == 13) test2_player_get_name();
    if (all || test == 14) test1_player_get_id();
    if (all || test == 15) test2_player_get_id();
    if (all || test == 16) test1_player_get_graphic_description();
    if (all || test == 17) test2_player_get_graphic_description();
    if (all || test == 18) test1_player_get_object();
    if (all || test == 19) test2_player_get_object();
    if (all || test == 20) test1_player_get_location();
    if (all || test == 21) test2_player_get_location();
    if (all || test == 22) test1_player_get_objects_number();
    if (all || test == 23) test2_player_get_objects_number();
    if (all || test == 24) test3_player_get_objects_number();
    if (all || test == 25) test4_player_get_objects_number();
    if (all || test == 26) test1_player_add_object();
    if (all || test == 27) test2_player_add_object();
    if (all || test == 28) test1_player_del_object();
    if (all || test == 29) test2_player_del_object();
    if (all || test == 30) test3_player_del_object();
    if (all || test == 31) test1_player_is_empty();
    if (all || test == 32) test2_player_is_empty();
    if (all || test == 33) test3_player_is_empty();
    if (all || test == 34) test1_player_is_full();
    if (all || test == 35) test2_player_is_full();
    if (all || test == 36) test3_player_is_full();
    if (all || test == 37) test4_player_is_full();
    if (all || test == 38) test1_player_check_object();
    if (all || test == 39) test2_player_check_object();
    if (all || test == 40) test3_player_check_object();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_player_create() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(p != NULL);
    player_destroy(p);
}

void test2_player_create() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_get_id(p) == PLAYER_BASE_ID + 4);
    player_destroy(p);
}

void test1_player_set_name() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_set_name(p, "test") == OK);
    player_destroy(p);
}

void test2_player_set_name() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_name(p, "test") == ERROR);
}

void test3_player_set_name() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
    player_destroy(p);
}

void test1_player_set_graphic_description() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_set_graphic_description(p, "test") == OK);
    player_destroy(p);
}

void test2_player_set_graphic_description() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_graphic_description(p, "test") == ERROR);
}

void test3_player_set_graphic_description() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_set_graphic_description(p, NULL) == ERROR);
    player_destroy(p);
}

void test1_player_set_location() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    player_set_location(p, SPACE_BASE_ID + 1);
    PRINT_TEST_RESULT(player_get_location(p) == SPACE_BASE_ID + 1);
    player_destroy(p);
}

void test2_player_set_location() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_location(p, SPACE_BASE_ID + 1) == ERROR);
}

void test3_player_set_location() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_set_location(p, ID_RANGE + 1) == ERROR);
    player_destroy(p);
}

void test1_player_add_object() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    player_add_object(p, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(player_check_object(p, OBJECT_BASE_ID + 1) == TRUE);
    player_destroy(p);
}

void test2_player_add_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_add_object(p, OBJECT_BASE_ID + 1) == ERROR);
}

void test1_player_del_object() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    player_add_object(p, OBJECT_BASE_ID + 1);
    player_del_object(p, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(player_check_object(p, OBJECT_BASE_ID + 1) == FALSE);
    player_destroy(p);
}

void test2_player_del_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_del_object(p, OBJECT_BASE_ID + 1) == ERROR);
}

void test3_player_del_object() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    PRINT_TEST_RESULT(player_del_object(p, NO_ID) == ERROR);
    player_destroy(p);
}

void test1_player_get_name() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    player_set_name(p, "test");
    PRINT_TEST_RESULT(strcmp(player_get_name(p), "test") == 0);
    player_destroy(p);
}

void test2_player_get_name() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_name(p) == NULL);
}

void test1_player_get_id() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);
    PRINT_TEST_RESULT(player_get_id(p) == PLAYER_BASE_ID + 25);
    player_destroy(p);
}

void test2_player_get_id() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

void test1_player_get_graphic_description() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 4, 5);
    player_set_graphic_description(p, "test");
    PRINT_TEST_RESULT(strcmp(player_get_graphic_description(p), "test") == 0);
    player_destroy(p);
}

void test2_player_get_graphic_description() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_graphic_description(p) == NULL);
}

void test1_player_get_location() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);
    player_set_location(p, SPACE_BASE_ID + 1);
    PRINT_TEST_RESULT(player_get_location(p) == SPACE_BASE_ID + 1);
    player_destroy(p);
}

void test2_player_get_location() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}

void test1_player_get_object() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);
    player_add_object(p, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(player_get_object(p, 0) == OBJECT_BASE_ID + 1);
    player_destroy(p);
}

void test2_player_get_object() {
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_object(p, 0) == NO_ID);
}

void test1_player_get_objects_number() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);

    player_add_object(p, OBJECT_BASE_ID + 1);

    PRINT_TEST_RESULT(player_get_objects_number(p) == 1);
    player_destroy(p);
}

void test2_player_get_objects_number() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);

    PRINT_TEST_RESULT(player_get_objects_number(p) == 0);
    player_destroy(p);
}

void test3_player_get_objects_number() {
    Player *p = NULL;

    PRINT_TEST_RESULT(player_get_objects_number(p) == 0);
}

void test4_player_get_objects_number() {
    Player *p = NULL;
    int i;

    p = player_create(PLAYER_BASE_ID + 25, 5);
    for (i = 0; i <= MAX_OBJECTS + 1; i++) {
        player_add_object(p, OBJECT_BASE_ID + 1 + i);
    }

    PRINT_TEST_RESULT(player_get_objects_number(p) == SET_MAX_IDS);
    player_destroy(p);
}

void test1_player_is_empty() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);

    PRINT_TEST_RESULT(player_is_empty(p) == TRUE);
    player_destroy(p);
}

void test2_player_is_empty() {
    Player *p = NULL;

    PRINT_TEST_RESULT(player_is_empty(p) == TRUE);
}

void test3_player_is_empty() {
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 25, 5);

    player_add_object(p, OBJECT_BASE_ID + 1);

    PRINT_TEST_RESULT(player_is_empty(p) == FALSE);
    player_destroy(p);
}

void test1_player_is_full() {
    Player *p = NULL;
    int i;

    p = player_create(PLAYER_BASE_ID + 25, 5);
    for (i = 0; i <= MAX_OBJECTS + 1; i++) {
        player_add_object(p, OBJECT_BASE_ID + 1 + i);
    }

    PRINT_TEST_RESULT(player_is_full(p) == TRUE);
    player_destroy(p);
}

void test2_player_is_full() {
    Player *p = NULL;

    p = player_create(PLAYER_BASE_ID + 25, 5);

    PRINT_TEST_RESULT(player_is_full(p) == FALSE);
    player_destroy(p);
}

void test3_player_is_full() {
    Player *p = NULL;

    PRINT_TEST_RESULT(player_is_full(p) == TRUE);
}

void test4_player_is_full() {
    Player *p = NULL;

    p = player_create(PLAYER_BASE_ID + 25, 5);
    player_add_object(p, OBJECT_BASE_ID + 1);

    PRINT_TEST_RESULT(player_is_full(p) == FALSE);
    player_destroy(p);
}

void test1_player_check_object() {
    Player *p = NULL;

    p = player_create(PLAYER_BASE_ID + 25, 5);
    player_add_object(p, OBJECT_BASE_ID + 1);

    PRINT_TEST_RESULT(player_check_object(p, OBJECT_BASE_ID + 1) == TRUE);
    player_destroy(p);
}

void test2_player_check_object() {
    Player *p = NULL;

    p = player_create(PLAYER_BASE_ID + 25, 5);

    PRINT_TEST_RESULT(player_check_object(p, OBJECT_BASE_ID + 1) == FALSE);
    player_destroy(p);
}

void test3_player_check_object() {
    Player *p = NULL;

    PRINT_TEST_RESULT(player_check_object(p, OBJECT_BASE_ID + 1) == FALSE);
}
