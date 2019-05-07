/**
 * @brief It declares the tests for the space module
 *
 * @file space_tb.h
 * @author Miguel Rodríguez
 * @version 2.0
 * @date 05-05-2019
 * @copyright GNU Public License
 */

#ifndef SPACE_TB_H
#define SPACE_TB_H




 /**
  * @test Creates a space on an integer
  * @pre The integer -1 as parameter
  * @post A null pointer to the created space
  */
void test1_space_create();

/**
 * @test Creates a space on an integer
 * @pre The integer 1 as parameter
 * @post A pointer to the created space
 */
void test2_space_create();

/**
 * @test destroys a space
 * @pre A space pointer as parameter
 * @post An ERROR
 */
void test1_space_destroy();

/**
 * @test destroys a space
 * @pre A space pointer as parameter
 * @post An OK
 */
void test2_space_destroy();

/**
 * @test gets the id of the space
 * @pre A null space pointer as parameter
 * @post The integer -1
 */
void test1_space_get_id();

/**
 * @test gets the id of the space
 * @pre A space pointer as parameter
 * @post The id of the space
 */
void test2_space_get_id();

/**
 * @test sets the name of the space
 * @pre A null space pointer and a name as parameters
 * @post An ERROR
 */
void test1_space_set_name();

/**
 * @test sets the name of the space
 * @pre A space pointer and a name as parameters
 * @post An OK
 */
void test2_space_set_name();

/**
 * @test gets the description of the space
 * @pre A null space pointer as parameter
 * @post A null pointer to the description
 */
void test1_space_get_descrp();

/**
 * @test gets the description of the space
 * @pre A space pointer as parameter
 * @post A pointer to the description
 */
void test2__space_get_descrp();

/**
 * @test gets the long description of the space
 * @pre A null space pointer as parameter
 * @post A null pointer to the long description
 */
void test1_space_get_ldescrp();

/**
 * @test gets the long description of the space
 * @pre A space pointer as parameter
 * @post A pointer to the long description
 */
void test2_space_get_ldescrp();

/**
 * @test gets the objects of the space
 * @pre A null space pointer as parameter
 * @post A null pointer to the objects
 */
void test1_space_get_objects();

/**
 * @test gets the objects of the space
 * @pre A space pointer as parameter
 * @post A pointer to the objects
 */
void test2_space_get_objects();

/**
 * @test sets the description of the space
 * @pre A null space pointer and a description as parameters
 * @post An Error
 */
void test1_space_set_descrp();

/**
 * @test sets the description of the space
 * @pre A space pointer and a description as parameters
 * @post An OK
 */
void test2_space_set_descrp();

/**
 * @test sets the long description of the space
 * @pre A null space pointer and a long description as parameters
 * @post An Error
 */
void test1_space_set_ldescrp();

/**
 * @test sets the long description of the space
 * @pre A space pointer and a long description as parameters
 * @post An OK
 */
void test2_space_set_ldescrp();

/**
 * @test gets the name of the space
 * @pre A null space pointer as parameter
 * @post A null pointer to the name
 */
void test1_space_get_name();

/**
 * @test gets the name of the space
 * @pre A space pointer as parameter
 * @post A pointer to the name
 */
void test2_space_get_name();

/**
 * @test gets the link of the space
 * @pre A null space pointer as parameter
 * @post The integer -1
 */
void test1_space_get_link();

/**
 * @test gets the link of the space
 * @pre A space pointer as parameter
 * @post The integer of the link
 */
void test2_space_get_link();

/**
 * @test sets the link of the space
 * @pre A null space pointer and an integer as parameters
 * @post An ERROR
 */
void test1_space_set_link();

/**
 * @test sets the link of the space
 * @pre A space pointer and an integer as parameters
 * @post An OK
 */
void test2_space_set_link();

/**
 * @test deletes an object of the space
 * @pre A null space pointer and an integer as parameters
 * @post An ERROR
 */
void test1_space_del_object();

/**
 * @test deletes an object of the space
 * @pre A space pointer and an integer as parameters
 * @post An OK
 */
void test2_space_del_object();

/**
 * @test adds an object in the space
 * @pre A null space pointer and an integer as parameters
 * @post An ERROR
 */
void test1_space_add_object();

/**
 * @test adds an object in the space
 * @pre A space pointer and an integer as parameters
 * @post An OK
 */
void test2_space_add_object();

/**
 * @test gets an object of the space
 * @pre A null space pointer and an integer as parameters
 * @post The integer -1
 */
void test1_space_get_object();

/**
 * @test gets an object of the space
 * @pre A null space pointer and an integer as parameters
 * @post The id of the object
 */
void test2_space_get_object();

/**
 * @test sees if an object is in the space
 * @pre A null space pointer and an integer as parameters
 * @post An ERROR
 */
void test1_space_has_object();

/**
 * @test sees if an object is in the space
 * @pre A space pointer and an integer as parameters
 * @post An OK
 */
void test2_space_has_object();

/**
 * @test sets the picture of the space
 * @pre A null space pointer and a char pinter as parameters
 * @post An ERROR
 */
void test1_space_set_picture();

/**
 * @test sets the picture of the space
 * @pre A space pointer and a char pinter as parameters
 * @post An OK
 */
void test2_space_set_picture();

/**
 * @test gets the picture of the space
 * @pre A null space pointer as parameter
 * @post A null pointer
 */
void test1_space_get_picture();

/**
 * @test gets the picture of the space
 * @pre A space pointer as parameter
 * @post A pointer
 */
void test2_space_get_picture();

/**
 * @test sets the light of the space
 * @pre A null space pointer and a bollean as parameters
 * @post An ERROR
 */
void test1_space_set_light();

/**
 * @test sets the light of the space
 * @pre A space pointer and a bollean as parameters
 * @post An OK
 */
void test2_space_set_light();

/**
 * @test changes the state of the space's light
 * @pre A null space pointer as parameter
 * @post An ERROR
 */
void test1_space_toggle_light();

/**
 * @test changes the state of the space's light
 * @pre A space pointer as parameter
 * @post An OK
 */
void test2_space_toggle_light();

/**
 * @test gets the space's light
 * @pre A null space pointer as parameter
 * @post An ERROR
 */
void test1_space_get_light();

/**
 * @test gets the space's light
 * @pre A space pointer as parameter
 * @post An OK
 */
void test2_space_get_light();



#endif
