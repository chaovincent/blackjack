#include <iostream>
#include <array>
#include <random>

enum CardRank
{
	RANK_2,			//0
	RANK_3,			//1
	RANK_4,			//2
	RANK_5,			//3
	RANK_6,			//4
	RANK_7,			//etc
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_J,
	RANK_Q,
	RANK_K,
	RANK_A,
	MAX_RANK		//13
};

enum CardSuit
{
	SUIT_CLUB,		//0
	SUIT_DIAMOND,	//1
	SUIT_HEART,		//2
	SUIT_SPADE,		//3
	MAX_SUIT		//4
};

struct Card
{
	CardRank rank;
	CardSuit suit;
};

void printCard(const Card card)
{
	switch(card.rank)
	{
		case(RANK_2) : std::cout << "2"; 	break;
		case(RANK_3) : std::cout << "3"; 	break;
		case(RANK_4) : std::cout << "4"; 	break;
		case(RANK_5) : std::cout << "5"; 	break;
		case(RANK_6) : std::cout << "6"; 	break;
		case(RANK_7) : std::cout << "7"; 	break;
		case(RANK_8) : std::cout << "8"; 	break;
		case(RANK_9) : std::cout << "9"; 	break;
		case(RANK_10) : std::cout << "10"; 	break;
		case(RANK_J) : std::cout << "J"; 	break;
		case(RANK_Q) : std::cout << "Q"; 	break;
		case(RANK_K) : std::cout << "K"; 	break;
		case(RANK_A) : std::cout << "A"; 	break;
		default : std::cout << "Error, please try again"; break;
	}
	switch(card.suit)
	{
		case(SUIT_CLUB) : std::cout << "C"; break;
		case(SUIT_DIAMOND) : std::cout << "D"; break;
		case(SUIT_HEART) : std::cout << "H"; break;
		case(SUIT_SPADE) : std::cout << "S"; break;
		default : std::cout << "Error, please try again"; break;
	}
}

int getCardValue(Card card)
{
	if (card.rank <= 7)
	{
		return (card.rank + 2);
	}
	else if (card.rank < 13)
	{
		return 10;
	}
	return 0;
}

void swapCard(Card &card1, Card &card2)
{
	Card temp = card1;
	card1 = card2;
	card2 = temp;
}

void shuffleDeck(Card *deck)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	unsigned int rng(0);
	for (int i = 0; i < 52; ++i)
	{
		do
		{
			rng = (mersenne() % 52);
		} while (rng != (mersenne() % 52));
		swapCard(deck[i], deck[(mersenne() % 52)]);

	}
}

char getPlayerChoice()
{
	std::cout << "(h) to hit, or (s) to stand: ";
	char choice;
	do
	{
		std::cin >> choice;
	} while (choice != 'h' && choice != 's');
	return choice;
}

bool playBlackjack(Card *deck)	// Returns true if player wins
{
	// Setup initial game state
	const Card *cardPtr = &deck[0];
	int pScore = 0;
	int dScore = 0;

	// Dealer gets one card (top of the deck)
	dScore += getCardValue(*cardPtr);
	std::cout << "The dealer is showing: " << dScore << '\n';

	// Deal two cards to the player
	pScore += getCardValue(*cardPtr++);
	pScore += getCardValue(*cardPtr++);

	// Player goes first
	while(1)
	{
		std::cout << "You have: " << pScore << '\n';

		// Check if the player busted
		if (pScore > 21)
			return false;

		char choice = getPlayerChoice();
		if (choice == 's')
			break;

		pScore += getCardValue(*cardPtr++);
	}

	// If the player hasn't busted, dealer goes until they have at least 17 points
	while (dScore < 17)
	{
		dScore += getCardValue(*cardPtr++);
		std::cout << "The dealer now has: " << dScore << '\n';
	}

	// Check if dealer busted
	if (dScore > 21)
		return true;

	return (pScore > dScore);
}

int main()
{
	// Create a standard deck and shuffle
	Card deck[52];
	for(int suit = 0; suit < 4; ++suit)
		for (int rank = 0; rank < 13; ++rank)
			deck[(suit*13)+(rank)] = {static_cast<CardRank>(rank), static_cast<CardSuit>(suit)};
	shuffleDeck(deck);

	if(playBlackjack(deck))
		std::cout << "You Win!";
	else
		std::cout << "You Lose!";

	return 0;
}
