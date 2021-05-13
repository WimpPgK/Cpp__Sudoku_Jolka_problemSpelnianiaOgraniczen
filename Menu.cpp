#include "Menu.h"
#include <iostream>
#include "Sudoku.h"
#include "Puzzle.h"
#include <chrono>
#include <Windows.h>

void Menu::start()
{
	int problemNumber;
	int algorithmNumber;
	int datasetNumber;
	Sudoku sudoku;
	Puzzle puzzle;


	showUserInterface01();
	cin >> problemNumber;
	Sleep(500);
	switch (problemNumber)
	{
		case 1:			//dla gry sudoku
			system("cls");
			showUserInterface02();				// menu wybor algorytmu
			cin >> algorithmNumber;
			system("cls");
			showUserInterface03(problemNumber); // menu wybor konkretnego problemu
			cin>> datasetNumber;
			system("cls");
			sudoku.init(datasetNumber);
			sudoku.solve(algorithmNumber);
			break;
		
		
		case 2:			// dla gry fill in
			system("cls");
			showUserInterface02();				// menu wybor algorytmu
			cin >> algorithmNumber;
			system("cls");
			showUserInterface03(problemNumber);	// menu wybor konkretnego problemu
			cin >> datasetNumber;
			system("cls");
			puzzle.init(datasetNumber);
			puzzle.solve(algorithmNumber);

			break;
		default:
			cout << "Incorrect value" << endl << endl;
			break;
	}
}

void Menu::showUserInterface01()
{
	cout << "*********************************************" << endl;
	cout << "***    CONSTRAIN SATISFACTION PROBLEM     ***" << endl;
	cout << "*********************************************" << endl << endl;
	cout << "	1. Sudoku" << endl;
	cout << "	2. Fill-in" << endl;
	
}
void Menu::showUserInterface02()
{
	cout << "*********************************************" << endl;
	cout << "***    CONSTRAIN SATISFACTION PROBLEM     ***" << endl;
	cout << "*********************************************" << endl << endl;
	cout << "	1. Backtracking algorithm" << endl;
	cout << "	2. Foward checking algorithm" << endl;

}

void Menu::showUserInterface03(int problemNumber)
{
	cout << "*********************************************" << endl;
	cout << "***    CONSTRAIN SATISFACTION PROBLEM     ***" << endl;
	cout << "*********************************************" << endl << endl;
	cout << "Choose proper dataset:" << endl;
	
	if (problemNumber == 1)
	{
		cout << "	1. Easy problem ( ID = 9, difficulty = 1 )"  << endl;
		cout << "	2. Medium problem ( ID = 25, difficulty = 4 )" << endl;
		cout << "	3. Difficult problem ( ID = 39, difficulty = 7 )" << endl;
		cout << "	4. Mingle problem ( ID = 41, difficulty = 8 )" << endl;
		cout << "	5. Mingle problem ( ID = 45, difficulty = 9 )" << endl;
	}
	else if (problemNumber == 2)
	{
		cout << "	0. puzzle0" << endl;
		cout << "	1. puzzle1" << endl;
		cout << "	2. puzzle2" << endl;
		cout << "	3. puzzle3" << endl;
		cout << "	4. puzzle4" << endl;
	}

}