CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g -O3
CFLAGS = -I../include/
# LFLAGS = -L../lib/
LDFLAGS = -pthread -lenet


SRC_DIR = src
OBJ_DIR = bin
MAIN = $(SRC_DIR)/test.cpp 
LIB_DIR = ../lib

SRC = $(filter-out $(MAIN),  $(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)


SRC = $(wildcard ../$(SRC_DIR)/*.cpp)
OBJ = $(SRC:../$(SRC_DIR)/%.cpp=../$(OBJ_DIR)/%.o)
SRC_TST = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_TST = $(filter-out ../$(OBJ_DIR)/$(EXEC).o, $(OBJ)) $(SRC_TST:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)


EXEC_TEST = test


all: $(EXEC_TEST)

$(EXEC_TEST): $(OBJ)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LFLAGS) $(filter-out ../bin/main.o, $(OBJ)) $(MAIN) -o $@ $(LDFLAGS)

../$(OBJ_DIR)/%.o: ../$(SRC_DIR)/%.cpp
	@mkdir -p ../$(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<


clean:
	@rm -Rf $(OBJ_DIR) $(EXEC_TEST)
	@echo "Removed obj and exe from server/test"

veryclean: clean
	@rm -f $(SAVES)
	@echo "Removed save files from server/test"

.PHONY: clean veryclean

.depend:
	$(CC) $(CCFLAGS) -MM $(SRC) > .depends
-include .depends
