#ifndef _BOARD_H
#define _BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <vld.h>

#define ROWS 10
#define COLS 10
#define WATER '~'
#define HIT 'S'
#define MISS 'm'

typedef enum
{
	FALSE, TRUE
} booleann;

typedef struct
{
	int row;
	int column;
	int shot;
} coordinate;

typedef struct 
{
	char symbol;
	coordinate position;
} cell;

/** Funkcja wypisuj¹ca aktualn¹ planszê
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza
@param show parametr pozwalaj¹cy wyœwietliæ odpowiedni¹ dla gracza wersje planszy
*/
void print_board(cell game_board[][COLS], booleann show);

/** Funkcja inicjalizuj¹ca planszê znakami '~' lub czytaj¹ca z pliku jeœli wywo³amy maina z parametrami
@param player1_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza lub komputera
@param argc jeden z parametrów wywo³ania programu
@param argv jeden z parametrów wywo³ania programu
*/
void initialize_game_board(cell player1_board[][COLS], cell player2_board[][COLS], int argc, char** argv);

/** Funkcja aktualizuj¹ca pola na planszy po wykonaniu strza³u
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza
@param target wspó³rzêdne wykonanego strza³u
*/
void update_game_board(cell game_board[][COLS], coordinate target);

#endif // !_BOARD_H

