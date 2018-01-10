#Which files to compile
OBJS = src/main.cpp src/input.cpp

#Which compiler:
CC = g++

#Put libraries to link here:
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

#Name of executable:
OBJ_NAME = bin/main

#Compile the executable:
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
