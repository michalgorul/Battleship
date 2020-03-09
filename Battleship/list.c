#include "list.h"

void initialize_lists(stats** stats_pHead, ship **ship_pHead)
{
	initialize_stats_list(stats_pHead);
	initialize_ship_list(ship_pHead);
}

void initialize_stats_list(stats **pHead)
{	
	push_stats_front(pHead, 0);
	push_stats_back(*pHead, 1);
	clear_stats(pHead);
}

void initialize_ship_list(ship** pHead)
{
	push_ship_front(pHead, 'd', 2, "Destroyer");
	push_ship_front(pHead, 's', 3, "Submarine");
	push_ship_front(pHead, 'r', 3, "Cruiser");
	push_ship_front(pHead, 'b', 4, "Battleship");
	push_ship_front(pHead, 'c', 5, "Carrier");
}

void delete_stats_list(stats ** pHead)				
{
	stats * p = NULL;

	while (*pHead != NULL)
	{
		if (*pHead != NULL)
		{
			p = (*pHead)->pNext;
			free(*pHead);
			*pHead = p;
		}
	}
}		

void delete_ship_list(ship** pHead)
{
	ship* p = NULL;

	while (*pHead != NULL)
	{
		if (*pHead != NULL)
		{
			p = (*pHead)->pNext;
			free(*pHead);
			*pHead = p;
		}
	}
}

void delete_lists(stats** stats_pHead, ship** ship_pHead)
{
	delete_ship_list(ship_pHead);
	delete_stats_list(stats_pHead);
}

void push_stats_front(stats **pHead, int Player)				
{
	stats *current;
	current = (stats *)malloc(sizeof(stats));

	current->player = Player;
	current->pNext = (*pHead);
	*pHead = current;
}

void push_stats_back(stats *pHead, int Player)
{
	stats *current = pHead;
	stats *New = (stats *)malloc(sizeof(stats));

	New->player = Player;
	New->pNext = NULL;

	while (current->pNext) 
		current = current->pNext;
	
	current->pNext = New;
}

void push_ship_front(ship **pHead, char Symbol, int Length, char *Name)
{
	ship* current;
	current = (ship*)malloc(sizeof(ship));

	current->name = Name;
	current->symbol = Symbol;
	current->length = Length;

	current->pNext = (*pHead);
	*pHead = current;
}

void clear_stats(stats **pHead)
{
	if (pHead == NULL)
		printf("List is empty");
	else
	{
		stats *current = *pHead;
		do
		{
			current->num_of_hits = 0;
			current->num_of_misses = 0;
			current->total_shots = 0;
			current->accuracy = 0.0;

			current = current->pNext;
		} while (current != NULL);
	}
}

void change_value_in_list(stats **pHead, int Player, char* what_to_add)
{
	if (pHead == NULL)
		printf("List is empty");
	else
	{
		stats *current = *pHead;

		while(TRUE)
		{
			if (current->player == Player)
			{
				if (what_to_add == "hits")
					current->num_of_hits++;
				else if (what_to_add == "misses")
					current->num_of_misses++;

				current->total_shots++;

				current->accuracy = ((double)current->num_of_hits / (double)current->total_shots) * 100;

				break;
			}
			else
				current = current->pNext;
		}	
	}
}

