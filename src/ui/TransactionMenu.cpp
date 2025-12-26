#include "ui/TransactionMenu.hpp"

#include <iostream>

using namespace std;

void TransactionMenu::show()
{
	bool running = true;
	while (running)
	{
		printHeader("--- Transactions ---");
		cout << "1. View all transactions\n"
			 << "2. View patron transaction history\n"
			 << "3. View patron overdue items\n"
			 << "4. View book transaction history\n"
			 << "0. Back\n";

		int choice = readInt("Choose: ");

		switch (choice)
		{
		case 0:
			running = false;
			break;

		case 1:
		{
			listTransactions();
			break;
		}
		case 2:
		{
			listTransactionsForPatron();
			break;
		}
		case 3:
		{
			listOverdueForPatron();
			break;
		}

		case 4:
		{
			listTransactionsForBook();
			break;
		}

		default:
			cout << "Unknown choice.\n";
			break;
		}
	}
}

void TransactionMenu::listTransactions()
{
	printHeader("List Transactions");
	Array<Transaction *> transactions = controller.listAllTransactions();
	tablePrint(transactions);
	waitForEnter();
}

void TransactionMenu::listTransactionsForPatron()
{
	printHeader("List Transactions For Patron");
	string pid = readString("Patron ID: ");
	controller.listTransactionsForPatron(pid);
	waitForEnter();
}

void TransactionMenu::listOverdueForPatron()
{
	printHeader("List Overdue For Patron");
	string pid = readString("Patron ID: ");
	controller.listOverdueForPatron(pid);
	waitForEnter();
}

void TransactionMenu::listTransactionsForBook()
{
	printHeader("List Transactions For Book");
	string bid = readString("Book ID: ");
	controller.listTransactionsForBook(bid);
	waitForEnter();
}

void TransactionMenu::searchTransactions()
{
	printHeader("Search Transactions");
	cout << "1. By Transaction ID\n"
		 << "0. Back\n";
	int choice = readInt("Choose: ");

	switch (choice)
	{
	case 0:
		return;
	case 1:
	{
		string txID = readString("Enter Transaction ID: ");
		auto *tx = controller.findTransactionById(txID);
		if (tx)
			print(*tx);
		else
			cout << "Transaction not found.\n";
		break;
	}
	default:
		cout << "Invalid choice.\n";
		break;
	}
	waitForEnter();
}

void TransactionMenu::sortTransactions()
{
	printHeader("Sort Transactions");
	cout << "1. By Return Date\n"
		<< "2, By Due Date\n"
		<< "3, By Borrow Date\n"

		 << "0. Back\n";
	int choice = readInt("Choose: ");

	if(choice == 0){
		return;
	}

	bool reverse = false;

	Array<Transaction *> transactions;

	switch (choice)
	{
	case 0:
		return;
	case 1:
	{
		transactions = controller.sortTransactionsByReturnDate(reverse);
		tablePrint(transactions);
		break;
	}
	case 2:
	{
		transactions = controller.sortTransactionsByDueDate(reverse);
		tablePrint(transactions);
		break;
	}
	case 3:
	{
		transactions = controller.sortTransactionsByBorrowDate(reverse);
		tablePrint(transactions);
		break;
	}
	default:
		cout << "Invalid choice.\n";
		break;
	}
	waitForEnter();
}
