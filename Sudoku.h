#pragma once
#include "FieldDomain.h"
#include "Game.h"
class Sudoku: public Game
{

private:
	const char EMPTY_ENTRY = '.';	// znacznik pustego miejsca w planszy sudoku

	bool checkConditions(int position_x, int position_y, char number);	// wywoluje zbiorczo funkcje checkColumn, checkRow, checkSquare i zarzadza nimi
	bool checkColumn(int position_x, int position_y, char number);		// sprawdza warunki zgodnosci wstawianej liczby dla kolumny
	bool checkRow(int position_x, int position_y, char number);			// sprawdza warunki zgodnosci wstawianej liczby dla wiersza
	bool checkSquare(int position_x, int position_y, char number);		// sprawdza warunki zgodnosci wstawianej liczby dla wewnetrznych kwadratow
	
	void domainAdd(int position_x, int position_y,char number);			// aktualizuje dziedzine po wstawieniu liczby
	void domainRemove(int position_x, int position_y, char number);		// aktualizuje dziedzine po usunieciu liczby

	// algorithmNumber: 1 dla backtracking algorithm, 2 dla forward checking algorithm
	// funkcja rekurencyjna odpowiedzialna za generowanie rozwiazan 
	bool recursiveFunction(int wiersz, int kolumna, int algorithmNumber);	

public:
	char** board;					// plansza sudoku
	FieldDomain** fieldDomain;		// dziedzina dla kazdego pola sudoku
	int numberOfVisitedNodes;		// liczba odwiedzonych wezlow
	int numberOfBacktracks;			// liczba nawrotow
	int n;							// rozmiar planszy sudoku

	virtual void init(int datasetNumber);		// funkcja inicjalizuje plansze wartosciami
	virtual void solve(int algorithmNumber);	// funkcja rozwiazuje cale sudoku
	virtual void print();						// funkcja wypisuje stan planszy


};

