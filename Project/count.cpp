#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;

extern int book_num;
extern int reader_num;

int count(string table) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char* query = NULL;
	int returnvalue;
	unsigned int t;
	const char* tablename;

	tablename = table.data();

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			//printf("Select successfully the database!\n");
			con->reconnect = 1;
			query = "set names \'GBK\'";
			returnvalue = mysql_real_query(con, query, strlen(query));
			if (returnvalue) {
				printf("Error making query: %s !!!\n", mysql_error(con));
			}
			else {
				//printf("query %s succeed!\n", query);
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}

	sprintf(tmp, "select * from %s", tablename);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	/*
	if (returnvalue)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}
	*/
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		count++;
	}

	mysql_free_result(res);
	mysql_close(con);
	return count;
}

string& trim(string& s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

int check_input(string input) {
	char* a = "--";
	char* b = ";";
	char* c = "drop table";
	int i;
	if (strstr(input.c_str(), a) != NULL) {
		cout << "非法输入——" << endl;
		return 1;
	}
	if (strstr(input.c_str(), b) != NULL) {
		cout << "非法输入——" << endl;
		return 1;
	}
	if (strstr(input.c_str(), c) != NULL) {
		cout << "非法输入——" << endl;
		return 1;
	}
	return 0;
}

string compute_date(string borrowdate) {
	string returndate;
	string syear;
	string smonth;
	string sday;
	int year;
	int month;
	int day;
	syear = borrowdate.substr(0, 4);
	smonth = borrowdate.substr(5, 2);
	sday = borrowdate.substr(8, 2);
	year = atoi(syear.data());
	month = atoi(smonth.data());
	day = atoi(sday.data());
	month = month + 2;
	if (month > 12) {
		month = month - 12;
		year = year + 1;
	}
	returndate = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
	return returndate;
}