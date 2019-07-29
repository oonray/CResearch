/*
	nqueens
	by Dan Gookin, February 20, 2015

	My attempt at solving the 8 queens puzzle. This one uses a 2D char
	array to store the board and to track the queens' attacks.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_square(char *board, int starting_pos, int max);
void set_queen(char *b, int r, int c, int s);
void show_board(int squares,char *board);

int output_mode;
int solution;

int main(int argc, char **argv)
{
	int squares,s;
	char *board;
	
	solution = 0;			/* solution tally */

	/* handle command line options, if any */
	if (argc <= 1)
	{
	   squares = 8;
	   output_mode = 0;
	}
	else
	{
		if( argv[1][0] >= '0' && argv[1][0] <= '9')
			squares = atoi(argv[1]);
		else
		{
			puts("nQueens\nWritten by Dan Gookin\n");
			puts("This code outputs solutions to the 8 Queens programming puzzle. If a board-");
			puts("size argument isn't specified, 8 is used. The code crunches through all");
			puts("permutations. When a solution is found, it's output. Format:\n");
			puts("nqueens [squares] [output]\n");
			puts("squares  is an optional value indicating board size. 8 is the default");
			puts("output   is the output format. Options are 'brief' for a row summary and");
			puts("         'board' for checkerboard output. When omitted, a single-line");
			puts("         summary of the result tally is displayed.\n");
			return(8);
		}
		if( argv[2] != NULL)
		{
			if(strcmp(argv[2],"brief") == 0)
				output_mode = 1;
			else if(strcmp(argv[2],"board") == 0)
				output_mode = 2;
			else
				fprintf(stderr,"Unrecognized option\n");
		}
	}

	printf("Finding solutions for a %dx%d board:\n",squares,squares);

	/* Allocate space for the board */
	board = (char *)malloc(squares*squares*sizeof(char));
	if(board==NULL)
	{
		fprintf(stderr,"Memory allocation error.\n");
		exit(1);
	}
	
	/* Initialize the board: space=open, *=attacked, Q=queen */
	for(s=0;s<squares*squares;s++)
		*(board+s) = ' ';
	
	/* begin the recursion, starting at the first row, 0 */
	find_square(board,0,squares);

	/* At exit, display summary, if that's the chosen output mode */
	if(output_mode == 0)
		printf("A total of %d solutions were found.\n",solution);
}

void find_square(char *board, int starting_row, int max)
{
	int row,column;

	if(starting_row == max)
	{
		show_board(max,board);
		return;
	}

	for(row=0;row<max;row++)
	{
		for(column=0;column<max;column++)
		{
			if( *(board+max*row+column)==' ' )
			{
				set_queen(board,row,column,max);
				find_square(board,starting_row+1,max);
			}
		}
	}
}

/*
	Set the grid for attacks and queen position
*/
void set_queen(char *b, int r, int c, int s)
{
	int x,y;

	for(x=0;x<s;x++)
		for(y=0;y<s;y++)
		{
			if(x==r)					/* row attack */
				*(b+s*x+y) = '*';
			if(y==c)					/* column attack */
				*(b+s*x+y) = '*';
			if( c-x == y-r )			/* SW-NE diagonal attack */
				*(b+s*x+y) = '*';
			if( x-r == y-c )			/* NW - SE attack */
				*(b+s*x+y) = '*';
			if( x==r && y==c )			/* place the queen */
				*(b+s*x+y) = 'Q';
		}
	show_board(s,b);
}

/* output the board */
void show_board(int squares,char *board)
{
	int x,y;

	solution++;
	/* Display a single line A1-to-H8 grid summary of the solution */
	if(output_mode == 1)
	{
	}
	/* Display a chessboard solution grid */
	if(output_mode == 2)
	{
		printf("Solution %d:\n",solution);
		for(x=0;x<squares;x++)
		{
			/* Draw the top line */
			for(y=0;y<squares;y++)
				printf(" ---");
			putchar('\n');
			/* Draw the squares */
			for(y=0;y<squares;y++)
				printf("| %c ",*(board+squares*x+y));
			printf("|\n");
		}
		/* Draw the bottom line */
		for(y=0;y<squares;y++)
			printf(" ---");
		putchar('\n');
	}
	/* output_mode 0 falls through to here: no output */
}

