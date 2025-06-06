#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <lua.h>
#include <lauxlib.h>

#define ESC "\x1b"

int lui_graphics_clear(lua_State *L) {
    printf(ESC "c");
    return 0;
}

int lui_graphics_draw(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    char *text_copy = strdup(text);
    if (!text_copy) {
        luaL_error(L, "Memory allocation failed");
    }

    char *line = strtok(text_copy, "\n");
    int line_num = 0;

    while (line != NULL) {
        printf("\033[%d;%dH", y + line_num, x);
        printf("%s", line);

        line = strtok(NULL, "\n");
        line_num++;
    }

    free(text_copy);
    return 0;
}

int lui_graphics_get_dimensions(lua_State *L) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return luaL_error(L, "Failed to get terminal size");
    }

    lua_pushinteger(L, w.ws_col);
    lua_pushinteger(L, w.ws_row);
    return 2;
}

int lui_graphics_get_width(lua_State *L) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return luaL_error(L, "Failed to get terminal size");
    }

    lua_pushinteger(L, w.ws_col);
    return 1;
}

int lui_graphics_get_height(lua_State *L) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return luaL_error(L, "Failed to get terminal size");
    }

    lua_pushinteger(L, w.ws_row);
    return 1;
}