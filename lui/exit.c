#include "exit.h"
#include <lua.h>

int lui_exit(lua_State *L) {
    lua_getglobal(L, "lui");

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    lua_pushboolean(L, 0);
    lua_setfield(L, -2, "state");

    lua_pop(L, 1);                                                             // Flush "lui"
    return 1;
}