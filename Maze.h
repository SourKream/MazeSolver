#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Point.h"

#include<X11/Xlib.h>
#include <unistd.h>

using namespace std;

class Maze {

	private :
		static const char START = 'S';
		static const char END = 'E';
		static const char WALL = '#';
		static const char OPEN = ' ';
		static const char VISITED = '.';

		int numColumns;
		int numRows;
		char** squares;
		bool** visited;
		Point start;
		Point end;

		void checkIndices(Point pt);
    
        // X-Lib Variables
        Display *dsp;
        int screenNumber;
        unsigned long white;
        unsigned long black;
        Colormap thecolormap;
        Window win;
        long eventMask;
        XEvent evt;
        GC gc;
        void DrawBox (int x, int y, char c);
        int Pixel;
    

	public :
		Maze(string filename);
        ~Maze();
		void print();

		int getNumRows();
		int getNumColumns();
		Point getStartPoint();
		Point getEndPoint();

		bool isInBounds(Point pt);
		bool isEndPoint(Point pt);
		bool isVisited(Point pt);
		void setVisited(Point pt);
		void clearVisited();
		bool isWall(Point pt);
		bool isOpen(Point pt);
        void DrawMaze();
        void MarkSolution (Point* temppath, int n);
};

#endif
