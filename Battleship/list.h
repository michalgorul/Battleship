#ifndef _LIST_H
#define _LIST_H

#include "game.h"

/** Funkcja inicjalizuj�ca listy jednokierunkowe statk�w i statystyk
@param stats_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param ship_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
*/
void initialize_lists(stats** stats_pHead, ship** ship_pHead);

/** Funkcja inicjalizuj�ca list� jednokierunkow� statk�w
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
*/
void initialize_ship_list(ship** pHead);

/** Funkcja inicjalizuj�ca list� jednokierunkow� statystyk
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
*/
void initialize_stats_list(stats **pHead);

/** Funkcja usuwaj�ca list� jednokierunkow� statystyk
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
*/
void delete_stats_list(stats ** pHead);

/** Funkcja usuwaj�ca list� jednokierunkow� statk�w
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
*/
void delete_ship_list(ship** pHead);

/** Funkcja usuwaj�ca listy jednokierunkowe statystyk i statk�w
@param stats_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param ship_pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
*/
void delete_lists(stats** stats_pHead, ship** ship_pHead);

/** Funkcja dodaj�ca na pocz�tek listy jednokierunkowej statystyk element
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param Player numer gracza kt�rego dodajemy do listy
*/
void push_stats_front(stats **pHead, int Player);

/** Funkcja dodaj�ca na koniec listy jednokierunkowej statystyk element
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param Player numer gracza kt�rego dodajemy do listy
*/
void push_stats_back(stats *pHead, int Player);

/** Funkcja dodaj�ca na pocz�tek listy jednokierunkowej statk�w element
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statkach
@param Symbol symbol danego statku
@param Length d�ugo�� danego statku
@param Name nazwa danego statku
*/
void push_ship_front(ship** pHead, char Symbol, int Length, char* Name);

/** Funkcja zeruj�ca statystyki obu graczy
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
*/
void clear_stats(stats **pHead);

/** Funkcja zmieniaj�ca warto�� w jednym, wybranym polu
@param pHead g�owa listy jednokierunkowej przechowuj�cej informacje o statystykach
@param Player numer gracza u kt�rego zmieniamy warto��
@param what_to_add wybieramy kt�r� warto�� chcemy zmieni�
*/
void change_value_in_list(stats **pHead, int Player, char *what_to_add);

#endif // !_LIST_H
