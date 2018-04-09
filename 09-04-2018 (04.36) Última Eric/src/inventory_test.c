/** 
 * @brief It defines the inventory test functions
 * @file inventory_test.c
 * @author Alejandro Pascual
 * @version 1.0 
 * @date 06-04-2018
 * @updated 07-04-2018
 * @copyright GNU Public License
 */

/*C libraries*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
/*Own libraries*/
#include "../include/inventory_test.h"
#include "../include/inventory.h"
#include "../include/test.h"
#include "../include/types.h"

/*We define the maximun amount of tests we will do*/
#define MAX_TESTS 34

int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test2_inventory_create();
    if (all || test == 3) test1_inventory_destroy();
    if (all || test == 4) test2_inventory_destroy();
    if (all || test == 5) test1_inventory_add();
    if (all || test == 6) test2_inventory_add();
    if (all || test == 7) test3_inventory_add();
    if (all || test == 8) test4_inventory_add();
    if (all || test == 9) test1_inventory_del();
    if (all || test == 10) test2_inventory_del();
    if (all || test == 11) test3_inventory_del();
    if (all || test == 12) test4_inventory_del();
    if (all || test == 13) test1_inventory_set_max_objects();
    if (all || test == 14) test2_inventory_set_max_objects();
    if (all || test == 15) test3_inventory_set_max_objects();
    if (all || test == 16) test4_inventory_set_max_objects();
    if (all || test == 17) test1_inventory_get_object_id();
    if (all || test == 18) test2_inventory_get_object_id();
    if (all || test == 19) test3_inventory_get_object_id();
    if (all || test == 20) test1_inventory_get_objects_number();
    if (all || test == 21) test2_inventory_get_objects_number();
    if (all || test == 22) test3_inventory_get_objects_number();
    if (all || test == 23) test1_inventory_get_max_objects();
    if (all || test == 24) test2_inventory_get_max_objects();
    if (all || test == 25) test3_inventory_get_max_objects();
    if (all || test == 26) test1_inventory_check_object();
    if (all || test == 27) test2_inventory_check_object();
    if (all || test == 28) test3_inventory_check_object();
    if (all || test == 29) test1_inventory_is_empty();
    if (all || test == 30) test2_inventory_is_empty();
    if (all || test == 31) test3_inventory_is_empty();
    if (all || test == 32) test1_inventory_is_full();
    if (all || test == 33) test2_inventory_is_full();
    if (all || test == 34) test3_inventory_is_full();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_inventory_create() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_max_objects(inventory) == 1);
}

void test2_inventory_create() {
    Inventory *inventory = NULL;
    inventory = inventory_create(-1);
    PRINT_TEST_RESULT(inventory == NULL);
    if (inventory != NULL) inventory_destroy(inventory);
}

void test1_inventory_destroy() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_destroy(inventory) == OK);
}

void test2_inventory_destroy() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_destroy(inventory) == ERROR);
}

void test1_inventory_add() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_get_object_id(inventory, 0) == OBJECT_BASE_ID + 1);
}

void test2_inventory_add() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_add(inventory, NO_ID) == ERROR);
}

void test3_inventory_add() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_add(inventory, OBJECT_BASE_ID + 1) == ERROR);
}

void test4_inventory_add() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_add(inventory, OBJECT_BASE_ID + 1) == ERROR);
}

void test1_inventory_del() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    inventory_del(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_is_empty(inventory) == TRUE);
}

void test2_inventory_del() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_del(inventory, OBJECT_BASE_ID + 2) == ERROR);
}

void test3_inventory_del() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_del(inventory, OBJECT_BASE_ID + 1) == ERROR);
}

void test4_inventory_del() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_del(inventory, OBJECT_BASE_ID + 1) == ERROR);
}

void test1_inventory_set_max_objects() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    inventory_set_max_objects(inventory, 1);
    PRINT_TEST_RESULT(inventory_get_max_objects(inventory) == 1);
}

void test2_inventory_set_max_objects() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_set_max_objects(inventory, -1) == ERROR);
}

void test3_inventory_set_max_objects() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_set_max_objects(inventory, 1000) == ERROR);
}

void test4_inventory_set_max_objects() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_set_max_objects(inventory, 1) == ERROR);
}

void test1_inventory_get_object_id() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_get_object_id(inventory, 0) == OBJECT_BASE_ID + 1);
}

void test2_inventory_get_object_id() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_object_id(inventory, 0) == NO_ID);
}

void test3_inventory_get_object_id() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_object_id(inventory, 0) == NO_ID);
}

void test1_inventory_get_objects_number() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_get_objects_number(inventory) == 1);
}

void test2_inventory_get_objects_number() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_objects_number(inventory) == 0);
}

void test3_inventory_get_objects_number() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_objects_number(inventory) == 0);
}

void test1_inventory_get_max_objects() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_max_objects(inventory) == 1);
}

void test2_inventory_get_max_objects() {
    Inventory *inventory = NULL;
    inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_get_max_objects(inventory) == 0);
}

void test3_inventory_get_max_objects() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_get_max_objects(inventory) == 0);
}

void test1_inventory_check_object() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_check_object(inventory, OBJECT_BASE_ID + 1) == TRUE);
}

void test2_inventory_check_object() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_check_object(inventory, OBJECT_BASE_ID + 2) == FALSE);
}

void test3_inventory_check_object() {
    Inventory *inventory = NULL;
    ;
    PRINT_TEST_RESULT(inventory_check_object(inventory, OBJECT_BASE_ID + 1) == FALSE);
}

void test1_inventory_is_empty() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_is_empty(inventory) == TRUE);
}

void test2_inventory_is_empty() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_is_empty(inventory) == FALSE);
}

void test3_inventory_is_empty() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_is_empty(inventory) == TRUE);
}

void test1_inventory_is_full() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    inventory_add(inventory, OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(inventory_is_full(inventory) == TRUE);
}

void test2_inventory_is_full() {
    Inventory *inventory = NULL;
    inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_is_full(inventory) == FALSE);
}

void test3_inventory_is_full() {
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_is_full(inventory) == TRUE);
}
