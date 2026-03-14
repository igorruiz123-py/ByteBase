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

.PHONY: compile clean inject

$(BIN_PATH):
	mkdir -p $(BIN_PATH)

$(TARGET): $(FILES_OBJ)
	$(CC) $(FILES_OBJ) -o $(TARGET)

$(FUNCS_OBJ): $(FUNCS_SRC) | $(BIN_PATH)
	$(CC) $(CFLAGS) -c $(FUNCS_SRC) -o $(FUNCS_OBJ)

$(MAIN_OBJ): $(MAIN_SRC) | $(BIN_PATH)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

compile:
	@echo "[INFO] compiling source code..."
	$(MAKE) $(TARGET)
	@echo "[OK] compilation done."

clean:
	rm -f $(FILES_OBJ) $(TARGET)
	@echo "[INFO] removing source code..."
	@echo "[OK] source code removed."

inject:
	python3 automation.py
