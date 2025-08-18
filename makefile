TARGET := out/main
SRC    := $(wildcard *.c)

CFLAGS = -Wall -Wextra -g -O0 #-fsanitize=address
all:
	mkdir -p out
	gcc $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
