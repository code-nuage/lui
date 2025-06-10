#include "run.h"
#include "buffer.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include <lua.h>

#define ESC "\x1b"

static struct termios orig_termios;

static int get_lui_state(lua_State *L) {
    lua_getglobal(L, "lui");

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    lua_getfield(L, -1, "state");
    int state = 0;
    if (lua_isboolean(L, -1)) {
        state = lua_toboolean(L, -1);
    }

    lua_pop(L, 2);                                                             // Pop 'state' and 'lui'
    return state;
}

static void set_lui_state(lua_State *L, int value) {
    lua_getglobal(L, "lui");

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushboolean(L, value);
    lua_setfield(L, -2, "state");

    lua_pop(L, 1);                                                             // Pop 'lui'
}

static void restore() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    printf(ESC "c");
    printf(ESC "[0m");                                                         // Reset colors
    printf(ESC "[?25h");                                                       // Show cursor
    fflush(stdout);
}

static int call_optional_function(lua_State *L, const char *name) {
    lua_getglobal(L, "lui");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    lua_getfield(L, -1, name);
    lua_remove(L, -2);

    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1);
        return 0;
    }

    if (lua_pcall(L, 0, 0, 0) != 0) {
        restore();
        const char *err = lua_tostring(L, -1);

        char msg[512];
        snprintf(msg, sizeof(msg), "%s", err);

        lua_pop(L, 1);
        lua_pushstring(L, msg);
        return lua_error(L);
    }

    return 1;
}

static void set_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    setvbuf(stdout, NULL, _IONBF, 0);
    printf(ESC "[?25l");                                                       // Hide cursor
    fflush(stdout);
}

static void set_lui_input(lua_State *L, const char *input) {
    lua_getglobal(L, "lui");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return;
    }

    lua_pushstring(L, input);
    lua_setfield(L, -2, "input");

    lua_pop(L, 1);
}

static char *parse_ansi() {
    char buf[16] = {0};
    int i = 0;

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        buf[i++] = c;

        if (i >= 15) break;

        if (i == 1 && c != '\x1b') break;

        if (i >= 2) {
            unsigned char byte = (unsigned char)c;
            if (byte >= '@' && byte <= '~' && byte != '[') {
                break;
            }
        }
    }

    return strdup(buf);
}

wchar_t *current_screen[MAX_HEIGHT][MAX_WIDTH];

void init_current_screen() {
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            current_screen[y][x] = malloc(sizeof(wchar_t));
            *current_screen[y][x] = L' ';
        }
    }
}

void free_current_screen() {
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            free(current_screen[y][x]);
        }
    }
}

void reset_buffer() {
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            screen_buffer[y][x] = L' ';
        }
    }
}

void flush_buffer() {
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            if (screen_buffer[y][x] != *current_screen[y][x]) {
                *current_screen[y][x] = screen_buffer[y][x];
                if (screen_buffer[y][x] < 32 || screen_buffer[y][x] > 126) {
                    wprintf(L"\033[%d;%dH*", y + 1, x + 1); // caractère de debug visible
                } else {
                    wprintf(L"\033[%d;%dH%lc", y + 1, x + 1, *current_screen[y][x]);
                }
            }
        }
    }
    fflush(stdout);
}

// --+ LUA INTERFACE +--
int lui_run(lua_State *L) {
    setlocale(LC_ALL, "");
    fwide(stdout, 1); // 1 = wide orientation for stdout
    set_raw_mode();
    set_lui_state(L, 1);

    call_optional_function(L, "load");
    init_current_screen();

    while (get_lui_state(L)) {
        reset_buffer();
        call_optional_function(L, "draw");
        printf(ESC "[?25l");                                                   // Hide cursor
        flush_buffer();

        char *input = parse_ansi();
        if (input) {
            set_lui_input(L, input);
            free(input);
        }

        call_optional_function(L, "update");
    }

    free_current_screen();
    restore();
    return 0;
}
