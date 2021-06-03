CC = g++
CCFLAGS = -Wall -Werror -std=c++11 -g -O3
CFLAGS = -Iinclude/
# LFLAGS = -Llib/
LDFLAGS = -pthread -lenet

SRC_DIR = src
OBJ_DIR = bin
LIB_DIR = lib
TST_DIR = tests


SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SAVES = $(wildcard *.txt)
LIB = $(LIB_DIR)/libgames.a


EXEC = enetServer


all: $(EXEC)

$(EXEC): $(OBJ)
	ar -cr $(LIB) $(OBJ)
	$(CC) $(CCFLAGS) $(CFLAGS) $(LFLAGS) $(LIB) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) $(CFLAGS) -o $@ -c $<


# library: $(LIB)
# 	@mv $(LIB:%=lib%.a) $(LIB_DIR)

# $(LIB): 
# 	@make $(filter $(LIB_DIR)/$@/%.o, $(LIB_OBJ))
# 	ar rcs lib$@.a $(filter $(LIB_DIR)/$@/%.o, $(LIB_OBJ))

# $(LIB_DIR)/%.o: $(LIB_DIR)/%.c
# 	gcc -o $@ -c $<


testcase: 
	@cd $(TST_DIR); make

clean: cleantest
	@rm -Rf $(OBJ_DIR) $(EXEC) $(LIB)
	@echo "Removed obj and exe from server"
# $(LIB_OBJ)

veryclean: clean
	@rm -f $(SAVES)
	@echo "Removed save files from server"
# $(LIB:%=$(LIB_DIR)/lib%.a)

cleantest:
	@cd $(TST_DIR) ; make veryclean

distclean : veryclean cleantest


.PHONY: testcase clean veryclean cleantest distclean

.depend:
	$(CC) $(CCFLAGS) -MM $(SRC) > .depends
-include .depends
