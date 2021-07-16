#include "Deck.h"
Deck::Deck()
{
	this->size = 52;
	int j = 0;
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Spade);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Diamond);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Heart);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Club);
		j++;
	}

}
void Deck::display()
{
	cout << "DECK\n";
	int j = 0, index = 5;
	for (int k = 0; k < 4; k++)
	{
		for (int i = 1; i <= 13; i++)
		{
			deck[j]->display(index, i);
			j++;
		}
		index += 10;
	}
}
int Deck::getSize()
{
	return this->size;
}
bool Deck::IsEmpty()
{
	if (this->size >= 0)
		return true;
	else
		return false;
}
PlayingCard Deck::Remove(int i)
{
	if (deck[i] != nullptr)
	{
		PlayingCard* play = deck[i];
		deck[i] = NULL;
		for (int j = i; j < size - 1; j++)
		{
			deck[j] = (deck[j + 1]);
			deck[j + 1] = NULL;
		}
		this->size--;
		return *play;
	}

}
Deck :: ~Deck()
{
	for (int i = 0; i < size; i++)
	{
		if (deck[i] != NULL)
			delete deck[i];
	}

}