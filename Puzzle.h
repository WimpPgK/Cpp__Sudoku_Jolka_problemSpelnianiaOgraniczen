#include <iostream>
#pragma once
using namespace std;

class Puzzle
{
	bool recursiveFunction(int positionX, int positionY, int algorithmNumber);
	bool forbiddenPosition_horizontal(int positionX, int positionY);
	bool forbiddenPosition_vertical(int positionX, int positionY);
	void addHorizontalWord(int positionX,int positionY,int id_horizontal_word);
	void addVerticalWord(int positionX,int positionY,int id_vertical_word);
	void removeVerticalWord(int positionX, int positionY, int id_horizontal_word);
	void removeHorizontalWord(int positionX, int positionY, int id_vertical_word);
	bool wordExist_vertical(int positionX, int positionY);
	bool checkDomain();
	bool checkConditions(int positionX, int positionY, string napis, bool* wordIsVetrical);
	bool checkColumn(int positionX, int positionY, string napis);
	bool checkRow(int positionX, int positionY, string napis);

public:
	int n;					// number of rows
	int m;					// number of columns
	int numberOfWords;		// liczba slow z zbiorze
	char** board;			// plansza 
	string* wordsTab;		// slowa ktore nalezy wpisac na planszy
	bool* allowedWord;		// tablica okreslajaca czy dane slowo zostalo juz wpisane czy nie
	int numberOfBacktracks;					// liczba nawrotow
	int numberOfVisitedNodes;				// liczba odwiedzonych wezlow
	const char GAP = '_';					// znak oznaczajacy puste pole na planszy
	const char FORBIDDEN_POSITION = '#';	// znak oznaczajacy niedozwolone pole na planszy

	void init(int numerZbioru);				// tworzy plansze i inicjalizuje wszystkie zmienne
	void solve(int algorithmNumber);		// nadrzedna funkcja rozwiazujaca fill-in
	void print();
};

