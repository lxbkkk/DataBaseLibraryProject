#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;

string search_reader(string cardid,int i) {
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
	unsigned int t;
	string result;

	int count = 0;

	const char* pcardid;
	pcardid = cardid.data();

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

	sprintf(tmp, "select * from %s where card_id = \"%s\"", tablename, pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		//printf("%s executed!!!\n", tmp);
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		result = row[i];
		count++;
	}

	mysql_free_result(res);
	mysql_close(con);
	return result;
}

string search_type(string cardid, int i) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "reader";
	char* query = NULL;
	int returnvalue;
	unsigned int t;
	string result;

	int count = 0;

	const char* pcardid;
	pcardid = cardid.data();

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

	sprintf(tmp, "select * from %s where card_id = \"%s\"", tablename, pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		//printf("%s executed!!!\n", tmp);
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		result = row[i];
		count++;
	}

	mysql_free_result(res);
	mysql_close(con);
	return result;
}

int search_book_string(int num, string input, int ifborrow) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL_RES* res2;
	MYSQL_ROW row2;
	char tmp[400];
	char tmp2[400];
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "book";
	char* query = NULL;
	int returnvalue;
	unsigned int t;
	unsigned int t2;
	string outputyear;
	int marknull = 0;
	const char* pinput;
	const char* pa = "book_id";
	pinput = input.data();
	string stock0;
	const char* stock1;
	const char* stock2 = "0";

	int count = 0;

	if (num == 0) pa = "book_id";
	if (num == 1) pa = "book_name";
	if (num == 2) pa = "category";
	if (num == 3) pa = "press";
	if (num == 4) pa = "author";

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			con->reconnect = 1;
			query = "set names \'GBK\'";
			returnvalue = mysql_real_query(con, query, strlen(query));
			if (returnvalue) {
				cout << "Error making query: " << mysql_error(con) << endl;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}

	sprintf(tmp, "select * from book where %s = \"%s\"", pa, pinput);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	cout << "书本id, 书本类别, 书本名称, 出版社, 作者, 价格, 年份, 馆藏总数, 当前馆内数目" << endl;

	while (row = mysql_fetch_row(res)) {
		marknull = 0;
		for (t = 0; t < mysql_num_fields(res); t++) {
			stock0 = row[8];
			stock1 = stock0.c_str();
			marknull = !(strcmp(stock1, stock2));
			if (t == 0)
				cout << row[t];
			else {
				cout << ", " << row[t];
			}
		}
		if (ifborrow == 1) {
			if (marknull == 1) {
				sprintf(tmp2, "select * from borrow where book_id = \"%s\"", row[0]);
				mysql_real_query(con, tmp2, strlen(tmp2));
				res2 = mysql_store_result(con);//将结果保存在res结构体中
				while (row2 = mysql_fetch_row(res2)) {
					for (t2 = 0; t2 < mysql_num_fields(res2); t2++) {
						if (t2 == 0) {
							outputyear = row2[5];
						}
						else if (row2[5] < outputyear) {
							outputyear = row2[5];
						}
					}
				}
				cout << endl << "最早归还时间：" << outputyear;
			}
		}
		cout << endl;
		count++;
	}
	mysql_free_result(res);
	mysql_close(con);
	return 0;

}

int search_book_range(int num, string down, string up) {
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
	unsigned int t;
	double p1, p2;
	int y1, y2;

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			con->reconnect = 1;
			query = "set names \'GBK\'";
			returnvalue = mysql_real_query(con, query, strlen(query));
			if (returnvalue) {
				cout << "Error making query: " << mysql_error(con) << endl;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}

	if (num == 0) {
		const char* pa = "price";
		p1 = atof(down.c_str());
		p2 = atof(up.c_str());
		sprintf(tmp, "select * from book where (%s > %.2f and %s < %.2f)", pa,p1,pa,p2);
	}
	else if (num == 1) {
		const char* pa = "year";
		y1 = atoi(down.c_str());
		y2 = atoi(up.c_str());
		sprintf(tmp, "select * from book where (%s > %d and %s < %d)", pa, y1,pa,y2);
	}
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中
	cout << "书本id, 书本类别, 书本名称, 出版社, 作者, 价格, 年份, 馆藏总数, 当前馆内数目" << endl;
	while (row = mysql_fetch_row(res)) {
		for (t = 0; t < mysql_num_fields(res); t++) {
			if (t == 0) cout << row[t];
			else cout << ", " << row[t];
		}
		cout << endl;
		count++;
	}
	mysql_free_result(res);
	mysql_close(con);
	return 0;
}

int search_borrow_book(string cardid) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	string sbookid;
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "borrow";
	char* query = NULL;
	int returnvalue;
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
				cout << "Error making query: " << mysql_error(con) << endl;
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}
	sprintf(tmp, "select * from borrow where card_id=\"%s\" and if_returned = 0", pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中
	//cout << "书本id, 书本类别, 书本名称, 出版社, 作者, 价格, 年份, 馆藏总数, 当前馆内数目" << endl;
	while (row = mysql_fetch_row(res)) {
		search_book_string(0, row[2],0);
	}
	mysql_close(con);
	return 0;
}

int search_if_user(string cardid) {
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
	unsigned int t;
	int result = 0;

	int count = 0;

	const char* pcardid;
	pcardid = cardid.data();

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

	sprintf(tmp, "select * from %s where card_id = \"%s\"", tablename, pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		//printf("%s executed!!!\n", tmp);
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		count++;
	}

	mysql_free_result(res);
	mysql_close(con);
	return count;
}
