CURR_PATH=$(shell pwd) 
SERVER = $(CURR_PATH)/Server
CLIENT = $(CURR_PATH)/Client
DATA_POOL = $(CURR_PATH)/DataPool
LIB = $(CURR_PATH)/lib 
COMM = $(CURR_PATH)/Common

INCLUDE = -I$(DATA_POOL)  -I$(LIB)/include
LIB_PATH = -L$(LIB)/lib 

Flag = -lpthread -ljsoncpp
cc = g++
ser_bin = ChatSystem
cli_bin = ChatClient

ser_obj = $(shell ls $(SERVER)/*.cpp $(DATA_POOL)/*.cpp $(COMM)/*.cpp | sed -e 's/\/.*\///'-e 's/\.cpp/\.o/')
cli_obj = $(shell ls $(CLIENT)/*.cpp $(COMM)/*.cpp | sed -e 's/\/.*\///'-e 's/\.cpp/\.o/')

.PHONY:all
all:$(ser_bin) $(cli_bin)

$(ser_bin):$(ser_obj)
	$(cc)  $^ -o $@  $(LIB_PATH) $(Flag)
$(cli_bin):$(ser_obj)
	$(cc)  $^ -o $@  $(LIB_PATH) $(Flag)

%.o:$(SERVER)/%.cpp 
	$(cc) -c $< $(INCLUDE)
%.o:$(CLIENT)/%.cpp
	$(cc) -c $<
%.o:$(DATA_POOL)/%.cpp 
	$(cc) -c $<
%.o:$(COMM)/*.cpp 
	$(cc) -c $<  $(INCLUDE)

.PHONY:clear
clear:
	rm -rf *.o $(ser_bin) $(cli_bin)
.PHONY:debug
debug:
	@echo $(ser_obj)
	@echo $(cli_obj)



