TARGET = test

SRC_DIR = ./project/src/
INCLUDE = ./project/include/

SRC = $(SRC_DIR)main.c\
      $(SRC_DIR)composition.c\
      $(SRC_DIR)playlist.c\

all: build memcheck

build:
	$(CC) -o $(TARGET) -I $(INCLUDE) $(SRC)

memcheck:
	valgrind --tool=memcheck --leak-check=full ./$(TARGET)
