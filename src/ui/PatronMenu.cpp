#include "ui/PatronMenu.hpp"

void PatronMenu::show()
{
	bool running = true;
	while (running)
	{
		printHeader("Patron Menu ");
		cout << "1. List patrons\n"
			 << "2. Add patron\n"
			 << "3. Remove patron\n"
			 << "4, Update Patron\n"
			 << "5, Search Patrons\n"
			 << "6, Sort Patons\n"
			 << "0. Back\n";

		int choice = readInt("Choose: ");

		switch (choice)
		{
		case 0:
			running = false;
			break;
		case 1:
			listPatrons();
			break;
		case 2:
			addPatron();
			break;
		case 3:
			removePatron();
			break;
		case 4:
			updatePatron();
			break;
		case 5:
			searchPatrons();
			break;
		case 6:
			sortPatrons();
			break;
		default:
			cout << "Unknown choice.\n";
			break;
		}
	}
}

void PatronMenu::listPatrons()
{
	printHeader("List Patrons");
	Array<Patron *> patrons = controller.listAllPatrons();
	tablePrint(patrons);
	waitForEnter();
}

void PatronMenu::addPatron()
{
	printHeader(" Add Patron ");
	Patron newPatron;
	newPatron.setID(readString("ID: "));
	newPatron.setName(readString("Name: "));
	newPatron.setContact(readString("Contact: "));
	newPatron.setMembershipDate(readString("Membership date: "));

	if (controller.addPatron(newPatron))
		cout << "Patron added.\n";
	else
		cout << "ID exists.\n";
	waitForEnter();
}

void PatronMenu::removePatron()
{
	printHeader("Remove Patron");
	string id = readString("Enter Patron ID: ");
	if (controller.removePatronById(id))
		cout << "Removed.\n";
	else
		cout << "Cannot remove (active loans or not found).\n";
	waitForEnter();
}

void PatronMenu::updatePatron()
{
	printHeader("Update Patron");
}

void PatronMenu::searchPatrons(){
	printHeader("Search Patrons");
}

void PatronMenu::sortPatrons()
{
	printHeader("Sort Patrons");
}
