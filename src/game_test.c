/** 
 * @brief It tests the game module
 * @file game_test.command
 * @author Javier Lougedo
 * @version 1.0 
 * @date 06-04-2018
 * @updated 06-04-2018
 * @copyright GNU Public License
 */

#undef __STRICT_ANSI__

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <wchar.h>
#include "../include/game.h"
#include "../include/game_test.h"
#include "../include/test.h"


#define MAX_TESTS 60

/*
 * Main function for GAME unit tests. 
 * 
 * You may execute ALL or a SINGLE test:
 *   1.- No parameter -> ALL tests are executed.
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed.
 */

int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Game:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 && test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1) test1_game_create();
    if (all || test == 2) test1_game_create_from_file();
    if (all || test == 3) test2_game_create_from_file();
    if (all || test == 4) test3_game_create_from_file();
    if (all || test == 5) test4_game_create_from_file();
    if (all || test == 6) test1_game_update();
    if (all || test == 7) test2_game_update();
    if (all || test == 8) test1_game_destroy();
    if (all || test == 9) test2_game_destroy();
    if (all || test == 10) test1_game_is_over();
    if (all || test == 11) test2_game_is_over();
    if (all || test == 12) test1_game_add_space();
    if (all || test == 13) test2_game_add_space();
    if (all || test == 14) test3_game_add_space();
    if (all || test == 15) test4_game_add_space();
    if (all || test == 16) test1_game_add_player();
    if (all || test == 17) test2_game_add_player();
    if (all || test == 18) test3_game_add_player();
    if (all || test == 19) test4_game_add_player();
    if (all || test == 20) test5_game_add_player();
    if (all || test == 21) test1_game_add_object();
    if (all || test == 22) test2_game_add_object();
    if (all || test == 23) test3_game_add_object();
    if (all || test == 24) test4_game_add_object();
    if (all || test == 25) test5_game_add_object();
    if (all || test == 26) test6_game_add_object();
    if (all || test == 27) test1_game_get_spaces_number();
    if (all || test == 28) test2_game_get_spaces_number();
    if (all || test == 29) test3_game_get_spaces_number();
    if (all || test == 30) test4_game_get_spaces_number();
    if (all || test == 31) test1_game_get_players_number();
    if (all || test == 32) test2_game_get_players_number();
    if (all || test == 33) test3_game_get_players_number();
    if (all || test == 34) test4_game_get_players_number();
    if (all || test == 35) test1_game_get_objects_number();
    if (all || test == 36) test2_game_get_objects_number();
    if (all || test == 37) test3_game_get_objects_number();
    if (all || test == 38) test4_game_get_objects_number();
    if (all || test == 39) test1_game_get_dies_number();
    if (all || test == 40) test2_game_get_dies_number();
    if (all || test == 41) test1_game_set_object_location();
    if (all || test == 42) test2_game_set_object_location();
    if (all || test == 43) test3_game_set_object_location();
    if (all || test == 44) test4_game_set_object_location();
    if (all || test == 45) test1_game_get_last_command();
    if (all || test == 46) test2_game_get_last_command();
    if (all || test == 47) test1_game_get_status_last_command();
    if (all || test == 48) test2_game_get_status_last_command();
    if (all || test == 49) test1_game_get_last_text_description();
    if (all || test == 50) test2_game_get_last_text_description();
    if (all || test == 51) test3_game_get_last_text_description();
    if (all || test == 52) test1_game_add_link();
    if (all || test == 53) test2_game_add_link();
    if (all || test == 54) test3_game_add_link();
    if (all || test == 55) test1_game_find();
    if (all || test == 56) test2_game_find();
    if (all || test == 57) test3_game_find();
    if (all || test == 58) test1_game_find_name();
    if (all || test == 59) test2_game_find_name();
    if (all || test == 60) test3_game_find_name();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_game_create() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game != NULL);
    game_destroy(game);
}

void test1_game_create_from_file() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_create_from_file(game, "./datafiles/test.dat") == OK);
    game_destroy(game);
}

void test2_game_create_from_file() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_create_from_file(game, "./datafiles/test.dat") == ERROR);
}

void test3_game_create_from_file() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_create_from_file(game, NULL) == ERROR);
    game_destroy(game);
}

void test4_game_create_from_file() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_create_from_file(game, "non_existing_file") == ERROR);
    game_destroy(game);
}

void test1_game_update() {
    Game *game = NULL;
    Command *command = NULL;
    PRINT_TEST_RESULT(game_update(game, command) == ERROR);
}

void test2_game_update() {
    Game *game = NULL;
    Command *command = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_update(game, command) == ERROR);
    game_destroy(game);
}

void test1_game_destroy() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_destroy(game) == OK);
}

void test2_game_destroy() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_destroy(game) == ERROR);
}

void test1_game_is_over() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_is_over(game) == FALSE);
    game_destroy(game);
}

void test2_game_is_over() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_is_over(game) == TRUE);
}

void test1_game_add_space() {
    Game *game = NULL;
    Space *space = NULL;
    game = game_create();
    space = space_create(SPACE_BASE_ID+5);
    PRINT_TEST_RESULT(game_add_space(game, space) == OK);
    game_destroy(game);
}

void test2_game_add_space() {
    Game *game = NULL;
    Space *space = NULL;
    space = space_create(SPACE_BASE_ID+4);
    PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
    space_destroy(space);
}

void test3_game_add_space() {
    Game *game = NULL;
    Space *space = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
    game_destroy(game);
}

void test4_game_add_space() {
    Game *game = NULL;
    Space *space = NULL;
    int i = 0;
    game = game_create();
    for (i = 0; i < MAX_SPACES; i++) {
        space = space_create(SPACE_BASE_ID+1+i);
        game_add_space(game, space);
    }
    PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
    game_destroy(game);
}

void test1_game_add_player() {
    Game *game = NULL;
    Player *player = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    player = player_create(PLAYER_BASE_ID+2, 1);
    PRINT_TEST_RESULT(game_add_player(game, player, 4) == OK);
    game_destroy(game);
}

void test2_game_add_player() {
    Game *game = NULL;
    Player *player = NULL;
    player = player_create(PLAYER_BASE_ID+1, 1);
    PRINT_TEST_RESULT(game_add_player(game, player, 1) == ERROR);
    player_destroy(player);
}

void test3_game_add_player() {
    Game *game = NULL;
    Player *player = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_player(game, player, 1) == ERROR);
    game_destroy(game);
}

void test4_game_add_player() {
    Game *game = NULL;
    Player *player = NULL;
    game = game_create();
    player = player_create(PLAYER_BASE_ID+1, 1);
    PRINT_TEST_RESULT(game_add_player(game, player, NO_ID) == ERROR);
    game_destroy(game);
}

void test5_game_add_player() {
    Game *game = NULL;
    Player *player = NULL;
    int i = 0;
    game = game_create();
    for (i = 0; i < MAX_PLAYERS; i++) {
        player = player_create(PLAYER_BASE_ID+1+i, 1);
        game_add_player(game, player, 1);
    }
    PRINT_TEST_RESULT(game_add_player(game, player, 1) == ERROR);
    game_destroy(game);
}

void test1_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(game_add_object(game, object, 2) == OK);
    game_destroy(game);
}

void test2_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(game_add_object(game, object, 1) == ERROR);
    object_destroy(object);
}

void test3_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_object(game, object, 1) == ERROR);
    game_destroy(game);
}

void test4_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    game = game_create();
    object = object_create(OBJECT_BASE_ID+1);
    PRINT_TEST_RESULT(game_add_object(game, object, NO_ID) == ERROR);
    object_destroy(object);
    game_destroy(game);
}

void test5_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    int i = 0;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    for (i = 0; i < SET_MAX_IDS; i++) {
        object = object_create(OBJECT_BASE_ID+1+i);
        game_add_object(game, object, 3);
    }
    PRINT_TEST_RESULT(game_add_object(game, object, 3) == ERROR);
    game_destroy(game);
}

void test6_game_add_object() {
    Game *game = NULL;
    Object *object = NULL;
    int i = 0, j = 0;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    for (i = game_get_objects_number(game); i < MAX_OBJECTS; i++) {
        object = object_create(OBJECT_BASE_ID+1+i);
        if (game_add_object(game, object, SPACE_BASE_ID+j) == ERROR) {
            j++;
            game_add_object(game, object, SPACE_BASE_ID+j);
        }
    }
    PRINT_TEST_RESULT(game_add_object(game, object, SPACE_BASE_ID+1) == ERROR);
    game_destroy(game);
}

void test1_game_get_spaces_number() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_spaces_number(game) == 4);
    game_destroy(game);
}

void test2_game_get_spaces_number() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_spaces_number(game) == 0);
    game_destroy(game);
}

void test3_game_get_spaces_number() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_spaces_number(game) == 0);
}

void test4_game_get_spaces_number() {
    Game *game = NULL;
    Space *space = NULL;
    int i = 0;
    game = game_create();
    for (i = 0; i < MAX_SPACES; i++) {
        space = space_create(SPACE_BASE_ID+1+i);
        game_add_space(game, space);
    }
    PRINT_TEST_RESULT(game_get_spaces_number(game) == MAX_SPACES);
    game_destroy(game);
}

void test1_game_get_players_number() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_players_number(game) == 1);
    game_destroy(game);
}

void test2_game_get_players_number() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_players_number(game) == 0);
    game_destroy(game);
}

void test3_game_get_players_number() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_players_number(game) == 0);
}

void test4_game_get_players_number() {
    Game *game = NULL;
    Player *player = NULL;
    int i = 0;
    game = game_create();
    for (i = 0; i < MAX_PLAYERS; i++) {
        player = player_create(PLAYER_BASE_ID+1+i, 1);
        game_add_player(game, player, SPACE_BASE_ID+1);
    }
    PRINT_TEST_RESULT(game_get_players_number(game) == MAX_PLAYERS);
    game_destroy(game);
}

void test1_game_get_objects_number() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_objects_number(game) == 1);
    game_destroy(game);
}

void test2_game_get_objects_number() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_objects_number(game) == 0);
    game_destroy(game);
}

void test3_game_get_objects_number() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_objects_number(game) == 0);
}

void test4_game_get_objects_number() {
    Game *game = NULL;
    Object *object = NULL;
    int i = 0, j = 0;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    for (i = game_get_objects_number(game); i < MAX_OBJECTS; i++) {
        object = object_create(OBJECT_BASE_ID+1+i);
        if (game_add_object(game, object, j) == ERROR) {
            j++;
            game_add_object(game, object, j);
        }
    }
    PRINT_TEST_RESULT(game_get_objects_number(game) == MAX_OBJECTS);
    game_destroy(game);
}

void test1_game_get_dies_number() {
    Game *game = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_get_dies_number(game) == 1);
    game_destroy(game);
}

void test2_game_get_dies_number() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_dies_number(game) == 0);
}

void test1_game_find() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find(game, 1) != NULL);
    game_destroy(game);
}

void test2_game_find() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_find(game, 1) == NULL);
}

void test3_game_find() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find(game, NO_ID) == NULL);
    game_destroy(game);
}

void test1_game_find_name() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find_name(game, "OBJ_NAME") != NULL);
    game_destroy(game);
}

void test2_game_find_name() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_find_name(game, "OBJ_NAME") == NULL);
}

void test3_game_find_name() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find_name(game, NULL) == NULL);
    game_destroy(game);
}

void test1_game_set_object_location() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(game, 1, 2) == OK);
    game_destroy(game);
}

void test2_game_set_object_location() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_set_object_location(game, 2, 1) == ERROR);
}

void test3_game_set_object_location() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(game, NO_ID, 1) == ERROR);
    game_destroy(game);
}

void test4_game_set_object_location() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(game, 3, NO_ID) == ERROR);
    game_destroy(game);
}

void test5_game_set_object_location() {
    Game *game = NULL;
    game = game_create();
    game_create_from_file(game, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(game, 2, 1) == OK);
    game_destroy(game);
}

void test1_game_get_last_command() {
    Game *game = NULL;
    Command *command = NULL;
    game = game_create();
    command = command_create();
    game_create_from_file(game, "./datafiles/test.dat");
    command_get_user_input(command);
    game_update(game, command);   
    PRINT_TEST_RESULT(game_get_last_command(game) == GRASP);
    game_destroy(game);
    command_destroy(command);
}

void test2_game_get_last_command() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_last_command(game) == NO_CMD);
}

void test1_game_get_status_last_command() {
    Game *game = NULL;
    Command *command = NULL;
    game = game_create();
    command = command_create();
    game_create_from_file(game, "./datafiles/test.dat");
    command_get_user_input(command);
    game_update(game, command);
    PRINT_TEST_RESULT(game_get_status_last_command(game) == OK);
    game_destroy(game);
    command_destroy(command);
}

void test2_game_get_status_last_command() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_status_last_command(game) == ERROR);
}

void test1_game_get_last_text_description() {
    Game *game = NULL;
    Command *command = NULL;
    wchar_t **desc = NULL;
    game = game_create();
    command = command_create();
    game_create_from_file(game, "./datafiles/test.dat");
    command_get_user_input(command);
    game_update(game, command);
    desc = game_get_last_text_description(game);
    PRINT_TEST_RESULT(!wcscmp(desc[0], L"OBJ DESC 1") || !wcscmp(desc[1], L"OBJ DESC 2") || !wcscmp(desc[2], L"OBJ DESC 3"));
    game_destroy(game);
    command_destroy(command);
}

void test2_game_get_last_text_description() {
    Game *game = NULL;
    PRINT_TEST_RESULT(game_get_last_text_description(game) == NULL);
}

void test3_game_get_last_text_description() {
    Game *game = NULL;
    Command *command = NULL;
    wchar_t **desc = NULL;
    game = game_create();
    command = command_create();
    game_create_from_file(game, "./datafiles/test.dat");
    command_get_user_input(command);
    game_update(game, command);
    desc = game_get_last_text_description(game);
    PRINT_TEST_RESULT(!wcscmp(desc[0], L"CHECK DESC 1") || !wcscmp(desc[1], L"CHECK DESC 2") || !wcscmp(desc[2], L"CHECK DESC 3"));
    game_destroy(game);
    command_destroy(command);
}

void test1_game_add_link() {
    Game *game = NULL;
    Link *link = NULL;
    game = game_create();
    link = link_create(LINK_BASE_ID+1);
    PRINT_TEST_RESULT(game_add_link(game, link) == OK);
    game_destroy(game);
}

void test2_game_add_link() {
    Game *game = NULL;
    Link *link = NULL;
    link = link_create(LINK_BASE_ID+2);
    PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
    link_destroy(link);
}

void test3_game_add_link() {
    Game *game = NULL;
    Link *link = NULL;
    game = game_create();
    PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
    game_destroy(game);
}

void test4_game_add_link() {
    Game *game = NULL;
    Link *link = NULL;
    int i = 0;
    game = game_create();
    for (i = 0; i < MAX_LINKS; i++) {
        link = link_create(LINK_BASE_ID+1+i);
        game_add_link(game, link);
    }
    PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
    game_destroy(game);
}