/**
 * @brief Set module
 *
 * @file set.c
 * @author Santiago Pita
 * @version 0
 * @date 17-02-2026
 */

#include "set.h"
#define SIZE 256 /*64 Ids */

struct Set
{
    Id ids[SIZE];   /*Array of static Ids*/
    int n_ids;      /*Keeps track of the number of ids in the Set*/
};



