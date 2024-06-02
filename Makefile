CC := gcc
CFLAGS := -Wall -Wextra
CFLAGS += -Ilib/glad/include -Ilib/glfw/include -Ilib/stb 
LDFLAGS = lib/glad/src/glad.o 
LDFLAGS += -lglfw3 -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa

SRC := $(wildcard src/*.c)
OBJS := $(SRC:.c=.o)
BIN := bin

.PHONY: all clean

all: dirs libs project

libs:
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/glfw && cmake . && make

dirs:
	mkdir -p ./$(BIN)

project: $(OBJS)
	$(CC) -o $(BIN)/main $^ $(LDFLAGS)

run: all
	$(BIN)/main

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJS)
