#include "PlayingCard.h"
#include "ConsoleFunctions.h"

PlayingCard::PlayingCard(int rank, int suit)
{
	if (rank > 0 && rank <= 13 && suit >= 0 && suit <= 3)
	{
		this->rank = rank;
		this->suit = suit;
	}

	if (suit == 0 || suit == 1)
		this->color = 'r';
	else if (suit == 2 || suit == 3)
		this->color = 'b';
	this->faceUp = false;
	this->top = false;
}
void PlayingCard::print_shape(int x, int pos)
{
	char shape= 0;
	if (x == 0)
		shape = '\4';
	else if (x == 1)
		shape = '\3';
	else if (x == 2)
		shape = '\6';
	else if (x == 3)
		shape = '\5';
	if (pos == 0)
	{

		if (rank <= 9 && rank >1)
		{
				cout << rank <<shape<< " " << "     ";
		}
		else if (rank > 9 || rank ==1)
		{
			if (rank == 10)
				cout << rank <<shape<< " " << "    ";
			else if (rank == 13)
				cout << "K" <<shape<< " " << "     ";
			else if (rank == 12)
				cout << "Q" <<shape<< " " << "     ";
			else if (rank == 11)
				cout << "J" <<shape<< " " << "     ";
			else if (rank == 1)
				cout << "A" <<shape<< " " << "     ";
			

		}
	}
	if (pos == 1)
	{
		if (rank <= 9 && rank > 1)
		{
				cout << "      " << rank << shape;
		}
		else if (rank > 9 || rank == 1)
		{
			if (rank == 10)
				cout << "     " << rank << shape;
			else if (rank == 13)
				cout << "      " << "K" << shape;
			else if (rank == 12)
				cout << "      " << "Q" << shape;
			else if (rank == 11)
				cout << "      " << "J" << shape;
			else if (rank == 1)
				cout << "      " << "A" << shape;
		}
	}
}
void PlayingCard::display(int x, int y)
{
	ConsoleFunctions dumy;
	if (this->top == true && this->faceUp == true)
	{
		int count = 1;
		dumy.SetCursorAt(x, y);

		//Seting the colors of text
		if (this->color == 'r')
			dumy.SetColor(red, white);
		else if (this->color == 'b')
			dumy.SetColor(black, white);

		//printing the shape of diamond , heart etc
		this->print_shape(suit, 0);
		for (int i = y; i < y + 5; i++)
		{
			dumy.SetCursorAt(x, i + 1);

			for (int j = 0; j < 8; j++)
			{
				cout << " ";

			}
		}
		dumy.SetCursorAt(x, y + 6);
		this->print_shape(suit, 1);
		dumy.SetColor(white, black);
	}
	else if (this->top == false && this->faceUp == true)
	{
		int count = 1;
		dumy.SetCursorAt(x, y);

		//Seting the colors of text
		if (this->color == 'r')
			dumy.SetColor(red, white);
		else if (this->color == 'b')
			dumy.SetColor(black, white);

		//printing the shape of diamond , heart etc
		this->print_shape(this->suit, 0);
		for (int i = y; i <= y; i++)
		{
			dumy.SetCursorAt(x, i + 1);

			for (int j = 0; j < 8; j++)
			{
				if (i == y)
				{
					dumy.SetColor(black, white);
					cout << "_";
				}
				else
					cout << " ";
			}
		}

	}
	else if (this->top == false && this->faceUp == false)
	{
		dumy.SetCursorAt(x, y);
		dumy.SetColor(white, red);

		for (int i = y; i <= y + 1; i++)
		{

			for (int j = 0; j < 8; j++)
			{
				if (i == y + 1)
				{

					dumy.SetColor(black, red);
					cout << "_";
				}
				else
					cout << " ";
			}
			dumy.SetCursorAt(x, i + 1);
		}



	}
	else if (this->top == true && this->faceUp == false)
	{
		dumy.SetCursorAt(x, y);
		if (color != 'g')
			dumy.SetColor(white, red);
		else if (color == 'g')
			dumy.SetColor(black, dark_green);
		for (int i = y; i < y + 7; i++)
		{

			for (int j = 0; j < 8; j++)
			{
				cout << " ";
			}
			dumy.SetCursorAt(x, i + 1);
		}
	}
}
bool PlayingCard::isFaceUp()
{
	return this->faceUp;
}
void PlayingCard::setFaceUp(bool val)
{
	this->faceUp = val;
}
bool PlayingCard::isTop()
{
	return this->top;
}
void PlayingCard::setTop(bool val)
{
	this->top = val;
}
int PlayingCard::getSuit()
{
	return this->suit;
}
int PlayingCard::getRank()
{
	return this->rank;
}
char PlayingCard::getColor()
{
	return this->color;
}
void PlayingCard::setColor(char set)
{
	this->color = set;
}