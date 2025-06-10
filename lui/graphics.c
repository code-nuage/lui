#include "graphics.h"
#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <lua.h>
#include <lauxlib.h>
#include <wchar.h>
#include <locale.h>

#define ESC "\x1b"

int lui_graphics_clear(lua_State *L) {
    printf(ESC "c");
    return 0;
}

int lui_graphics_draw(lua_State *L) {
    // Get UTF-8 text from Lua and convert to wide string
    const char *text = luaL_checkstring(L, 1);

    size_t len = mbstowcs(NULL, text, 0);
    if (len == (size_t)-1) {
        return luaL_error(L, "Invalid UTF-8 input");
    }

    wchar_t *wtext = malloc((len + 1) * sizeof(wchar_t));
    if (!wtext) {
        return luaL_error(L, "Memory allocation failed");
    }

    mbstowcs(wtext, text, len + 1);

    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    wchar_t *saveptr;
    wchar_t *line = wcstok(wtext, L"\n", &saveptr);
    int line_num = 0;

    while (line && y + line_num < MAX_HEIGHT) {
        int i = 0;
        while (line[i] != L'\0' && x + i < MAX_WIDTH) {
            screen_buffer[y + line_num][x + i] = line[i];
            i++;
        }
        line = wcstok(NULL, L"\n", &saveptr);
        line_num++;
    }

    free(wtext);
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
