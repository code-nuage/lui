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

    // --+ KEYBOARD +--
    lua_newtable(L);

    // IS_DOWN
    lua_pushcfunction(L, lui_keyboard_is_down);
    lua_setfield(L, -2, "is_down");

    lua_setfield(L, -2, "keyboard");

    // --+ SET _G.lui +--
    lua_pushvalue(L, -1);
    lua_setglobal(L, "lui");

    return 1;
}
