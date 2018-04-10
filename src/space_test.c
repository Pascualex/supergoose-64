/** 
 * @brief It tests space module
 * @file space_test.c
 * @author Profesores Pprog and Eric Morales
 * @version 2.0 
 * @date 16-01-2015
 * @updated 19-01-2016
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/space.h"
#include "../include/space_test.h"
#include "../include/test.h"

#define MAX_TESTS 56

/*
 * Main function for SPACE unit tests. 
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
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_space_create();
    if (all || test == 2) test2_space_create();
    if (all || test == 3) test1_space_set_name();
    if (all || test == 4) test2_space_set_name();
    if (all || test == 5) test3_space_set_name();
    if (all || test == 6) test1_space_set_north();
    if (all || test == 7) test2_space_set_north();
    if (all || test == 8) test1_space_set_north();
    if (all || test == 9) test2_space_set_north();
    if (all || test == 10) test1_space_set_south();
    if (all || test == 11) test2_space_set_south();
    if (all || test == 12) test1_space_set_east();
    if (all || test == 13) test2_space_set_east();
    if (all || test == 15) test1_space_set_west();
    if (all || test == 16) test2_space_set_west();
    if (all || test == 17) test1_space_set_graphic_description();
    if (all || test == 18) test2_space_set_graphic_description();
    if (all || test == 19) test3_space_set_graphic_description();
    if (all || test == 20) test1_space_set_check();
    if (all || test == 21) test2_space_set_check();
    if (all || test == 22) test3_space_set_check();
    if (all || test == 23) test1_space_get_name();
    if (all || test == 24) test2_space_get_name();
    if (all || test == 25) test1_space_get_north();
    if (all || test == 26) test2_space_get_north();
    if (all || test == 27) test1_space_get_south();
    if (all || test == 28) test2_space_get_south();
    if (all || test == 29) test1_space_get_east();
    if (all || test == 30) test2_space_get_east();
    if (all || test == 31) test1_space_get_west();
    if (all || test == 32) test2_space_get_west();
    if (all || test == 33) test1_space_get_id();
    if (all || test == 34) test2_space_get_id();
    if (all || test == 35) test1_space_get_graphic_description();
    if (all || test == 36) test2_space_get_graphic_description();
    if (all || test == 37) test1_space_get_check();
    if (all || test == 37) test2_space_get_check();
    if (all || test == 38) test1_space_get_object_id();
    if (all || test == 39) test2_space_get_object_id();
    if (all || test == 40) test1_space_get_objects_number();
    if (all || test == 41) test2_space_get_objects_number();
    if (all || test == 42) test3_space_get_objects_number();
    if (all || test == 43) test4_space_get_objects_number();
    if (all || test == 44) test1_space_add_object();
    if (all || test == 45) test2_space_add_object();
    if (all || test == 46) test1_space_is_empty();
    if (all || test == 47) test2_space_is_empty();
    if (all || test == 48) test3_space_is_empty();
    if (all || test == 49) test1_space_is_full();
    if (all || test == 50) test2_space_is_full();
    if (all || test == 51) test3_space_is_full();
    if (all || test == 52) test4_space_is_full();
    if (all || test == 53) test1_space_check_object();
    if (all || test == 54) test2_space_check_object();
    if (all || test == 55) test3_space_check_object();
    if (all || test == 56) test3_space_check_object();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_space_create() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(s != NULL);
    space_destroy(s);
}

void test2_space_create() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_id(s) == 1);
    space_destroy(s);
}

void test1_space_set_name() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_name(s, "test") == OK);
    space_destroy(s);
}

void test2_space_set_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "test") == ERROR);
}

void test3_space_set_name() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
    space_destroy(s);
}

void test1_space_set_north() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_north(s, LINK_BASE_ID+1) == OK);
    space_destroy(s);
}

void test2_space_set_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_north(s, LINK_BASE_ID+1) == ERROR);
}

void test1_space_set_south() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_south(s, LINK_BASE_ID+1) == OK);
    space_destroy(s);
}

void test2_space_set_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_south(s, LINK_BASE_ID+1) == ERROR);
}

void test1_space_set_east() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_east(s, LINK_BASE_ID+1) == OK);
    space_destroy(s);
}

void test2_space_set_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_east(s, LINK_BASE_ID+1) == ERROR);
}

void test1_space_set_west() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_west(s, LINK_BASE_ID+1) == OK);
    space_destroy(s);
}

void test2_space_set_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_west(s, LINK_BASE_ID+1) == ERROR);
}

void test1_space_set_graphic_description() {
    Space *s = NULL;
    char desc[MAX_GDESC_R][MAX_GDESC_C];
    int i;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i < MAX_GDESC_R; i++) {
        strcpy(desc[i], "desc");
    }
    PRINT_TEST_RESULT(space_set_graphic_description(s, desc) == OK);
    space_destroy(s);
}

void test2_space_set_graphic_description() {
    Space *s = NULL;
    char desc[MAX_GDESC_R][MAX_GDESC_C];
    int i;
    for (i = 0; i < MAX_GDESC_R; i++) {
        strcpy(desc[i], "desc");
    }
    PRINT_TEST_RESULT(space_set_graphic_description(s, desc) == ERROR);
}

void test3_space_set_graphic_description() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_graphic_description(s, NULL) == ERROR);
    space_destroy(s);
}

void test1_space_set_check() {
    Space *s = NULL;
    char check[MAX_CHECK_R][MAX_CHECK_C];
    int i;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i < MAX_CHECK_R; i++) {
        strcpy(check[i], "CHECK");
    }
    PRINT_TEST_RESULT(space_set_check(s, check) == OK);
    space_destroy(s);
}

void test2_space_set_check() {
    Space *s = NULL;
    char check[MAX_CHECK_R][MAX_CHECK_C];
    int i;
    for (i = 0; i < MAX_CHECK_R; i++) {
        strcpy(check[i], "CHECK");
    }
    PRINT_TEST_RESULT(space_set_check(s, check) == ERROR);
}

void test3_space_set_check() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_set_check(s, NULL) == ERROR);
    space_destroy(s);
}

void test1_space_get_name() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_set_name(s, "test");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "test") == 0);
    space_destroy(s);
}

void test2_space_get_name() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_id() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_id(s) == SPACE_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_id() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_get_north() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_set_north(s, LINK_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_north(s) == LINK_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_north() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_north(s) == NO_ID);
}

void test1_space_get_south() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_set_south(s, LINK_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_south(s) == LINK_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_south() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_south(s) == NO_ID);
}

void test1_space_get_east() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_set_east(s, LINK_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_east(s) == LINK_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_east() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_east(s) == NO_ID);
}

void test1_space_get_west() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_set_west(s, LINK_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_west(s) == LINK_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_west() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_west(s) == NO_ID);
}

void test1_space_get_graphic_description() {
    Space *s = NULL;
    char desc[MAX_GDESC_R][MAX_GDESC_C];
    char **descEnd;
    int i;
    int result = 0;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i < MAX_GDESC_R; i++) {
        strcpy(desc[i], "desc");
    }
    space_set_graphic_description(s, desc);
    descEnd = space_get_graphic_description(s);
    for (i = 0; i < MAX_GDESC_R; i++) {
        if (strcmp(descEnd[i], "desc") != 0) {
            result = 1;
        }
    }
    PRINT_TEST_RESULT(result == 0);
    space_destroy(s);
}

void test2_space_get_graphic_description() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_graphic_description(s) == NULL);
}

void test1_space_get_check() {
    Space *s = NULL;
    char check[MAX_CHECK_R][MAX_CHECK_C];
    char **checkEnd;
    int i;
    int result = 0;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i < MAX_CHECK_R; i++) {
        strcpy(check[i], "CHECK");
    }
    space_set_check(s, check);
    checkEnd = space_get_check(s);
    for (i = 0; i < MAX_CHECK_R; i++) {
        if (strcmp(checkEnd[i], "CHECK") != 0) {
            result = 1;
        }
    }
    PRINT_TEST_RESULT(result == 0);
    space_destroy(s);
}

void test2_space_get_check() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_check(s) == NULL);
}

void test1_space_get_object_id() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_add_object(s, OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_object_id(s, 0) == OBJECT_BASE_ID+1);
    space_destroy(s);
}

void test2_space_get_object_id() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_object_id(s, 0) == NO_ID);
}

void test1_space_get_objects_number() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_add_object(s, OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_objects_number(s) == 1);
    space_destroy(s);
}

void test2_space_get_objects_number() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_get_objects_number(s) == 0);
    space_destroy(s);
}

void test3_space_get_objects_number() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_objects_number(s) == 0);
}

void test4_space_get_objects_number() {
    Space *s = NULL;
    int i;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i <= MAX_OBJECTS+1; i++) {
        space_add_object(s, OBJECT_BASE_ID+1 + i);
    }
    PRINT_TEST_RESULT(space_get_objects_number(s) == SET_MAX_IDS);
    space_destroy(s);
}

void test1_space_add_object() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_add_object(s, TRUE) == OK);
    space_destroy(s);
}

void test2_space_add_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, TRUE) == ERROR);
}

void test1_space_is_empty() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_is_empty(s) == TRUE);
    space_destroy(s);
}

void test2_space_is_empty() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_is_empty(s) == TRUE);
}

void test3_space_is_empty() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_add_object(s, OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(space_is_empty(s) == FALSE);
    space_destroy(s);
}

void test1_space_is_full() {
    Space *s = NULL;
    int i;
    s = space_create(SPACE_BASE_ID+1);
    for (i = 0; i <= MAX_OBJECTS+1; i++) {
        space_add_object(s, OBJECT_BASE_ID+1 + i);
    }
    PRINT_TEST_RESULT(space_is_full(s) == TRUE);
    space_destroy(s);
}

void test2_space_is_full() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_is_full(s) == FALSE);
    space_destroy(s);
}

void test3_space_is_full() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_is_full(s) == TRUE);
}

void test4_space_is_full() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_add_object(s, OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(space_is_full(s) == FALSE);
    space_destroy(s);
}

void test1_space_check_object() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    space_add_object(s, OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(space_check_object(s, OBJECT_BASE_ID+1) == TRUE);
    space_destroy(s);
}

void test2_space_check_object() {
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID+1);
    PRINT_TEST_RESULT(space_check_object(s, OBJECT_BASE_ID+1) == FALSE);
    space_destroy(s);
}

void test3_space_check_object() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_check_object(s, OBJECT_BASE_ID+1) == FALSE);
}
