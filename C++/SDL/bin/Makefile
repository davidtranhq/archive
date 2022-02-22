#OBJS specifies which files to compile as part of the project 
OBJS = C:\Users\david\Documents\Programming\C++\SDL\source\lesson07\geometry.cpp

#CC specifies which compiler we're using 
CC = g++ 

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2 \
				-IC:\mingw_dev_lib\include\SDLpp \
				-IC:\mingw_dev_lib\include\SDL_image

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
# -Wl,-subsystem,windows gets rid of the console window 
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lsdlcpp -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = geometry.exe

#This is the target that compiles our executable 

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)