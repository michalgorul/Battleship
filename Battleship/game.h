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

/** Funkcja losuj¹ca cyfrê 0 lub 1 w celu wybrania gracza rozpoczynaj¹cego rozgrywkê
@return numer gracza rozpoczynaj¹cego rozgrywkê
*/
int who_first(void);

/** Funkcja sprawdzaj¹ca czy dany gracz wystrzela³ ju¿ wszystkie statki
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param Player numer sprawdzanego gracza
@return wartoœæ TRUE jeœli dany gracz zwyciê¿y³, FALSE jeœli nie
*/
booleann is_winner(stats **pHead, int Player);

/** Funkcja wywo³ywana, gdy gracz postanowi³ zakoñczyæ rozgrywkê. Zapisuje stan planszy i statystyk jeœli gracz sobie tego za¿yczy i usuwa listy
@param player1_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param sh_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param argc jeden z parametrów wywo³ania programu
@param argv jeden z parametrów wywo³ania programu
@return wspó³rzêdne strza³u
*/
void end_decision(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, ship* sh_pHead, int argc, char** argv);

/** Funkcja pobieraj¹ca od gracza wspó³rzêdne do strza³u
@param player1_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param sh_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param argc jeden z parametrów wywo³ania programu
@param argv jeden z parametrów wywo³ania programu
@return wspó³rzêdne strza³u
*/
coordinate get_target(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, ship* sh_pHead, int argc, char** argv);

/** Funkcja sprawdzaj¹ca w co gracz trafi³
@param board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param row wiersz wykonanego strza³u
@param column kolumna wykonanego strza³u
@return 0 gdy by³o to pud³o, 1 gdy trafiono w statek, -1 jeœli trafiono we wczeœniej trafione miejsce
*/
int check_shot(cell board[][COLS], int row, int column);

/** Funkcja odpowiedzialna na wybranie komórki do strza³u przez gracza
@param player1_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy pierwszego gracza
@param player2_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy drugiego gracza lub komputera
@param st_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param player numer gracza strzelaj¹cego
@param sunk_ship dwuwymiarowa tablica przechowuj¹ca informacje o tym ile ka¿dy statek danego gracza ma nietraionych pól
@param sh_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param argc jeden z parametrów wywo³ania programu
@param argv jeden z parametrów wywo³ania programu
*/
void player_shot(cell player1_board[][COLS], cell player2_board[][COLS], stats* st_pHead, int player, int sunk_ship[2][NUMBER_OF_SHIPS], ship* sh_pHead, int argc, char** argv);

/** Funkcja odpowiedzialna na wybranie komórki do strza³u obok ostatniego strza³u przez komputer
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param shots_info struktura przechowuj¹ca informacje o strza³ach komputera
@return wspó³rzêdne strza³u
*/
coordinate near_shot(cell player_board[][COLS], shots* shots_info);

/** Funkcja odpowiedzialna za strza³ komputera na poziomie trudnoœci - ³atwy
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param less zakres liczb do losowania
@param more zakres liczb do losowania
@return wspó³rzêdne strza³u
*/
coordinate easy(cell player_board[][COLS], int less, int more);

/** Funkcja odpowiedzialna za strza³ komputera na poziomie trudnoœci - œredni
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param shots_info struktura przechowuj¹ca informacje o strza³ach komputera
@return wspó³rzêdne strza³u
*/
coordinate medium(cell player_board[][COLS], shots* shots_info);

/** Funkcja odpowiedzialna za strza³ komputera na poziomie trudnoœci - trudny
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param shots_info struktura przechowuj¹ca informacje o strza³ach komputera
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@return wspó³rzêdne strza³u
*/
coordinate hard(cell player_board[][COLS], shots* shots_info, stats* pHead);

/** Funkcja odpowiedzialna za strza³ komputera w statek gracza. Wywo³ywana na poziomie hard, gdy graczowi zosta³y 3 trafy do zwyciêstwa
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@return wspó³rzêdne strza³u
*/
coordinate make_hit(cell player_board[][COLS]);

/** G³ówna funkcja odpowiedzialna za strza³ komputera
@param player_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy
@param difficulty wybrana przez u¿ytkownika trudnoœæ
@param sunk_ship dwuwymiarowa tablica przechowuj¹ca informacje o tym ile ka¿dy statek danego gracza ma nietraionych pól
@param player numer gracza strzelaj¹cego
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param shots_info struktura przechowuj¹ca informacje o strza³ach komputera
*/
void ai_shot(cell player_board[][COLS], int difficulty, int sunk_ship[2][NUMBER_OF_SHIPS], int player, stats** pHead, shots *shots_info);

/** G³ówna funkcja odpowiedzialna za ca³¹ rozgrywkê
@param player1_game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy gracza o numerze 1
@param player2_game_board dwuwymiarowa tablica przechowuj¹ca informacje o planszy gracza o numerze 2
@param with_computer informacja, czy gramy z komputerem czy z innym graczem (TRUE - gramy z komputerem
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param difficulty wybrana przez u¿ytkownika trudnoœæ
@param sh_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param argc jeden z parametrów wywo³ania programu
@param argv jeden z parametrów wywo³ania programu
*/
void play(cell player1_game_board[][COLS], cell player2_game_board[][COLS], booleann with_computer, stats** pHead, int difficulty, ship* sh_pHead, int argc, char** argv);

#endif // !_GAME_H

