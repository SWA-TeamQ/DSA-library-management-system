#pragma once
#include <string>
#include <iostream>
using namespace std;

class BookMenu{
    void handleBookMenu();
   
   // --- Book Operations ---
   void handleAddBook();
   void handleListBooks();
   void handleSearchBooks();
   void handleSortBooks();
   void handleRemoveBook();

};