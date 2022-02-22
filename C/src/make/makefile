all: hello.exe

hello.exe: hello.o
	gcc -o hello.exe hello.o
	
hello.o: hello.c
	gcc -c hello.c
	
clean:
	del hello.o hello.exe