#include "Maze.h"
#include "misc.h"

#define Speed 10

Maze::Maze(string filename) {
    
    fstream f;
    char buf[5];
    string sbuf;
    
    f.open(filename.data(), ios::in);
    if(f == NULL)
    {
        string err_msg;
        err_msg += "opening ";
        err_msg += filename;
        err_msg += " : FAILED!";
        printAndExit(err_msg);
    }
    
    //read number of columns
    f >> buf;
    numColumns = atoi(buf);
    
    //read number of rows
    f >> buf;
    numRows = atoi(buf);
    
    squares = new char*[numRows];
    visited = new bool*[numRows];
    for(int i = 0; i < numRows; i++)
    {
        squares[i] = new char[numColumns];
        visited[i] = new bool[numColumns];
    }
    
    getline(f, sbuf);
    for(int i = 0; i < numRows; i++)
    {
        getline(f, sbuf);
        for(int j = 0; j < numColumns; j++)
        {
            squares[i][j] = sbuf[j];
            if(squares[i][j] == Maze::START)
            {
                start.setRow(i);
                start.setColumn(j);
            }
            if(squares[i][j] == Maze::END)
            {
                end.setRow(i);
                end.setColumn(j);
            }
            
            if(squares[i][j] == Maze::VISITED)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }
    
    f.close();
    
    // X-lib Initialisations

    Pixel = 20;
    if (numColumns*Pixel > 1200)
        Pixel = 1200/numColumns;
    if (numRows*Pixel > 700)
        Pixel = 700/numRows;

    dsp = XOpenDisplay( NULL );
    screenNumber = DefaultScreen(dsp);
    white = WhitePixel(dsp,screenNumber);
    black = BlackPixel(dsp,screenNumber);
    win = XCreateSimpleWindow(dsp,
                                DefaultRootWindow(dsp),
                                0, 0,   // origin
                                numColumns*Pixel, numRows*Pixel, // size
                                0, white, // border
                                white );  // backgd
    
    thecolormap = DefaultColormap(dsp,screenNumber);
    XMapWindow( dsp, win );
    eventMask = StructureNotifyMask;
    XSelectInput( dsp, win, eventMask );
    do{
        XNextEvent( dsp, &evt );   // calls XFlush
    }while( evt.type != MapNotify );
    gc = XCreateGC( dsp, win,
                      0,        // mask of values
                      NULL );   // array of values

}

void Maze::print()
{
    cout << "numRows = " << numRows << "\t\tnumColumns = " << numColumns << endl;
    
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            cout << squares[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            cout << visited[i][j] << " ";
        }
        cout << endl;
    }
}

int Maze::getNumRows()
{
    return numRows;
}

int Maze::getNumColumns()
{
    return numColumns;
}

Point Maze::getStartPoint()
{
    return start;
}

Point Maze::getEndPoint()
{
    return end;
}

bool Maze::isInBounds(Point pt)
{
    if(pt.getRow() >= 0 && pt.getRow() < numRows && pt.getColumn() >= 0 && pt.getColumn() < numColumns)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Maze::isEndPoint(Point pt)
{
    if(pt.getRow() == end.getRow() && pt.getColumn() == end.getColumn())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Maze::isVisited(Point pt)
{
    checkIndices(pt);
    return isInBounds(pt) && visited[pt.getRow()][pt.getColumn()];
}

void Maze::setVisited(Point pt)
{
    checkIndices(pt);
    if(isInBounds(pt))
        visited[pt.getRow()][pt.getColumn()] = true;
    DrawBox(pt.getColumn(), pt.getRow(), VISITED);
    XFlush(dsp);
    usleep(200000/Speed);
}

void Maze::clearVisited()
{
    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numColumns; j++)
        {
            visited[i][j] = false;
        }
    }
}

bool Maze::isWall(Point pt)
{
    checkIndices(pt);
    return isInBounds(pt) && squares[pt.getRow()][pt.getColumn()] == Maze::WALL;
}

bool Maze::isOpen(Point pt)
{
    checkIndices(pt);
    return isInBounds(pt) && squares[pt.getRow()][pt.getColumn()] == Maze::OPEN;
}

void Maze::checkIndices(Point pt)
{
    if(!isInBounds(pt))
    {
        string err_msg;
        err_msg += "bad indices : row = ";
        err_msg += pt.getRow();
        err_msg += ", column = ";
        err_msg += pt.getColumn();
        printAndExit(err_msg);
    }
}

// Draw a pixel around (x,y) with the given RGB color
void Maze::DrawBox (int x, int y, char c)
{
    x*=Pixel;
    x+=Pixel/2;
    y*=Pixel;
    y+=Pixel/2;
    
    XColor boxcolor;
    XPoint Box[4];
    Box[0].x = x-Pixel/2; Box[0].y = y-Pixel/2;
    Box[1].x = x+Pixel/2; Box[1].y = y-Pixel/2;
    Box[2].x = x+Pixel/2; Box[2].y = y+Pixel/2;
    Box[3].x = x-Pixel/2; Box[3].y = y+Pixel/2;
    
    if (c==VISITED)
    { boxcolor.red = 65000;boxcolor.green = 0;boxcolor.blue = 0; }

    else
    { boxcolor.red = 0;boxcolor.green = 65000;boxcolor.blue = 0; }

    boxcolor.flags = DoRed | DoGreen | DoBlue;

    XAllocColor(dsp,thecolormap,&boxcolor);
    XSetForeground(dsp,gc,boxcolor.pixel);
    XFillPolygon(dsp,win,gc,Box,4,Complex,CoordModeOrigin);
}

void Maze::DrawMaze()
{
    int x,y;
    XPoint Box[4];
    XSetForeground(dsp,gc,black);

    for(int i=0;i<numRows;i++)
        for (int j=0;j<numColumns;j++)
            if (squares[i][j]==WALL)
            {
                x = j*Pixel + Pixel/2;
                y = i*Pixel + Pixel/2;
                
                Box[0].x = x-Pixel/2; Box[0].y = y-Pixel/2;
                Box[1].x = x+Pixel/2; Box[1].y = y-Pixel/2;
                Box[2].x = x+Pixel/2; Box[2].y = y+Pixel/2;
                Box[3].x = x-Pixel/2; Box[3].y = y+Pixel/2;
                
                XFillPolygon(dsp,win,gc,Box,4,Complex,CoordModeOrigin);
            }
    XColor boxcolor;
    
    boxcolor.red = 0;boxcolor.green = 65000;boxcolor.blue = 0;
    boxcolor.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(dsp,thecolormap,&boxcolor);
    XSetForeground(dsp,gc,boxcolor.pixel);
    
    x = start.getColumn()*Pixel + Pixel/2;
    y = start.getRow()*Pixel + Pixel/2;
    
    Box[0].x = x-Pixel/2; Box[0].y = y-Pixel/2;
    Box[1].x = x+Pixel/2; Box[1].y = y-Pixel/2;
    Box[2].x = x+Pixel/2; Box[2].y = y+Pixel/2;
    Box[3].x = x-Pixel/2; Box[3].y = y+Pixel/2;
    
    XFillPolygon(dsp,win,gc,Box,4,Complex,CoordModeOrigin);

    x = end.getColumn()*Pixel + Pixel/2;
    y = end.getRow()*Pixel + Pixel/2;
    
    Box[0].x = x-Pixel/2; Box[0].y = y-Pixel/2;
    Box[1].x = x+Pixel/2; Box[1].y = y-Pixel/2;
    Box[2].x = x+Pixel/2; Box[2].y = y+Pixel/2;
    Box[3].x = x-Pixel/2; Box[3].y = y+Pixel/2;
    
    XFillPolygon(dsp,win,gc,Box,4,Complex,CoordModeOrigin);

    XFlush(dsp);
}

void Maze::MarkSolution (Point* temppath, int n)
{
    int k = 0;
    Point* path = new Point[n];                     // Stores path from S to E
    path[k++] = getEndPoint();                // Initially stores from E to S
    for(int i=n-1;i>-1;i--)
        if(temppath[i].isNeighbor(path[k-1]))
            path[k++]=temppath[i];
    Point t;
    for(int i=0;i<k/2;i++)                      // Order reversed to get S to E
    {
        t = path[i];
        path[i] = path[k-i-1];
        path[k-i-1] = t;
    }
    for(int i=1;i<n-1;i++)
        DrawBox(path[i].getColumn(), path[i].getRow(), START);
    XFlush(dsp);
}

Maze::~Maze()
{
/*    // Pause
    eventMask = ButtonPressMask|ButtonReleaseMask;
    XSelectInput(dsp,win,eventMask); // override prev
    
    do{
        XNextEvent( dsp, &evt );   // calls XFlush()
    }while( evt.type != ButtonRelease );
*/
    XDestroyWindow( dsp, win );
    XCloseDisplay( dsp );
}
