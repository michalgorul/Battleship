#ifndef _FILES_H
#define _FILES_H

#include "board.h"
#include "game.h"

typedef FILE* file;

/** Funkcja zapisuj�ca statystyki w pliku o podanej nazwie
@param name nazwa pliku w kt�rym zapisuje informacje
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach 
*/
void write_stats_in_file(char *name, stats *pHead);

/** Funkcja czytaj�ca plansz� z pliku i zapisuj�ca j� w tablicy dwuwymiarowej
@param name nazwa pliku w kt�rego zczytuje informacje
@param game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
*/
void read_board_from_file(char *name, cell game_board[][COLS]);

/** Funkcja zapisuj�ca aktualny stan planszy do pliku o podanej nazwie
@param name nazwa pliku w kt�rego zczytuje informacje
@param game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
*/
void save_board_to_file(char *name, cell game_board[][COLS]);

#endif // !_FILES_H

