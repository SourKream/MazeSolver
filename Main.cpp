
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<queue>
#include<stack>

#include "Point.h"
#include "Maze.h"
#include "PriorityQueueADT.h"
#include "PriorityQueueSTL.cpp"
#include "PriorityQueueArray.cpp"
#include "/Users/Shantanu/Documents/workspace/COL106/Assignment 5/Assignment 5/DequeADT.h"
#include "/Users/Shantanu/Documents/workspace/COL106/Assignment 5/Assignment 5/DequeSTL.cpp"

using namespace std;

void solve(Maze * maze, PriorityQueueADT * pq);
void solve(Maze * maze, DequeADT<Point> * dq);
void solveBFS(Maze * maze);
void solveDFS(Maze * maze);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

    cout << "===================" << endl;
	cout << "COL 106 Maze Solver" << endl;
	cout << "===================" << endl;
/*
	if(argc != 3 && argc != 4)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile> <priority-queue-type>" << endl;
		cout << "priority-queue-type = 0 for stl::priority-queue (Part A), priority-queue-type = 1 for user-defined priority-queue (Part B)" << endl;
		exit(1);
	}
*/
    
    cout << endl << "input filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	Point destination = maze->getEndPoint();
    
    maze->DrawMaze();
    cout << "\nMaze Loaded";

    cout << "\n\n1. Priority Queue (Assignment 5)\n2. Deque (Assignment 2)\n3. BFS (Queue)\n4. DFS (Stack)\n\n";
    cout << "Choose an option : ";
    int ch;
    do{
    cin >> ch;
    } while ((ch<1)||(ch>4));
    ch--;
    
    cout << endl << "solving maze .... " << endl;
    
    if(ch == 0)
	{
        PriorityQueueADT * pq;
		pq = new PriorityQueueSTL(&destination);
        solve(maze, pq);
	}
	else if(ch==1)
	{
        DequeADT<Point> * dq;
        dq = new DequeSTL<Point>();
        solve(maze, dq);
	}
    else if (ch==2)
    {
        solveBFS(maze);
    }
    else if (ch==3)
    {
        solveDFS(maze);
    }
	for(int i=0;i<10;i++)
	{
		
	}


//	maze->print();
/*
	if(argc == 4)
	{
		cout << endl << "verifying solution .... " << endl;
		verifySolution(maze, argv[3]);
	}
 */
    usleep(3000000);
}


void solve(Maze * maze, PriorityQueueADT * pq)
{
    Point* temppath = new Point[maze->getNumColumns()*maze->getNumRows()];  /////
    int n = 0;                  ///////

    if(maze==NULL)
    {
        cout << "\nNULL MAZE\n";
        exit(0);
    }
    int Solved = 0;
    maze->clearVisited();
    pq->push(maze->getStartPoint());
    while ((!pq->empty())&&(!Solved))
    {
        Point L = pq->top();
        pq->pop();
        
        if(L.isEqual(maze->getEndPoint()))
            Solved++;
        else if ((maze->isVisited(L))||(maze->isWall(L)))
        {}
        else
        {
            maze->setVisited(L);
            temppath[n++] = L;                      ///////
            Point temp;
            temp.setColumn(L.getColumn());
            temp.setRow(L.getRow()-1);
                    pq->push(temp);
            temp.setRow(L.getRow()+1);
                    pq->push(temp);
            temp.setColumn(L.getColumn()-1);
            temp.setRow(L.getRow());
                    pq->push(temp);
            temp.setColumn(L.getColumn()+1);
                    pq->push(temp);
        }
    }
    if(!Solved)
        cout << "\nNO SOLUTION TO MAZE\n\n";
    else
    {
        cout << "\nMAZE SOLVED\n\n";
        maze->MarkSolution(temppath, n);
    }
}


void solveBFS(Maze * maze)
{
    Point* temppath = new Point[maze->getNumColumns()*maze->getNumRows()];  /////
    int n = 0;                  ///////

    if(maze==NULL)
    {
        cout << "\nNULL MAZE\n";
        exit(0);
    }
    queue<Point>* pq = new queue<Point>;
    int Solved = 0;
    maze->clearVisited();
    pq->push(maze->getStartPoint());
    while ((!pq->empty())&&(!Solved))
    {
        Point L = pq->front();
        pq->pop();
        
        if(L.isEqual(maze->getEndPoint()))
            Solved++;
        else if ((maze->isVisited(L))||(maze->isWall(L)))
        {}
        else
        {
            maze->setVisited(L);
            temppath[n++] = L;                      ///////
            Point temp;
            temp.setColumn(L.getColumn());
            temp.setRow(L.getRow()-1);
            pq->push(temp);
            temp.setRow(L.getRow()+1);
            pq->push(temp);
            temp.setColumn(L.getColumn()-1);
            temp.setRow(L.getRow());
            pq->push(temp);
            temp.setColumn(L.getColumn()+1);
            pq->push(temp);
        }
    }
    if(!Solved)
        cout << "\nNO SOLUTION TO MAZE\n\n";
    else
    {
        cout << "\nMAZE SOLVED\n\n";
        maze->MarkSolution(temppath, n);
    }
    
}

void solveDFS(Maze * maze)
{
    Point* temppath = new Point[maze->getNumColumns()*maze->getNumRows()];  /////
    int n = 0;                  ///////
   
    if(maze==NULL)
    {
        cout << "\nNULL MAZE\n";
        exit(0);
    }
    stack<Point>* pq = new stack<Point>;
    int Solved = 0;
    maze->clearVisited();
    pq->push(maze->getStartPoint());
    while ((!pq->empty())&&(!Solved))
    {
        Point L = pq->top();
        pq->pop();
        
        if(L.isEqual(maze->getEndPoint()))
            Solved++;
        else if ((maze->isVisited(L))||(maze->isWall(L)))
        {}
        else
        {
            maze->setVisited(L);
            temppath[n++] = L;                      ///////
            Point temp;
            temp.setColumn(L.getColumn());
            temp.setRow(L.getRow()-1);
            pq->push(temp);
            temp.setRow(L.getRow()+1);
            pq->push(temp);
            temp.setColumn(L.getColumn()-1);
            temp.setRow(L.getRow());
            pq->push(temp);
            temp.setColumn(L.getColumn()+1);
            pq->push(temp);
        }
    }
    if(!Solved)
        cout << "\nNO SOLUTION TO MAZE\n\n";
    else
    {
        cout << "\nMAZE SOLVED\n\n";
        maze->MarkSolution(temppath, n);
    }    
}


void solve(Maze * maze, DequeADT<Point> * dq)
{
    Point* temppath = new Point[maze->getNumColumns()*maze->getNumRows()];
    int n = 0;

    if(maze==NULL)
    {
        cout << "\nNULL MAZE\n";
        exit(0);
    }
    int Solved = 0;
    dq->clear();
    maze->clearVisited();
    dq->push_back(maze->getStartPoint());
    while ((!dq->empty())&&(!Solved))
    {
        Point L = dq->front();
        dq->pop_front();
        
        if(L.isEqual(maze->getEndPoint()))
            Solved++;
        else if ((maze->isVisited(L))||(maze->isWall(L)))
        {}
        else
        {
            maze->setVisited(L);
            temppath[n++] = L;              //////
            
            int d = L.distanceFrom(maze->getEndPoint());
            Point temp;
            temp.setColumn(L.getColumn());
            temp.setRow(L.getRow()-1);
            if(maze->isInBounds(temp))
            {
                if(temp.distanceFrom(maze->getEndPoint())<d)
                    dq->push_front(temp);
                else
                    dq->push_back(temp);
            }
            temp.setColumn(L.getColumn());
            temp.setRow(L.getRow()+1);
            if(maze->isInBounds(temp))
            {
                if(temp.distanceFrom(maze->getEndPoint())<d)
                    dq->push_front(temp);
                else
                    dq->push_back(temp);
            }
            temp.setColumn(L.getColumn()-1);
            temp.setRow(L.getRow());
            if(maze->isInBounds(temp))
            {
                if(temp.distanceFrom(maze->getEndPoint())<d)
                    dq->push_front(temp);
                else
                    dq->push_back(temp);
            }
            temp.setColumn(L.getColumn()+1);
            temp.setRow(L.getRow());
            if(maze->isInBounds(temp))
            {
                if(temp.distanceFrom(maze->getEndPoint())<d)
                    dq->push_front(temp);
                else
                    dq->push_back(temp);
            }
        }
    }
    if(!Solved)
        cout << "\nNO SOLUTION TO MAZE\n\n";
    else
    {
        cout << "\nMAZE SOLVED\n\n";
        maze->MarkSolution(temppath, n);
    }
    
}

void verifySolution(Maze * maze, std::string path)
{
	Maze * correct_solution = new Maze(path);

	if(maze->getNumRows() != correct_solution->getNumRows() || maze->getNumColumns() != correct_solution->getNumColumns())
	{
		cout << "dimension mismatch between input and correct output mazes" << endl;
		exit(1);
	}

	for(int i = 0; i < maze->getNumRows(); i++)
	{
		for(int j = 0; j < maze->getNumColumns(); j++)
		{
			Point p;
			p.setRow(i);
			p.setColumn(j);
			if(maze->isVisited(p) != correct_solution->isVisited(p) && !p.isEqual(maze->getStartPoint()))
			{
				cout << "incorrect solution" << endl;
				cout << "mismatch at : (" << i << "," << j << ")" << endl;
				exit(0);
			}
		}
	}

	cout << "correct solution!" << endl;
}
