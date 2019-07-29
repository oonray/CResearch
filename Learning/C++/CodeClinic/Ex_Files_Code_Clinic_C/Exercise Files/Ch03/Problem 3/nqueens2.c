/*
	nqueens
	by Dan Gookin, February 20, 2015

	A second attempt to solve the 8 queens puzzle. This one uses a single
	int array to store row/column information for the queen's position.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_square(int *board, int row, int squares);
void show_board(int *board, int squares);

int output_mode;
int solution;

int main(int argc, char **argv)
{
	int squares,s;
	int *board;
	
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
	board = (int *)malloc(squares*sizeof(int));
	if(board==NULL)
	{
		fprintf(stderr,"Memory allocation error.\n");
		exit(1);
	}
	
	/* Initialize the board to a value otherwise unavailable */
	for(s=0;s<squares;s++)
		*(board+s) = squares+1;
	
	/* begin the recursion, starting at the first row, 0 */
	find_square(board,0,squares);

	/* At exit, display summary, if that's the chosen output mode */
	if(output_mode == 0)
		printf("A total of %d solutions were found.\n",solution);
}

/*
	Recursive routine to find squares not under attack
*/
void find_square(int *board, int current_row, int squares)
{
	int column,this_row,next_row;
	int vertical,horizontal_left,horizontal_right;

	/* If past the last row, then show the found solution */
	if(current_row == squares)
	{
		show_board(board,squares);
		return;
	}

	/* Move through the current row a column at a time. For each column,
	   check the positions above, on previous rows. If a previous row contains
	   a queen, move to the next column via a `break` statement */
	for(column=0;column<squares;column++)
	{
		for(this_row=0;this_row<current_row;this_row++)
		{
			/* check for column attack */
			if( *(board+this_row)==column)
				break;			/* Check next column */
			/* check for diagonal attack */
			vertical = current_row-this_row;
			horizontal_left = *(board+this_row) - column;
			horizontal_right = column - *(board+this_row);
			if(vertical==horizontal_left || vertical==horizontal_right)
				break;
			/* if no queens are above, then keep checking the rows
			   in the current column */
		}
		/* If the current row is reached, then it's a valid position */
		if(this_row==current_row)
		{
			*(board+current_row) = column;
			next_row = current_row+1;
			find_square(board,next_row,squares);
			/* Recursion returns here, to continue scanning the same
			   row for valid queen positions */
		}
	}
}

/*
   output the board
*/
void show_board(int *board, int squares)
{
	int x,y;
	int *b;

	solution++;
	/* Display a single line A1-to-H8 grid summary of the solution */
	if(output_mode == 1)
	{
		printf("Solution %d:",solution);
		b = (int *)malloc(squares*sizeof(int));
		if(b==NULL)
		{
			fprintf(stderr,"Memory allocation error.\n");
			exit(1);
		}
		/* Must turn board 90 degrees CCW to get proper output */
		for(x=0;x<squares;x++)
			*(b+board[x]) = squares-x;
		for(x=0;x<squares;x++)
			printf(" %c%d",'A'+x,*(b+x));
		putchar('\n');
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
				printf("| %c ",*(board+x)==y?'Q':' ');
			printf("|\n");
		}
		/* Draw the bottom line */
		for(y=0;y<squares;y++)
			printf(" ---");
		putchar('\n');
	}
	/* output_mode 0 falls through to here: no output */
}

