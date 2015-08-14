#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>

#include "Point.h"
#include "Maze.h"
#include "PriorityQueueADT.h"
#include "PriorityQueueSTL.cpp"
#include "DequeADT.h"
#include "DequeSTL.cpp"

using namespace std;

void solve(Maze * maze, PriorityQueueADT * pq);
void solve(Maze * maze, DequeADT<Point> * dq);
void solveBFS(Maze * maze);
void solveDFS(Maze * maze);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

    cout << "=================================" << endl;
	cout << "     SourKream's Maze Solver     " << endl;
	cout << "=================================" << endl;

	if(argc != 2)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile>" << endl;
		exit(1);
	}
    
    cout << endl << "Input Filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	Point destination = maze->getEndPoint();
    
    maze->DrawMaze();
    cout << "\nMaze Loaded\n";

    cout << "\n1. Priority Queue  (Informed Search)";
    cout << "\n2. Deque           (Informed Search)";
    cout << "\n3. Queue - BFS     (Uninformed Search)";
    cout << "\n4. Stack - DFS     (Uninformed Search)";
    cout << "\n\nChoose a type of search option (1-4) : ";
    
    int ch;
    do { cin >> ch; } while ((ch<1)||(ch>4));
    
    cout << endl << "Solving maze .... " << endl;
    
    switch (ch)
    {
        case 1: PriorityQueueADT * pq;
                pq = new PriorityQueueSTL(&destination);
                solve(maze, pq);
                break;

        case 2: DequeADT<Point> * dq;
                dq = new DequeSTL<Point>();
                solve(maze, dq);
                break;

        case 3: solveBFS(maze);
                break;

        case 4: solveDFS(maze);
                break;

    }

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