all: Main.cpp Maze.cpp misc.cpp comparator.h PriorityQueueADT.h PriorityQueueSTL.cpp PriorityQueueArray.cpp Point.cpp
	g++ misc.cpp Point.cpp Maze.cpp Main.cpp -lX11 -L/usr/X11R6/lib/ -I/opt/X11/include -o Maze.out

clean:
	rm -rf *.out *.o
