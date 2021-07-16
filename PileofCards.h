#pragma once
#include <iostream>
#include "PlayingCard.h"
using namespace std;


class PileofCards
{
private:
	PlayingCard* pile;
	int top;
	int size;
	point startPt;
	point endPt;
public:
	PileofCards(int size);
	~PileofCards();
	PlayingCard Peek();
	PlayingCard Remove();
	void Add(PlayingCard card);
	bool IsEmpty();
	bool IsFull();
	int getTop();
	void setStartPt(int x, int y);
	point getStartPt();
	void setEndPt(int x, int y);
	point getEndPt();
	PileofCards& operator=(const PileofCards& poc);
	PlayingCard viewCard(int i);
	void SimpleDisplay();
	void CascadingDisplay();
	PlayingCard RemoveDeck();

};
