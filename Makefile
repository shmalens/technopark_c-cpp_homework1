TARGET = composition.out

SRC_DIR = ./project/src/
INCLUDE = ./project/include/

SRC = $(SRC_DIR)main.c\
      $(SRC_DIR)composition.c\
      $(SRC_DIR)playlist.c\

VALGRIND_OPIONS = --tool=memcheck --leak-check=full  --show-leak-kinds=all

all: build

build:
	$(CC) -o $(TARGET) -I $(INCLUDE) $(SRC)

memcheck:
	valgrind $(VALGRIND_OPIONS) ./$(TARGET)

clean:
	rm -rf $(TARGET)
