/****************************************************************************/
/*                A simple Texas Hold'em Poker simulartion.                 */
/*                Program runs fine, but gameplay still has some bugs.      */
/****************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string.h>
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

const int suits_count = 4;
const int ranks_count = 13;
const int m_sleep_time = 2;
const int SpaceBetweenaCards = 5;

std::string suits[suits_count];
std::string ranks[ranks_count];

void press_Enter()
{
	printf("\nPress Enter to continue.\n");
	while (getchar() != '\n');
}

void m_sleep(int time)
{
#ifdef __linux__
	sleep(time);
#elif _WIN32
	Sleep(time);
#endif
}

class Card
{
public:
	int suit;
	int rank;
};

int compareCards(const void *card1, const void *card2)
{
	return (*(Card *)card1).rank - (*(Card *)card2).rank;
}

class Deck
{

private:
	int top;
	static const int card_tally = 52;

	Card cards[card_tally];

public:
	Deck()
	{
		for (int i = 0; i < suits_count; i++)
		{
			for (int j = 0; j < ranks_count; j++)
			{
				cards[i * ranks_count + j].suit = i;
				cards[i * ranks_count + j].rank = j;
			}
		}
		suits[0] = "D";
		suits[1] = "S";
		suits[2] = "H";
		suits[3] = "C";

		ranks[0] = "2";
		ranks[1] = "3";
		ranks[2] = "4";
		ranks[3] = "5";
		ranks[4] = "6";
		ranks[5] = "7";
		ranks[6] = "8";
		ranks[7] = "9";
		ranks[8] = "T";
		ranks[9] = "J";
		ranks[10] = "Q";
		ranks[11] = "K";
		ranks[12] = "A";
	}

	void print()
	{
		std::cout << "Printing the deck..." << std::endl;
		m_sleep(1);
		for (int i = 0; i < card_tally; i++)
		{
			std::cout << ranks[cards[i].rank] << suits[cards[i].suit] << std::endl;
		}
		printf("\n");
	}

	void shuffle()
	{
		top = card_tally - 1;

		for (int i = 0; i < suits_count; i++)
		{
			for (int j = 0; j < ranks_count; j++)
			{
				cards[i * ranks_count + j].suit = i;
				cards[i * ranks_count + j].rank = j;
			}
		}

		int x;
		Card tempCard;
		for (int i = 0; i < card_tally; i++)
		{
			x = rand() % card_tally;
			tempCard = cards[i];
			cards[i] = cards[x];
			cards[x] = tempCard;
		}
	}

	Card hitme()
	{
		top--;
		return cards[top + 1];
	}
};

class Player
{
public:
	std::string name;
	int money;
	Card cards[2];
	bool playing;
	int round;
	int goodToGo;
	int bet;
};

class PokerGame
{
public:
	void start(const std::string &name)
	{
		for (int i = 0; i < players_count; i++)
		{
			players[i].money = 1000;
			players[i].playing = true;
		}

		for(int i = 0; i < players_count; i++){
            if(playerIndex == i)
                players[playerIndex].name = name;
            else
                players[i].name = "Player" + std::to_string(i+1);
            }


		startGame();
	}

	void deal()
	{
		for (int i = 0; i < players_count; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (players[i].playing)
				{
					players[i].cards[j] = deck1.hitme();
				}
			}
		}
		for (int i = 0; i < 5; i++){
			tableCards[i].rank = -1;
			tableCards[i].suit = -1;
        }
	}

	void flop()
	{
		for (int i = 0; i < 3; i++)
			tableCards[i] = deck1.hitme();
	}

	void turn()
	{
		tableCards[3] = deck1.hitme();
	}

	void river()
	{
		tableCards[4] = deck1.hitme();
	}

	std::string findSiut(int CardSiut)
	{
        switch(CardSiut)
            {
                case 0: return "Diamonds";
                case 1: return "Spades";
                case 2: return "Heart";
                case 3: return "Clubs";
            }
	}

	std::string findRank(int CardRank)
	{
        switch(CardRank)
            {
                case 0: return "2";
                case 1: return "3";
                case 2: return "4";
                case 3: return "5";
                case 4: return "6";
                case 5: return "7";
                case 6: return "8";
                case 7: return "9";
                case 8: return "10";
                case 9: return "Jack";
                case 10: return  "Queen";
                case 11: return "King";
                case 12: return "Ace";
            }
	}

	void PrintCards(Card cards[],int amountOfCards)
	{
        using std::cout;
        using std::setw;
        using std::endl;
        using std::string;
        int Width = 12;
        for(int i = 0; i < amountOfCards; i++){
            for(int j = 0; j <= Width; j++)
                cout << "_";
            cout << setw(SpaceBetweenaCards);
        }
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++)
            cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
       cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++)
            cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++){
            if(cards[i].rank >= 0 && cards[i].rank <= 12)
                cout << "|" << findRank(cards[i].rank) << setw(Width - findRank(cards[i].rank).size()) << "|" << setw(SpaceBetweenaCards);
            else
                cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
        }
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++){
            if(cards[i].suit >= 0 && cards[i].suit <= 3)
                cout << "|" << findSiut(cards[i].suit) << setw(Width - findSiut(cards[i].suit).size()) << "|" << setw(SpaceBetweenaCards);
            else
                cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
        }
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++)
            cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++)
            cout << "|" << setw(Width) << "|" << setw(SpaceBetweenaCards);
        cout << setw(0) << endl;

        for(int i = 0; i < amountOfCards; i++){
            for(int j = 0; j <= Width; j++)
                cout << "_";
            cout << setw(SpaceBetweenaCards);
        }
        cout << setw(0) << endl;
	}
	void printTable()
	{
		using std::cout;
		using std::endl;
		using std::setw;
		int HalfPlayers = players_count / 2;

		cout << "----------------------------------------------------------------------------------" << endl;
		for(int i = 0; i < HalfPlayers; i++)
            cout << "  " << ((players[i].playing) ? (players[i].name) : "      ") << "         ";
        cout << endl;

        for(int i = 0; i < HalfPlayers; i++)
            cout << "   $" << setw(4) << ((players[i].playing) ? (players[i].money) : 0) << "         ";
        cout << endl;

        for(int i = 0; i < HalfPlayers; i++)
            cout << "      " << ((bind == i) ? "@" : " ") << "            ";
        cout << endl;

        PrintCards(tableCards, 5);
        cout << endl;

        for(int i = players_count - 1; i >= HalfPlayers; i--)
            cout << "      " << ((bind == i) ? "@" : " ") << "            ";
        cout << endl;

		for(int i = players_count - 1; i >= HalfPlayers; i--)
            cout << "  " << ((players[i].playing) ? (players[i].name) : "      ") << "         ";
        cout << endl;

        for(int i = players_count - 1; i >= HalfPlayers; i--)
            cout << "   $" << setw(4) << ((players[i].playing) ? (players[i].money) : 0) << "         ";
        cout << endl << endl;

        cout << setw(40) << "POT: " << pot << endl;
        cout << "----------------------------------------------------------------------------------" << endl;
		cout << endl;

		if (players[playerIndex].round)
		{
            cout << "   Your hand:" << endl;
           PrintCards(players[playerIndex].cards, 2);
		}

		m_sleep(3);
	}

private:
	static const int players_count = 8;
	Player players[players_count];
	Deck deck1;
	int bind;
	Card tableCards[5];
	int pot, action, rational, betOn, winner, maxPoints, roundWinner;
	int handPoints[players_count];
	int bestHand[players_count][3];
	enum Decision{FLOP = 1, CHECK, BET_or_CALL, RAISE};
	int playerIndex = 4;
	bool raise;

	int playersLeft()
	{
		int count = 0;
		for (int i = 0; i < players_count; i++)
			if (players[i].money > 0)
				count++;
		return count;
	}

	int computerAction(int playerNum)
	{
		if (players[playerNum].cards[0].rank < 8 && players[playerNum].cards[1].rank < 8)
		{
			if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
				return 1;
			else
				return 2;
		}

		else if (players[playerNum].cards[0].rank < 10 && players[playerNum].cards[1].rank < 10)
		{
			if (players[playerNum].cards[0].rank != players[playerNum].cards[1].rank)
				return 2;
			else
				return 3;
		}
		else
		{
			return 3;
		}
	}

	/*checks if someone still got bet/call*/
	bool playersToBet()
	{
		for (int i = 0; i < players_count; i++)
			if (players[i].round == 1 && players[i].goodToGo == 0)
				return true;

		return false;
	}

	void takeBets()
	{
		using std::cout;
		using std::cin;
		using std::endl;

		betOn = 0;
		raise = false;
		for (int k = 0; k < players_count; k++)
			players[k].goodToGo = 0;

		for (int k = bind + 1; k < bind + (players_count + 1); k++)
		{
			/* human player actions */
			if (k % players_count == playerIndex && players[playerIndex].round)
			{
				if (betOn)
				{
                    if(players[playerIndex].money > betOn)
					{
                        cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL (4) RAISE ";
                        cin >> action;
                        while ((action < Decision::FLOP || action > Decision::RAISE )&& action != Decision::CHECK)
                        {
                            cout << "Invalid number pressed." << endl;
                            cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL (4) RAISE ";
                            cin >> action;
                        }
					}
                    else if(players[playerIndex].money > 0 && players[playerIndex].money == betOn){
                        cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL ";
                        cin >> action;
                        while (action != Decision::FLOP && action != Decision::BET_or_CALL)
                        {
                            cout << "Invalid number pressed." << endl;
                            cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL ";
                            cin >> action;
                        }
					}
					else
					{
                        cout << "\t\t\t\t\tYour action: (1) FLOP ";
                        cin >> action;
                        while (action != Decision::FLOP)
                        {
                            cout << "Invalid number pressed." << endl;
                            cout << "\t\t\t\t\tYour action: (1) FLOP ";
                            cin >> action;
                        }
					}
				}
				else
				{
                    if(players[playerIndex].money > 0 && players[playerIndex].money >= betOn){
                        cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK (3) BET/CALL ";
                        cin >> action;
                        while (action < Decision::FLOP || action > Decision::BET_or_CALL)
                        {
                            cout << "Invalid number pressed." << endl;
                            cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK (3) BET/CALL ";
                            cin >> action;
                        }
					}
					else
					{
                        cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK ";
                        cin >> action;
                        while (action < Decision::FLOP || action > Decision::CHECK)
                        {
                            cout << "Invalid number pressed." << endl;
                            cout << "\t\t\t\t\tYour action: (1) FLOP (2) CHECK ";
                            cin >> action;
                        }
					}
				}

				cout << endl;

				if (action == Decision::FLOP)
				{
					players[playerIndex].round = 0;
					cout << "\t- " << players[playerIndex].name << " flops...\n";
				}
				else if (action == Decision::CHECK)
				{
					cout << "\t+ " << players[playerIndex].name << " checks.\n";
					continue;
				}
				else if(action == Decision::BET_or_CALL)
				{
					if (betOn)
					{
						pot += betOn;
						players[playerIndex].money -= betOn;
						players[playerIndex].goodToGo = 1;
						cout << "\t+ " << players[playerIndex].name << " bets " << betOn << "$\n";
						players[playerIndex].bet = betOn;
					}
					else
					{
                            cout << "How much do you want to bet: ";
                            cin >> players[playerIndex].bet;
                            while (players[playerIndex].bet > players[playerIndex].money || players[playerIndex].bet < 1)
                            {
                                cout << "Invalid number to bet." << endl;
                                cout << "How much do you want to bet: ";
                                cin >> players[playerIndex].bet;
                                cout << endl << endl;
                            }
                            pot += players[playerIndex].bet;
                            players[playerIndex].money -= players[playerIndex].bet;
                            betOn = players[playerIndex].bet;
                            players[playerIndex].goodToGo = 1;

                            cout << "\t+ " << players[playerIndex].name << " bets " << players[playerIndex].bet << "$\n";
					}
				}
				else
				{
                    cout << "How much money do you want to bet: ";
                    cin >> players[playerIndex].bet;
                    while(players[playerIndex].bet > players[playerIndex].money || players[playerIndex].bet <= betOn)
                    {
                        cout << "Invalid number to raise.\n";
                        cout << "How much money do you want to bet: ";
                        cin >> players[playerIndex].bet;
                        cout << "\n\n";
                    }
                    pot += players[playerIndex].bet;
                    players[playerIndex].money -= players[playerIndex].bet;
                    players[playerIndex].goodToGo = 1;
                    betOn = players[playerIndex].bet;
                    cout << "\t+ " << players[playerIndex].name << " bets " << players[playerIndex].bet << "$\n";
                    raise = true;

				}
			}
			/* computers actions */
			else
			{
				if (players[k % players_count].round == 0)
				{
					continue;
				}
				rational = rand() % 2;
				if (rational)
				{
					action = computerAction(k % players_count);
				}
				else
				{
					action = (rand() % 3)+1;
				}
				if (action == Decision::FLOP)
				{
					players[k % players_count].round = 0;
					cout << "\t- " << players[k % players_count].name << " flops..." << endl;
				}
				else if (action == Decision::CHECK && betOn == 0)
				{
					cout << "\t+ " << players[k % players_count].name << " checks." << endl;
					continue;
				}
				else
				{
                    int RaiseOrBet = (rand() % 2) + 1;
                    if(RaiseOrBet == 1 && players[k % players_count].money > betOn)
                    {
                        players[k % players_count].bet = betOn + (rand() % (((players[k % players_count].money-betOn) / 3) + 10));
                        pot += players[k % players_count].bet;
                        cout << "\t+ " << players[k % players_count].name << " bets " << players[k % players_count].bet << "$" << endl;
                        players[k % players_count].goodToGo = 1;
                        betOn = players[k % players_count].bet;
                        players[k % players_count].money -= players[k % players_count].bet;
                        raise = true;
                    }
                    else
                    {
                        if(players[k % players_count].money >= betOn){
                            if (betOn)
                            {
                                pot += betOn;
                                players[k % players_count].money -= betOn;
                                cout << "\t++ " << players[k % players_count].name << " calls!" << endl;
                                players[k % players_count].goodToGo = 1;
                                players[k % players_count].bet = betOn;
                            }
                            else
                            {
                                players[k % players_count].bet = (rand() % ((players[k % players_count].money / 3) + 10));
                                pot += players[k % players_count].bet;
                                players[k % players_count].money -= players[k % players_count].bet;
                                cout << '\a';
                                cout << "\t+ " << players[k % players_count].name << " bets " << players[k % players_count].bet << "$" << endl;
                                betOn = players[k % players_count].bet;
                                players[k % players_count].goodToGo = 1;
                            }
                        }
					}
				}
				m_sleep(1);
			}
		}

		if (betOn && playersToBet())
		{
			for (int k = bind + 1; k < bind + (players_count + 1); k++)
			{
				if (k % players_count == playerIndex)
				{
					if (players[playerIndex].round && players[playerIndex].goodToGo == 0)
					{
                        if(players[playerIndex].money > betOn)
                        {
                            cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL (4) RAISE ";
                            cin >> action;
                            while ((action < Decision::FLOP || action > Decision::RAISE) && action != Decision::CHECK)
                            {
                                cout << "Invalid number pressed." << endl;
                                cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL (4) RAISE ";
                                cin >> action;
                            }
                        }
                        else if(players[playerIndex].money > 0 && players[playerIndex].money == betOn){
                            cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL ";
                            cin >> action;
                            while (action != Decision::FLOP && action != Decision::BET_or_CALL)
                            {
                                cout << "Invalid number pressed." << endl;
                                cout << "\t\t\t\t\tYour action: (1) FLOP (3) BET/CALL ";
                                cin >> action;
                                cout << endl << endl;
                            }
						}
						else
						{
                             cout << "\t\t\t\t\tYour action: (1) FLOP ";
                                cin >> action;
                                while (action != Decision::FLOP)
                                {
                                    cout << "Invalid number pressed." << endl;
                                    cout << "\t\t\t\t\tYour action: (1) FLOP ";
                                    cin >> action;
                                    cout << endl << endl;
                                }
						}
						if (action == Decision::FLOP)
						{
							cout << "\t- " << players[playerIndex].name << " flops...\n";
							players[playerIndex].round = 0;
						}
						else
						{
							pot += betOn;
							players[playerIndex].money -= betOn;
							players[playerIndex].goodToGo = 1;
							players[playerIndex].bet = betOn;

							cout << "\t+ " << players[playerIndex].name << " bets " << betOn << "$\n";
						}
					}
				}

				else
				{
					if (players[k % players_count].round == 0 || players[k % players_count].goodToGo == 1)
						continue;
					action = (rand() % 2) + 1;
					if(action == Decision::BET_or_CALL && players[k % players_count].money >= betOn)
					{
						pot += betOn;
						players[k % players_count].money -= betOn;
						cout << "\t++ " << players[k % players_count].name << " calls!" << endl;
						players[k % players_count].goodToGo = 1;
						players[k % players_count].bet = betOn;
					}
					else
					{
                        players[k % players_count].round = 0;
						cout << "\t- " << players[k % players_count].name << " flops..." << endl;
					}
				}
			}
		}
		if(raise == true)
		{
            for (int k = 0; k < players_count; k++)
                if(k == playerIndex && players[k].bet < betOn && players[k].goodToGo == 1)
                {
                     cout << "\t\t\t\t\tYour action: (1) FLOP ";
                     if(players[k].money >= (betOn - players[k].bet))
                        cout << "(4) ADD TO POT ";
                     cin >> action;
                     if(action == Decision::RAISE && players[k].money >= (betOn - players[k].bet))
                     {
                        players[k].money -= (betOn - players[k].bet);
                        pot += (betOn - players[k].bet);
                     }
                     else
                     {
                        cout << "\t- " << players[k].name << " flops...\n";
                        players[k].round = 0;
                     }
                }
                else if(players[k].bet < betOn && players[k].goodToGo == 1)
                {
                    int random = (rand() % 4) + 1;
                    if(players[k].money >= (betOn - players[k].bet) && (random >= 1 && random <= 3))
                    {
                        players[k].money -= (betOn - players[k].bet);
                        pot += (betOn - players[k].bet);
                    }
                    else
                    {
                        cout << "\t- " << players[k].name << " flops...\n";
                        players[k].round = 0;
                    }
                }
        }
	}

	bool oneLeft()
	{
		int count = 0;
		for (int k = 0; k < players_count; k++)
			if (players[k].round)
				count++;
		if (count == 1)
			return true;
		else
			return false;
	}

	int getWinner()
	{
		int winner;
		for (int k = 0; k < players_count; k++)
			if (players[k].round)
				winner = k;
		return winner;
	}

	int getScore(Card hand[])
	{
		qsort(hand, 5, sizeof(Card), compareCards);
		int straight, flush, three, four, full, pairs, high;
		int k;

		straight = flush = three = four = full = pairs = high = 0;
		k = 0;

		/*checks for flush*/
		while (k < 4 && hand[k].suit == hand[k + 1].suit)
			k++;
		if (k == 4)
			flush = 1;

		/* checks for straight*/
		k = 0;
		while (k < 4 && hand[k].rank == hand[k + 1].rank - 1)
			k++;
		if (k == 4)
			straight = 1;

		/* checks for fours */
		for (int i = 0; i < 2; i++)
		{
			k = i;
			while (k < i + 3 && hand[k].rank == hand[k + 1].rank)
				k++;
			if (k == i + 3)
			{
				four = 1;
				high = hand[i].rank;
			}
		}

		/*checks for threes and fullhouse*/
		if (!four)
		{
			for (int i = 0; i < 3; i++)
			{
				k = i;
				while (k < i + 2 && hand[k].rank == hand[k + 1].rank)
					k++;
				if (k == i + 2)
				{
					three = 1;
					high = hand[i].rank;
					if (i == 0)
					{
						if (hand[3].rank == hand[4].rank)
							full = 1;
					}
					else if (i == 1)
					{
						if (hand[0].rank == hand[4].rank)
							full = 1;
					}
					else
					{
						if (hand[0].rank == hand[1].rank)
							full = 1;
					}
				}
			}
		}

		if (straight && flush)
			return 170 + hand[4].rank;
		else if (four)
			return 150 + high;
		else if (full)
			return 130 + high;
		else if (flush)
			return 110;
		else if (straight)
			return 90 + hand[4].rank;
		else if (three)
			return 70 + high;

		/* checks for pairs*/
		for (k = 0; k < 4; k++)
			if (hand[k].rank == hand[k + 1].rank)
			{
				pairs++;
				if (hand[k].rank>high)
					high = hand[k].rank;
			}

		if (pairs == 2)
			return 50 + high;
		else if (pairs)
			return 30 + high;
		else
			return hand[4].rank;
	}

	int tryHand(int array[], int player)
	{
		Card hand[5];

		/* get cards from table and player */
		for (int i = 1; i < 4; i++)
			hand[i - 1] = tableCards[array[i]];

		for (int i = 0; i < 2; i++)
			hand[i + 3] = players[player].cards[i];

		return getScore(hand);

	}

	void evaluateHands()
	{
		int stack[10], k;
		int currentPoints;

		for (int q = 0; q < players_count; q++)
		{
			if (players[q].round)
			{
				stack[0] = -1; /* -1 is not considered as part of the set */
				k = 0;
				while (1) {
					if (stack[k] < 4)
					{
						stack[k + 1] = stack[k] + 1;
						k++;
					}

					else
					{
						stack[k - 1]++;
						k--;
					}

					if (k == 0)
						break;

					if (k == 3)
					{
						currentPoints = tryHand(stack, q);
						if (currentPoints > handPoints[q])
						{
							handPoints[q] = currentPoints;
							for (int x = 0; x < 3; x++)
								bestHand[q][x] = stack[x + 1];
						}
					}
				}

			}
		}
	} /*end of evaluateHands() */

	void printWinningHand(int winner)
	{
		using std::cout;
		using std::endl;

		Card winningHand[5];
		for (int i = 0; i < 3; i++)
			winningHand[i] = tableCards[bestHand[winner][i]];

		for (int i = 0; i < 2; i++)
			winningHand[i + 3] = players[winner].cards[i];

		qsort(winningHand, 5, sizeof(Card), compareCards);

		cout << endl;

		if((tableCards[4].suit < 0 || tableCards[4].suit > 3) && (tableCards[4].rank < 0 || tableCards[4].rank > 12)){
            cout << "No card to display\n";
            return;
        }

		PrintCards(winningHand,5);

		cout << endl << endl;
		m_sleep(3);
	}

	void PrintPlayersCards()
	{
        std::cout << "   The winning hand:" << std::endl;
			printWinningHand(roundWinner);
			for(int i = 0; i < players_count; i++){
                if(i == roundWinner)
                    continue;
                else if(players[i].round){
                    std::cout << players[i].name << " cards: " << std::endl;
                    printWinningHand(i);
                }
            }
	}
	void WithdrawMoney()
	{
        players[roundWinner].money += pot;
        pot = 0;
	}

	/* main gameplay function*/
	void startGame()
	{
		int i = 0;

		while (playersLeft() > 1)
		{
			/* starting default values*/
			for (int z = 0; z < players_count; z++)
				if (players[z].money<1)
				{
					players[z].playing = 0;
					players[z].round = 0;
				}
			for (int z = 0; z < players_count; z++)
			{
				if (players[z].playing)
					players[z].round = 1;
				handPoints[z] = -1;
			}
			for (int x = 0; x < players_count; x++)
			{
				for (int y = 0; y<3; y++)
				{
					bestHand[x][y] = -1;
				}
			}

			/* checking for game over*/
			if (players[playerIndex].playing == 0)
			{
				std::cout << "You are out of money, sorry." << std::endl;
				std::cout << "Game over." << std::endl;
				break;
			}

			bind = i % players_count;

			/* paying bind */
			pot = 20;
			if (players[bind].money >= 20)
				players[bind].money -= 20;
			else
				players[bind].playing = 0;

			std::cout << "\n\n\n\n\n\n\n";
			std::cout << "\t\t\t\t\t ------ ROUND " << i + 1 << " ------\n\n\n";
			m_sleep(1);
			deck1.shuffle();

			/* pre-flop */
			deal();
			m_sleep(m_sleep_time);
			printTable();
			takeBets();
			if (oneLeft())
			{
				winner = getWinner();
				std::cout << players[winner].name << " wins $" << pot << "\n\n";
				i++;
				players[winner].money += pot;
				PrintPlayersCards();
				continue;
			}

			/* flop */
			flop();
			std::cout << std::endl;
			m_sleep(m_sleep_time);
			printTable();
			takeBets();
			if (oneLeft())
			{
				winner = getWinner();
				std::cout << players[winner].name << " wins $" << pot << "\n\n";
				i++;
				players[winner].money += pot;
				PrintPlayersCards();
				continue;
			}

			/* turn */
			turn();
			std::cout << std::endl;
			m_sleep(m_sleep_time);
			printTable();
			takeBets();
			if (oneLeft())
			{
				winner = getWinner();
				std::cout << players[winner].name << " wins $" << pot << "\n\n";
				i++;
				players[winner].money += pot;
				PrintPlayersCards();
				continue;
			}

			/* river */
			river();
			std::cout << std::endl;
			m_sleep(m_sleep_time);
			printTable();
			takeBets();

			evaluateHands();

			/* find and declare round winner */
			maxPoints = 0;
			for (int q = 0; q < players_count; q++)
			{
				if (players[q].round)
				{
					if (handPoints[q] > maxPoints)
					{
						maxPoints = handPoints[q];
						roundWinner = q;
					}
				}
			}
			std::cout << std::endl;
			std::cout << players[roundWinner].name << " wins $" << pot << " with ";
			if (maxPoints < 30)
				std::cout << "HIGH CARD";
			else if (maxPoints < 50)
				std::cout << "SINGLE PAIR";
			else if (maxPoints < 70)
				std::cout << "TWO PAIRS";
			else if (maxPoints < 90)
				std::cout << "THREE OF A KIND";
			else if (maxPoints < 110)
				std::cout << "STRAIGHT";
			else if (maxPoints < 130)
				std::cout << "FLUSH";
			else if (maxPoints < 150)
				std::cout << "FULL HOUSE";
			else if (maxPoints < 170)
				std::cout << "FOUR OF A KIND";
			else
				std::cout << "STRAIGHT FLUSH";
			std::cout << "\n\n";

            players[roundWinner].money += pot;

            PrintPlayersCards();

			i++;
		}

	}
};


int main()
{
	std::string name;
	PokerGame game1;

	srand(time(NULL));

	using std::cout;
	using std::endl;

	cout << "Welcome to..." << endl << endl;
	cout << "#######                        ###### " << endl;
	cout << "   #    ###### #    # #####    #     #  ####  #    # ###### #####" << endl;
	cout << "   #    #       #  #    #      #     # #    # #   #  #      #    #" << endl;
	cout << "   #    #####    ##     #      ######  #    # ####   #####  #    #" << endl;
	cout << "   #    #        ##     #      #       #    # #  #   #      #####" << endl;
	cout << "   #    #       #  #    #      #       #    # #   #  #      #   #" << endl;
	cout << "   #    ###### #    #   #      #        ####  #    # ###### #    #" << endl << endl;

	cout << "Please type your name: ";
	std::cin >> name;

	cout << "OK " << name << " let's play some poker!" << endl << endl;

	game1.start(name);

	return 0;
}
