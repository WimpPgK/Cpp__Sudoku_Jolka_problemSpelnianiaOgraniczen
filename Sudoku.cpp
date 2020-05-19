#include "Sudoku.h"
#include "FieldDomain.h"
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

void Sudoku::solve(int algorithmNumber)
{	
	print();
	cout << endl << endl;
	auto start = std::chrono::high_resolution_clock::now();
	/*
		Sprawdzenie, czy algorytm zakonczyl sie sukcesem.
	*/
	if (recursiveFunction(0, 0, algorithmNumber))
	{
		cout << "Sollution was found. " << endl << endl;
		print();
	}
	else
	{
		cout << "Sollution wasn't found. " << endl << endl;
	}
	/*
		Wypisanie danych o procesie.
	*/
	auto finish = std::chrono::high_resolution_clock::now();
	cout << "Number of backtracks:		 " << numberOfBacktracks << endl;
	cout << "Number of visited nodes:	 " << numberOfVisitedNodes << endl;
	chrono::duration<double> elapsed = finish - start;
	cout << "Execution time[s]:		" << elapsed.count() << " s\n";


}

bool Sudoku::recursiveFunction(int position_y, int position_x, int algorithmNumber)
{	
	numberOfVisitedNodes++;

	/*
		Warunek zmiany wiersza i zakonczenia programu. 
		Jesli dojdziemy do ostatniego wiersza i ostatniej kolumny to znaczy,
		ze poprawnie udalo sie uzupelnic cale sudoku.
	*/
	if (position_x == n)
	{
		position_x = 0;
		position_y++;
		if (position_y == n)
		{
			return true;
		}
	}

	/*
		gdy na naszej pozycji domyslnie byla wpisana jakas liczba, to przechodzimy
		na kolejna pozycje
	*/
	if (board[position_y][position_x] != EMPTY_ENTRY)
	{
		return recursiveFunction(position_y, position_x + 1, algorithmNumber);
	}

	/*
				wlasciwa czesc uzupelniania sudoku,
		Petla przechodzi po wszystkich dowzolonych wartosciach ktore mozna wpisac do sudoku.
		W kazdej iteracji program probuje wstawic kolejna liczbe do danego pola w planszy.
		Jesli liczba ta spelnia kryteria sudoku, to rekurencyjnie wywolywana jest ta funkcja
		dla kolejnej pozycji. Jesli wstawiona liczba jest niezgodna z kryteriami, to program proboje inna.
		W przypadku, gdy petla przeiteruje po wszystkich liczbach i zadna nie pasuje, to 
		znaczy, że w poprzednich krokach gdzies zostal popelniony blad. Funkcja zwraca false i rekurencyjnie
		wycofuje sie do poprzednich pozycji.
	*/
	for (int value = 1; value <= n; value++)
	{
		char number = (char)(value + '0');	
		
		/*
			dla algorytmu forward checking sprawdzane jest, czy wstawienie danej liczby
			zgodne jest z dziedzina
		*/
		if (fieldDomain[position_y][position_x].domain[number - '0'] == false)
		{
			if (algorithmNumber == 1)
			{
				numberOfBacktracks++;
			}
			continue;
		}
		else if (checkConditions(position_y, position_x, number)) 	// jesli wstawiona liczba spelnia warunki sudoku
		{
			
			board[position_y][position_x] = number;						
			domainAdd(position_x, position_y, number);
			/*
				wstawiamy liczbe do planszy sudoku i wywolujemy funkcje z kolejnej pozycji
			*/
			if (recursiveFunction(position_y, position_x + 1, algorithmNumber)) 		
			{
				return true;
			}

			/*
				jesli wstawiona liczba okazala sie zla to usuwamy wstawiona liczbe
				poprzez nadpisanie jej zmienna EMPTY_ENTRY i usuwamy ja z dziedziny
			*/
			board[position_y][position_x] = EMPTY_ENTRY;		
			domainRemove(position_x, position_y, number);
			numberOfBacktracks++;											
		}
	}
	return false;
}

bool Sudoku::checkConditions(int position_x, int position_y, char number)
{
	if (checkColumn(position_x, position_y, number) && checkRow(position_x, position_y, number) && checkSquare(position_x, position_y, number))
	{
		return true;
	}
	return false;

}

bool Sudoku::checkColumn(int position_x, int position_y, char number)
{
	for (int i = 0; i < n; i++)
	{
		if (board[i][position_y] == number)
		{
			return false;
		}
	}
	return true;
}
bool Sudoku::checkRow(int position_x, int position_y, char number)
{
	for (int i = 0; i < n; i++)
	{
		if (board[position_x][i] == number)
		{
			return false;
		}
	}
	return true;
}
bool Sudoku::checkSquare(int position_x, int position_y, char number)
{

	int squareSize = (int)sqrt(n);

	int xSquareIndex = position_x / squareSize;
	int ySquareIndex = position_y / squareSize;

	int positionOfSquareBegining_x = squareSize * xSquareIndex;
	int positionOfSquareBegining_y = squareSize * ySquareIndex;

	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			if (number == board[positionOfSquareBegining_x + i][positionOfSquareBegining_y + j])
			{
				return false;
			}
		}
	}

	return true;
}

void Sudoku::domainAdd(int position_x, int position_y, char number)
{	
	// ustawiamy ze wstawiona liczba jest juz zajeta dla calego wiersza
	for (int i = 0; i < n; i++)
	{
		fieldDomain[position_y][i].domain[number - '0'] = false;
	}
	// ustawiamy ze wstawiona liczba jest juz zajeta dla calej kolumny
	for (int i = 0; i < n; i++)
	{
		fieldDomain[i][position_x].domain[number - '0'] = false;
	}

	// ustawiamy ze wstawiona liczba jest juz zajeta dla calego kwadratu
	int squareSize = (int)sqrt(n);
	int xSquareIndex = position_x / squareSize;
	int ySquareIndex = position_y / squareSize;
	int positionOfSquareBegining_x = squareSize * xSquareIndex;
	int positionOfSquareBegining_y = squareSize *ySquareIndex;

	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			fieldDomain[positionOfSquareBegining_y + i][positionOfSquareBegining_x + j].domain[number - '0'] = false;
		}
	}
}
void Sudoku::domainRemove(int position_x, int position_y, char number)
{
	// ustawiamy ze przeslana liczba jest juz dozwolona dla wszystkich pozycji w calym wierszu
	for (int i = 0; i < n; i++)
	{
		fieldDomain[position_y][i].domain[number - '0'] = true;
	}
	// ustawiamy ze przeslana liczba jest juz dozwolona dla wszystkich pozycji w calej kolumnie
	for (int i = 0; i < n; i++)
	{
		fieldDomain[i][position_x].domain[number - '0'] = true;
	}

	// ustawiamy ze przeslana liczba jest juz dozwolona dla wszystkich pozycji w calym kwadracie
	int squareSize = (int)sqrt(n);
	int xSquareIndex = position_x / squareSize;
	int ySquareIndex = position_y / squareSize;
	int positionOfSquareBegining_x = squareSize * xSquareIndex;
	int positionOfSquareBegining_y = squareSize * ySquareIndex;

	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			fieldDomain[positionOfSquareBegining_y + i][positionOfSquareBegining_x + j].domain[number - '0'] = true;
		}
	}
}



void Sudoku::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << board[i][j] << "  ";
			if (j % 3 == 2 && j != n-1)
				cout << "|";
		}
		if (i % 3 == 2 && i != n-1)
			cout << endl << "---------------------------" << endl;
		else
			cout << endl;
	}
}


void Sudoku::init(int datasetNumber)
{
	string dataSet;
	n = 9;
	numberOfVisitedNodes = 0;
	numberOfBacktracks = 0;

	board = new char* [n];
	fieldDomain = new FieldDomain * [n];
	for (int i = 0; i < n; i++)
	{
		board[i] = new char[n];
		fieldDomain[i] = new FieldDomain[n];
	}

	switch (datasetNumber)
	{	
		case 1:	
			dataSet = "....3..5..8...5..1.592.63..42.5......6.4.2........9..5.46.....3.....78..........4";
			break;
		case 2:	
			dataSet = "8..1.5..........2...49..3......7..3...1.48....8....9.27.6.......4.7..29.298....63";
			break;
		case 3:
			dataSet = "..7.....1.58......6.197...2...48.29.......3.6...3.7..............5.46..8.6..1..5.";
			break;
		case 4:	
			dataSet = "32.........8.....9..569.3.2...4.69..1...7....2.35..4........5....1....74...7..8..";
			break;
		case 5:
			dataSet = "85.1.5..........2...49..3......7..3...1.48....8....9.27.6.......4.7..29.298....63";
			break;
		default:
			exit(0);
			break;
	}

	int iterator = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = dataSet[iterator];
			if (dataSet[iterator] != EMPTY_ENTRY)
			{
				domainAdd(j, i, dataSet[iterator]);
			}
			iterator++;
		}
	}
}