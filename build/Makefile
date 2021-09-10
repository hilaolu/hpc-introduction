SOURCE=../src/$(PROJ)
SEARCH_PATH=../lib
OBJ_DIR=./obj
BIN_DIR=./bin
LIB_DIR=../lib
CC=g++
CFLAG=-Wall -c -MMD -std=c++14 -g
LFLAG=-Wall -lm
TARGET=$(BIN_DIR)/$(PROJ)
OBJECT=$(patsubst $(SOURCE)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SOURCE)/*.cpp))
LIB_DIR_1=$(LIB_DIR)/algorithm
OBJECT_1=$(patsubst $(LIB_DIR_1)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(LIB_DIR_1)/*.cpp))
PROJ=$(proj)
proj=
all:check_proj $(TARGET) $(LIB)

$(TARGET):%:$(OBJECT) $(OBJECT_1)
	$(CC) $(LFLAG) $^ -o $@

$(OBJECT):$(OBJ_DIR)/%.o:$(SOURCE)/%.cpp
	$(CC) -I$(SEARCH_PATH) $(CFLAG) $< -o $@
	
$(OBJECT_1):$(OBJ_DIR)/%.o:$(LIB_DIR_1)/%.cpp 
	$(CC) -I$(SEARCH_PATH) $(CFLAG) $< -o $@
	
run:check_proj all
	$(BIN_DIR)/$(PROJ)
	
clean:
	rm bin/* obj/* -f
	
check_proj:
ifndef proj
	$(error proj is not set)
endif
ifneq ($(wildcard $(SOURCE)/.*),)
else
	$(error $(PROJ) is not found)
endif

-include obj/*.d