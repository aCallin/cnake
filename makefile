CC = gcc
SDL_CFLAGS = $(shell sdl2-config --cflags)
SRC = src/*.c
OUT = cnake.out
SDL_LIBS = $(shell sdl2-config --libs)

.PHONY: all
all:
	$(CC) $(SDL_CFLAGS) $(SRC) -o $(OUT) $(SDL_LIBS)

.PHONY: run
run: all
	./$(OUT)

.PHONY: clean
clean:
	rm -rf $(OUT)
