#ifndef _SHIPS_H
#define _SHIPS_H

#include "board.h"

#define HORIZONTAL 0
#define VERTICAL 1
#define NUMBER_OF_SHIPS 5

#define CARRIER       'c'
#define BATTLESHIP    'b'
#define CRUISER       'r'
#define SUBMARINE     's'
#define DESTROYER     'd'

typedef struct _ship
{
	char symbol;
	int length;
	char *name;
	struct _ship *pNext;
} ship;

/** Funkcja ustawiaj¹ca statek na planszy
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param Symbol symbol danego statku
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param position wspó³rzêdne na których ustawiony zostanie statek
@param direction kierunek w którym zostanie ustawiony statek (poziomo lub pionowo)
*/
void put_ship_on_board(cell game_board[][COLS], char Symbol, ship* pHead, coordinate position, int direction);

/** Funkcja ustawiaj¹ca losowo statki na planszy
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void randomly_place_ships_on_board(cell game_board[][COLS], ship* pHead);

/** Funkcja generuj¹ca pozycje do ustawienia statku
@param direction kierunek w którym zostanie ustawiony statek (poziomo lub pionowo)
@param length d³ugoœæ statku dla którego zostanie wygenerowana pozycja
@return wspó³rzêdne wygenerowanej pozycji
*/
coordinate generate_position(int direction, int length);

/** Funkcja sprawdzaj¹ca czy dany statek zaton¹³
@param sunkShip dwuwymiarowa tablica przechowuj¹ca informacje o tym ile ka¿dy statek danego gracza ma nietraionych pól
@param player numer gracza strzelaj¹cego
@param ship_symbol symbol statku w postaci literki
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@return informacja czy dany statek zaton¹³
*/
booleann check_sunk_ship(int sunkShip[][NUMBER_OF_SHIPS], int player, char ship_symbol, cell game_board[][COLS]);

/** Funkcja sprawdzaj¹ca czy dana pozycja jest dostêpna
@param board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param position wspó³rzêdne na których ma byæ ustawiony statek
@param direction kierunek w którym zostanie ustawiony statek (poziomo lub pionowo)
@param length d³ugoœæ statku dla którego zostanie wygenerowana pozycja
@return informacja czy dana pozycja jest dostêpna
*/
booleann is_valid(cell board[][COLS], coordinate position, int direction, int length);

/** Funkcja ustawiaj¹ca manualnie statki na planszy
@param game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void manually_place_ships_on_board(cell game_board[][COLS], ship *pHead);

/** Funkcja losuj¹ca jedn¹ liczbê z danego zakresu
@param less zakres liczb do losowania
@param more zakres liczb do losowania
@return losowa liczba
*/
int get_random_number(int less, int more);

#endif // !_SHIPS_H

