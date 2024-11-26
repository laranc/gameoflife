CC 		 ?= clang
CFLAGS ?= -O2
RAYLIB ?= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC := $(wildcard src/*.c)
DIR := ./build
OUT := $(DIR)/gameoflife

default: $(DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(RAYLIB)

debug: $(DIR)
	$(CC) $(CFLAGS) -g $(SRC) -o $(OUT)-debug $(RAYLIB) -DDEBUG
	./$(OUT)-debug

run: $(OUT)
	./$(OUT)

clean:
	rm -rf $(DIR)
