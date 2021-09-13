#ifndef INSERT_H
#define INSERT_H
#include <string>
#include <iostream>
using namespace std;

string insert_reader_user(string username, string password, string cardid, string department, int type);

int insert_one_book(string book_name, string category, string press, string author, double price, int year);

int insert_borrow_book(string cardid, string bookid, string borrowdate);

int insert_return_book(string cardid, string bookid, string returndate);

#endif