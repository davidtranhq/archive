#OBJS specifies which files to compile as part of the project 
OBJS = main.o

#CC specifies which compiler we're using 
CC = g++ 

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2 \
				-IC:\mingw_dev_lib\include\SDL_image \
				-IC:\mingw_dev_lib\include\SDLpp

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
# -Wall includes all warnings
# -Wl,-subsystem,windows gets rid of the console window 
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDLpp -lSDL2main -lSDL2 -lSDL2_image 

#EXE_NAME specifies the name of our executable 
EXE_NAME = Simulator

#FINAL_PATH specifies the final path of the library
FINAL_PATH = C:\mingw_dev_lib\lib

#This is the target that compiles our executable 

.PHONY : clean move full

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(EXE_NAME)

%.o : %.cpp
	$(CC) $< $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) -c $(LINKER_FLAGS) -o $@