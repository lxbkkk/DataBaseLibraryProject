#include <iostream>
#include <string>
#include "mysql.h"

using namespace std;

#include "count.h"
extern int book_num;
extern int reader_num;

string insert_reader_user(string username, string password, string cardid, string department, int type) {
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
	string readerid = "reader_" + to_string(reader_num);
	reader_num++;
	const char* preaderid;
	const char* pusername;
	const char* ppassword;
	const char* pcardid;
	const char* pdepartment;

	pusername = username.data();

	ppassword = password.data();

	pdepartment = department.data();

	pcardid = cardid.data();
	preaderid = readerid.data();

	int count = 0;

	con = mysql_init((MYSQL*)0);

	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			//printf("Select successfully the database!\n");
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

	sprintf(tmp, "insert reader values('%s',\"%s\",\"%s\",0,%d)",pcardid,pusername,pdepartment,type);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	sprintf(tmp, "insert userinfo values('%s',\"%s\",\"%s\")", pcardid, pusername,ppassword);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query:" << mysql_error(con) << endl;
	}
	mysql_close(con);
	return readerid;
}

int insert_one_book(string book_name,string category,string press,string author,double price, int year) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	int bookid = count("numbook");
	string sbookid;
	//database configuartion
	char dbuser[30] = "root";
	char dbpasswd[30] = "66668888"; // it must be changed
	char dbip[30] = "localhost";
	char dbname[50] = "library";
	char tablename[50] = "book";
	char* query = NULL;
	int returnvalue;
	unsigned int t;
	const char* pbookname;
	const char* pcategory;
	const char* ppress;
	const char* pauthor;
	const char* pbookid;

	pbookname = book_name.data();
	pcategory = category.data();
	ppress = press.data();
	pauthor = author.data();

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
	sprintf(tmp, "select * from book where (book_name=\"%s\" and category=\"%s\" and press=\"%s\" and author=\"%s\" and price=%.2f and year=%d)", pbookname, pcategory, ppress, pauthor,price,year);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中

	while (row = mysql_fetch_row(res)) {
		sbookid = row[0];
		count++;
	}
	mysql_free_result(res);
	if (count == 1) {
		pbookid = sbookid.data();
		sprintf(tmp, "update book set total=total+1,stock=stock+1 where book_id=\"%s\"",pbookid);
		returnvalue = mysql_real_query(con, tmp, strlen(tmp));
		if (returnvalue)
		{
			cout << "Error making query: " << mysql_error(con) << endl;
		}
		sprintf(tmp, "insert numbook values(1)");
		returnvalue = mysql_real_query(con, tmp, strlen(tmp));
		if (returnvalue)
		{
			cout << "Error making query: " << mysql_error(con) << endl;
		}
		return 0;
	}
	sprintf(tmp, "insert book values(\"book_no_%d\",\"%s\",\"%s\",\"%s\",\"%s\",%.2f,%d,1,1)", bookid, pcategory, pbookname, ppress,pauthor,price,year);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	sprintf(tmp, "insert numbook values(1)");
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}

	mysql_close(con);
	return 0;
}

int insert_borrow_book(string cardid, string bookid, string borrowdate) {
	MYSQL* con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES* res;
	MYSQL_ROW row;
	char tmp[400];
	int borrowid = count("borrow");
	string mindate = "9999/99/99";
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
	string sshould;
	const char* pcardid;
	const char* pbookid;
	const char* pborrowdate;
	const char* preturndate = "0000/00/00";
	sshould = compute_date(borrowdate);
	const char* should = sshould.data();
	int ifreturn = 0;
	int yesorno;

	pcardid = cardid.data();
	pbookid = bookid.data();
	pborrowdate = borrowdate.data();

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
	sprintf(tmp, "select * from book where book_id=\"%s\"", pbookid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中
	yesorno = 1;
	while (row = mysql_fetch_row(res)) {
		if (row[8] <= 0) {
			cout << "此书全部借出——" << endl;
			yesorno = 0;
		}
	}
	mysql_free_result(res);
	if (yesorno == 0) {
		sprintf(tmp, "select * from borrow where book_id=\"%s\"", pbookid);
		returnvalue = mysql_real_query(con, tmp, strlen(tmp));
		if (returnvalue)
		{
			cout << "Error making query: " << mysql_error(con) << endl;
		}
		res = mysql_store_result(con);//将结果保存在res结构体中
		while (row = mysql_fetch_row(res)) {
			if (row[6] == 0) {
				if (row[5] < mindate) {
					mindate = row[5];
				}
			}
		}
		cout << mindate << endl;
		return 0;
	}
	sprintf(tmp, "select * from borrow where book_id=\"%s\" and card_id=\"%s\" and if_returned=0", pbookid,pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	res = mysql_store_result(con);//将结果保存在res结构体中
	count = 0;
	while (row = mysql_fetch_row(res)) {
		count++;
	}
	if (count > 0) {
		cout << "已借过该书且未归还——" << endl;
		return 0;
	}
	sprintf(tmp, "insert borrow values(\"%d\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",0)", borrowid, pcardid, pbookid, pborrowdate, preturndate, should);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	sprintf(tmp, "insert numbook values(1)");
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	sprintf(tmp, "update book set stock=stock-1 where book_id=\"%s\"", pbookid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	mysql_close(con);
	return 0;
}

int insert_return_book(string cardid, string bookid, string returndate) {
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
	char* query = NULL;
	int returnvalue;
	unsigned int t;
	const char* pcardid;
	const char* pbookid;
	const char* preturndate;
	const char* pborrowid;

	pcardid = cardid.data();
	pbookid = bookid.data();
	preturndate = returndate.data();

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
	cout << pcardid;
	sprintf(tmp, "update borrow set if_returned=1,return_date=\"%s\" where book_id=\"%s\" and card_id=\"%s\"",preturndate,pbookid,pcardid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	sprintf(tmp, "update book set stock=stock+1 where book_id=\"%s\"", pbookid);
	returnvalue = mysql_real_query(con, tmp, strlen(tmp));
	if (returnvalue)
	{
		cout << "Error making query: " << mysql_error(con) << endl;
	}
	mysql_close(con);
	return 0;
}