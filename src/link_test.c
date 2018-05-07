/** 
 * @brief It defines the link test functions
 * @file link_test.c
 * @author Victor Yrazusta
 * @version 1.0 
 * @date 06-04-2018
 * @updated 06-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

/*C libraries*/
#include <stdio.h> 
#include <stdlib.h> 
#include <wchar.h> 
/*Own libraries*/
#include "../include/link.h"
#include "../include/link_test.h"
#include "../include/test.h"
#include "../include/types.h"

/*We define the maximun amount of tests we will do*/
#define MAX_TESTS 23

int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Link:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_link_create();
    if (all || test == 2) test2_link_create();
    if (all || test == 3) test3_link_create();
    if (all || test == 4) test4_link_create();
    if (all || test == 5) test1_link_set_name();
    if (all || test == 6) test2_link_set_name();
    if (all || test == 7) test3_link_set_name();
    if (all || test == 8) test1_link_add_space();
    if (all || test == 9) test2_link_add_space();
    if (all || test == 10) test3_link_add_space();
    if (all || test == 11) test1_link_set_status();
    if (all || test == 12) test2_link_set_status();
    if (all || test == 13) test1_link_get_id();
    if (all || test == 14) test2_link_get_id();
    if (all || test == 15) test1_link_get_name();
    if (all || test == 16) test2_link_get_name();
    if (all || test == 17) test1_link_get_status();
    if (all || test == 18) test2_link_get_status();
    if (all || test == 19) test1_link_get_other_side();
    if (all || test == 20) test2_link_get_other_side();
    if (all || test == 21) test3_link_get_other_side();
    if (all || test == 22) test1_link_destroy();
    if (all || test == 23) test2_link_destroy();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_link_create() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link != NULL);
    link_destroy(link);
}

void test2_link_create() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_get_id(link) == LINK_BASE_ID+1);
    link_destroy(link);
}

void test3_link_create() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_set_status(link, CLOSED);
    PRINT_TEST_RESULT(link_get_id(link) == LINK_BASE_ID+1 && link_get_status(link) == CLOSED);
    link_destroy(link);
}

void test4_link_create() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+2);
    link_set_status(link, CLOSED);
    PRINT_TEST_RESULT(link_get_id(link) == LINK_BASE_ID+1 && link_get_status(link) == CLOSED && link_get_other_side(link, SPACE_BASE_ID+1) == SPACE_BASE_ID+2 && link_get_other_side(link, SPACE_BASE_ID+2) == SPACE_BASE_ID+1);
    link_destroy(link);
}

void test1_link_set_name() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_set_name(link, L"string") == OK);
    link_destroy(link);
}

void test2_link_set_name() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_set_name(link, L"string") == ERROR);
    link_destroy(link);
}

void test3_link_set_name() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
    link_destroy(link);
}

void test1_link_add_space() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_add_space(link, SPACE_BASE_ID+1) == OK && link_add_space(link, SPACE_BASE_ID+2) == OK);
    link_destroy(link);
}

void test2_link_add_space() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_add_space(link, DIE_BASE_ID+1) == ERROR && link_add_space(link, SPACE_BASE_ID+1) == OK);
    link_destroy(link);
}

void test3_link_add_space() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_add_space(link, DIE_BASE_ID+1) == ERROR && link_add_space(link, SPACE_BASE_ID+1) == ERROR);
}

void test1_link_set_status() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_set_status(link, CLOSED) == OK);
    link_destroy(link);
}

void test2_link_set_status() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_set_status(link, CLOSED) == ERROR);
}

void test1_link_get_id() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_get_id(link) == LINK_BASE_ID+1);
    link_destroy(link);
}

void test2_link_get_id() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_id(link) == NO_ID);
}

void test1_link_get_name() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_set_name(link, L"string");
    PRINT_TEST_RESULT(!wcscmp(link_get_name(link), L"string"));
    link_destroy(link);
}

void test2_link_get_name() {
    Link *link = NULL;
    link_set_name(link, L"string");
    PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_get_status() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_set_status(link, CLOSED);
    PRINT_TEST_RESULT(link_get_status(link) == CLOSED);
    link_destroy(link);
}

void test2_link_get_status() {
    Link *link = NULL;
    link_set_status(link, CLOSED);
    PRINT_TEST_RESULT(link_get_status(link) == CLOSED);
}

void test1_link_get_other_side() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+2);
    PRINT_TEST_RESULT(link_get_other_side(link, SPACE_BASE_ID+1) == SPACE_BASE_ID+2 && link_get_other_side(link, SPACE_BASE_ID+2) == SPACE_BASE_ID+1);
    link_destroy(link);
}

void test2_link_get_other_side() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    link_add_space(link, DIE_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+2);
    PRINT_TEST_RESULT(link_get_other_side(link, DIE_BASE_ID+1) != SPACE_BASE_ID+2);
    link_destroy(link);
}

void test3_link_get_other_side() {
    Link *link = NULL;
    link_add_space(link, SPACE_BASE_ID+1);
    link_add_space(link, SPACE_BASE_ID+2);
    PRINT_TEST_RESULT(link_get_other_side(link, SPACE_BASE_ID+1) != SPACE_BASE_ID+2);
}

void test1_link_destroy() {
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(link_destroy(link) == OK);
}

void test2_link_destroy() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_destroy(link) == ERROR);
}
