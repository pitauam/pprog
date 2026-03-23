/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /*size of the words*/
#define NO_ID -1       /*used when an ID */

typedef long Id;

typedef enum { FALSE, TRUE } Bool;          /*!< whether it is true or false, used when returning booleans in a function*/

typedef enum { ERROR, OK } Status;          /*!< whether a function goes well or has an error*/

typedef enum { UNKNOWN, N, S, E, W } Direction;      /*!< whether a space is connected north, south, east or west*/

#endif