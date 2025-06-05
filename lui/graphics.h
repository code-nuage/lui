#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <lua.h>

int lui_graphics_clear(lua_State *L);
int lui_graphics_draw(lua_State *L);
int lui_graphics_get_dimensions(lua_State *L);
int lui_graphics_get_width(lua_State *L);
int lui_graphics_get_height(lua_State *L);

#endif