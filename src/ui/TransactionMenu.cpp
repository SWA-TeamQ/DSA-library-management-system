#include "ui/TransactionMenu.hpp"

#include <iostream>

using namespace std;

void TransactionMenu::show()
{
	bool running = true;
	while (running)
	{
		printHeader("--- Transactions ---");
		cout << "1. Borrow book\n"
			 << "2. Return book\n"
			 << "3. View all transactions\n"
			 << "4. View patron transaction history\n"
			 << "5. View patron overdue items\n"
			 << "0. Back\n";

		int choice;
		cin >> choice;
		cin.ignore(INT_MAX, '\n');

		switch (choice)
		{
		case 1:
		{
			string pid = readString("Patron ID: ");
			string isbn = readString("Book ISBN: ");
			if (controller.borrowBook(pid, isbn))
				cout << "Borrowed.\n";
			else
				cout << "Borrow failed.\n";
			waitForEnter();
			break;
		}
		case 2:
		{
			string pid = readString("Patron ID: ");
			string isbn = readString("Book ISBN: ");
			if (controller.returnBook(pid, isbn))
				cout << "Returned.\n";
			else
				cout << "Return failed.\n";
			waitForEnter();
			break;
		}
		case 3:
		{
			Array<Transaction *> txs = controller.listAllTransactions();
			tablePrint(txs);
			break;
		}
			waitForEnter();
			break;
		case 4:
		{
			string pid = readString("Patron ID: ");
			controller.listTransactionsForPatron(pid);
			waitForEnter();
			break;
		}
		case 5:
		{
			string pid = readString("Patron ID: ");
			controller.listOverdueForPatron(pid);
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
