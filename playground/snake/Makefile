ifeq ($(OS),Windows_NT)
	APP_NAME = main.exe
else
	APP_NAME = main
endif
MAIN = main

CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -pedantic
DEPS =

BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)

SOURCES = $(filter-out main.c, $(wildcard *.c))
OBJECTS = $(patsubst ./%.c,$(OBJ_DIR)/%.o,$(SOURCES))

$(APP_NAME): $(BIN_DIR)/$(APP_NAME)

$(OBJ_DIR)/%.o: %.c
	if not exist $(@D) mkdir $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN_DIR)/$(APP_NAME): $(OBJECTS) $(OBJ_DIR)/$(MAIN).o
	if not exist $(@D) mkdir $(@D)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run

run: $(BIN_DIR)/$(APP_NAME)
	./$(BIN_DIR)/$(APP_NAME)

ifeq ($(OS),Windows_NT)
clean:
	del /f /s /q $(OBJ_DIR) $(BIN_DIR)
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
else
# TODO: add linux support
endif
