#include "PileofCards.h"
PileofCards::PileofCards(int size)
{
	this->size = size;
	this->top = -1;
	pile = new PlayingCard[size];
	this->startPt.x = 0;
	this->startPt.y = 0;
	this->endPt.x = 0;
	this->endPt.y = 0;

}
void PileofCards::Add(PlayingCard card)
{
	if (!(IsFull()))
	{
		top = top + 1;
		pile[top] = card;
	}
	else
		cout << "Error! Pile is Full\n";

}
PlayingCard PileofCards::Remove()
{
	PlayingCard card;
	if (!(IsEmpty()))
	{
		card = pile[top];
		if (top - 1 >= 0)
		{
			pile[top - 1].setTop(true);
			pile[top - 1].setFaceUp(true);
		}
		//cout << "\nCard removed";
		top = top - 1;
	}
	else
		cout << "Error! Pile is Empty\n";

	return card;
}
PlayingCard PileofCards::RemoveDeck()
{
	PlayingCard card;
	if (!(IsEmpty()))
	{
		card = pile[top];
		if (top - 1 >= 0)
			pile[top - 1].setTop(true);
			
		top = top - 1;
	}
	else
		cout << "Error! Pile is Empty\n";

	return card;
}
PlayingCard PileofCards::Peek()
{
	return pile[top];
}
bool PileofCards::IsEmpty()
{
	if (top == -1)
	{
		return true;
	}
	else
		return false;

}
bool PileofCards::IsFull()
{
	if (top == size - 1)
	{
		return true;
	}
	else
		return false;
}
PileofCards :: ~PileofCards()
{
	if (pile != NULL)
		delete pile;
}
int PileofCards::getTop()
{
	return this->top;
}
void PileofCards::setStartPt(int x, int y)
{
	this->startPt.x = x;
	this->startPt.y = y;
}
point PileofCards::getStartPt()
{
	return this->startPt;
}
void PileofCards::setEndPt(int x, int y)
{
	this->endPt.x = x;
	this->endPt.y = y;
}
point PileofCards::getEndPt()
{
	return this->endPt;
}
PileofCards& PileofCards ::operator=(const PileofCards& poc)
{
	this->size = poc.size;
	this->top = poc.top;
	this->startPt.x = poc.startPt.x;
	this->startPt.y = poc.startPt.y;
	this->endPt.x = poc.endPt.x;
	this->endPt.y = poc.endPt.y;
	pile = new PlayingCard(this->size);
	for (int i = 0; i <= poc.size; i++)
	{
		poc.pile[i] = pile[i];
	}

	return *this;
}
PlayingCard PileofCards::viewCard(int i)
{
	PlayingCard card;
	if (i >= 0 && i < size)
	{
		card = pile[i];
	}
	else
		cout << "No card found...!\n";
	return card;
}
void PileofCards::SimpleDisplay()
{
	if (!(IsEmpty()))
	{
		pile[top].display(startPt.x, startPt.y);
	}
	else
	{
		PlayingCard card;
		card.setFaceUp(false);
		card.setTop(true);
		card.setColor('g');
		card.display(startPt.x, startPt.y);
	}
}
void PileofCards::CascadingDisplay()
{
	int index = 0;
	if (!(IsEmpty()))
	{
		for (int i = 0; i <= top; i++)
		{
			this->pile[i].display(startPt.x, startPt.y + index);
			index = index + 2;
		}
	}
	else
	{
		PlayingCard card;
		card.setFaceUp(false);
		card.setTop(true);
		card.setColor('g');
		card.display(startPt.x, startPt.y);

	}

}
