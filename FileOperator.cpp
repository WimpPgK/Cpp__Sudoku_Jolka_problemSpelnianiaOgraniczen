#include "FileOperator.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

void FileOperator::readWords(string fileName, string* tab)
{
	fstream dane;
	dane.open(fileName.c_str(), ios::in);  

	if (dane.good() == false)	
	{
		cout << "Can't oppen the file." << endl;
	}
	else
	{
		string linia;
		string wartosc;

		int licznik = 0;
		int iterator = 0;
		while (!dane.eof())     
		{
			getline(dane, linia);
			string pom = linia;
			tab[iterator] = pom;
			iterator++;
		}
	}
	dane.close();

}

