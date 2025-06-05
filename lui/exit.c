#include "exit.h"
#include <lua.h>

int lui_exit(lua_State *L) {
    lua_getglobal(L, "lui");

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    lua_getfield(L, -1, "state");
    lua_pushboolean(L, 0);

    lua_pop(L, 2);
    return 1;
}