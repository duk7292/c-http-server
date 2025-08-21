TARGET := out/main
SRC    := $(wildcard src/*.c)

CFLAGS = -Wall -Wextra -g -O0 #-fsanitize=address
INCLUDES = -Iinclude

all:
	mkdir -p out
	gcc $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
