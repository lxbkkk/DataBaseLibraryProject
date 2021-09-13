#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include <iostream>
using namespace std;

string search_reader(string readerid,int i);

int check_input(string input);

string search_type(string readerid, int i);

int search_book_string(int num, string input, int ifborrow);

int search_book_range(int num, string down, string up);

int search_borrow_book(string cardid);

int search_if_user(string cardid);

#endif
