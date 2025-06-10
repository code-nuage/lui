TARGET = lui.so
SRC = lui.c run.c exit.c graphics.c colors.c keyboard.c buffer.c

LUA_VERSION = 5.1
LUA_INC = -I/usr/include/lua5.1
LUA_LIB = -llua5.1
TAGS = -O2 -shared -fPIC -Wall -Wextra -std=c99 -D_XOPEN_SOURCE=700

all:
	$(CC) $(TAGS) $(SRC:%=lui/%) -o $(TARGET) $(LUA_INC) $(LUA_LIB)

clean:
	rm -f *.so lui/*.o