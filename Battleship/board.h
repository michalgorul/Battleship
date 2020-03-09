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

/** Funkcja wypisuj�ca aktualn� plansz�
@param game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza
@param show parametr pozwalaj�cy wy�wietli� odpowiedni� dla gracza wersje planszy
*/
void print_board(cell game_board[][COLS], booleann show);

/** Funkcja inicjalizuj�ca plansz� znakami '~' lub czytaj�ca z pliku je�li wywo�amy maina z parametrami
@param player1_board dwuwymiarowa tablica przechowuj�ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza lub komputera
@param argc jeden z parametr�w wywo�ania programu
@param argv jeden z parametr�w wywo�ania programu
*/
void initialize_game_board(cell player1_board[][COLS], cell player2_board[][COLS], int argc, char** argv);

/** Funkcja aktualizuj�ca pola na planszy po wykonaniu strza�u
@param game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza
@param target wsp�rz�dne wykonanego strza�u
*/
void update_game_board(cell game_board[][COLS], coordinate target);

#endif // !_BOARD_H

