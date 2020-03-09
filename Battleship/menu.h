#ifndef _MENU_H
#define _MENU_H

#include "board.h"
#include "ships.h"
#include "game.h"

/** Funkcja wypisuj¹ca ekran powitalny
*/
void welcome_screen(void);

/** G³ówna funkcja odpowiedzialna za pocz¹tkow¹ fazê gry - wybieramy tu poziom trudnoœci, sposób rozmieszczenia statków itp.
@param player1_game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy gracza o numerze 1
@param player2_game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy gracza o numerze 2
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param option_with_who informacja, czy gramy z komputerem czy z innym graczem (TRUE - gramy z komputerem)
@param difficulty wybrana przez u¿ytkownika trudnoœæ
@param argc jeden z parametrów wywo³ania programu
*/
void menu(cell player1_game_board[][COLS], cell player2_game_board[][COLS], ship *pHead, booleann *option_with_who, int *difficulty, int argc);

/** Funkcja w której wybieramy z kim chcemy zagraæ - z komputerem czy innym graczem
@return TRUE - z komputerem, FALSE - z innym graczem
*/
booleann with_who(void);

/** Funkcja w której wybieramy jak chcemy rozmieœciæ statki na planszy
@param player numer gracza wybieraj¹cego sposób rozmieszczenia statków
@return TRUE - rêcznie, FALSE - losowo
*/
booleann way_of_placing(int player);

/** Funkcja w której wybieramy na jakim poziomie trudnoœci chcemy graæ
@return wybrany przez nas poziom trudnoæci
*/
int what_difficulty(void);

/** Funkcja wypisuj¹ca statystyki na ekran
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
*/
void write_stats(stats *pHead);

#endif // !_MENU_H
