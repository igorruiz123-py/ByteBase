RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

CC = gcc

CFLAGS = -Iinclude

BIN_PATH = output/bin

SRC_PATH = src

FILES_OBJ = $(BIN_PATH)/funcs.o $(BIN_PATH)/main.o

TARGET = $(BIN_PATH)/bytebase

MAIN_OBJ = $(BIN_PATH)/main.o

FUNCS_OBJ = $(BIN_PATH)/funcs.o

MAIN_SRC = $(SRC_PATH)/main.c

FUNCS_SRC = $(SRC_PATH)/funcs.c

.PHONY: compile rmcode inject build rmdb

$(BIN_PATH):
	mkdir -p $(BIN_PATH)

$(TARGET): $(FILES_OBJ)
	$(CC) $(FILES_OBJ) -o $(TARGET)

$(FUNCS_OBJ): $(FUNCS_SRC) | $(BIN_PATH)
	$(CC) $(CFLAGS) -c $(FUNCS_SRC) -o $(FUNCS_OBJ)

$(MAIN_OBJ): $(MAIN_SRC) | $(BIN_PATH)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

compile:
	@printf "$(YELLOW) [INFO] compiling source code... $(RESET) \n"
	$(MAKE) $(TARGET)
	@printf "$(GREEN) [OK] compilation done. $(RESET) \n"

rmcode:
	@printf "$(YELLOW) [INFO] granting executable permission for 'rmcode.sh'... $(RESET) \n"
	chmod +x rmcode.sh
	@printf "$(GREEN) [OK] permission granted. $(RESET) \n"
	./rmcode.sh

inject:
	python3 automation.py

build:
	@printf "$(YELLOW) [INFO] granting executable permission for 'build.sh'... $(RESET) \n"
	chmod +x build.sh
	@printf "$(GREEN) [OK] permission granted. $(RESET) \n"
	./build.sh

rmdb:
	@printf "$(YELLOW) [INFO] granting executable permission for 'rmdb.sh'... $(RESET) \n"
	chmod +x rmdb.sh
	@printf "$(GREEN) [OK] permission granted. $(RESET) \n"
	./rmdb.sh