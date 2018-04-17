/** 
 * @brief It tests object module
 * @file object_test.c
 * @author Eric Morales
 * @version 1.0 
 * @date 08-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/object.h"
#include "../include/object_test.h"
#include "../include/test.h"

#define MAX_TESTS 26

/*
 * Main function for Object unit tests. 
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
        printf("Running all test for module Object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();
    if (all || test == 3) test1_object_set_name();
    if (all || test == 4) test2_object_set_name();
    if (all || test == 5) test3_object_set_name();
    if (all || test == 6) test1_object_set_location();
    if (all || test == 7) test2_object_set_location();
    if (all || test == 8) test3_object_set_location();
    if (all || test == 9) test1_object_set_check();
    if (all || test == 10) test2_object_set_check();
    if (all || test == 11) test1_object_get_name();
    if (all || test == 12) test2_object_get_name();
    if (all || test == 13) test1_object_get_id();
    if (all || test == 14) test2_object_get_id();
    if (all || test == 15) test1_object_get_location();
    if (all || test == 16) test2_object_get_location();
    if (all || test == 17) test1_object_get_check();
    if (all || test == 18) test2_object_get_check();
    if (all || test == 19) test1_object_add_tags();
    if (all || test == 20) test2_object_add_tags();
    if (all || test == 21) test1_object_get_tags();
    if (all || test == 22) test2_object_get_tags();
    if (all || test == 23) test1_object_get_tags_number();
    if (all || test == 24) test2_object_get_tags_number();
    if (all || test == 25) test1_object_is();
    if (all || test == 26) test2_object_is();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_object_create() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object != NULL);
    object_destroy(object);
}

void test2_object_create() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_get_id(object) == OBJECT_BASE_ID+1);
    object_destroy(object);
}

void test1_object_set_name() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_set_name(object, "test") == OK);
    object_destroy(object);
}

void test2_object_set_name() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_name(object, "test") == ERROR);
}

void test3_object_set_name() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_set_name(object, NULL) == ERROR);
    object_destroy(object);
}

void test1_object_set_location() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    object_set_location(object, SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(object_get_location(object) == SPACE_BASE_ID+1);
    object_destroy(object);
}

void test2_object_set_location() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_set_location(object, SPACE_BASE_ID+1) == ERROR);
}

void test3_object_set_location() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_set_location(object, NO_ID) == ERROR);
    object_destroy(object);
}

void test1_object_set_check() {
    Object *object = NULL;
    char check[MAX_TDESC_R][MAX_TDESC_C];
    int i;
    object = object_create(OBJECT_BASE_ID+1);
    for (i = 0; i < MAX_TDESC_R; i++) {
        strcpy(check[i], "CHECK");
    }
    PRINT_TEST_RESULT(object_set_check(object, check) == OK);
    object_destroy(object);
}

void test2_object_set_check() {
    Object *object = NULL;
    char check[MAX_TDESC_R][MAX_TDESC_C];
    int i;
    for (i = 0; i < MAX_TDESC_R; i++) {
        strcpy(check[i], "CHECK");
    }
    PRINT_TEST_RESULT(object_set_check(object, check) == ERROR);
}

void test1_object_get_name() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    object_set_name(object, "test");
    PRINT_TEST_RESULT(strcmp(object_get_name(object), "test") == 0);
    object_destroy(object);
}

void test2_object_get_name() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_name(object) == NULL);
}

void test1_object_get_id() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_get_id(object) == OBJECT_BASE_ID+1);
    object_destroy(object);
}

void test2_object_get_id() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_id(object) == NO_ID);
}

void test1_object_get_location() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    object_set_location(object, SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(object_get_location(object) == SPACE_BASE_ID+1);
    object_destroy(object);
}

void test2_object_get_location() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_location(object) == NO_ID);
}

void test1_object_get_check() {
    Object *object = NULL;
    char check[MAX_TDESC_R][MAX_TDESC_C];
    char **checkEnd;
    int i;
    int result = 0;
    object = object_create(OBJECT_BASE_ID+1);
    for (i = 0; i < MAX_TDESC_R; i++) {
        strcpy(check[i], "CHECK");
    }
    object_set_check(object, check);
    checkEnd = object_get_check(object);
    for (i = 0; i < MAX_TDESC_R; i++) {
        if (strcmp(checkEnd[i], "CHECK") != 0) {
            result = 1;
        }
    }
    PRINT_TEST_RESULT(result == 0);
    object_destroy(object);
}

void test2_object_get_check() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_check(object) == NULL);
}

void test1_object_add_tags() {
    Object *object = NULL;
    object = object_create (OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(object_add_tags(object, 5, VISIBLE, MOVABLE, MOVED, HIDDEN, IS_KEY) == OK);
    object_destroy(object);
}

void test2_object_add_tags() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_add_tags(object, 5, VISIBLE, MOVABLE, MOVED, HIDDEN, IS_KEY) == ERROR);
}

void test1_object_get_tags() {
    Object *object = NULL;
    object = object_create (OBJECT_BASE_ID+1);
    object_add_tags(object, 2, VISIBLE, MOVABLE);
    PRINT_TEST_RESULT(object_get_tags(object) != NULL);
    object_destroy(object);
}

void test2_object_get_tags() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_tags(object) == NULL);
}

void test1_object_get_tags_number() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    object_add_tags(object, 2, IS_KEY, GLOWING);
    PRINT_TEST_RESULT(object_get_tags_number(object) == 4);    
    object_destroy(object);
}

void test2_object_get_tags_number() {
    Object *object = NULL;
    PRINT_TEST_RESULT(object_get_tags_number(object) == 0);
}

void test1_object_is() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    object_add_tags(object, 2, IS_KEY, MOVABLE);
    PRINT_TEST_RESULT(object_is(object, IS_KEY));
    object_destroy(object);
}

void test2_object_is() {
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(!object_is(object, HIDDEN));
    object_destroy(object);
}