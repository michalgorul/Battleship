#include "board.h"
#include "menu.h"
#include "game.h"
#include "files.h"
#include "list.h"


int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));
	int difficulty;
	booleann option_with_who;
	
	cell player1_game_board[ROWS][COLS];
	cell player2_game_board[ROWS][COLS];

	shots shots_info = { 0 };
	 
	stats *stats_Head = NULL;
	ship *ship_Head = NULL;
										 
	initialize_game_board(player1_game_board, player2_game_board, argc, argv);
	initialize_lists(&stats_Head, &ship_Head);

	menu(player1_game_board, player2_game_board, ship_Head, &option_with_who, &difficulty, argc);

	play(player1_game_board, player2_game_board, option_with_who, &stats_Head, difficulty, ship_Head, argc, argv);

	delete_lists(&stats_Head, &ship_Head);

	return 0;
} 