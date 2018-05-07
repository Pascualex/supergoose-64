/** 
 * @brief It declares the tests for the Game Reader module
 * @file game_reader_test.h
 * @author Alejandro Pascual
 * @version 1.0 
 * @date 07-04-2018 (creation)
 * @copyright GNU Public License
 */

#ifndef GAME_READER_TEST_H
#define GAME_READER_TEST_H

/**
 * @test Test function for loading Spaces
 * @pre A valid Game and a .dat with Spaces defined
 * @post OK. The Spaces should be loaded in the Game
 */
void test1_game_reader_load_spaces();

/**
 * @test Test function for loading Spaces
 * @pre A valid Game and a .dat with no Spaces defined
 * @post OK. There should be no Spaces loaded
 */
void test2_game_reader_load_spaces();

/**
 * @test Test function for loading Spaces
 * @pre An invalid Game and a valid .dat
 * @post ERROR
 */
void test3_game_reader_load_spaces();

/**
 * @test Test function for loading Spaces
 * @pre A valid Game and an non-existent .dat 
 * @post ERROR
 */
void test4_game_reader_load_spaces();

/**
 * @test Test function for loading Players
 * @pre A valid Game and a .dat with Players defined
 * @post OK. The Players should be loaded in the Game
 */
void test1_game_reader_load_players();

/**
 * @test Test function for loading Players
 * @pre A valid Game and a .dat with no Players defined
 * @post OK. There should be no Players loaded
 */
void test2_game_reader_load_players();

/**
 * @test Test function for loading Players
 * @pre An invalid Game and a valid .dat
 * @post ERROR
 */
void test3_game_reader_load_players();

/**
 * @test Test function for loading Players
 * @pre A valid Game and an non-existent .dat 
 * @post ERROR
 */
void test4_game_reader_load_players();

/**
 * @test Test function for loading Objects
 * @pre A valid Game and a .dat with Objects defined
 * @post OK. The Objects should be loaded in the Game
 */
void test1_game_reader_load_objects();

/**
 * @test Test function for loading Objects
 * @pre A valid Game and a .dat with no Objects defined
 * @post OK. There should be no Objects loaded
 */
void test2_game_reader_load_objects();

/**
 * @test Test function for loading Objects
 * @pre An invalid Game and a valid .dat
 * @post ERROR
 */
void test3_game_reader_load_objects();

/**
 * @test Test function for loading Objects
 * @pre A valid Game and an non-existent .dat 
 * @post ERROR
 */
void test4_game_reader_load_objects();

/**
 * @test Test function for loading Links
 * @pre A valid Game and a .dat with Links defined
 * @post OK. The Links should be loaded in the Game
 */
void test1_game_reader_load_links();

/**
 * @test Test function for loading Links
 * @pre A valid Game and a .dat with no Links defined
 * @post OK. There should be no Links loaded
 */
void test2_game_reader_load_links();

/**
 * @test Test function for loading Links
 * @pre An invalid Game and a valid .dat
 * @post ERROR
 */
void test3_game_reader_load_links();

/**
 * @test Test function for loading Links
 * @pre A valid Game and an non-existent .dat 
 * @post ERROR
 */
void test4_game_reader_load_links();

#endif