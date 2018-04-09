/** 
 * @brief It tests the game module
 * @file game_test.c
 * @author Javier Lougedo
 * @version 1.0 
 * @date 06-04-2018
 * @updated 06-04-2018
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../include/game.h"
#include "../include/game_test.h"
#include "../include/test.h"


#define MAX_TESTS 56

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
    /*if (all || test == 45) test1_game_get_last_command();*/
    if (all || test == 46) test2_game_get_last_command();
    if (all || test == 47) test1_game_get_status_last_command();
    if (all || test == 48) test1_game_get_last_check();
    if (all || test == 49) test1_game_add_link();
    if (all || test == 50) test2_game_add_link();
    if (all || test == 51) test3_game_add_link();
    if (all || test == 52) test1_game_find();
    if (all || test == 53) test2_game_find();
    if (all || test == 54) test3_game_find();
    if (all || test == 55) test1_game_find_name();
    if (all || test == 56) test2_game_find_name();
    if (all || test == 57) test3_game_find_name();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_game_create() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(g != NULL);
    game_destroy(g);
}

void test1_game_create_from_file() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, "./datafiles/test.dat") == OK);
    game_destroy(g);
}

void test2_game_create_from_file() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_create_from_file(g, "./datafiles/test.dat") == ERROR);
}

void test3_game_create_from_file() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, NULL) == ERROR);
    game_destroy(g);
}

void test4_game_create_from_file() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_create_from_file(g, "non_existing_file") == ERROR);
    game_destroy(g);
}

void test1_game_update() {
    Game *g = NULL;
    Command *c = NULL;
    PRINT_TEST_RESULT(game_update(g, c) == ERROR);
}

void test2_game_update() {
    Game *g = NULL;
    Command *c = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_update(g, c) == ERROR);
    game_destroy(g);
}

void test1_game_destroy() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_destroy(g) == OK);
}

void test2_game_destroy() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_destroy(g) == ERROR);
}

void test1_game_is_over() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_is_over(g) == FALSE);
    game_destroy(g);
}

void test2_game_is_over() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_is_over(g) == TRUE);
}

void test1_game_add_space() {
    Game *g = NULL;
    Space *s = NULL;
    g = game_create();
    s = space_create(SPACE_BASE_ID + 5);
    PRINT_TEST_RESULT(game_add_space(g, s) == OK);
    game_destroy(g);
}

void test2_game_add_space() {
    Game *g = NULL;
    Space *s = NULL;
    s = space_create(SPACE_BASE_ID + 4);
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
    space_destroy(s);
}

void test3_game_add_space() {
    Game *g = NULL;
    Space *s = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
    game_destroy(g);
}

void test4_game_add_space() {
    Game *g = NULL;
    Space *s = NULL;
    int i = 0;
    g = game_create();
    for (i = 0; i < MAX_SPACES + 2; i++) {
        space_create(SPACE_BASE_ID + i);
        game_add_space(g, s);
    }
    PRINT_TEST_RESULT(game_add_space(g, s) == ERROR);
    game_destroy(g);
}

void test1_game_add_player() {
    Game *g = NULL;
    Player *p = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    p = player_create(PLAYER_BASE_ID + 2, 2);
    PRINT_TEST_RESULT(game_add_player(g, p, 2) == OK);
    game_destroy(g);
}

void test2_game_add_player() {
    Game *g = NULL;
    Player *p = NULL;
    p = player_create(PLAYER_BASE_ID + 1, 1);
    PRINT_TEST_RESULT(game_add_player(g, p, 1) == ERROR);
    player_destroy(p);
}

void test3_game_add_player() {
    Game *g = NULL;
    Player *p = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_player(g, p, 1) == ERROR);
    game_destroy(g);
}

void test4_game_add_player() {
    Game *g = NULL;
    Player *p = NULL;
    g = game_create();
    p = player_create(PLAYER_BASE_ID + 1, 1);
    PRINT_TEST_RESULT(game_add_player(g, p, NO_ID) == ERROR);
    game_destroy(g);
}

void test5_game_add_player() {
    Game *g = NULL;
    Player *p = NULL;
    int i = 0;
    g = game_create();
    for (i = 0; i < MAX_PLAYERS + 2; i++) {
        player_create(PLAYER_BASE_ID + i, 1);
        game_add_player(g, p, 1);
    }
    PRINT_TEST_RESULT(game_add_player(g, p, 1) == ERROR);
    game_destroy(g);
}

void test1_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    o = object_create(OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(game_add_object(g, o, 2) == OK);
    game_destroy(g);
}

void test2_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    o = object_create(OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(game_add_object(g, o, 1) == ERROR);
    object_destroy(o);
}

void test3_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_object(g, o, 1) == ERROR);
    game_destroy(g);
}

void test4_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    g = game_create();
    o = object_create(OBJECT_BASE_ID + 1);
    PRINT_TEST_RESULT(game_add_object(g, o, NO_ID) == ERROR);
    game_destroy(g);
}

void test5_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    int i = 0;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    for (i = 0; i < SET_MAX_IDS; i++) {
        o = object_create(OBJECT_BASE_ID + i);
        game_add_object(g, o, 3);
    }
    PRINT_TEST_RESULT(game_add_object(g, o, 3) == ERROR);
    game_destroy(g);
}

void test6_game_add_object() {
    Game *g = NULL;
    Object *o = NULL;
    int i = 0, j = 0;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    for (i = 0; i <= MAX_OBJECTS; i++) {
        o = object_create(OBJECT_BASE_ID + i);
        if (game_add_object(g, o, j) == ERROR) {
            j++;
            game_add_object(g, o, j);
        }
    }
    PRINT_TEST_RESULT(game_add_object(g, o, 4) == ERROR);
    game_destroy(g);
}

void test1_game_get_spaces_number() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_spaces_number(g) == 4);
    game_destroy(g);
}

void test2_game_get_spaces_number() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_spaces_number(g) == 0);
    game_destroy(g);
}

void test3_game_get_spaces_number() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_spaces_number(g) == 0);
}

void test4_game_get_spaces_number() {
    Game *g = NULL;
    Space *s = NULL;
    int i = 0;
    g = game_create();
    for (i = 0; i <= MAX_SPACES; i++) {
        s = space_create(i);
        game_add_space(g, s);
    }
    PRINT_TEST_RESULT(game_get_spaces_number(g) == MAX_SPACES);
    game_destroy(g);
}

void test1_game_get_players_number() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_players_number(g) == 1);
    game_destroy(g);
}

void test2_game_get_players_number() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_players_number(g) == 0);
    game_destroy(g);
}

void test3_game_get_players_number() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_players_number(g) == 0);
}

void test4_game_get_players_number() {
    Game *g = NULL;
    Player *p = NULL;
    int i = 0;
    g = game_create();
    for (i = 0; i <= MAX_PLAYERS; i++) {
        p = player_create(PLAYER_BASE_ID + i, 1);
        game_add_player(g, p, 1);
    }
    PRINT_TEST_RESULT(game_get_players_number(g) == MAX_PLAYERS);
    game_destroy(g);
}

void test1_game_get_objects_number() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_get_objects_number(g) == 1);
    game_destroy(g);
}

void test2_game_get_objects_number() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_objects_number(g) == 0);
    game_destroy(g);
}

void test3_game_get_objects_number() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_objects_number(g) == 0);
}

void test4_game_get_objects_number() {
    Game *g = NULL;
    Object *o = NULL;
    int i = 0, j = 0;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    for (i = 0; i <= MAX_OBJECTS + 1; i++) {
        o = object_create(OBJECT_BASE_ID + i);
        if (game_add_object(g, o, j) == ERROR) {
            j++;
            game_add_object(g, o, j);
        }
    }
    PRINT_TEST_RESULT(game_get_objects_number(g) == MAX_OBJECTS);
    game_destroy(g);
}

void test1_game_get_dies_number() {
    Game *g = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_get_dies_number(g) == 1);
    game_destroy(g);
}

void test2_game_get_dies_number() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_dies_number(g) == 0);
}

void test1_game_find() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find(g, 1) != NULL);
}

void test2_game_find() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_find(g, 1) == NULL);
}

void test3_game_find() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find(g, NO_ID) == NULL);
}

void test1_game_find_name() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find_name(g, "OBJ_NAME") != NULL);
}

void test2_game_find_name() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_find_name(g, "OBJ_NAME") == NULL);
}

void test3_game_find_name() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_find_name(g, NULL) == NULL);
}

void test1_game_set_object_location() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(g, 1, 2) == OK);
    game_destroy(g);
}

void test2_game_set_object_location() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_set_object_location(g, 2, 1) == ERROR);
}

void test3_game_set_object_location() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(g, NO_ID, 1) == ERROR);
    game_destroy(g);
}

void test4_game_set_object_location() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(g, 3, NO_ID) == ERROR);
    game_destroy(g);
}

void test5_game_set_object_location() {
    Game *g = NULL;
    g = game_create();
    game_create_from_file(g, "./datafiles/test.dat");
    PRINT_TEST_RESULT(game_set_object_location(g, 2, 1) == OK);
    game_destroy(g);
}

/*void test1_game_get_last_command() {
    Game *g = NULL;
    Command *c = NULL;
    g = game_create();
    c = command_create();
    game_create_from_file(g, "./datafiles/test.dat");
    printf("\tWrite any thing you want: ");
    command_get_user_input(c);
    game_update(g, c);   
    PRINT_TEST_RESULT(game_get_last_command(g)!=NO_CMD);
    game_destroy(g);
    command_destroy(c);
}*/

void test2_game_get_last_command() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_last_command(g) == NO_CMD);
}

void test1_game_get_status_last_command() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_status_last_command(g) == ERROR);
}

void test1_game_get_last_check() {
    Game *g = NULL;
    PRINT_TEST_RESULT(game_get_last_check(g) == NULL);
}

void test1_game_add_link() {
    Game *g = NULL;
    Link *l = NULL;
    g = game_create();
    l = link_create(LINK_BASE_ID + 1);
    PRINT_TEST_RESULT(game_add_link(g, l) == OK);
    game_destroy(g);
}

void test2_game_add_link() {
    Game *g = NULL;
    Link *l = NULL;
    l = link_create(LINK_BASE_ID + 2);
    PRINT_TEST_RESULT(game_add_link(g, l) == ERROR);
    link_destroy(l);
}

void test3_game_add_link() {
    Game *g = NULL;
    Link *l = NULL;
    g = game_create();
    PRINT_TEST_RESULT(game_add_link(g, l) == ERROR);
    game_destroy(g);
}

void test4_game_add_link() {
    Game *g = NULL;
    Link *l = NULL;
    int i = 0;
    g = game_create();
    for (i = 0; i <= MAX_LINKS; i++) {
        l = link_create(LINK_BASE_ID + i);
        game_add_link(g, l);
    }
    PRINT_TEST_RESULT(game_add_link(g, l) == ERROR);
    game_destroy(g);
}

/*FOLLOWING FUNCTION IS NO LONGER PUBLIC; BUT LEAVING IT IN CASE IT IS IN THE FUTURE*/

/*void test1_game_get_connection() {
    Game *g = NULL;
    Space *s1 = NULL, *s2 = NULL;
    g = game_create();
    g = game_create_from_file(g, "./datafiles/test.dat");
    s1 = space_create(2);
    s2 = space_create(3);
    PRINT_TEST_RESULT(game_get_connection(g, s1, s2)==NULL);
    game_destroy(g);
    space_destroy(s1);
    space_destroy(s2);    
}

void test2_game_get_connection() {
    Game *g = NULL;
    Space *s1 = NULL, *s2 = NULL;
    s1 = space_create(2);
    s2 = space_create(3);
    PRINT_TEST_RESULT(game_get_connection(g, s1, s2)==NULL);
    space_destroy(s1);
    space_destroy(s2);    
}

void test3_game_get_connection() {
    Game *g = NULL;
    Space *s1 = NULL, *s2 = NULL;
    g = game_create();
    s2 = space_create(3);
    PRINT_TEST_RESULT(game_get_connection(g, s1, s2)==NULL);
    game_destroy(g);
    space_destroy(s2);    
}

void test4_game_get_connection() {
    Game *g = NULL;
    Space *s1 = NULL, *s2 = NULL;
    g = game_create();
    s1 = space_create(2);
    PRINT_TEST_RESULT(game_get_connection(g, s1, s2)==NULL);
    game_destroy(g);
    space_destroy(s1);    
}

void test5_game_get_connection() {
    Game *g = NULL;
    Space *s1 = NULL, *s2 = NULL;
    g = game_create();
    s1 = space_create(2);
    s2 = space_create(3);
    PRINT_TEST_RESULT(game_get_connection(g, s1, s2)==NULL);
    game_destroy(g);
    space_destroy(s1);
    space_destroy(s2);    
}*/