/** 
 * @brief It declares the tests for the command module
 * @file command_test.h
 * @author Victor Yrazusta
 * @version 1.0 
 * @date 07-04-2018 (creation)
 * @copyright GNU Public License
 */

#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

/**
 * @test Test command creation
 * @pre Nothing
 * @post Non NULL pointer to command
 */
void test1_command_create();

/**
 * @test Test command destruction
 * @pre A non NULL pointer
 * @post Output == OK
 */
void test1_command_destroy();

/**
 * @test Test command destruction
 * @pre A NULL pointer
 * @post Output == ERROR
 */
void test2_command_destroy();

/**
 * @test Test command input
 * @pre A correct command pointer and file
 * @post Output == OK
 */
void test1_command_get_user_input();

/**
 * @test Test command input
 * @pre An incorrect command pointer but a correct file
 * @post Output == ERROR
 */
void test2_command_get_user_input();

/**
 * @test Test command input
 * @pre A correct command and file
 * @post Registered command == Passed command
 */
void test3_command_get_user_input();

/**
 * @test Test command for reading command->command setting
 * @pre A correct command and file
 * @post Read command == Passed command
 */
void test1_command_get_command();

/**
 * @test Test command for reading command->command setting
 * @pre A NULL pointer to command
 * @post Read command == NO_CMD
 */
void test2_command_get_command();

/**
 * @test Test command for reading command->info setting
 * @pre A correct command and file
 * @post Read info == Passed info
 */
void test1_command_get_info();

/**
 * @test Test command for reading command->info setting
 * @pre A NULL pointer to command
 * @post Read info == NULL
 */
void test2_command_get_info();

#endif
