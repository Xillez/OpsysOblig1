#Files to be compiled
OBJS = main3.c

#Compiler
UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CC = gcc
    endif
    ifeq ($(UNAME_S),Darwin)
        CC = gcc-7
    endif
 
#Compiler flags
# -Wall 		Includes ALL warnings
# -g			Include debug
# -ggdb			More debug info (gdb specific)
# -std=c++14	Use c++ 14
# -O0			Turn off optimization
# -O1           Optimize (LEVEL 1!)
# -O2           Optimize (LEVEL 2!)
# -O3           Optimize (LEVEL 3!)
# -pthread      Say we're making a multithreaded program
CFLAGS = -Wall -pthread

#Linker flags
# -lSDL2
# -lSDL2_image
LFLAGS = -lpthread
# -L/usr/include/SFML
# -lSDL2 				Link to the SDL2 library
# -lSDL2_image			Link to the SDL2_image library, needed for more advanced image file types
# -lassimp
# -lsfml-graphics
# -lsfml-window
# -lsfml-system
# -lsfml-audio
# -lGL
# -lGLU
# -lGLEW				Link to glew library
# -lglut
# -lglfw
# -lpthread             Link to pthread library

#Name of our exectuable
OBJ_NAME = ./bin/main3

#This is the target that compiles our executable
#Run with command: "make"
all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $(OBJ_NAME)

#Removes old compiled files. Usefull for running clean builds.
#Run with command: "make clean" OR "make clear"
clean :
	rm *.o
	rm $(OBJ_NAME)

clear :
	rm *.o
	rm $(OBJ_NAME)

run :
	./$(OBJ_NAME)
