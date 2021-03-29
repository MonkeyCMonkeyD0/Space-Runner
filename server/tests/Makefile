EXEC_TEST = test
EXEC = enetServer
# LIB = enet
CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
CFLAGS = -I../include/
LDFLAGS = -L../lib/
LDFLAGS = 
# LDFLAGS += $(LIB:%=-l%)
# FMFLAGS = -framework Cocoa -framework OpenGL -framework IOKit

SRC_DIR = src
OBJ_DIR = bin
LIB_DIR = ../lib



SRC = $(wildcard ../$(SRC_DIR)/*.cpp)
OBJ = $(SRC:../$(SRC_DIR)/%.cpp=../$(OBJ_DIR)/%.o)
SRC_TST = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_TST = $(filter-out ../$(OBJ_DIR)/$(EXEC).o, $(OBJ)) $(SRC_TST:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)


all: exe


exe: $(EXEC_TEST)

$(EXEC_TEST): $(OBJ_TST)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LDFLAGS) $(FMFLAGS) $^ -o $@

../$(OBJ_DIR)/%.o: ../$(SRC_DIR)/%.cpp
	@mkdir -p ../$(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<


.depend:
	$(CC) $(CCFLAGS) -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ_TST) $(EXEC)
veryclean: clean
	rm -f $(SAVES)


debug:
	@echo 