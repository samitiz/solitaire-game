#pragma once
#include "PileofCards.h"
class Deck
{

private:

	PlayingCard* deck[52];
	int size;

public:

	Deck();
	void display();
	int getSize();
	bool IsEmpty();
	PlayingCard Remove(int i);
	~Deck();

};
