/** 
 * @brief It declares the tests for the test module
 * @file link_test.h
 * @author Victor Yrazusta
 * @version 1.0 
 * @date 05-03-2018 (creation)
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @test Test link creation
 * @pre Link ID 
 * @post Non NULL pointer to link
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre Link ID
 * @post Link_ID == Supplied Link Id
 */
void test2_link_create();

/**
 * @test Test link creation
 * @pre Link ID and Link Status
 * @post Link_ID == Supplied Link Id and Link_Status == Supplied Link Status
 */
void test3_link_create();

/**
 * @test Test link creation
 * @pre Link ID and Link Status and two Space IDs
 * @post Link_ID == Supplied Link Id and Link_Status == Supplied Link Status and both Spaces_IDs == Supplied Space IDs
 */
void test4_link_create();

/**
 * @test Test function for link->name setting
 * @pre A string
 * @post Output == OK
 */
void test1_link_set_name();

/**
 * @test Test function for link->name setting
 * @pre A null link pointer
 * @post Output == ERROR
 */
void test2_link_set_name();

/**
 * @test Test function for link->name setting
 * @pre A null string pointer
 * @post Output == ERROR
 */
void test3_link_set_name();

/**
 * @test Test function for link->space1 and link->space2 settings
 * @pre Two correct Space IDs
 * @post Output == OK
 */
void test1_link_add_space();

/**
 * @test Test function for link->space1 and link->space2 settings
 * @pre One correct Space ID amd one incorrect
 * @post Output == ERROR for the incorrect one and == OK for the correct one
 */
void test2_link_add_space();

/**
 * @test Test function for link->space1 and link->space2 settings
 * @pre A NULL Link pointer
 * @post Output == ERROR
 */
void test3_link_add_space();

/**
 * @test Test function for link->status setting
 * @pre A link status
 * @post Output == OK
 */
void test1_link_set_status();

/**
 * @test Test function for link->status setting
 * @pre A NULL Link pointer
 * @post Output == ERROR
 */
void test2_link_set_status();

/**
 * @test Test function for reading link->id setting
 * @pre A Correct Link Id
 * @post Registered ID == Given ID
 */
void test1_link_get_id();

/**
 * @test Test function for reading link->id setting
 * @pre A NULL Link pointer
 * @post Output == NO_ID
 */
void test2_link_get_id();

/**
 * @test Test function for reading link->name setting
 * @pre A Correct string
 * @post Registered name == Given string
 */
void test1_link_get_name();

/**
 * @test Test function for reading link->name setting
 * @pre A NULL Link pointer
 * @post Registered name == NULL
 */
void test2_link_get_name();

/**
 * @test Test function for reading link->status setting
 * @pre A correct Link pointer
 * @post Registered status == Given status
 */
void test1_link_get_status();

/**
 * @test Test function for reading link->status setting
 * @pre A incorrect Link pointer
 * @post Registered status != Given status
 */
void test2_link_get_status();

/**
 * @test Test function for link_get_other_side
 * @pre Two correct Space IDs
 * @post Registered IDs == Given IDs
 */
void test1_link_get_other_side();

/**
 * @test Test function for link_get_other_side
 * @pre One correct Space ID and one incorrect
 * @post Registered IDs != Given IDs
 */
void test2_link_get_other_side();

/**
 * @test Test function for link_get_other_side
 * @pre A NULL Link pointer
 * @post Registered IDs != Given IDs
 */
void test3_link_get_other_side();

/**
 * @test Test function for destroying links
 * @pre A correct Link pointer
 * @post Output == OK
 */
void test1_link_destroy();

/**
 * @test Test function for destroying links
 * @pre A NULL Link pointer
 * @post Output == ERROR
 */
void test2_link_destroy();

#endif
