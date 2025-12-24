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

	cout << "1. By ID\n"
		 << "2. By Name\n"
		 << "0. Back\n";
		 int choice = readInt("Choose: ");
		 switch (choice)
		 {
		 case 0:
			return;
		 case 1:
			{
				string id = readString("Enter Patron ID: ");
				if (controller.removePatronById(id))
					cout << "Patron removed.\n";
				else
					cout << "can not remove (active loans or Patron not found.)\n";
				break;
			}
		 case 2:
			{
				string name = readString("Enter Patron Name: ");
				if (controller.removePatronByName(name))
					cout << "Patron removed.\n";
				else
					cout << "can not remove (active loans or Patron not found.)\n";
				break;
			}
		 default:
			cout << "Invalid choice.\n";
			break;
		 }
		waitForEnter();

	cout << "1. By ID\n"
		 << "2. By Name\n"
		 << "0. Back\n";
		 int choice = readInt("Choose: ");
		 switch (choice)
		 {
		 case 0:
			return;
		 case 1:
			{
				string id = readString("Enter Patron ID: ");
				if (controller.removePatronById(id))
					cout << "Patron removed.\n";
				else
					cout << "can not remove (active loans or Patron not found.)\n";
				break;
			}
		 case 2:
			{
				string name = readString("Enter Patron Name: ");
				if (controller.removePatronByName(name))
					cout << "Patron removed.\n";
				else
					cout << "can not remove (active loans or Patron not found.)\n";
				break;
			}
		 default:
			cout << "Invalid choice.\n";
			break;
		 }
		waitForEnter();
}

void PatronMenu::updatePatron()
{
	printHeader("Update Patron");
	controller.updatePatron(Patron());
	cout<<"Enter the Patron Id: \n";
	string id = readString("Enter Patron ID: ");
	if (auto *patron = controller.findPatronById(id))
	{
		cout << "Current details:\n";
		print(*patron);
		cout << "Enter new details:\n";
		patron->setName(readString("Name: "));
		patron->setContact(readString("Contact: "));
		patron->setMembershipDate(readString("Membership date: "));
		controller.updatePatron(*patron);
		cout << "Patron updated.\n";
	}
	else
		cout << "Patron not found.\n";
	
	waitForEnter();
}

void PatronMenu::searchPatrons(){
	printHeader("Search Patrons");
	cout<<"1. By ID(single)\n"
		<< "2. By Name(single)\n"
		<< "3. By Id(multiple)\n"
		<< "4. By Name(multiple)\n"
		<< "0. Back\n";
		int choice = readInt("Choose: ");
		switch (choice)
		{
			case 0:
				return;
			case 1:
				{
					string id = readString("Enter Patron ID: ");
					if (auto *patron = controller.findPatronById(id))
					{
						cout << "Patron found:\n";
						print(*patron);
					}
					else
						cout << "Patron not found.\n";
					break;
				}
			case 2:
				{
					string name = readString("Enter Patron Name: ");
					if (auto *patron = controller.findPatronByName(name))
					{
						cout << "Patron found:\n";
						print(*patron);
					}
					else
						cout << "Patron not found.\n";
					break;
				}
			case 3:
				{
					string id = readString("Enter Patron ID: ");
					Array<Patron *> patrons = controller.findPatronsById(id);
					tablePrint(patrons);
					break;
				}
			case 4:
				{
					string name = readString("Enter Patron Name: ");
					Array<Patron *> patrons = controller.findPatronsByName(name);
					tablePrint(patrons);
					break;
				}
			default:
				cout << "Invalid choice.\n";
				break;
		}
		waitForEnter();
}

void PatronMenu::sortPatrons()
{
	printHeader("Sort Patrons");
	cout << "1. Name\n"
		 << "2. Membership date\n"
		 << "3. Borrow count\n"
		 << "0. Back\n";
		 int choice =readInt("Choose: ");
		 switch (choice)
		 {	
			case 0:
				return;
			case 1:
				{
					string order = readString("Reverse order? (y/n): ");
					bool reverse = (order == "y" || order == "Y");
					Array<Patron *> patrons = controller.sortPatronsByName(reverse);
					tablePrint(patrons);
					break;
				}
			case 2:
}
