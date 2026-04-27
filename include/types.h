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

#define WORD_SIZE 1000 /*!< size of the words*/
#define NO_ID -1       /*!< used when an ID does not exist*/

typedef long Id;

typedef enum { FALSE, TRUE } Bool;          /*!< Whether it is true or false, used when returning booleans in a function*/

typedef enum { ERROR, OK } Status;          /*!< Whether a function goes well or has an error*/

typedef enum { NO_DIR = -1, N, S, E, W } Direction;      /*!< Whether a space is connected north, south, east or west or here is no connection*/

typedef enum {NO_CAT = -1, Venom, Elixir, Strenght, Cursed} Category; /*!< Category of the objects when you use them */

#endif