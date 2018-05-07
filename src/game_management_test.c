/*C libraries*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
/*Own libraries*/
#include "../include/game_management.h"
#include "../include/game.h"
#include "../include/test.h"
#include "../include/types.h"
#include "nfd.h"

/*We define the maximun amount of tests we will do*/
#define MAX_TESTS 34

int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Game Management:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_game_management_load_spaces();
    if (all || test == 2) test2_game_management_load_spaces();
    if (all || test == 3) test3_game_management_load_spaces();
    if (all || test == 4) test4_game_management_load_spaces();
    if (all || test == 5) test1_game_management_load_players();
    if (all || test == 6) test2_game_management_load_players();
    if (all || test == 7) test3_game_management_load_players();
    if (all || test == 8) test4_game_management_load_players();
    if (all || test == 9) test1_game_management_load_objects();
    if (all || test == 10) test2_game_management_load_objects();
    if (all || test == 11) test3_game_management_load_objects();
    if (all || test == 12) test4_game_management_load_objects();
    if (all || test == 13) test1_game_management_load_links();
    if (all || test == 14) test2_game_management_load_links();
    if (all || test == 15) test3_game_management_load_links();
    if (all || test == 16) test4_game_management_load_links();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_game_management_load_spaces() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_spaces(game, "./datafiles/game_management_test_1.dat") == OK && game_find(game, SPACE_BASE_ID+1) != NULL && game_find(game, SPACE_BASE_ID+2) != NULL);
    game_destroy(game);
}

void test2_game_management_load_spaces() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_spaces(game, "./datafiles/game_management_test_2.dat") == OK);
    game_destroy(game);
}

void test3_game_management_load_spaces() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_management_load_spaces(game, "./datafiles/game_management_test_1.dat") == ERROR);
}

void test4_game_management_load_spaces() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_spaces(game, "./datafiles/non-existent.dat") == ERROR);
    game_destroy(game);
}

void test1_game_management_load_players() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_players(game, "./datafiles/game_management_test_1.dat") == OK && game_find(game, PLAYER_BASE_ID+1) != NULL);
    game_destroy(game);
}

void test2_game_management_load_players() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_players(game, "./datafiles/game_management_test_2.dat") == OK);
    game_destroy(game);
}

void test3_game_management_load_players() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_management_load_players(game, "./datafiles/game_management_test_1.dat") == ERROR);
}

void test4_game_management_load_players() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_players(game, "./datafiles/non-existent.dat") == ERROR);
    game_destroy(game);
}

void test1_game_management_load_objects() {
    Game *game = NULL;
    game = game_create();
    game_management_load_spaces(game, "./datafiles/game_management_test_1.dat");
    PRINT_TEST_RESULT(game_management_load_objects(game, "./datafiles/game_management_test_1.dat") == OK && game_find(game, OBJECT_BASE_ID+1) != NULL);
    game_destroy(game);
}

void test2_game_management_load_objects() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_objects(game, "./datafiles/game_management_test_2.dat") == OK);
    game_destroy(game);
}

void test3_game_management_load_objects() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_management_load_objects(game, "./datafiles/game_management_test_1.dat") == ERROR);
}

void test4_game_management_load_objects() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_objects(game, "./datafiles/non-existent.dat") == ERROR);
    game_destroy(game);
}

void test1_game_management_load_links() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_links(game, "./datafiles/game_management_test_1.dat") == OK && game_find(game, LINK_BASE_ID+1) != NULL);
    game_destroy(game);
}

void test2_game_management_load_links() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_links(game, "./datafiles/game_management_test_2.dat") == OK);
    game_destroy(game);
}

void test3_game_management_load_links() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_management_load_links(game, "./datafiles/game_management_test_1.dat") == ERROR);
}

void test4_game_management_load_links() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_management_load_links(game, "./datafiles/non-existent.dat") == ERROR);
    game_destroy(game);
}
