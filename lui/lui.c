#include <lua.h>
#include <lauxlib.h>

#include "run.h"
#include "exit.h"
#include "graphics.h"
#include "colors.h"
#include "keyboard.h"

int luaopen_lui(lua_State *L) {
    lua_newtable(L);

    // --+ RUN +--
    lua_pushcfunction(L, lui_run);
    lua_setfield(L, -2, "run");

    // --+ EXIT +--
    lua_pushcfunction(L, lui_exit);
    lua_setfield(L, -2, "exit");

    // --+ GRAPHICS +--
    lua_newtable(L);

    // CLEAR
    lua_pushcfunction(L, lui_graphics_clear);
    lua_setfield(L, -2, "clear");

    // DRAW
    lua_pushcfunction(L, lui_graphics_draw);
    lua_setfield(L, -2, "draw");

    // GET_DIMENSIONS
    lua_pushcfunction(L, lui_graphics_get_dimensions);
    lua_setfield(L, -2, "get_dimensions");

    // GET_WIDTH
    lua_pushcfunction(L, lui_graphics_get_width);
    lua_setfield(L, -2, "get_width");

    // GET_HEIGHT
    lua_pushcfunction(L, lui_graphics_get_height);
    lua_setfield(L, -2, "get_height");

    lua_setfield(L, -2, "graphics");

    return 1;
}
