TARGET := out/main
SRC    := $(wildcard *.c)

all:
	mkdir -p out
	gcc $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

