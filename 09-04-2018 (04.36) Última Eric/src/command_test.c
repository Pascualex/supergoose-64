/** 
 * @brief It defines the command test functions
 * @file command_test.c
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
#include <unistd.h> 
#include <fcntl.h>
/*Own libraries*/
#include "../include/command.h"
#include "../include/command_test.h"
#include "../include/test.h"
#include "../include/types.h"

/*We define the maximun amount of tests we will do*/
#define MAX_TESTS 10

int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Command:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }


    if (all || test == 1) test1_command_create();
    if (all || test == 2) test1_command_destroy();
    if (all || test == 3) test2_command_destroy();
    if (all || test == 4) test1_command_get_user_input();
    if (all || test == 5) test2_command_get_user_input();
    if (all || test == 6) test3_command_get_user_input();
    if (all || test == 7) test1_command_get_command();
    if (all || test == 8) test2_command_get_command();
    if (all || test == 9) test1_command_get_info();
    if (all || test == 10) test2_command_get_info();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_command_create() {
    Command *command = NULL;
    command = command_create();
    PRINT_TEST_RESULT(command != NULL);
    command_destroy(command);
}

void test1_command_destroy() {
    Command *command = NULL;
    command = command_create();
    PRINT_TEST_RESULT(command_destroy(command) == OK);
}

void test2_command_destroy() {
    Command *command = NULL;
    PRINT_TEST_RESULT(command_destroy(command) == ERROR);
}

void test1_command_get_user_input() {
    Command *command = NULL;
    command = command_create();
    PRINT_TEST_RESULT(command_get_user_input(command) == OK);
    command_destroy(command);
}

void test2_command_get_user_input() {
    Command *command = NULL;
    PRINT_TEST_RESULT(command_get_user_input(command) == ERROR);
    command_destroy(command);
}

void test3_command_get_user_input() {
    Command *command = NULL;
    command = command_create();
    PRINT_TEST_RESULT(command_get_user_input(command) == OK && command_get_command(command) == GRASP && !strcmp(command_get_info(command), "key"));
    command_destroy(command);
}

void test1_command_get_command() {
    Command *command = NULL;
    command = command_create();
    command_get_user_input(command);
    PRINT_TEST_RESULT(command_get_command(command) == GRASP);
    command_destroy(command);
}

void test2_command_get_command() {
    Command *command = NULL;
    PRINT_TEST_RESULT(command_get_command(command) == NO_CMD);
}

void test1_command_get_info() {
    Command *command = NULL;
    command = command_create();
    command_get_user_input(command);
    PRINT_TEST_RESULT(!strcmp(command_get_info(command), "key"));
    command_destroy(command);
}

void test2_command_get_info() {
    Command *command = NULL;
    PRINT_TEST_RESULT(command_get_info(command) == NULL);
}
