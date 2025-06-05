TARGET = lui.so
SRC = lui.c run.c exit.c graphics.c colors.c keyboard.c

LUA_VERSION = 5.1
LUA_INC = -I/usr/include/lua5.1
LUA_LIB = -llua5.1

all:
	$(CC) -O2 -Wall -shared -fPIC $(SRC:%=lui/%) -o $(TARGET) $(LUA_INC) $(LUA_LIB)

clean:
	rm -f *.so