#OBJS specifies which files to compile as part of the project 
OBJS = example.cpp

#CC specifies which compiler we're using 
CC = g++ 

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2 \
				-IC:\mingw_dev_lib\include\SDL_image \
				-IC:\mingw_dev_lib\include\SDLpp \
				-IC:\Users\david\Documents\Programming\C++\src\draw\include

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
# -Wall includes all warnings
# -Wl,-subsystem,windows gets rid of the console window 
COMPILER_FLAGS = -Wall -std=c++17 -g

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lDraw -lSDLpp -lSDL2main -lSDL2 -lSDL2_image

#LIB_NAME specifies the name of our library 
LIB_NAME = libDraw.a

#FINAL_PATH specifies the final path of the library
FINAL_PATH = C:\mingw_dev_lib\lib

#This is the target that compiles our executable 

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o hello.exe
	
