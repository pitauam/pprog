/**
 * @brief Implements the inventory module
 *
 * @file inventory.h
 * @author Mario Rodriguez
 * @version 1
 * @date 13-04-2026
 */
#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

#define MAX_OBJ 2

typedef struct _Inventory Inventory;


/**
 * @brief Creates a new inventory, allocating memory and initialazing all of its parameters
 * @author Mario Rodriguez
 *
 * @return a new initialized inventory
 */
Inventory* inventory_create();

/**
 * @brief It destroys a inventory, freeing the allocated memory
 * @author Mario Rodriguez
 *
 * @param iventory a pointer to the inventory that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_destroy(Inventory *inventory);

/**
 * @brief It sets the max objects of a inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @param max a int with the valeu of max objects
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_set_max_obj(Inventory* inventory, int max);

/**
 * @brief It gets the max objects of a inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @return the max space of theinventory
 */
int inventory_get_max_obj(Inventory* inventory);

/**
 * @brief It adds a object to the inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @param id an Id, specifying the object to place in the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_add_object(Inventory* inventory, Id id);

/**
 * @brief It removes a object to the inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @param id an Id, specifying the object to place in the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_remove_object(Inventory* inventory, Id id);

/**
 * @brief It gets whether the inventory has an object or not
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @return True if there is an object, False if there is no object
 */
Bool inventory_is_empty(Inventory* inventory);

/**
 * @brief It gets whether the inventory is full or not
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @return True if is full, False if otherwise
 */
Bool inventory_is_full(Inventory* inventory);

/**
 * @brief It gets the object from an inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @param pos position in the array
 * @return id of the object or NO_ID
 */
Id inventory_get_object_id(Inventory* inventory, int pos);

/**
 * @brief It finds the id of an object in a inventory
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @param id id of the object you want to find
 * @return True if it finds the object, otherwise False
 */
Bool inventory_find_object(Inventory* inventory, Id id);

/**
 * @brief It gets the number of the objects of the inventory
 * @author Mario Rodriguez
 *
 * @param Inventory a pointer to the inventory
 * @return an int with the number of objects in the inventory
 */
int inventory_get_n_objects(Inventory* inventory);

/**
 * @brief It prints the inventory information
 * @author Mario Rodriguez
 *
 * @param inventory a pointer to the inventory
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory* inventory);

#endif