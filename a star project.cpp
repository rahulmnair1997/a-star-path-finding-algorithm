
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<float.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>

#define ROW 9
#define COL 9

/* Creating a shortcut for int, int pair type */
struct pair
{
    int first;
    int second;
};
/* Creating a shortcut for pair<int, pair(int,int) type */
struct Pair
{
    double third;
    struct pair fourth;
};

/* A structure to hold the necessary parameters */

struct cell
{


int parent_i, parent_j;

double f,g,h;
};
/* Implementing two Stack for tracing path */
 int stack1[100];
void push1();
void pop1();
 int stack2[100];
void push2();
void pop2();
   int top1 = -1;
    void push1( int data)
    {
        if(top1<=100)
        {
            top1++;
            stack1[top1]=data;
        }
    }
    void pop1()
    {
        if(top1>=-1)
        {
            top1--;
        }
    }
   int top2 = -1;
    void push2( int data)
    {
        if(top2<=100)
        {
            top2++;
            stack2[top2]=data;
        }
    }
    void pop2()
    {
        if(top2>=-1)
        {
            top2--;
        }
    }
    /*  For implementation of OpenList*/
    struct Pair heap[100];
int heapsize = 0;
void insert(struct Pair p)
{
    int q = p.third;
    heapsize++;
    heap[heapsize]= p;
    int now = heapsize;
    while(heap[now/2].third>q)
    {
        heap[now]= heap[now/2];
        now= now/2;
    }
    heap[now]= p;
}

struct Pair DeleteMin()
{
    int min_element,last_element;
    int child,now;
    min_element=heap[1].third;
    last_element= heap[heapsize].third;
    for(now = 1; now * 2 <= heapsize ; now = child)
    {
        child=now*2;
        if (child != heapsize && heap[child + 1].third < heap[child].third) {
            child++;
        }
         if (last_element > heap[child].third) {
            heap[now] = heap[child];
        } else /* It fits there */
        {
            break;
        }
        }
    heap[now] = heap[heapsize];
    heapsize--;
    return heap[1];
}
 /* A utility Function to check whether given cell (row,col) is a valid cell or not */

 bool isValid(int row, int col)
 {
     /* Returns true if row number and column number is in range */

     return (row >=0) && (row < ROW) && (col >=0) && (col < COL);
 }

 /* A Utility Function to check whether the given cell is blocked or not */

 bool isUnblocked(int grid[][COL], int row, int col)
 {
     /* returns true if the cell is not blocked else false */
     if(grid[row][col] == 1)
        return (true);
     else
        return (false);
 }

 /* A Utility Function to check whether destination cell has been reached or not */

 bool isDestination(int row, int col,struct pair dest)
 {
     if(row == dest.first && col == dest.second)
        return true;
     else
        return false;
 }

/* A Utility function to calculate the 'h' heuristics. */

double calculateHValue(int row, int col, struct pair dest)
{
    /* Return using the distance formula */
    return ((double)sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

/* A Utility function to trace the path from the source to destination */

void tracePath(struct cell cellDetails[][COL], struct pair dest)
{    int row,col;
    printf("\n The Path is ");
     row = dest.first;
     col = dest.second;

     while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
     {
         push1(row);
         push2(col);
         int temp_row = cellDetails[row][col].parent_i;
         int temp_col = cellDetails[row][col].parent_j;
         row = temp_row;
         col = temp_col;
     }
     push1(row);
     push2(col);

     while(top1>=0 && top2>=0)
     {
         printf("-> (%d,%d)",stack1[top1],stack2[top2]);
         int x=getmaxx()/9;
 int y=getmaxy()/9;
  int i,j,k=0,poly[8],l,m=0,q,w;
 char string[100];
 for(i=1,k+=y;m<9;i+=y,m++)
 for(j=1,l=0;l<9;j+=x,l++)
 {

 if( l%2==1 && m%2==0 ||   l%2==0 && m%2==1)
  {
   setcolor(14);
   setfillstyle(1,14);
   poly[0]=j;
   poly[1]=i;
   poly[2]=j+x;
   poly[3]=i;
   poly[4]=j+x;
   poly[5]=k+i;
   poly[6]=j;
   poly[7]=k+i;
   fillpoly(4,poly);
   q=(poly[0]+poly[4])/2;
   w=(poly[1]+poly[5])/2;
   sprintf(string,"{%d,%d}",l,m);
   outtextxy(q,w,string);
  }
  else if( l==stack1[top1] && stack1[top1]%2==1 && m==stack2[top2] && stack2[top2]%2==1 || l==stack1[top1] && stack1[top1]%2==0 && m==stack2[top2] && stack2[top2]%2==0)
     {
     setcolor(2);                                /*IN BLACK CHEKS*/
   setfillstyle(1,2);
   poly[0]=j;
   poly[1]=i;
   poly[2]=j+x;
   poly[3]=i;
   poly[4]=j+x;
   poly[5]=k+i;
   poly[6]=j;
   poly[7]=k+i;
   fillpoly(4,poly);
   q=(poly[0]+poly[4])/2;
   w=(poly[1]+poly[5])/2;
   sprintf(string,"(%d,%d)",l,m);
   outtextxy(q,w,string);
   delay(1100);
     }
     else{}
 }
 setcolor(2);
 rectangle(0,0,(8*x)+1,(8*y)+1);
   /*IN WHITE CHEKS*/
pop1();
         pop2();

     }
     getch();
     return;
}
/* A Function to find the shortest path between
   a given source cell to a destination cell according
   to A* Search Algorithm */

void aStarSearch(int grid[][COL],struct pair src, struct pair dest)
{
    /*If the source is out of range*/
    if(isValid(src.first,src.second)==false)
    {
        printf("Source is invalid\n");
        return;
    }
    /* If the destination is out of range*/
    if(isValid(dest.first,dest.second)==false)
    {
        printf("Destination is invalid\n");
        return;
    }
    /*Either the source or destination is blocked*/
    if(isUnblocked(grid,src.first,src.second)==false || isUnblocked(grid,dest.first,dest.second)==false)
    {
        printf("Source or the destination is blocked\n");
        return;
    }
    /*If the destination cell is the same as source cell*/
    if(isDestination(src.first,src.second,dest)==true)
    {
        printf("We are already at the destination\n");
        return;
    }
      /*Create a closed list and initialise it to false which means
	 that no cell has been included yet
	 This closed list is implemented as a boolean 2D array*/
	 bool closedList[ROW][COL];
	 memset(closedList,false,sizeof(closedList));
	 	/* Declare a 2D array of structure to hold the details
	        of that cell */
       struct cell cellDetails[ROW][COL];
     int i,j;
     for(i=0;i<ROW;i++)
     {
         for(j=0;j<COL;j++)
         {
             cellDetails[i][j].f = FLT_MAX;
             cellDetails[i][j].g = FLT_MAX;
             cellDetails[i][j].h = FLT_MAX;
             cellDetails[i][j].parent_i = -1;
             cellDetails[i][j].parent_j = -1;
         }
     }
    /* Initialising the parameters of the starting node */
         i = src.first, j = src.second;
         cellDetails[i][j].f = 0.0;
         cellDetails[i][j].g = 0.0;
         cellDetails[i][j].h = 0.0;
         cellDetails[i][j].parent_i = i;
         cellDetails[i][j].parent_j = j;
         	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of pair of pair.*/
    struct Pair p = {0,i,j};
    insert(p);
    bool foundDest = false;
    int k;
    while(heapsize!=0)
    {
        i = heap[1].fourth.first;
        j = heap[1].fourth.second;
        closedList[i][j] = true;
        DeleteMin();

         /* To store the 'g', 'h' and 'f' of the 8 successors */
        double gNew, hNew, fNew;

        /*----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one */
        if (isValid(i-1, j) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i-1, j, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }
            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i-1][j] == false &&
                     isUnblocked(grid, i-1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i-1, j, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i-1][j].f == FLT_MAX ||
                        cellDetails[i-1][j].f > fNew)
                {
                    struct Pair p1 = {fNew,i-1,j};
                    insert(p1);

                    /* Update the details of this cell */
                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        /* Second Successor */

        /* Only process this cell if this is a valid one */
        if (isValid(i+1, j) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i+1, j, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i+1][j] == false &&
                     isUnblocked(grid, i+1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1, j, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i+1][j].f == FLT_MAX ||
                        cellDetails[i+1][j].f > fNew)
                {
                    struct Pair p2 = {fNew,i+1,j};
                    /* Update the details of this cell */
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }
        /*----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one */
        if (isValid (i, j+1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i, j+1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i][j+1] == false &&
                     isUnblocked(grid, i, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue (i, j+1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i][j+1].f == FLT_MAX ||
                        cellDetails[i][j+1].f > fNew)
                {
                    struct Pair p3 = {fNew,i,j+1};
                    insert(p3);

                    /* Update the details of this cell */
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        /*----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one */
        if (isValid(i, j-1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i, j-1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i][j-1] == false &&
                     isUnblocked(grid, i, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j-1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i][j-1].f == FLT_MAX ||
                        cellDetails[i][j-1].f > fNew)
                {
                    struct Pair p4 = {fNew,i,j-1};
                    insert(p4);

                    /* Update the details of this cell */
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }

        /*----------- 5th Successor (North-East) ------------

        // Only process this cell if this is a valid one */
        if (isValid(i-1, j+1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i-1, j+1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i-1][j+1] == false &&
                     isUnblocked(grid, i-1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i-1, j+1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i-1][j+1].f == FLT_MAX ||
                        cellDetails[i-1][j+1].f > fNew)
                {
                    struct Pair p5 = {fNew,i-1,j+1};

                    /* Update the details of this cell */
                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }

        /*----------- 6th Successor (North-West) ------------

        // Only process this cell if this is a valid one */
        if (isValid (i-1, j-1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination (i-1, j-1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i-1][j-1] == false &&
                     isUnblocked(grid, i-1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i-1, j-1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i-1][j-1].f == FLT_MAX ||
                        cellDetails[i-1][j-1].f > fNew)
                {
                    struct Pair p6 = {fNew,i-1,j-1};
                    insert(p6);
                    /* Update the details of this cell */
                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }

        /*----------- 7th Successor (South-East) ------------

        // Only process this cell if this is a valid one */
        if (isValid(i+1, j+1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i+1, j+1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                printf ("The destination cell is found\n");
                tracePath (cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i+1][j+1] == false &&
                     isUnblocked(grid, i+1, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i+1, j+1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.*/
                if (cellDetails[i+1][j+1].f == FLT_MAX ||
                        cellDetails[i+1][j+1].f > fNew)
                {
                    struct Pair p7 = {fNew,i+1,j+1};
                    insert(p7);

                    /* Update the details of this cell */
                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }

        /*----------- 8th Successor (South-West) ------------

        // Only process this cell if this is a valid one */
        if (isValid (i+1, j-1) == true)
        {
            /* If the destination cell is the same as the
            // current successor */
            if (isDestination(i+1, j-1, dest) == true)
            {
                /* Set the Parent of the destination cell */
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            /* If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following */
            else if (closedList[i+1][j-1] == false &&
                     isUnblocked(grid, i+1, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i+1, j-1, dest);
                fNew = gNew + hNew;

                /* If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure. */
                if (cellDetails[i+1][j-1].f == FLT_MAX ||
                        cellDetails[i+1][j-1].f > fNew)
                {
                    struct Pair p8 = {fNew,i+1,j-1};
                    insert(p8);

                    /* Update the details of this cell */
                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }

    /* When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages) */
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}

/* Driver program to test above function */
int main()
{
    /* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */
    int grid[ROW][COL] =
    {
        {1,0,1,0,1,0,1,0,1 },
        {0,1,0,1,0,1,0,1,0 },
        {1,0,1,0,1,0,1,0,1 },
        {0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1},
        {0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1},
        {0,1,0,1,0,1,0,1,0},
        {1,0,1,0,1,0,1,0,1}
    };
int a=DETECT,b,c;

 initgraph(&a,&b,"\\tc\\bgi");
         int x=getmaxx()/9;
 int y=getmaxy()/9;
  int i,j,k=0,poly[8],l,m=0,q,w;
 char string[100];
 for(i=1,k+=y;m<9;i+=y,m++)
 for(j=1,l=0;l<9;j+=x,l++)
 {

 if( l%2==1 && m%2==0 ||   l%2==0 && m%2==1)
  {
   setcolor(14);
   setfillstyle(1,14);
   poly[0]=j;
   poly[1]=i;
   poly[2]=j+x;
   poly[3]=i;
   poly[4]=j+x;
   poly[5]=k+i;
   poly[6]=j;
   poly[7]=k+i;
   fillpoly(4,poly);
   q=(poly[0]+poly[4])/2;
   w=(poly[1]+poly[5])/2;
   sprintf(string,"{%d,%d}",l,m);
   outtextxy(q,w,string);
  }
  else
  {
      setcolor(5);
   setfillstyle(1,5);
   poly[0]=j;
   poly[1]=i;
   poly[2]=j+x;
   poly[3]=i;
   poly[4]=j+x;
   poly[5]=k+i;
   poly[6]=j;
   poly[7]=k+i;
   fillpoly(4,poly);
   q=(poly[0]+poly[4])/2;
   w=(poly[1]+poly[5])/2;
   sprintf(string,"{%d,%d}",l,m);
   outtextxy(q,w,string);
  }
 }

    /* Source is the left-most bottom-most corner */
     int z,p,r,t;
     printf("HEY! YELLO GRIDS ARE OBSTACLES YOU CAN'T GO THERE\n");
     printf("\n");
     printf("PURPLE GRIDS ARE THE PLACES WHERE YOU CAN GO\n");
     printf("\n");
    printf("Enter the Source Coordinates\n");
    scanf("%d,%d",&z,&p);
    printf("Enter the Destination Coordinates\n");
    scanf("%d,%d",&r,&t);
  struct pair src = {z,p};

    /* Destination is the left-most top-most corner */
   struct pair dest = {r,t};


  aStarSearch(grid, src, dest);
}


