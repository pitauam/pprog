/**
 * @brief It implements the interface data strucutre
 *
 * @file interface_data.c
 * @author Profesores PPROG, Samuel Manzorro and Marta López
 * @version 0
 * @date 12-04-2026
 * @copyright GNU Public License
 */

#ifndef INTERFACE_DATA_H
#define INTERFACE_DATA_H

#include "command.h"
#include "types.h"
#include "player.h"


typedef struct _InterfaceData InterfaceData;

/**
 * @brief It creates an interface data, allocating its memory
 * @author Samuel Manzorro
 * 
 * @return a new interface data, with its memory allocated
 */
InterfaceData *interface_data_create();

/**
 * @brief It destroys an interface data
 * @author Samuel Manzorro
 * 
 * @param intDat a pointer to the interface data
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status interface_data_destroy(InterfaceData *intData);

/**
 * @brief It gets the last command executed in the game
 * @author Samuel Manzorro
 *
 * @param intDat a pointer to the interface data
 * @return a pointer to the last command structure
 */
Command* interface_data_get_last_command(InterfaceData *intDat) ;

/**
 * @brief It sets the last command executed in the game
 * @author Samuel Manzorro
 *
 * @param intDat a pointer to the interface data
 * @param command a pointer to the command structure to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status interface_data_set_last_command(InterfaceData *intDat, Command *command);

/**
 * @brief It gets the last status of the last command executed in the game
 * @author Samuel Manzorro
 * 
 * @param intDat a pointer to the interface data
 * @return the last status of the last comand executed in the game
 */
Status interface_data_get_last_status(InterfaceData *intDat);


/**
 * @brief It sets the last status of the last command executed in the game
 * @author Samuel Manzorro
 * 
 * @param intDat a pointer to the interface data
 * @param status the status to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status interface_data_set_last_status(InterfaceData *intDat, Status status);

/**
 * @brief It gets the interface data message
 * @author Samuel Manzorro
 *
 * @param intDat a pointer to the interface data
 * @return the interface data message
 */
char *interface_data_get_message(InterfaceData *intDat);

/**
 * @brief It sets the interface data message
 * @author Samuel Manzorro
 *
 * @param intDat a pointer to the interface data
 * @param msg the new message to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status interface_data_set_message(InterfaceData *intDat, const char *msg);

/**
 * @brief It prints the interface data data
 * @author Marta López
 * 
 * @param intDat a pointer to the interface data
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status interface_data_print(InterfaceData *intData) ;

#endif