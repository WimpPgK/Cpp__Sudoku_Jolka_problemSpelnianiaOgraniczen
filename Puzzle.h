#pragma once
#include <iostream>
#include "Game.h"

using namespace std;

class Puzzle: public Game
{
	bool recursiveFunction(int positionX, int positionY, int algorithmNumber);		// rekurencyjna funkcja wywolujaca sie dla kazdego pola plaszy

	bool checkDomain();		// sprawdza, czy pozycja jest dozwolona poprzez wywolanie forbiddenPosition...
	bool forbiddenPosition_horizontal(int positionX, int positionY);				// sprawdza, czy podana pozycja wpisania slowa jest dozwolona w poziomie
	bool forbiddenPosition_vertical(int positionX, int positionY);					// sprawdza, czy podana pozycja wpisania slowa jest dozwolona w pionie
									
	bool checkConditions(int positionX, int positionY, string napis, bool* wordIsVetrical);	// sprawdza, czy mozna wpisac slowo wywolujac funkcje checkColumn i checkRow
	bool checkColumn(int positionX, int positionY, string napis);					// sprawdza, czy slowo mozna wpisac w pionie
	bool checkRow(int positionX, int positionY, string napis);						// sprawdza, czy slowo mozna wpisac w poziomie
	
	void addHorizontalWord(int positionX,int positionY,int id_horizontal_word);		// wstawia slowo w poziomie
	void addVerticalWord(int positionX,int positionY,int id_vertical_word);			// wstawia slowo w pionie
	void removeVerticalWord(int positionX, int positionY, int id_horizontal_word);	// usuwa slowo w pionie, jesli bylo bledne
	void removeHorizontalWord(int positionX, int positionY, int id_vertical_word);	// usuwa slowo w poziomie, jesli bylo bledne
	bool wordExist_vertical(int positionX, int positionY);							
	
public:
	int n;					// liczba wierszy
	int m;					// liczba kolumn
	int numberOfWords;		// liczba slow z zbiorze
	char** board;			// plansza 
	string* wordsTab;		// slowa ktore nalezy wpisac na planszy
	bool* allowedWord;		// tablica okreslajaca czy dane slowo zostalo juz wpisane czy nie
	int numberOfBacktracks;					// liczba nawrotow
	int numberOfVisitedNodes;				// liczba odwiedzonych wezlow
	const char GAP = '_';					// znak oznaczajacy puste pole na planszy
	const char FORBIDDEN_POSITION = '#';	// znak oznaczajacy niedozwolone pole na planszy

	virtual void init(int numerZbioru);				// tworzy plansze i inicjalizuje wszystkie zmienne
	virtual void solve(int algorithmNumber);		// nadrzedna funkcja rozwiazujaca fill-in
	virtual void print();							// wypisuje stan planszy
};

