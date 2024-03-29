/* ===================================================================================================================
** Assign3-NumberGame.cpp - Creator: Hui Chen
** Program currently contains 204 lines of codes excluding the lines only have brackets or nothing.
** ================================================================================================================= */

#include "pch.h"
#include <iostream>
#include <fstream>				//include <fstream> library for reading from and writing data in the game_record file;
#include <cstdlib>				//include <cstdilb> and <ctime> library for getting random numbers;
#include <ctime>
#include <iomanip>				//include <iomanip> library for setting width of output messages;
#include <string>
using namespace std;

const int number_of_players = 5;				//a global variable for defining the size of players as 5 players;

class players
{
private:
	string name;
	int nums[3], sum, current_money, bet_money;

public:
	players();
	void set_bet();
	int check_money_amount();
	void add_money();
	void setname();
	string getname();
	int* getnums(players player[], int number_of_players);	//this return the values of the array of one particular player's nums. 
	void setsum();
	int getsum();
};

void show_menu();
void start_a_game();
void read_record();
void save_record(players *player, string winner_name);	  //pass the object array (5 players) of the class 'players' to save their information into the record file.

int main()
{
	bool keep_looping = 1;
	while (keep_looping)
	{
		cout << "[-- The user is able to keep playing the game over and over again until he or she press 4 to exit the game --]\n\n" << endl;
		show_menu();
		bool wrong_input;
		do {
			wrong_input = 0;
			int choice;
			cin >> choice;
			switch (choice)
			{
			case 1:
			case 2:
				start_a_game();
				break;
			case 3:
				read_record();
				break;
			case 4:
				cout << "[-- Leaving the whole game program... --]" << endl;
				cout << "Thank you for playing the game! Hope you enjoyed it :)" << endl;
				keep_looping = 0;
				break;
			default:
				wrong_input = 1;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "[-- Entering this path where the program allows the user to keep trying until inputting proper number for choosing from menu. --] \n" << endl;
				cout << "Sorry, the program cannot recognise your choice. Try again!" << endl;
				break;
			}
		} while (wrong_input);
	}
	return 0;
}

players::players()
{
	current_money = 100;
}

void players::set_bet()
{
	cout << "\n\n[-- Entering the class function set_bet(), waiting for the player to input the amount of money they want to bet on --]\n\n" << endl;
	cout << "How much you want to bet on?" << endl;
	cin >> bet_money;

	while (bet_money > current_money || bet_money < 0 || cin.fail())
	{
		cout << "[-- Catching potential errors like betting over the player has or input wrong type of data --]\n\n" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Hey you only have " <<char(156) << current_money << ". Dont bet more than what you have! \nTry again! Input a proper number of money you want to bet on." << endl;
		cin >> bet_money;
	}
	if(bet_money <= current_money)
	{
		current_money -= bet_money;
	}
}

int players::check_money_amount()
{
	return current_money;
}

void players::add_money()
{
	cout << "\n [-- Entering the class function add_money() for the final winner and return to the main function again --]\n\n" << endl;
	current_money += bet_money + (bet_money * 2);
}
void players::setname()
{
	cout << "\n[-- Entering the class function setname(), waiting for the user to input a name... --]\n\n" << endl;
	cout << "Hello Player!What should I call you?" << endl;
	cin.ignore();
	getline(cin, name);
}

string players::getname()
{
	return name;
}

int* players::getnums(players player[], int number_of_players)
{
	return player[number_of_players].nums;
}

void players::setsum()
{
	cout << "\n[-- Entering the class function setsum()... --]\n\n" << endl;
	srand((unsigned)time(NULL));
	sum = 0;
	cout << "\n\n" << "* -------------------------------------------- *" << endl;
	cout << "*        Hi " << name << "! Here are Your Numbers:" << "       *" << endl;

	for (int i = 0; i < 3; i++)
	{
		nums[i] = rand() % 10 + 1;
		cout << "*         The Number " << i + 1 << " You Get is: " << nums[i] << "           *" << endl;
		sum += nums[i];
	}
	cout << "* -------------------------------------------- *" << endl;
	cout << "* The sum of your three random numbers is:" << sum << "   *" << endl;
	cout << "* -------------------------------------------- *" << endl;
}

int players::getsum()
{
	return sum;
}

void show_menu()
{
	cout << "[-- Entering the function show_menu(), waiting for the user to choose from the menu... --]\n\n" << endl;
	cout << "* -------------------------------------------- *" << endl;
	cout << "*     " << setw(36) << "< Welcome to Crazy Rich Adventure > " << "     *" << endl;
	cout << "*  " << setw(25) << "MENU" << setw(20) << "  *" << endl;
	cout << "*   " << setw(30) << "Press 1 to Start A Game" << setw(14) << "   *" << endl;
	cout << "*   " << setw(28) << "Press 2 to Play Again" << setw(16) << "   *" << endl;
	cout << "*     " << setw(36) << "Press 3 to Read Previous Record" << "     *" << endl;
	cout << "*     " << setw(29) << "Press 4 to Exit the Game" << setw(13) << "      *" << endl;
	cout << "* -------------------------------------------- *\n\n" << endl;
}

void start_a_game()
{
	cout << "[-- Entering the function start_a_game()... --]\n\n" << endl;

	players player[number_of_players];			//create an array to store 5 player objects of the class "players".

	for (int count_player = 0; count_player < number_of_players; count_player++)		//give each player numbers and sum.
	{
		player[count_player].setname();
		cout << "\n [-- Entering the class function check_money_amount()... --]\n\n" << endl;
		cout << "The amount of money you have currently: "<< char(156) <<player[count_player].check_money_amount();
		player[count_player].set_bet();
		player[count_player].setsum();
		cout << "\n\n";
	}

	int max = -1;
	for (int x = 0; x < number_of_players; x++)				//now a loop for comparing which total sum is the biggest.
	{
		if (player[x].getsum() > max)
		{
			max = player[x].getsum();
		}
	}
	cout << "[-- Checking what is the biggest sum --]\n\n" << endl;
	cout << "* -------------------------------------------- *" << endl;
	cout << "* " << setw(30) << "The Biggest Sum is: " << max << setw(14) << "*" << endl;
	cout << "* -------------------------------------------- *" << endl;

	cout << "[--Checking who has this biggest sum as the finnal winner --]\n\n" << endl;
	string winner_name= "";
	for (int y = 0; y < number_of_players; y++)					//now another loop to idendify which player the biggest sum belongs to.
	{
		if (player[y].getsum() == max)									//store finnal winner's name.
		{
			winner_name += player[y].getname() + " ";			//if there are two players have the same biggest sums, both of their names will be stored as final winners.
			player[y].add_money();
		}											
	}

	cout << "* -------------------------------------------- *" << endl;
	cout << "*              OUR FINNAL WINNER:              *" << endl;
	cout << "*             " << setw(10) << winner_name << "!!" << setw(22) << "       *" << endl;
	cout << "* -------------------------------------------- *\n\n" << endl;

	cout << "[--Updating the amount of money each player has --]\n\n" << endl;
	for (int a = 0; a < number_of_players; a++)
	{
		cout << "The amount of money " << player[a].getname() << " has is: " << char(156) << player[a].check_money_amount() << "\n" << endl;
	}

	save_record(player, winner_name);
	cout << "\n\n";
}

void read_record()
{
	cout << "[-- Entering the function read-record(), reading from the file GameRecord.txt... --] \n\n" << endl;
	ifstream my_file;
	my_file.open("GameRecord.txt");
	if (my_file.is_open())
	{
		char ch = my_file.get();
		while (!my_file.eof())
		{
			cout << ch;					//display the first character read in;
			ch = my_file.get();		//read the next character until it reachs the end of the file;
		}
	}
	my_file.close();
}

void save_record(players *player, string winner_name)
{
	cout << "[-- Entering the function save-record(), waiting for the user to choose... --] \n\n" << endl;
	cout << "Dear user, do you want to save your game record to a file? (Y/N) \n\n" << endl;
	char save_or_not;
	bool wrong_input;
	do {
		cin >> save_or_not;
		wrong_input = 0;
		switch (save_or_not)
		{
		case 'N':
		case 'n':
			cout << "[-- Choosing the path of no saving... --]\n\n" << endl;
			cout << "You have left the game without saving it." << endl;
			cout << "Hope you enjoyed the game!\n\n" << endl;
			break;
		case 'Y':
		case 'y':
		{
			cout << "[-- Now starting to save record into the file GameRecord.txt... --]\n\n" << endl;
			ofstream myfile;
			myfile.open("GameRecord.txt", ios::app);
			if (myfile.is_open())
			{
				for (int z = 0; z < number_of_players; z++)
				{
					int* nums = player[z].getnums(player, z);
					myfile << z + 1 << "." << "Player's Name: " << player[z].getname() << endl;
					myfile << "The first number is: " << nums[0] << endl;
					myfile << "The second number is: " << nums[1] << endl;
					myfile << "The third number is: " << nums[2] << "\n" << endl;
					myfile << "The sum the player got: " << player[z].getsum() << "\n" << endl;
					myfile << "The current amount of money the player has after the bet is: " << char(156) << player[z].check_money_amount() << "\n" << endl;
				}
				myfile << "The finnal winner of the game was: " << winner_name << endl;
				myfile << "[ This is the last line of record for one game. ]\n\n" << endl;
				myfile.close();
				cout << "[-- Save Record Successfully --]\n\n" << endl;
			}
			break;
		}
		default:
			wrong_input = 1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "[-- Entering this path where the program allows the user to keep trying until inputting proper number for choosing from menu. --] \n" << endl;
			cout << "Sorry, the program cannot recognise your choice, please try again!" << endl;
			break;
		}
	} while (wrong_input);
}
