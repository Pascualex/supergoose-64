/** 
 * @brief It declares the tests for the Inventory module
 * @file inventory_test.h
 * @author Alejandro Pascual
 * @version 1.0 
 * @date 06-04-2018 (creation)
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test function for inventory creation
 * @pre A capacity of 0 or more 
 * @post Non NULL pointer to Inventory with the passed capacity
 */
void test1_inventory_create();

/**
 * @test Test function for inventory creation
 * @pre A capacity of less than 0 
 * @post NULL
 */
void test2_inventory_create();

/**
 * @test Test function for inventory destruction
 * @pre A non NULL Inventory pointer
 * @post OK
 */
void test1_inventory_destroy();

/**
 * @test Test function for inventory destruction
 * @pre A NULL Inventory pointer
 * @post ERROR
 */
void test2_inventory_destroy();

/**
 * @test Test function for adding an object
 * @pre A non full Inventory and a valid Id
 * @post OK. The inventory must contain the passed Id
 */
void test1_inventory_add();

/**
 * @test Test function for adding an object
 * @pre An invalid Id
 * @post ERROR
 */
void test2_inventory_add();

/**
 * @test Test function for adding an object
 * @pre A full inventory
 * @post ERROR
 */
void test3_inventory_add();

/**
 * @test Test function for adding an object
 * @pre A NULL Inventory pointer
 * @post ERROR
 */
void test4_inventory_add();

/**
 * @test Test function for deleting an object
 * @pre An Inventory with an Id and that Id
 * @post OK. The inventory mustn't contain the passed Id.
 */
void test1_inventory_del();

/**
 * @test Test function for deleting an object
 * @pre An Inventory with an Id and another Id
 * @post ERROR
 */
void test2_inventory_del();

/**
 * @test Test function for deleting an object
 * @pre An empty inventory and an Id
 * @post ERROR
 */
void test3_inventory_del();

/**
 * @test Test function for deleting an object
 * @pre A NULL Inventory pointer
 * @post ERROR
 */
void test4_inventory_del();

/**
 * @test Test function for setting the capacity
 * @pre A valid capacity
 * @post OK. The capacity should be the passed one.
 */
void test1_inventory_set_max_objects();

/**
 * @test Test function for setting the capacity
 * @pre A capacity of less than 0
 * @post ERROR
 */
void test2_inventory_set_max_objects();

/**
 * @test Test function for setting the capacity
 * @pre A capacity bigger than SET_MAX_IDS
 * @post ERROR
 */
void test3_inventory_set_max_objects();

/**
 * @test Test function for setting the capacity
 * @pre A NULL Inventory pointer
 * @post ERROR
 */
void test4_inventory_set_max_objects();

/**
 * @test Test function for getting an Object Id
 * @pre A non empty Inventory and a position with an Id
 * @post The Id in the specified position.
 */
void test1_inventory_get_object_id();

/**
 * @test Test function for getting an Object Id
 * @pre A non empty Inventory and a position with no Id
 * @post NO_ID
 */
void test2_inventory_get_object_id();

/**
 * @test Test function for getting an Object Id
 * @pre A NULL Inventory pointer
 * @post NO_ID
 */
void test3_inventory_get_object_id();

/**
 * @test Test function for getting the current number of Objects Ids
 * @pre A non empty Inventory
 * @post A value of more than 0
 */
void test1_inventory_get_objects_number();

/**
 * @test Test function for getting the current number of Objects Ids
 * @pre An empty Inventory
 * @post A value of 0
 */
void test2_inventory_get_objects_number();

/**
 * @test Test function for getting the current number of Objects Ids
 * @pre A NULL Inventory pointer
 * @post A value of 0
 */
void test3_inventory_get_objects_number();

/**
 * @test Test function for getting the capacity
 * @pre An Inventory with a capacity of more than 0
 * @post A capacity of more than 0
 */
void test1_inventory_get_max_objects();

/**
 * @test Test function for getting the capacity
 * @pre An Inventory with a capacity of 0
 * @post A capacity of 0
 */
void test2_inventory_get_max_objects();

/**
 * @test Test function for getting the capacity
 * @pre A NULL Inventory pointer
 * @post A capacity of 0
 */
void test3_inventory_get_max_objects();

/**
 * @test Test function for checking if an Object Id is in the Inventory
 * @pre An Inventory with an Id and that Id
 * @post TRUE
 */
void test1_inventory_check_object();

/**
 * @test Test function for checking if an Object Id is in the Inventory
 * @pre An Inventory with an Id and another Id
 * @post FALSE
 */
void test2_inventory_check_object();

/**
 * @test Test function for checking if an Object Id is in the Inventory
 * @pre A NULL Inventory pointer
 * @post FALSE
 */
void test3_inventory_check_object();

/**
 * @test Test function for checking if the Inventory is empty
 * @pre An empty Inventory
 * @post TRUE
 */
void test1_inventory_is_empty();

/**
 * @test Test function for checking if the Inventory is empty
 * @pre A non empty Inventory
 * @post FALSE
 */
void test2_inventory_is_empty();

/**
 * @test Test function for checking if the Inventory is empty
 * @pre A NULL Inventory pointer
 * @post TRUE
 */
void test3_inventory_is_empty();

/**
 * @test Test function for checking if the Inventory is full
 * @pre A full Inventory
 * @post TRUE
 */
void test1_inventory_is_full();

/**
 * @test Test function for checking if the Inventory is full
 * @pre A non full Inventory
 * @post FALSE
 */
void test2_inventory_is_full();

/**
 * @test Test function for checking if the Inventory is full
 * @pre A NULL Inventory pointer
 * @post TRUE
 */
void test3_inventory_is_full();

#endif
