#include "game.h"
#include "menu.h"
#include "files.h"
#include "list.h"

booleann is_winner(stats **pHead, int Player)
{
	booleann is_win = FALSE;
	stats *current = *pHead;

	while (TRUE)
	{
		if (current->player == Player)
		{
			if (current->num_of_hits == 17)
				is_win = TRUE;

			break;
		}
		else
			current = current->pNext;
	}
	return is_win;
}

void end_decision(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, ship* sh_pHead, int argc, char** argv)
{
	printf(" \nYou decided to end the game\n");
	getchar();
	char option1, option2;
	printf(" Do you want to save that board states? [y/n]\n");
	scanf("%c", &option1);

	if (option1 == 'y')
	{
		if (argc < 2)
		{
			save_board_to_file("player1_board.txt", player2_board);
			save_board_to_file("player2_board.txt", player1_board);
			printf("\n Player 1 and 2 board states saved!\n");
		}		
			
		else
		{
			save_board_to_file(argv[1], player2_board);
			save_board_to_file(argv[2], player1_board);
			printf("\n Player 1 and 2 board states saved!\n");
		}
	}

	getchar();
	printf("\n Do you want to save your stats? [y/n]\n");
	scanf("%c", &option2);

	if (option2 == 'y')
		if (argc < 4)
			write_stats_in_file("stats.txt", st_pHead);
		else
			write_stats_in_file(argv[3], st_pHead);

	delete_lists(&st_pHead, &sh_pHead);
	exit(0);
}

coordinate get_target(cell player1_board[][COLS], cell player2_board[][COLS], stats *st_pHead, ship* sh_pHead, int argc, char** argv)
{
	coordinate target;
	int n = 0;

	printf("> Enter Target (ex. > 3 [row] 4 [column]):\n");
	printf("> ");
	scanf("%d %d", &target.row, &target.column);

	if (target.row == 11 && target.column == 11)
		end_decision(player1_board, player2_board, st_pHead, sh_pHead, argc, argv);
	
	else if ((target.row < 0 || target.row > 9) && (target.column < 0 || target.column > 9))
	{
		do
		{
			getchar();
			printf("Please select row from 0 to 9 and column from 0 to 9\n");
			printf("> Enter Target (ex. > 3 [row] 4 [column]):\n");
			scanf("%d %d", &target.row, &target.column);

			if ((target.row > 0 && target.row < 9) && (target.column > 0 && target.column < 9))
				break;

		} while ((target.row < 0 || target.row > 9) && (target.column < 0 || target.column > 9));
	}
	
	return target;
}

void player_shot(cell player1_board[][COLS], cell player2_board[][COLS], stats *st_pHead, int player, int sunk_ship[2][NUMBER_OF_SHIPS], ship *sh_pHead, int argc, char** argv)
{
	char ship_symbol;
	coordinate target;
	int shot;
	booleann has_ship_sunk;

	do																// wykonanie strza³u
	{
		target = get_target(player1_board, player2_board, st_pHead, sh_pHead, argc, argv);
		if(player == 0)
			shot = check_shot(player2_board, target.row, target.column);
		else
			shot = check_shot(player1_board, target.row, target.column);

		if (shot == -1)												//informuje gracza o b³êdnych danych wprowadzonych
			printf("> Try inputting another target!\n");

	} while (shot == -1);

	if (player == 0)
		ship_symbol = player2_board[target.row][target.column].symbol;			//zapisuje znak na planszy
	else
		ship_symbol = player1_board[target.row][target.column].symbol; 

	if (shot == 1)    //trafiony
	{ 
		printf("> %d, %d is a hit!\n", target.row, target.column);
					
		change_value_in_list(&st_pHead, player, "hits");			//zapisuje to w statystykach gracza
		
		if (player == 0)
			has_ship_sunk = check_sunk_ship(sunk_ship, !player, ship_symbol, player2_board);	//sprawdzam czy statek zosta³ zatopiony
		else
			has_ship_sunk = check_sunk_ship(sunk_ship, !player, ship_symbol, player1_board);	
	}

	else				//pud³o
	{       
		printf("> %d, %d is a miss!\n", target.row, target.column);
							
		change_value_in_list(&st_pHead, player, "misses");					//zapisuje to w statystykach gracza
	}

	if (player == 0)
		update_game_board(player2_board, target);
	else
		update_game_board(player1_board, target);
}

coordinate near_shot(cell player_board[][COLS], shots* shots_info)
{
	int shot;
	coordinate target;
	int i = 0, j = 0, counter = 0;

	while (1)
	{
		do
		{
			counter++;
			if (counter > 10000)
			{
				target = easy(player_board, 1, 8);
				break;
			}
			
			i = get_random_number(-1, 3);

			if (i == 1 || i == -1)
				j = 0;
			else
				do
				{
					j = get_random_number(-1, 3);
				} while (j == 0);

				target.row = i + shots_info->last_hit_co.row;
				target.column = j + shots_info->last_hit_co.column;

				shot = check_shot(player_board, target.row, target.column);
		} while (shot == -1);
			
		if ((target.row > 0 && target.row < 9) && (target.column > 0 && target.column < 9))
			break;
	}
	target.shot = shot;
	
	return target;
}

coordinate easy(cell player_board[][COLS], int less, int more)
{
	int shot;
	coordinate target;

	do 
	{
		target.column = get_random_number(less, more);	
		target.row = get_random_number(less, more);

		shot = check_shot(player_board, target.row, target.column);
		target.shot = shot;
	} while (shot == -1);
	
	return target;
}

coordinate medium(cell player_board[][COLS], shots *shots_info)
{
	coordinate target;

	if (shots_info->if_last_shot == FALSE || shots_info->has_ship_sunk == TRUE)				//je¿eli wczeœniej nie trafiono lub zatopiono
		target = easy(player_board, 1, ROWS - 2);

	else								//je¿eli wczeœniej trafiono statek i go nie zatopiono
		target = near_shot(player_board, shots_info);

	return target;
}

coordinate hard(cell player_board[][COLS], shots* shots_info, stats *pHead)
{
	int shot;
	coordinate target;

	if (pHead->num_of_hits > 13)
		target = make_hit(player_board);	
																	//je¿eli wczeœniej nie trafiono lub zatopiono
	 else if ((shots_info->has_ship_sunk == TRUE && shots_info->if_last_shot == TRUE) || (shots_info->has_ship_sunk == FALSE &&
		shots_info->if_last_shot == FALSE && (shots_info->first_shot.column < 1 || shots_info->first_shot.column > 8)))				
	{
		shots_info->has_ship_sunk = FALSE;
		target = easy(player_board, 1, ROWS - 2);
	}																				//je¿eli wczeœniej nie trafiono i nie zatopiono
																					//wczeœniej trafionego statku
	else if (shots_info->if_last_shot == FALSE && (shots_info->first_shot.column > 1 && shots_info->first_shot.column < 8))						 
	{																																						
		if (player_board[shots_info->first_shot.row - 1][shots_info->first_shot.column].symbol == HIT)
		{
			int i = 0, j = 0;
			do
			{
				i++;
				target.row = shots_info->first_shot.row - i;
				target.column = shots_info->first_shot.column;
				for (j = 0; j < 5; j++)
				{
					if (player_board[target.row][target.column].symbol == MISS)
					{
						target.row = shots_info->first_shot.row + j + 1;
						break;
					}
				}
				shot = check_shot(player_board, target.row, target.column);
				target.shot = shot;
			} while (shot == -1);
		}
		else if (player_board[shots_info->first_shot.row + 1][shots_info->first_shot.column].symbol == HIT)
		{
			int i = 0, j = 0;
			do
			{
				i++;
				target.row = shots_info->first_shot.row + i;
				target.column = shots_info->first_shot.column;

				for (j = 0; j < 5; j++)
				{
					if (player_board[target.row][target.column].symbol == MISS)
					{
						target.row = shots_info->first_shot.row - j - 1;
						break;
					}
				}
				shot = check_shot(player_board, target.row, target.column);
				target.shot = shot;
			} while (shot == -1);
		}
		else if (player_board[shots_info->first_shot.row][shots_info->first_shot.column - 1].symbol == HIT)
		{
			int i = 0, j = 0;
			do
			{
				i++;
				target.row = shots_info->first_shot.row;
				target.column = shots_info->first_shot.column - i;

				for (j = 0; j < 5; j++)
				{
					if (player_board[target.row][target.column].symbol == MISS)
					{
						target.column = shots_info->first_shot.column + j + 1;
						break;
					}
				}
				shot = check_shot(player_board, target.row, target.column);
				target.shot = shot;
			} while (shot == -1);
		}
		else if (player_board[shots_info->first_shot.row][shots_info->first_shot.column + 1].symbol == HIT)
		{
			int i = 0, j = 0;
			do
			{
				i++;
				target.row = shots_info->first_shot.row;
				target.column = shots_info->first_shot.column + i;

				for (j = 0; j < 5; j++)
				{
					if (player_board[target.row][target.column].symbol == MISS)
					{
						target.column = shots_info->first_shot.column - j - 1;
						break;
					}
				}
				shot = check_shot(player_board, target.row, target.column);
				target.shot = shot;
			} while (shot == -1);
		}

		else								//je¿eli wczeœniej trafiono statek i go nie zatopiono
		{
			target = near_shot(player_board, shots_info);
		}
	}

	else			//je¿eli wczeœniej trafiono statek i go nie zatopiono
	{
		target = near_shot(player_board, shots_info);
	}

	return target;
}

coordinate make_hit(cell player_board[][COLS])
{
	coordinate target;

	do
	{
		target = easy(player_board, 1, 8);

	} while (player_board[target.row][target.column].symbol == WATER || 
			 player_board[target.row][target.column].symbol == HIT ||
			 player_board[target.row][target.column].symbol == MISS );

	return target;
}

void ai_shot(cell player_board[][COLS], int difficulty, int sunk_ship[2][NUMBER_OF_SHIPS], int player, stats **pHead, shots *shots_info)
{
	char ship_symbol;											
	coordinate target;																										
																																												//difficulty == 2 -> mniej losowe trafy, brdziej przemyœlane												
	if (difficulty == 1)										//difficulty == 1 -> losowe trafy
		target = easy(player_board, 0, ROWS - 1);

	else if (difficulty == 2)									//difficulty == 2 -> mniej losowe trafy, brdziej przemyœlane		
		target = medium(player_board, shots_info);
		
	else														//difficulty ==  -> bardziej "ludzkie" szcza³y
		target = hard(player_board, shots_info, *pHead);

	ship_symbol = player_board[target.row][target.column].symbol;
	update_game_board(player_board, target);
	print_board(player_board, TRUE);

	if (target.shot == 1)    //trafiony
	{
		printf("> Computer has hit %d, %d!\n", target.row, target.column);
		change_value_in_list(pHead, player, "hits");							//zapisuje to w statystykach gracza							

		shots_info->last_hit_co.row = target.row;
		shots_info->last_hit_co.column = target.column;
		shots_info->if_last_shot = TRUE;										//zapisuje koordynaty ostatniego szcza³u

		shots_info->has_ship_sunk = check_sunk_ship(sunk_ship, !player, ship_symbol, player_board);
		
		if (difficulty == 3)
		{
			if (shots_info->first_shot.column < 1 || shots_info->first_shot.column > 8)
			{
				shots_info->first_shot.row = target.row;
				shots_info->first_shot.column = target.column;
			}

			if (shots_info->has_ship_sunk == TRUE)
			{
				shots_info->first_shot.row = 0;
				shots_info->first_shot.column = 0;
			}
		}				
		Sleep(WAIT + 2000);
	}

	else											//pud³o
	{
		printf("> Computer has missed %d, %d!\n", target.row, target.column);
		change_value_in_list(pHead, player, "misses");							//zapisuje to w statystykach gracza							
		shots_info->if_last_shot = FALSE;

		if (shots_info->first_shot.column > 0 && shots_info->first_shot.column < 9)
		{
			shots_info->last_hit_co.column = shots_info->first_shot.column;
			shots_info->last_hit_co.row = shots_info->first_shot.row;			//zapisuje koordynaty ostatniego szcza³u
		}													
		Sleep(WAIT + 600);
	}	
}

int check_shot(cell board[][COLS], int row, int column) 
{
	int hit = -2;

	switch (board[row][column].symbol)
	{
		case WATER:			//pud³o
			hit = 0;
			break;

		case CARRIER:		//trafienie w statek
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			hit = 1;
			break; 

		case HIT:			// trafienie we wczeœniejsze trafienie
		case MISS:
		default:
			hit = -1;
			break;
	}
	return hit;
}

int who_first(void)
{
	int player;
	player = get_random_number(0, 10000) % 2;
	printf("> Player %d has been randomly selected to go first.\n", player + 1);
	Sleep(WAIT);
	printf("> Hit <ENTER> to continue!\n");
	system("cls");

	return player;
}

void play(cell player1_game_board[][COLS], cell player2_game_board[][COLS], booleann with_computer, stats **pHead, int difficulty, ship *sh_pHead, int argc, char** argv)
{
	int player;
	shots shots_info = { 0 };

	int sunk_ship[2][NUMBER_OF_SHIPS] = {{5, 4, 3, 3, 2},
										 {5, 4, 3, 3, 2}};

	getchar();
	printf("Now computer will choose who starts\n");
	Sleep(WAIT + 500);
	player = who_first();
	printf("Player %d starts!\n", player + 1);
	Sleep(WAIT + 500);
	system("cls");

	while (TRUE)
	{
		system("cls");
		printf("Player %d's turn.\n", player + 1);

		switch (player)
		{
			case PLAYER_ONE:
			{
				printf("> Player 2's Board:\n");
				print_board(player2_game_board, FALSE);
				player_shot(player1_game_board, player2_game_board, *pHead, player, sunk_ship, sh_pHead, argc, argv);
				Sleep(WAIT);
			}break;

			case PLAYER_TWO:
			{
				if (with_computer == TRUE)
					ai_shot(player1_game_board, difficulty, sunk_ship, player, pHead, &shots_info);

				else
				{
					printf("> Player 2's Board:\n");
					print_board(player1_game_board, FALSE);
					player_shot(player1_game_board, player2_game_board, *pHead, player, sunk_ship, sh_pHead, argc, argv);
					Sleep(WAIT);
				}
			}break;
		}

		if (is_winner(pHead, player)) 
		{
			printf("\n> Player %d wins!\n", player + 1);
			printf("\n Click enter to continue...\n");
			getchar();
			getchar();
			write_stats(*pHead);
			write_stats_in_file("stats.txt", *pHead);
			break;
		}
		player = !player;		//zmiana graczy
	}
}

