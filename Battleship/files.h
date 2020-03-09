#ifndef _FILES_H
#define _FILES_H

#include "board.h"
#include "game.h"

typedef FILE* file;

/** Funkcja zapisuj¹ca statystyki w pliku o podanej nazwie
@param name nazwa pliku w którym zapisuje informacje
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach 
*/
void write_stats_in_file(char *name, stats *pHead);

/** Funkcja czytaj¹ca planszê z pliku i zapisuj¹ca j¹ w tablicy dwuwymiarowej
@param name nazwa pliku w którego zczytuje informacje
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
*/
void read_board_from_file(char *name, cell game_board[][COLS]);

/** Funkcja zapisuj¹ca aktualny stan planszy do pliku o podanej nazwie
@param name nazwa pliku w którego zczytuje informacje
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
*/
void save_board_to_file(char *name, cell game_board[][COLS]);

#endif // !_FILES_H

