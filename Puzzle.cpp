#include "Puzzle.h"
#include "FileOperator.h"
#include <chrono>


void Puzzle::solve(int algorithmNumber)
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
	auto finish = std::chrono::high_resolution_clock::now();
	cout << "Number of backtracks:		 " << numberOfBacktracks << endl;
	cout << "Number of visited nodes:	 " << numberOfVisitedNodes << endl;
	chrono::duration<double> elapsed = finish - start;
	cout << "Execution time[s]:		" << elapsed.count() << " s\n";


}

bool Puzzle::recursiveFunction(int positionX, int positionY, int algorithmNumber)
{
	numberOfVisitedNodes++;

	/*
		sprawdzamy, czy plansza jest juz cala wypelniona
	*/
	bool end = true;
	char variable = '_';
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (board[i][j] == variable)
			{
				end = false;
			}
		}
	}

	/*
		warunek przejscia do kolejnego wiersza i zakonczenia programu.
		Jesli dojdziemy do ostatniej kolumny i ostatniego wiersza to program zakonczy swoje dzialanie.
		Jesli bedac na ostatniej pozycji cala plansza jest uzupelniona to znaczy, ze algorytm zakonczyl
		sie powodzeniem. 
	*/
	if (positionX == m)
	{
		positionX = 0;
		positionY++;

		if (positionY == n && end == false)
		{
			return false;
		}
		if (end == true)
		{
			return true;
		}

	}
	
	/*
		jezeli pozycja na ktorej sie znajdujemy jest niedozwolona, to przechodzimy
		do kolejnej pozycji
	*/
	if (forbiddenPosition_horizontal(positionX, positionY) && forbiddenPosition_vertical(positionX, positionY))	// sprawdzamy, czy na naszej pozycji moze zaczynac sie jakis wyraz
	{
		return recursiveFunction(positionX + 1, positionY, algorithmNumber);
	}
	
	bool wordIsVetrical;
	int id_vertical_word= -1;
	int id_horizontal_word = -1;

	/*
			wlasciwa czesc uzupelniania fill-in

	Petla przechodzi po wszystkich slowach ktore mozna wpisac do fill-in.
	W kazdej iteracji program probuje wstawic kolejne slowo na obecnej pozycji.
	Jesli jesli slowo to jest zgodne na calej swojej dlugosci to algorytm przechodzi na
	kolejna pozycje wywolujac sie rekurencyjnie. 
	Jesli wstawiany wyraz nie pasuje na danej pozycji, to program proboje wstawic kolejny.
	W przypadku, gdy petla przeiteruje po wszystkich slowach i zaden nie pasuje, to
	znaczy, że w poprzednich krokach gdzies zostal popelniony blad. Funkcja zwraca false i rekurencyjnie
	wycofuje sie do poprzednich pozycji.
	*/
	for (int i = 0; i < numberOfWords; i++)
	{
		id_horizontal_word = -1;	// zmienna przechowuje id slowa pasujacego w poziomie
		id_vertical_word= -1;		// zmienna przechowuje id slowa pasujacego w pionie
		
			if (allowedWord[i] == true)		// jesli slowo nie zostalo jeszcze uzyte
			{
				if (checkRow(positionX, positionY, wordsTab[i]))			// sprawdzamy, czy slowo o indeksie i pasuje w poziomie
				{
					id_horizontal_word = i;	
				}
				else if (checkColumn(positionX, positionY, wordsTab[i]))	// sprawdzamy, czy slowo o indeksie i pasuje w pionie
				{
					id_vertical_word= i;
				}
			}
			/*
				jesli sprawdzane slowo o indeksie i pasowalo w pionie lub poziomie to
				powinno zostac wpisane do planszy
			*/
			if (id_vertical_word!= -1 || id_horizontal_word != -1)
			{	
				/*
					tworzenie kopii stanu planszy przed wpisaniem slowa
				*/
				char** boardStara = new char* [n];
				for (int i = 0; i < n; i++)
				{
					boardStara[i] = new char[m];
				}
				for (int o = 0; o < n; o++)
				{
					for (int s = 0; s < m; s++)
					{
						boardStara[o][s] = board[o][s];
					}
				}
				/*
					Wstawienie slowa do planszy. Jesli slowo ma byc wstawione poziomo a nie pionowo,
					to funkcja addVerticalWord nie dokona zadnych zmian. Analogicznie w przypadku
					odwrotnym.
				*/
				addHorizontalWord(positionX, positionY, id_horizontal_word);
				addVerticalWord(positionX, positionY, id_vertical_word);
				

				if (algorithmNumber == 2)	// fragment dla algorytmu forward checking
				{	
					/*
						funkcja sprawdz, czy wstawiane slowo jest zgodne z dziedzina wszystkich elementow
					*/
					if (checkDomain() == false)
					{
					}
					else if (recursiveFunction(positionX + 1, positionY, algorithmNumber))
					{
						return true;
					}
				}
				else
				{
					if (recursiveFunction(positionX + 1, positionY, algorithmNumber))
					{
						return true;
					}
				}
				
				/*
					jesli wstawione slowo bylo zle, to zostaje usuniete
				*/
				removeVerticalWord(positionX, positionY, id_horizontal_word);
				removeHorizontalWord(positionX, positionY, id_vertical_word);
				numberOfBacktracks++;

				/*
					przywrocenie stanu planszy sprzed wstawienia slowa
				*/
				for (int o = 0; o < n; o++)
				{
					for (int s = 0; s < m; s++)
					{
						board[o][s] = boardStara[o][s];
					}
				}
				for (int i = 0; i < n; ++i)
				{
					delete[] boardStara[i];
				}
				delete[] boardStara;
			}
	}
	return false;
}

bool Puzzle::checkDomain()
{	

	int iterator;
	bool flag;
	for (int i = 0; i < m; i++)	
	{
		for (int j = 0; j < n; j++)
		{
			if (!forbiddenPosition_horizontal(i, j))	
			{
				if (wordExist_vertical(i, j) == false)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Puzzle::wordExist_vertical(int positionX, int positionY)
{
	string pom = "";
	int iterator = 0;
	while (positionX + iterator < m && board[positionY][positionX+iterator] != FORBIDDEN_POSITION)
	{
		pom += board[positionY][positionX + iterator];
		iterator++;
	}
	bool wordExist = true;

	for (int i = 0; i < numberOfWords; i++)
	{
		wordExist = true;
		if (wordsTab[i].size() != pom.size())
		{
			wordExist = false;
			continue;
		}
		for (int j = 0; j < pom.size(); j++)
		{	
			if (pom[j] == GAP)
			{
				continue;
			}
			if (pom[j] != wordsTab[i][j])
			{
				wordExist = false;
			}
		}
		if (wordExist == true)
		{
			/*
				jesli istnieje takie slowo, ktore da sie wstawic w danej pozycji dowolonej
				to znaczy, ze na danej pozycji wszystko jest ok
			*/
			return true;
		}
	}
	return false;
}


bool Puzzle::forbiddenPosition_horizontal(int positionX, int positionY)	
{
	if (board[positionY][positionX] != FORBIDDEN_POSITION)	
	{
		if ((positionX == 0 || board[positionY][positionX - 1] == FORBIDDEN_POSITION) && (positionX != m - 1 && board[positionY][positionX + 1] != FORBIDDEN_POSITION))
		{
			return false;
		}
	}
	return true;
}


bool Puzzle::forbiddenPosition_vertical(int positionX, int positionY)	
{

	if (board[positionY][positionX] != FORBIDDEN_POSITION)	
	{
		if ((positionY == 0 || board[positionY - 1][positionX] == FORBIDDEN_POSITION) && (positionY != n - 1 && board[positionY + 1][positionX] != FORBIDDEN_POSITION))
		{
			return false;
		}
	}
	return true;
}


bool Puzzle::checkConditions(int positionX, int positionY, string napis, bool* wordIsVetrical)
{

	if (checkRow(positionX, positionY, napis))
	{
		*wordIsVetrical = false;
		return true;
	}
	if (checkColumn(positionX, positionY, napis))
	{
		*wordIsVetrical = true;
		return true;
	}
	return false;
}

bool Puzzle::checkRow(int positionX, int positionY, string napis)
{
	if ((positionX == 0 || board[positionY][positionX - 1] == FORBIDDEN_POSITION))
	{
		int iterator = 0;
			int i;
			if (positionX + napis.length() > m)
			{
				return false;
			}
		for (i = positionX; iterator < napis.length(); i++, iterator++)
		{
			if (board[positionY][i] == GAP || board[positionY][i] == napis[iterator])
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		if (i == m)
		{
			return true;
		}
		if (board[positionY][i] == FORBIDDEN_POSITION)
		{
			return true;
		}
	}	
	return false;
}
bool Puzzle::checkColumn(int positionX, int positionY, string napis)
{

	int iterator = 0;
	int i;

	if (positionY + napis.length() > n)
	{
		return false;
	}
	for (i = positionY; iterator < napis.length(); i++, iterator++)
	{
		if (board[i][positionX] == GAP || board[i][positionX] == napis[iterator])
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	if (i == n)
	{
		return true;
	}
	if (board[i][positionX] == FORBIDDEN_POSITION)
	{
		return true;
	}
	return false;
}


void Puzzle::init(int numerZbioru)
{
	string pom;
	FileOperator o1;
	numberOfBacktracks = 0;
	numberOfVisitedNodes = 0;

	switch (numerZbioru)
	{
	case 0:
		pom = "_______#____";
		n = 3;	
		m = 4;	
		numberOfWords = 6;
		wordsTab = new string[numberOfWords];
		allowedWord = new bool[numberOfWords];
		o1.readWords("words0", wordsTab);
		break;
	case 1:	
		pom = "##___####____#____#___________#____#____####___##";
		n = 7;	// liczba wierszy
		m = 7;	// liczba kolumn
		numberOfWords = 18;
		wordsTab = new string[numberOfWords];
		allowedWord = new bool[numberOfWords];
		o1.readWords("words1", wordsTab);
		break;
	case 2:	
		pom = "_____#_______#______###____##______#_________#______##____###______#_______#_____";
		n = 9;	// liczba wierszy
		m = 9;	// liczba kolumn
		numberOfWords = 32;
		wordsTab = new string[numberOfWords];
		allowedWord = new bool[numberOfWords];
		o1.readWords("words2", wordsTab);
		break;
	case 3:	
		pom = "_____#____#_________#____#_________#____#________#___#______###____#___#_________#____####_____#_____#_______#_____#_______#_____#_____####____#_________#___#____###______#___#________#____#_________#____#_________#____#_____";
		n = 15;	// liczba wierszy
		m = 15;	// liczba kolumn
		numberOfWords = 84;
		wordsTab = new string[numberOfWords];
		allowedWord = new bool[numberOfWords];
		o1.readWords("words3", wordsTab);
		break;
	case 4:	
		pom =  "______#____#___________#____#______________#________________#_____________________#_______________#____________________#_______________#________________#_____________________#___________________#________________#_____________________#________________#___________#_______#_______________##_______________#_____#_______________#____________________#_______________#_____________#_______##_______________#___________________#________________#_____________________#________________#___________________#___________________________#__________#_______________#____#_______________#_____#__________#____________________#__________#_________________";
		n = 20;	// liczba wierszy
		m = 32;	// liczba kolumn
		numberOfWords = 123;
		wordsTab = new string[numberOfWords];
		allowedWord = new bool[numberOfWords];
		o1.readWords("words4", wordsTab);
		break;
	
	default:
		exit(0);
		break;
	}
	
	for (int i = 0; i < numberOfWords; i++)	// na poczatku wszystkie slowa sa dozwolone
	{
		allowedWord[i] = true;
	}
	
	board = new char* [n];
	for (int i = 0; i < n; i++)
	{
		board[i] = new char[m];
	}
	int iterator = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			board[i][j] = pom[iterator];
			iterator++;
		}
	}
}

void Puzzle::addVerticalWord(int positionX, int positionY, int id_vertical_word)
{
	if (id_vertical_word!= -1)
	{
		allowedWord[id_vertical_word] = false;
		int j;
		int iterator;
		for (j = positionY, iterator = 0; iterator < wordsTab[id_vertical_word].length(); j++, iterator++)
		{
			board[j][positionX] = wordsTab[id_vertical_word][iterator];
		}
	}
}

void Puzzle::addHorizontalWord(int positionX, int positionY, int id_horizontal_word)
{
	if (id_horizontal_word != -1)
	{
		allowedWord[id_horizontal_word] = false;
		int j;
		int iterator;
		for (j = positionX, iterator = 0; iterator < wordsTab[id_horizontal_word].length(); j++, iterator++)
		{
			board[positionY][j] = wordsTab[id_horizontal_word][iterator];
		}
	}
}

void Puzzle::removeHorizontalWord(int positionX, int positionY, int id_vertical_word)
{
	if (id_vertical_word!= -1)
	{
		allowedWord[id_vertical_word] = true;
		int j;
		int iterator;
		for (j = positionY, iterator = 0; iterator < wordsTab[id_vertical_word].length(); j++, iterator++)
		{
			board[j][positionX] = GAP;
		}
	}
}
void Puzzle::removeVerticalWord(int positionX, int positionY, int id_horizontal_word)
{
	if (id_horizontal_word != -1)
	{
		allowedWord[id_horizontal_word] = true;
		int j;
		int iterator;
		for (j = positionX, iterator = 0; iterator < wordsTab[id_horizontal_word].length(); j++, iterator++)
		{
			board[positionY][j] = GAP;
		}
	}
}

void Puzzle::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
}
