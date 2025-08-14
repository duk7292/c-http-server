TARGET := out/main
SRC    := $(wildcard *.c)

CFLAGS = -Wall -Wextra -g -O0
all:
	mkdir -p out
	gcc $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
