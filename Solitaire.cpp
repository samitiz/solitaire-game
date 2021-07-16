#include "Solitaire.h"

Solitaire::Solitaire()
{
	stock = new PileofCards(52);

	waste = new PileofCards(52);

	for (int i = 0; i < 4; i++)
		home[i] = new PileofCards(13);

	for (int i = 0; i < 7; i++)
		playingPile[i] = new PileofCards(13 + i);

	int index = 2;
	//setting start points of playingpile array
	for (int i = 0; i < 7; i++)
	{
		playingPile[i]->setStartPt(index, 10);
		playingPile[i]->setEndPt(index, 10);
		index = index + 14;
	}
	//setting start points of home array
	home[0]->setStartPt(44, 1);
	home[1]->setStartPt(58, 1);
	home[2]->setStartPt(72, 1);
	home[3]->setStartPt(86, 1);

	home[0]->setEndPt(51, 7);
	home[1]->setEndPt(65, 7);
	home[2]->setEndPt(79, 7);
	home[3]->setEndPt(93, 7);

	//setting start points of stock array
	stock->setStartPt(2, 1);
	stock->setEndPt(9, 7);

	//setting start points of waste array
	waste->setStartPt(16, 1);
	waste->setEndPt(23, 7);
}
void Solitaire::Shuffle()
{
	int i;
	while (!deckofCards.IsEmpty())
	{
		i = rand() % deckofCards.getSize();
		PlayingCard c = deckofCards.Remove(i);
		c.setFaceUp(false);
		stock->Add(c);
	}
}
void Solitaire::dealToPlayingPiles()
{

	//for changing the endpoint of piles
	int x = 2, y = 10;
	PlayingCard card;

	//dealing the cards to playing piles
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < i + 1; j++)
		{
			card = deckofCards.Remove(i);
			if (i + 1 == j + 1)
			{
				card.setFaceUp(true);
				card.setTop(true);
			}
			y += 2;
			playingPile[i]->Add(card);
			playingPile[i]->setEndPt(x, y);
		}
		x += 14;
	}

	//adding card to stock pile
	for (int i = 0; i < 24; i++)
	{
		card = deckofCards.Remove(0);
		card.setTop(true);
		stock->Add(card);
	}
}
void Solitaire::DisplayGame()
{

	stock->SimpleDisplay();

	waste->SimpleDisplay();

	home[0]->SimpleDisplay();
	home[1]->SimpleDisplay();
	home[2]->SimpleDisplay();
	home[3]->SimpleDisplay();

	playingPile[0]->CascadingDisplay();
	playingPile[1]->CascadingDisplay();
	playingPile[2]->CascadingDisplay();
	playingPile[3]->CascadingDisplay();
	playingPile[4]->CascadingDisplay();
	playingPile[5]->CascadingDisplay();
	playingPile[6]->CascadingDisplay();
}

point Solitaire::getClickedPoint()
{
	point p;
	while (true)
	{
		cf.DetectEvent();
		if (cf.IsMouseLeftClickEvent(p))
			break;
	}
	return p;
}
PileofCards *Solitaire::getClickedPile(point p, int &a, int &c)
{
	int index = 2;
	int loop = 0;
	point stock_S = stock->getStartPt();
	point waste_S = waste->getStartPt();

	if (p.x >= stock_S.x && p.y >= stock_S.y && p.x <= (stock_S.x) + 7 && p.y <= (stock_S.y) + 6)
	{
		return stock;
	}	
	else if (p.x >= waste_S.x && p.y >= waste_S.y && p.x <= (waste_S.x) + 7 && p.y <= (waste_S.y) + 6)
	{
		return waste;
	}
	for (int i = 0; i < 4; i++)
	{
		point home_S = home[i]->getStartPt();
		if (p.x >= home_S.x && p.y >= home_S.y && p.x <= (home_S.x) + 7 && p.y <= (home_S.y) + 6)
		{
			a = i;
			return home[i];
		}
	}
	for (int i = 0; i < 7; i++)
	{
		point playingPile_S = playingPile[i]->getStartPt();
		point playingPile_E = playingPile[i]->getEndPt();

		if (!playingPile[i]->IsEmpty())
		{
			if (p.x >= playingPile_S.x && p.y >= playingPile_S.y && p.x <= (playingPile_E.x) + 7 && p.y <= playingPile_E.y + 4)
			{
				loop = this->playingPile[i]->getTop();
				a = i;
				for (int j = 0; j <= loop; j++)
				{
					if (j == loop)
					{
						if (p.y >= (playingPile_S.y + (index - 2)) && p.y <= (playingPile_S.y) + 4 + index)
						{
							c = j;
						}
					}
					else
					{
						if (p.y >= (playingPile_S.y + (index - 2)) && p.y <= playingPile_S.y + index)
						{
							c = j;
						}
					}
					index += 2;
				}

				return playingPile[i];
				break;
			}
		}
		else if (playingPile[i]->IsEmpty())
		{
			if (p.x >= playingPile_S.x && p.y >= playingPile_S.y && p.x <= (playingPile_E.x) + 7 && p.y <= playingPile_E.y + 6)
			{
				a = i;
				return playingPile[i];
				break;
			}
		}
	}
}
void Solitaire::moveFromStock()
{
	PlayingCard card;

	if (!stock->IsEmpty())
	{
		card = stock->RemoveDeck();
		card.setFaceUp(true);
		card.setTop(true);
		waste->Add(card);
		stock->Peek().setFaceUp(false);
	}
	else
	{
		while (!waste->IsEmpty())
		{
			card = waste->Remove();
			card.setFaceUp(false);
			stock->Add(card);
		}
	}
}
void Solitaire::moveFromWasteToHome(int a)
{
	PlayingCard card;
	if (!waste->IsEmpty())
	{
		card = waste->Peek();
		card.setFaceUp(true);
		card.setTop(true);
		if (home[a]->IsEmpty() && card.getRank() == 1)
		{
			home[a]->Add(card);
			waste->Remove();
		}
		else if (((home[a]->Peek()).getRank() + 1) == card.getRank() && (home[a]->Peek()).getSuit() == card.getSuit() && (home[a]->Peek()).getColor() == card.getColor())
		{
			home[a]->Add(card);
			waste->Remove();
		}
	}
}
void Solitaire::moveFromWasteToPlayingPile(int a, int c)
{
	PlayingCard card;
	int x = 0, y = 0;
	if (!waste->IsEmpty())
	{
		card = waste->Peek();
		card.setFaceUp(true);
		card.setTop(true);
		if (playingPile[a]->IsEmpty() && card.getRank() == 13)
		{
			playingPile[a]->Add(card);
			x = playingPile[a]->getEndPt().x;
			y = playingPile[a]->getEndPt().y;
			playingPile[a]->setEndPt(x, y + 2);
			waste->Remove();
		}
		else if ((playingPile[a]->viewCard(c).getRank() - 1) == card.getRank() && playingPile[a]->viewCard(c).getColor() != card.getColor() && c == playingPile[a]->getTop())
		{
			playingPile[a]->Add(card);
			x = playingPile[a]->getEndPt().x;
			y = playingPile[a]->getEndPt().y;
			playingPile[a]->setEndPt(x, y + 2);
			waste->Remove();
		}
	}
}
void Solitaire::moveFromPlayingPileToHome(int a, int b, int c)
{
	int x = 0, y = 0;
	PlayingCard card;
	if (!playingPile[a]->IsEmpty())
	{
		card = playingPile[a]->viewCard(c);
		card.setFaceUp(true);
		card.setTop(true);
		if (home[b]->IsEmpty() && c == playingPile[a]->getTop() && card.getRank() == 1)
		{
			home[b]->Add(card);
			playingPile[a]->Remove();
			x = playingPile[a]->getEndPt().x;
			y = playingPile[a]->getEndPt().y;
			playingPile[a]->setEndPt(x, y - 2);
		}
		else if (!home[b]->IsEmpty() && c == playingPile[a]->getTop() && (home[b]->Peek().getRank() + 1) == card.getRank() && (home[b]->Peek()).getSuit() == card.getSuit() && (home[b]->Peek()).getColor() == card.getColor())
		{
			home[b]->Add(card);
			x = playingPile[a]->getEndPt().x;
			y = playingPile[a]->getEndPt().y;
			playingPile[a]->setEndPt(x, y - 2);
			playingPile[a]->Remove();
		}
	}
}
void Solitaire::moveFromPlayingPileToPlayingPile(int a, int b, int c1, int c2)
{
	int x = 0, y = 0;
	PlayingCard card;
	if (!playingPile[a]->IsEmpty())
	{
		card = playingPile[a]->viewCard(c1);

		if (playingPile[b]->IsEmpty() && card.getRank() == 13)
		{
			for (int i = c1; i <= playingPile[a]->getTop(); i++)
			{
				card = playingPile[a]->viewCard(i);
				card.setFaceUp(true);
				card.setTop(true);
				playingPile[b]->Add(card);
				x = playingPile[b]->getEndPt().x;
				y = playingPile[b]->getEndPt().y;
				playingPile[b]->setEndPt(x, y + 2);
			}
			for (int i = playingPile[a]->getTop(); i >= c1; i--)
			{
				playingPile[a]->Remove();
				x = playingPile[a]->getEndPt().x;
				y = playingPile[a]->getEndPt().y;
				playingPile[a]->setEndPt(x, y - 2);
			}
		}
		else if (!playingPile[b]->IsEmpty() && c2 == playingPile[b]->getTop() && (playingPile[b]->viewCard(c2).getRank() - 1) == card.getRank() && playingPile[b]->viewCard(c2).getColor() != card.getColor())
		{
			for (int i = c1; i <= playingPile[a]->getTop(); i++)
			{
				card = playingPile[a]->viewCard(i);
				card.setFaceUp(true);
				if (c1 == playingPile[a]->getTop())
				{
					card.setTop(true);
				}
				playingPile[b]->Add(card);
				x = playingPile[b]->getEndPt().x;
				y = playingPile[b]->getEndPt().y;
				playingPile[b]->setEndPt(x, y + 2);
			}
			for (int i = playingPile[a]->getTop(); i >= c1; i--)
			{
				playingPile[a]->Remove();
				x = playingPile[a]->getEndPt().x;
				y = playingPile[a]->getEndPt().y;
				playingPile[a]->setEndPt(x, y - 2);
			}
		}
	}
}
void Solitaire::moveFromHomeToPlayingPile(int a, int b, int c)
{
	int x = 0, y = 0;
	PlayingCard card;
	if (!home[a]->IsEmpty())
	{
		card = home[a]->Peek();
		card.setFaceUp(true);
		card.setTop(true);
		if (playingPile[b]->IsEmpty() && card.getRank() == 13)
		{
			playingPile[b]->Add(card);
			x = playingPile[b]->getEndPt().x;
			y = playingPile[b]->getEndPt().y;
			playingPile[b]->setEndPt(x, y + 2);
			home[a]->Remove();
		}
		else if (!playingPile[b]->IsEmpty() && c == playingPile[b]->getTop() && (playingPile[b]->Peek().getRank() - 1) == card.getRank() && playingPile[b]->Peek().getColor() != card.getColor())
		{
			playingPile[b]->Add(card);
			x = playingPile[b]->getEndPt().x;
			y = playingPile[b]->getEndPt().y;
			playingPile[b]->setEndPt(x, y + 2);
			home[a]->Remove();
		}
	}
}
void Solitaire::Play()
{
	int a = -1;
	int c = -1;
	int a2 = -1;
	int c2 = -1;
	while (true)
	{
		cout << "First click";
		point p1 = getClickedPoint();
		PileofCards *firstPile = getClickedPile(p1, a, c);

		if (firstPile == stock)
		{
			Solitaire::moveFromStock();
			cf.clearConsole();
			DisplayGame();
		}
		else
		{
			cf.clearConsole();
			DisplayGame();
			cout << "Second click";
			point p2 = getClickedPoint();
			PileofCards *secondPile = getClickedPile(p2, a2, c2);

			if (firstPile == waste && secondPile == home[a2] && !waste->IsEmpty())
			{
				this->moveFromWasteToHome(a2);
				cf.clearConsole();
				DisplayGame();
			}
			else if (firstPile == waste && secondPile == playingPile[a2] && !waste->IsEmpty())
			{

				this->moveFromWasteToPlayingPile(a2, c2);
				cf.clearConsole();
				DisplayGame();
			}
			else if (firstPile == playingPile[a] && secondPile == home[a2])
			{
				this->moveFromPlayingPileToHome(a, a2, c);
				cf.clearConsole();
				DisplayGame();
			}
			else if (firstPile == playingPile[a] && secondPile == playingPile[a2] && a != a2)
			{
				this->moveFromPlayingPileToPlayingPile(a, a2, c, c2);
				cf.clearConsole();
				DisplayGame();
			}
			else if (firstPile == home[a] && secondPile == playingPile[a2])
			{
				this->moveFromHomeToPlayingPile(a, a2, c2);
				cf.clearConsole();
				DisplayGame();
			}
			else
			{
				cf.SetCursorAt(0, 0);
				cout << "Invalid move Try again...";
				Sleep(1500);
				cf.clearConsole();
				DisplayGame();
			}
		}
		// For winner
		bool a = false, b = false, c = false, d = false;
		
		if (home[0]->getTop() == 12)
			a = true;
		if (home[1]->getTop() == 12)
			b = true;
		if (home[2]->getTop() == 12)
			c = true;
		if (home[3]->getTop() == 12)
			d = true;
			
		if (a && b && c && d)
		{
			cf.clearConsole();
			cf.SetCursorAt(0, 17);
			cout << "=============================================\n";
			cout << "|                                           |\n";
			cout << "|                  You Win!                 |\n";
			cout << "|                                           |\n";
			cout << "=============================================\n";
		}
	}
}
Solitaire ::~Solitaire()
{
	if (stock != NULL)
		delete stock;

	if (waste != NULL)
		delete waste;

	for (int i = 0; i < 4; i++)
		if (home[i] != NULL)
			delete home[i];

	for (int i = 0; i < 7; i++)
		if (playingPile[i] != NULL)
			delete playingPile[i];
}