CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g -O3
CFLAGS = -I../server/include/
# LFLAGS = -L../server/lib/
LDFLAGS = -pthread -lenet

SRC_DIR = src/cpp
OBJ_DIR = bin
TST_DIR = tests

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)


EXEC = client4


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LFLAGS) -o $@ -c $<


clean:
	@rm -Rf $(OBJ) $(EXEC)
	@echo "Removed obj and exe from client"

distclean: clean


.PHONY: clean distclean

.depend:
	$(CC) $(CCFLAGS) -MM $(SRC) > .depends
-include .depends
