#include "menu.h"
#include "ships.h"
#include "board.h"
#include "game.h"

void welcome_screen(void) 
{	
	printf("\n		########     ###    ######## ######## ##       ########  ######  ##     ## #### ########\n");
	printf("		##     ##   ## ##      ##       ##    ##       ##       ##    ## ##     ##  ##  ##     ##\n");
	printf("		##     ##  ##   ##     ##       ##    ##       ##       ##       ##     ##  ##  ##     ##\n");
	printf("		########  ##     ##    ##       ##    ##       ######    ######  #########  ##  ########\n");
	printf("		##     ## #########    ##       ##    ##       ##             ## ##     ##  ##  ##\n");
	printf("		##     ## ##     ##    ##       ##    ##       ##       ##    ## ##     ##  ##  ##\n");
	printf("		########  ##     ##    ##       ##    ######## ########  ######  ##     ## #### ##\n");
	printf("\n\n");
	printf("							RULES:\n\n");
	printf(" 1. This is a two player game.\n\n");
	printf(" 2. Player 1 is you and Player 2 is the computer or other player.\n\n");
	printf(" 3. A person will be asked if he wants to manually input coordinates\n");
	printf(" for the game board or have randomly generated game board,\n");
	printf(" computer's board will be generated randomly \n\n");
	printf(" 4. There are five types of ships to be placed by longest length to the\n");
	printf(" shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
	printf(" has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells.\n");
	printf(" Because of the small number of ships, each ship can be placed only with one or \n");
	printf(" more gaps between each other and the edges. \n\n");
	printf(" 5. It is randomly selected which player goes first.\n\n");
	printf(" 6. The game begins as each player tries to guess the location of the ships\n");
	printf(" of the opposing player's game board; [H] hit and [M] miss\n\n");
	printf(" 7. You can not place ship on borders and next to another ship\n\n");
	printf(" 8. If you want to exit game enter '11 11' while entering target\n\n");
	printf(" 9. First player who will shot all enemy ships wins\n");
	printf(" Press enter to continue...");
	getchar();
	system("cls");
}

booleann with_who(void)
{
	char option_with_who;
	int n = 0;

	printf("> Do you want to play with computer or other person?\n");
	printf("> [1] With computer\n");
	printf("> [2] With other person\n");
	printf("> Enter Option: ");
	scanf("%c", &option_with_who);

	int i_option_with_who = atoi(&option_with_who);

	if (i_option_with_who != 1 && i_option_with_who != 2)
	{
		do
		{
			getchar();
			printf("Please select option 1) or 2)\n");
			printf("> Enter Option: ");
			scanf("%c", &option_with_who);
			int i_option_with_who = option_with_who - '0';
			if (i_option_with_who == 1 || i_option_with_who == 2)
				break;
		} while (i_option_with_who != 1 && i_option_with_who != 2);
	}

	if (i_option_with_who == 1)
		return TRUE;					//true -> z komputerem
	else
		return FALSE;					//false -> z innym graczem
}

int what_difficulty(void)
{
	char difficulty;
	getchar();
	system("cls");
	printf("> What difficulty you choose?\n");
	printf("> [1] Easy\n");
	printf("> [2] Medium\n");
	printf("> [3] Hard\n");
	printf("> Enter option: ");
	scanf("%c", &difficulty);
	int i_difficulty = atoi(&difficulty);

	if (i_difficulty != 1 && i_difficulty != 2 && i_difficulty != 3)
	{
		do
		{
			getchar();
			printf("Please choose between 1) or 2)\n");
			printf("> Enter option:");
			scanf("%c", &difficulty);
			int i_difficulty = atoi(&difficulty);
			if (i_difficulty == 1 || i_difficulty == 2 || i_difficulty == 3)
				break;
		} while (i_difficulty != 1 && i_difficulty != 2 && i_difficulty != 3);
	}
	return i_difficulty;
}

booleann way_of_placing(int player)
{
	char option;
	int i_option;
	getchar();				
	system("cls");	
	printf("> PLAYER %d:\n", player);													//by³y du¿e problemy z buforem
	printf("> Do you want to place ships manually or randomly?\n");
	printf("> [1] Manually\n");
	printf("> [2] Randomly\n");
	printf("> Enter Option: ");
	scanf("%c", &option);
	i_option = atoi(&option);
	if (i_option != 1 && i_option != 2)
	{
		do
		{
			getchar();
			printf("Please select option 1) or 2)\n");
			printf("> Enter Option: ");
			scanf("%c", &option);
			int i_option = atoi(&option);
			if (i_option == 1 || i_option == 2)
				break;
		} while (i_option != 1 && i_option != 2);
	}

	if (i_option == 1)
		return TRUE;					//true -> rêcznie
	else
		return FALSE;					//false -> losowo
}

void menu(cell player1_game_board[][COLS], cell player2_game_board[][COLS], ship *pHead, booleann *option_with_who, int *difficulty, int argc)
{
	booleann option_how1, option_how2;

	welcome_screen();

	*option_with_who = with_who();			//true -> z komputerem, false -> z innym graczem

	if (*option_with_who == TRUE)
	{
		*difficulty = what_difficulty();
		if (argc < 6)
		{
			option_how1 = way_of_placing(1);			//true -> rêcznie, false -> losowo

			if (option_how1 == TRUE)
				manually_place_ships_on_board(player1_game_board, pHead);
			else
				randomly_place_ships_on_board(player1_game_board, pHead);

			randomly_place_ships_on_board(player2_game_board, pHead);
		}	
	}

	else
	{
		if (argc < 6)
		{
			option_how1 = way_of_placing(1);			//true -> manually, false -> randomly	

			if (option_how1 == TRUE)
				manually_place_ships_on_board(player1_game_board, pHead);
			else
				randomly_place_ships_on_board(player1_game_board, pHead);

			option_how2 = way_of_placing(2);			//true -> manually, false -> randomly	

			if (option_how2 == TRUE)
				manually_place_ships_on_board(player2_game_board, pHead);
			else
				randomly_place_ships_on_board(player2_game_board, pHead);
		}		
	}

	printf("\n Ships have been placed\n");
	Sleep(WAIT);
	system("cls");
}

void write_stats(stats *pHead)
{
	stats *p = pHead;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("\n	Date: %d-%d-%d	      Time: %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	printf("\n+===================================================+\n");
	printf("|                    PLAYER STATS                   |\n");
	printf("+---------------------------------------------------+\n");
	printf("| PLAYER 1 : %5d hits                             |\n", p->num_of_hits);
	printf("|            %5d misses                           |\n", p->num_of_misses);
	printf("|            %5d total shots                      |\n", p->total_shots);
	printf("|            %5.2lf%% accuracy                        |\n", p->accuracy);

	p = p->pNext;

	printf("|						    |\n");
	printf("| PLAYER 2 : %5d hits                             |\n", p->num_of_hits);
	printf("|            %5d misses                           |\n", p->num_of_misses);
	printf("|            %5d total shots                      |\n", p->total_shots);
	printf("|            %5.2lf%% accuracy                        |\n", p->accuracy);
	printf("+===================================================+\n\n");
}