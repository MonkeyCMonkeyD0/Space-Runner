EXEC = enetServer
LIB = enet
CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g
CFLAGS = -Iinclude/
LDFLAGS = -Llib/
LDFLAGS = 
LDFLAGS += $(LIB:%=-l%)
# FMFLAGS = -framework Cocoa -framework OpenGL -framework IOKit

SRC_DIR = src
OBJ_DIR = bin
LIB_DIR = lib
# TST_DIR = tests

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)
LIB_SRC = $(wildcard $(LIB_DIR)/*/*.c)
LIB_OBJ = $(LIB_SRC:%.c=%.o)


all: library exe


library: $(LIB)
	@mv $(LIB:%=lib%.a) $(LIB_DIR)/

$(LIB): 
	@make $(filter $(LIB_DIR)/$@/%.o, $(LIB_OBJ))
	ar rcs lib$@.a $(filter $(LIB_DIR)/$@/%.o, $(LIB_OBJ))

$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	@echo $@
	gcc -fPIC -o $@ -c $<


# testcase: 
# 	cd $(TST_DIR); make


exe: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LDFLAGS) $(FMFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<


.depend:
	$(CC) $(CCFLAGS) -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)
veryclean: clean
	rm -f $(SAVES)
cleantest:
	cd $(TST_DIR) ; make clean
distclean : clean cleantest


debug:
	@echo 