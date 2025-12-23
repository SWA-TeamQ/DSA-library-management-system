#include "ui/PatronMenu.hpp"

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

string PatronMenu::readLine(const string &prompt) const
{
	cout << prompt;
	string s;
	if (!getline(cin, s))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return {};
	}
	return s;
}

int PatronMenu::readInt(const string &prompt) const
{
	while (true)
	{
		string s = readLine(prompt);
		try
		{
			return std::stoi(s);
		}
		catch (...)
		{
			cout << "Invalid number, try again.\n";
		}
	}
}

void PatronMenu::waitForEnter() const
{
	cout << "\nPress Enter to continue...";
	string dummy;
	getline(std::cin, dummy);
}


void PatronMenu::show()
{
	bool running = true;
	while (running)
	{
		cout << "\n--- Patron Menu ---\n"
			 << "1. List patrons\n"
			 << "2. Add patron\n"
			 << "3. Remove patron\n"
			 << "0. Back\n";

		int choice;
		cin >> choice;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice)
		{
		case 1:
			controller.listAllPatrons();
			waitForEnter();
			break;
		case 2:
		{
			cout << "\n=== Add Patron ===\n";
			string id = readLine("ID: ");
			string name = readLine("Name: ");
			string contact = readLine("Contact: ");
			string date = readLine("Membership date: ");
			if (id.empty() || name.empty())
			{
				cout << "ID and name required.\n";
			}
			else
			{
				Patron p(id, name, contact, date);
				if (controller.addPatron(p)) cout << "Patron added.\n"; else cout << "ID exists.\n";
			}
			waitForEnter();
			break;
		}
		case 3:
		{
			string id = readLine("Enter Patron ID: ");
			if (controller.removePatron(id)) cout << "Removed.\n"; else cout << "Cannot remove (active loans or not found).\n";
			waitForEnter();
			break;
		}
		case 0:
			running = false;
			break;
		default:
			cout << "Unknown choice.\n";
			break;
		}
	}
}
