TARGET = composition.out

SRC_DIR = ./project
INCLUDE = ./project/include

SRC = $(SRC_DIR)/src/main.c\
      $(SRC_DIR)/src/composition.c\
      $(SRC_DIR)/src/playlist.c\
      $(SRC_DIR)/src/dataloader.c\
      $(SRC_DIR)/src/compilation.c

ALL_FILES = $(SRC)\
            $(INCLUDE)/composition.h\
            $(INCLUDE)/playlist.h\
            $(INCLUDE)/dataloader.h\
            $(INCLUDE)/compialtion.h

VALGRIND_OPIONS = -s --tool=memcheck --leak-check=full --track-origins=yes  --show-leak-kinds=all
COMPILER_OPTIONS = -Wall -O0 -ggdb3 -Wextra -Werror

all: build

check: memcheck staticcheck

build:
	$(CC) $(COMPILER_OPTIONS) -o $(TARGET) -I $(INCLUDE) $(SRC)

memcheck:
	valgrind $(VALGRIND_OPIONS) ./$(TARGET)

staticcheck:
	cppcheck $(ALL_FILES)

clean:
	rm -rf $(TARGET)
