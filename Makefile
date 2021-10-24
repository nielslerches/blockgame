# Makefile

CC=gcc
LIBS=glfw3 glew
INCLUDES=-Iinclude/stb
LINKS=$(pkg-config --cflags $(LIBS))
CFLAGS=-g -Wall -Wextra -pedantic -std=c17
LDFLAGS=$(shell pkg-config --libs $(LIBS))
SOURCES=$(wildcard src/*.c) $(wildcard src/*/*.c)
HEADERS=$(wildcard src/*.h) $(wildcard src/*/*.h)

.PHONY: build

build: Makefile build/main

build/main: $(SOURCES)
	$(CC) -o $@ $(INCLUDES) $(LDFLAGS) $(SOURCES) $(CFLAGS) $(LINKS)

clean:
	rm -rf build/*
