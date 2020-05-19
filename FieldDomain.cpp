#include "FieldDomain.h"
using namespace std;
#include <iostream>
FieldDomain::FieldDomain()
{
	//cout << "KONSTRUKTOR domain POLA" << endl;
	for (int i = 0; i < n; i++)
	{
		domain[i] = true;
	}
	domainSize = 9;
}
