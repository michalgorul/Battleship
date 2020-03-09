#include "files.h"

void write_stats_in_file(char *name, stats *pHead)
{
	file fp;								// u¿ywamy metody wysokopoziomowej - musimy mieæ zatem identyfikator pliku 

	if ((fp = fopen(name, "w")) == NULL) 
	{
		printf("Can't open\n");
		exit(1);
	}
	
	stats *p = pHead;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	fprintf(fp, "	Date: %d-%d-%d	      Time: %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	fprintf(fp, "\n+===================================================+\n");
	fprintf(fp, "|                    PLAYER STATS                   |\n");
	fprintf(fp, "+---------------------------------------------------+\n");
	fprintf(fp, "| PLAYER 1 : %5d hits                             |\n", p->num_of_hits);
	fprintf(fp, "|            %5d misses                           |\n", p->num_of_misses);
	fprintf(fp, "|            %5d total shots                      |\n", p->total_shots);
	fprintf(fp, "|            %5.2lf%% accuracy                        |\n", p->accuracy);

	p = p->pNext;

	fprintf(fp, "|						    |\n");
	fprintf(fp, "| PLAYER 2 : %5d hits                             |\n", p->num_of_hits);
	fprintf(fp, "|            %5d misses                           |\n", p->num_of_misses);
	fprintf(fp, "|            %5d total shots                      |\n", p->total_shots);
	fprintf(fp, "|            %5.2lf%% accuracy                        |\n", p->accuracy);
	fprintf(fp, "+===================================================+\n\n");
	
	printf("\n Stats saved!\n\n");

	fclose(fp); // zamknij plik 
}

void read_board_from_file(char *name, cell game_board[][COLS])
{
	file fp;
	int i = 0, j = 0;

	if ((fp = fopen(name, "r")) == NULL) 
	{
		printf("Can't open\n");
		exit(1);
	}

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			fscanf(fp, "%c", &game_board[i][j].symbol);
			game_board[i][j].position.row = i;
			game_board[i][j].position.column = j;
		}
		fscanf(fp, "\n");								//pobieram znak przejœcia do nastêpnej linii
	}
	fclose(fp); // zamknij plik 
}

void save_board_to_file(char *name, cell game_board[][COLS])
{
	file fp;
	int i = 0, j = 0;

	if ((fp = fopen(name, "w")) == NULL)
	{
		printf("Can't open\n");
		exit(1);
	}

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			fprintf(fp, "%c", game_board[i][j].symbol);
			
		fprintf(fp, "\n");			//znak przejœcia do nastêpnej linii
	}

	fclose(fp); // zamknij plik 
}
