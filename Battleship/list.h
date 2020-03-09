#ifndef _LIST_H
#define _LIST_H

#include "game.h"

/** Funkcja inicjalizuj¹ca listy jednokierunkowe statków i statystyk
@param stats_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param ship_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void initialize_lists(stats** stats_pHead, ship** ship_pHead);

/** Funkcja inicjalizuj¹ca listê jednokierunkow¹ statków
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void initialize_ship_list(ship** pHead);

/** Funkcja inicjalizuj¹ca listê jednokierunkow¹ statystyk
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
*/
void initialize_stats_list(stats **pHead);

/** Funkcja usuwaj¹ca listê jednokierunkow¹ statystyk
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
*/
void delete_stats_list(stats ** pHead);

/** Funkcja usuwaj¹ca listê jednokierunkow¹ statków
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void delete_ship_list(ship** pHead);

/** Funkcja usuwaj¹ca listy jednokierunkowe statystyk i statków
@param stats_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param ship_pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
*/
void delete_lists(stats** stats_pHead, ship** ship_pHead);

/** Funkcja dodaj¹ca na pocz¹tek listy jednokierunkowej statystyk element
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param Player numer gracza którego dodajemy do listy
*/
void push_stats_front(stats **pHead, int Player);

/** Funkcja dodaj¹ca na koniec listy jednokierunkowej statystyk element
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param Player numer gracza którego dodajemy do listy
*/
void push_stats_back(stats *pHead, int Player);

/** Funkcja dodaj¹ca na pocz¹tek listy jednokierunkowej statków element
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statkach
@param Symbol symbol danego statku
@param Length d³ugoœæ danego statku
@param Name nazwa danego statku
*/
void push_ship_front(ship** pHead, char Symbol, int Length, char* Name);

/** Funkcja zeruj¹ca statystyki obu graczy
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
*/
void clear_stats(stats **pHead);

/** Funkcja zmieniaj¹ca wartoœæ w jednym, wybranym polu
@param pHead g³owa listy jednokierunkowej przechowuj¹cej informacje o statystykach
@param Player numer gracza u którego zmieniamy wartoœæ
@param what_to_add wybieramy któr¹ wartoœæ chcemy zmieniæ
*/
void change_value_in_list(stats **pHead, int Player, char *what_to_add);

#endif // !_LIST_H
