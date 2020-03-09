#ifndef _GAME_H
#define _GAME_H

#include "board.h"
#include "ships.h"
#include <windows.h>
#include <vld.h>

#define PLAYER_ONE    0
#define PLAYER_TWO    1

#define WAIT 1400

typedef struct _stats
{
	int player;
	int num_of_hits;
	int num_of_misses;
	int total_shots;
	double accuracy;
	struct _stats *pNext;
} stats;

typedef struct _shots
{
	coordinate last_hit_co;
	coordinate first_shot;
	booleann has_ship_sunk;
	booleann if_last_shot;
} shots;

/** Funkcja losuj�ca cyfr� 0 lub 1 w celu wybrania gracza rozpoczynaj�cego rozgrywk�
@return numer gracza rozpoczynaj�cego rozgrywk�
*/
int who_first(void);

/** Funkcja sprawdzaj�ca czy dany gracz wystrzela� ju� wszystkie statki
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param Player numer sprawdzanego gracza
@return warto�� TRUE je�li dany gracz zwyci�y�, FALSE je�li nie
*/
booleann is_winner(stats **pHead, int Player);

/** Funkcja wywo�ywana, gdy gracz postanowi� zako�czy� rozgrywk�. Zapisuje stan planszy i statystyk je�li gracz sobie tego za�yczy i usuwa listy
@param player1_board dwuwymiarowa tablica przechowuj�ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param sh_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param argc jeden z parametr�w wywo�ania programu
@param argv jeden z parametr�w wywo�ania programu
@return wsp�rz�dne strza�u
*/
void end_decision(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, ship* sh_pHead, int argc, char** argv);

/** Funkcja pobieraj�ca od gracza wsp�rz�dne do strza�u
@param player1_board dwuwymiarowa tablica przechowuj�ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param sh_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param argc jeden z parametr�w wywo�ania programu
@param argv jeden z parametr�w wywo�ania programu
@return wsp�rz�dne strza�u
*/
coordinate get_target(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, ship* sh_pHead, int argc, char** argv);

/** Funkcja sprawdzaj�ca w co gracz trafi�
@param board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param row wiersz wykonanego strza�u
@param column kolumna wykonanego strza�u
@return 0 gdy by�o to pud�o, 1 gdy trafiono w statek, -1 je�li trafiono we wcze�niej trafione miejsce
*/
int check_shot(cell board[][COLS], int row, int column);

/** Funkcja odpowiedzialna na wybranie kom�rki do strza�u przez gracza
@param player1_board dwuwymiarowa tablica przechowuj�ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj�ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param player numer gracza strzelaj�cego
@param sunk_ship dwuwymiarowa tablica przechowuj�ca informacje o tym ile ka�dy statek danego gracza ma nietraionych p�l
@param sh_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param argc jeden z parametr�w wywo�ania programu
@param argv jeden z parametr�w wywo�ania programu
*/
void player_shot(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, int player, int sunk_ship[2][NUMBER_OF_SHIPS], ship* sh_pHead, int argc, char** argv);

/** Funkcja odpowiedzialna na wybranie kom�rki do strza�u obok ostatniego strza�u przez komputer
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param shots_info struktura przechowuj�ca informacje o strza�ach komputera
@return wsp�rz�dne strza�u
*/
coordinate near_shot(cell player_board[][COLS], shots* shots_info);

/** Funkcja odpowiedzialna za strza� komputera na poziomie trudno�ci - �atwy
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param less zakres liczb do losowania
@param more zakres liczb do losowania
@return wsp�rz�dne strza�u
*/
coordinate easy(cell player_board[][COLS], int less, int more);

/** Funkcja odpowiedzialna za strza� komputera na poziomie trudno�ci - �redni
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param shots_info struktura przechowuj�ca informacje o strza�ach komputera
@return wsp�rz�dne strza�u
*/
coordinate medium(cell player_board[][COLS], shots* shots_info);

/** Funkcja odpowiedzialna za strza� komputera na poziomie trudno�ci - trudny
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param shots_info struktura przechowuj�ca informacje o strza�ach komputera
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@return wsp�rz�dne strza�u
*/
coordinate hard(cell player_board[][COLS], shots* shots_info, stats* pHead);

/** Funkcja odpowiedzialna za strza� komputera w statek gracza. Wywo�ywana na poziomie hard, gdy graczowi zosta�y 3 trafy do zwyci�stwa
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@return wsp�rz�dne strza�u
*/
coordinate make_hit(cell player_board[][COLS]);

/** G��wna funkcja odpowiedzialna za strza� komputera
@param player_board dwuwymiarowa tablica przechowuj�ca informacje o planszy
@param difficulty wybrana przez u�ytkownika trudno��
@param sunk_ship dwuwymiarowa tablica przechowuj�ca informacje o tym ile ka�dy statek danego gracza ma nietraionych p�l
@param player numer gracza strzelaj�cego
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param shots_info struktura przechowuj�ca informacje o strza�ach komputera
*/
void ai_shot(cell player_board[][COLS], int difficulty, int sunk_ship[2][NUMBER_OF_SHIPS], int player, stats** pHead, shots *shots_info);

/** G��wna funkcja odpowiedzialna za ca�� rozgrywk�
@param player1_game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy gracza o numerze 1
@param player2_game_board dwuwymiarowa tablica przechowuj�ca informacje o planszy gracza o numerze 2
@param with_computer informacja, czy gramy z komputerem czy z innym graczem (TRUE - gramy z komputerem
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param difficulty wybrana przez u�ytkownika trudno��
@param sh_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param argc jeden z parametr�w wywo�ania programu
@param argv jeden z parametr�w wywo�ania programu
*/
void play(cell player1_game_board[][COLS], cell player2_game_board[][COLS], booleann with_computer, stats** pHead, int difficulty, ship* sh_pHead, int argc, char** argv);

#endif // !_GAME_H

