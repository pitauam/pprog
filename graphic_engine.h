/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief creates the graphic engine, reserved the memory and initialice the variables
 * @author Profesores PPROG
 *
 * @return the graphic engine if every thing was correct or NULL if something was wrong
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief destroys the ge, frees the memory
 * @author Profesores PPROG
 *
 * @param ge pointer to the graphic engine
 * @return the graphic engine if every thing was correct or NULL if something was wrong
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief displays the visuals of the map creating the diferent areas
 * @author Profesores PPROG
 *
 * @param ge pointer to the graphic engine
 * @param game pointer to the game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
