#ifndef _MENU_H
#define _MENU_H

#include "board.h"
#include "ships.h"
#include "game.h"

/** Funkcja wypisuj�ca ekran powitalny
*/
void welcome_screen(void);

/** G��wna funkcja odpowiedzialna za pocz�tkow� faz� gry - wybieramy tu poziom trudno�ci, spos�b rozmieszczenia statk�w itp.
@param player1_game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy gracza o numerze 1
@param player2_game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy gracza o numerze 2
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param option_with_who informacja, czy gramy z komputerem czy z innym graczem (TRUE - gramy z komputerem)
@param difficulty wybrana przez u�ytkownika trudno��
@param argc jeden z parametr�w wywo�ania programu
*/
void menu(cell player1_game_board[][COLS], cell player2_game_board[][COLS], ship *pHead, booleann *option_with_who, int *difficulty, int argc);

/** Funkcja w kt�rej wybieramy z kim chcemy zagra� - z komputerem czy innym graczem
@return TRUE - z komputerem, FALSE - z innym graczem
*/
booleann with_who(void);

/** Funkcja w kt�rej wybieramy jak chcemy rozmie�ci� statki na planszy
@param player numer gracza wybieraj�cego spos�b rozmieszczenia statk�w
@return TRUE - r�cznie, FALSE - losowo
*/
booleann way_of_placing(int player);

/** Funkcja w kt�rej wybieramy na jakim poziomie trudno�ci chcemy gra�
@return wybrany przez nas poziom trudno�ci
*/
int what_difficulty(void);

/** Funkcja wypisuj�ca statystyki na ekran
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
*/
void write_stats(stats *pHead);

#endif // !_MENU_H
