#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;

#include "insert.h"


int delete_reader(string cardid) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "userinfo";
	char* query = NULL;
	int returnvalue;
	double price;
	int year, total, stock;
	unsigned int t;
	const char* pcardid;

	pcardid = cardid.data();

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			con->reconnect = 1;
			query = "set names \'GBK\'";
			returnvalue = mysql_real_query(con, query, strlen(query));
			if (returnvalue) {
				cout << "Error making query1: " << mysql_error(con) << endl;
				return 1;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
		return 1;
	}
	sprintf(tmp, "select * from borrow where card_id = \"%s\" and if_returned = 0", pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query2: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		insert_return_book(pcardid, row[2], "0000/00/00");
	}

	sprintf(tmp, "delete from userinfo where card_id=\"%s\"", pcardid);
	
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query3: " << mysql_error(con) << endl;
		return 1;
	}

	sprintf(tmp, "delete from reader where card_id=\"%s\"", pcardid);

	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query4: " << mysql_error(con) << endl;
		return 1;
	}
	
	mysql_close(con);
	return 0;
}