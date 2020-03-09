#include "board.h"
#include "ships.h"
#include "files.h"

void initialize_game_board(cell player1_board[][COLS], cell player2_board[][COLS], int argc, char** argv)
{
	int i = 0, j = 0;

	if (argc == 6)
	{
		read_board_from_file(argv[4], player2_board);
		read_board_from_file(argv[5], player1_board);
	}	
	else
	{
		for (i = 0; i < ROWS; i++)
			for (j = 0; j < COLS; j++)
			{
				player1_board[i][j].symbol = WATER;
				player1_board[i][j].position.row = i;
				player1_board[i][j].position.column = j;
				player2_board[i][j].symbol = WATER;
				player2_board[i][j].position.row = i;
				player2_board[i][j].position.column = j;
			}
	}
}

void print_board(cell game_board[][COLS], booleann show)
{
	int i = 0, j = 0;

	printf("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < ROWS; i++)
	{
		printf("%d ", i);

		for (j = 0; j < COLS; j++)
		{
			if (show == TRUE)
				printf("%c ", game_board[i][j].symbol);
			else
			{
				switch (game_board[i][j].symbol)
				{
				case HIT: 
					printf("%c ", HIT);
					break;
				case MISS:  
					printf("%c ", MISS);
					break;
				case WATER:
				default:   
					printf("%c ", WATER);
					break;
				}
			}
		}
		putchar('\n');
	}
}

void update_game_board(cell game_board[][COLS], coordinate target)
{
	switch (game_board[target.row][target.column].symbol)
	{
		case WATER:											//pud³o
			game_board[target.row][target.column].symbol = MISS;
			break;

	
		case CARRIER:										//trafiony
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			game_board[target.row][target.column].symbol = HIT;
			break;

		case HIT:
		case MISS:
		default:
			break;
	}
}