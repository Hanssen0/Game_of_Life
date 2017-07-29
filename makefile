objs = main.o Error.o Window.o
main.out : $(objs)
	g++ -o main.out $(objs) -lSDL2 -lGL -lGLEW

main.o : main.cc Error.h Window.h
	g++ -c -o main.o main.cc

Error.o : Error.cc Error.h
	g++ -c -o Error.o Error.cc
	
Window.o : Window.cc Window.h Error.h
	g++ -c -o Window.o Window.cc
