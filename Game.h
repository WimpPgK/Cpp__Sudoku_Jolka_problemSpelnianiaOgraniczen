#pragma once
class Game
{
public:
	virtual void init(int) = 0;		// funkcja inicjalizuje plansze
	virtual void solve(int) = 0;	// funkcja znajduje rozwiazanie gry
	virtual void print() = 0;		// funkcja wypisuje stan planszy
};

