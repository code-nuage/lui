#include "keyboard.h"

#include <string.h>

#include <lua.h>
#include <lauxlib.h>

char * get_lui_input(lua_State *L) {
    lua_getglobal(L, "lui");
    
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return NULL;
    }

    lua_getfield(L, -1, "input");
    char *input = NULL;
    if (lua_isstring(L, -1)) {
        const char *tmp = lua_tostring(L, -1);
        input = strdup(tmp);
    }

    lua_pop(L, 2);                                                             // Pop 'input' and 'lui'
    return input;
}

// --+ LUA INTERFACE +--
int lui_keyboard_is_down(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);

    if (get_lui_input(L) == key) {
        lua_pushboolean(L, 1);
    }

    return 1;
}