#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;

extern int book_num;
extern int reader_num;

int update_book(int num,string update,string bookid) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "book";
	char* query = NULL;
	int returnvalue;
	double price;
	int year, total, stock;
	unsigned int t;
	const char* pupdate;
	const char* ptype;
	const char* pbookid;
	string type;
	if (num == 0) type = "book_name";
	if (num == 1) type = "category";
	if (num == 2) type = "press";
	if (num == 3) type = "author";
	if (num == 4) type = "price";
	if (num == 5) type = "year";
	if (num == 6) type = "total";
	if (num == 7) type = "stock";

	pupdate = update.data();
	ptype = type.data();
	pbookid = bookid.data();

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			con->reconnect = 1;
			query = "set names \'GBK\'";
			returnvalue = mysql_real_query(con, query, strlen(query));
			if (returnvalue) {
				cout << "Error making query: " << mysql_error(con) << endl;
				return 1;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
		return 1;
	}
	if(num < 4) sprintf(tmp, "update book set %s=\"%s\" where book_id = \"%s\"", ptype, pupdate,pbookid);
	else {
		if (num == 4) {
			price = atof(update.c_str());
			sprintf(tmp, "update book set %s=%.2f where book_id = \"%s\"", ptype, price, pbookid);
		}else if(num == 5){
			year = atoi(update.c_str());
			sprintf(tmp, "update book set %s=%d where book_id = \"%s\"", ptype, year, pbookid);
		}else if (num == 6) {
			total = atoi(update.c_str());
			sprintf(tmp, "update book set %s=%d where book_id = \"%s\"", ptype, total, pbookid);
		}else if (num == 7) {
			stock = atoi(update.c_str());
			sprintf(tmp, "update book set %s=%d where book_id = \"%s\"", ptype, stock, pbookid);
		}
	}
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
		return 1;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	mysql_free_result(res);
	mysql_close(con);
	return 0;
}