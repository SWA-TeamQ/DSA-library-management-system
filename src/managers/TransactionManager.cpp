#include <iostream>

using namespace std;

TransactionManager::TransactionManager(const string &filename) : store(filename)
{
    loadTransactions();
}