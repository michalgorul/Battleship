#include "ships.h"
#include "board.h"
#include "game.h"
#include "files.h"

void put_ship_on_board(cell game_board[][COLS], char Symbol, ship *pHead, coordinate position, int direction)
{
	int i;
	ship* current = pHead;

	if (pHead == NULL)
		printf("List is empty");
	else
	{
		while (TRUE)
		{
			if (current->symbol == Symbol)
				break;		
			else
				current = current->pNext;
		}
	}

	for (i = 0; i < current->length; i++) {
		if (direction == HORIZONTAL)
			game_board[position.row][position.column + i].symbol = current->symbol;
		else 
			game_board[position.row + i][position.column].symbol = current->symbol;
	}
}

void randomly_place_ships_on_board(cell game_board[][COLS], ship *pHead) 
{
	coordinate position;
	ship* current;
	int direction = -1;
	int i = 0;

	if (pHead == NULL)
		printf("List is empty");
	else
	{
		current = pHead;
		do
		{
			while (1)
			{
				direction = get_random_number(0, 10000) % 2;					// 0 -> poziomo, 1 -> pionowo 
				position = generate_position(direction, current->length);

				if (is_valid(game_board, position, direction, current->length))
					break;
			}
			put_ship_on_board(game_board, current->symbol, pHead, position, direction);

			current = current->pNext;
		} while (current != NULL);
	}
}

void manually_place_ships_on_board(cell game_board[][COLS], ship *pHead)
{
	int direction = 0, i = 0, n = 0;

	coordinate position;
	booleann valid = FALSE;
	ship* current;

	if (pHead == NULL)
		printf("List is empty");
	else
	{
		current = pHead;
		do
		{
			do
			{
				system("cls");
				print_board(game_board, TRUE);
				printf("\n Set the %s! Please select first cell(row and after space column)\n", current->name);
				scanf("%d %d", &position.row, &position.column);
				printf(" Now choose direction (horizontal - 0, vertical - 1)\n");
				scanf("%d", &direction);

				valid = is_valid(game_board, position, direction, current->length);

				if (valid == TRUE)
				{
					put_ship_on_board(game_board, current->symbol, pHead, position, direction);
					break;
				}

				else
				{
					printf("> Try inputting another cell!\n");
					Sleep(WAIT);
				}
			} while (1);

			current = current->pNext;
		} while (current != NULL);
	}
}

coordinate generate_position(int direction, int length) 
{
	coordinate position;

	if (direction == HORIZONTAL) 
	{
		position.row = get_random_number(0, ROWS);
		position.column = get_random_number(0, COLS - length);
	}
	else 
	{ 
		position.row = get_random_number(0, ROWS - length);
		position.column = get_random_number(0, COLS);
	}

	return position;
}

booleann is_valid(cell game_board[][COLS], coordinate position, int direction, int length)
{
	int i;
	booleann valid = TRUE;

	for (i = 0; i < length; i++)
	{
		if (direction == HORIZONTAL)
		{
			if (game_board[position.row][position.column + i].symbol != WATER ||
				game_board[position.row - 1][position.column + i].symbol != WATER ||
				game_board[position.row + 1][position.column + i].symbol != WATER ||			//sprawdzam wszystkie komórki woko³
				game_board[position.row][position.column + i - 1].symbol != WATER ||
				game_board[position.row][position.column + i + 1].symbol != WATER ||
				game_board[position.row + 1][position.column + i + 1].symbol != WATER ||
				game_board[position.row - 1][position.column + i - 1].symbol != WATER ||
				game_board[position.row + 1][position.column + i - 1].symbol != WATER ||
				game_board[position.row - 1][position.column + i + 1].symbol != WATER ||
				position.row < 1 || position.row > 8 || position.column < 1 || position.column + 1 > 8 || position.column + length > 9)

				valid = FALSE;
		}
		else
		{
			if (game_board[position.row + i][position.column].symbol != WATER ||
				game_board[position.row + i - 1][position.column].symbol != WATER ||
				game_board[position.row + i + 1][position.column].symbol != WATER ||
				game_board[position.row + i][position.column - 1].symbol != WATER ||
				game_board[position.row + i][position.column + 1].symbol != WATER ||				//sprawdzam wszystkie komórki woko³
				game_board[position.row + i + 1][position.column + 1].symbol != WATER ||
				game_board[position.row + i - 1][position.column - 1].symbol != WATER ||
				game_board[position.row + i + 1][position.column - 1].symbol != WATER ||
				game_board[position.row + i - 1][position.column + 1].symbol != WATER ||
				position.row - 1 < 1 || position.row > 8 || position.column < 1 || position.column > 8)

				valid = FALSE;
		}
	}
	return valid;
}

booleann check_sunk_ship(int sunk_ship[][NUMBER_OF_SHIPS], int player, char ship_symbol, cell game_board[][COLS])
{
	booleann sunk = FALSE;

	switch (ship_symbol)
	{
		case CARRIER:
		{
			sunk_ship[player][0] -= 1;
			if (sunk_ship[player][0] == 0)
			{
				printf("> Player %d's Carrier is sunk!\n", player + 1);
				Sleep(WAIT);
				sunk = TRUE;
			}
			break;
		}	
		case BATTLESHIP:
		{
			sunk_ship[player][1] -= 1;
			if (sunk_ship[player][1] == 0)
			{
				printf("> Player %d's Battleship is sunk!\n", player + 1);
				Sleep(WAIT);
				sunk = TRUE;
			}
			break;

		}	
		case CRUISER:
		{
			sunk_ship[player][2] -= 1;
			if (sunk_ship[player][2] == 0)
			{
				printf("> Player %d's Cruiser is sunk!\n", player + 1);
				Sleep(WAIT);
				sunk = TRUE;
			}
			break;
		}	
		case SUBMARINE:
		{
			sunk_ship[player][3] -= 1;
			if (sunk_ship[player][3] == 0)
			{
				printf("> Player %d's Submarine is sunk!\n", player + 1);
				Sleep(WAIT);
				sunk = TRUE;
			}
			break;
		}	
		case DESTROYER:
		{
			sunk_ship[player][4] -= 1;
			if (sunk_ship[player][4] == 0)
			{
				printf("> Player %d's Destroyer is sunk!\n", player + 1);
				Sleep(WAIT);
				sunk = TRUE;
			}
			break;
		}		
	}
	return sunk;
}

int get_random_number(int less, int more) 
{
	return rand() % more + less;
}
