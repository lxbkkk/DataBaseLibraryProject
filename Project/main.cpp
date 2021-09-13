#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "mysql.h"

using namespace std;

#include "search.h"
#include "insert.h"
#include "count.h"
#include "update.h"
#include "delete.h"

int book_num;
int reader_num;


int main()
{
	char t;
	int sign;
	int flag;
	int i,j,k;
	string bookid;
	string book_name;
	string category;
	string press;
	string author;
	string sprice1, sprice2;
	string syear1, syear2;
	string borrowdate;
	string returndate;
	double price;
	int year=0;
	string username;
	string userpassword;
	string userpassword2;
	string cardid;
	string department;
	string readerid;
	string filename;
	string addbook;
	string updatebook;
	ifstream icin;
	int updateresult;
	int intreaderid;
	int check;
	int adop1, adop2; //管理员操作标志
	int stop1, stop2,stop3; //学生老师操作标志
	int up1, up2;
	int adcard; //借书证管理
	int cardresult; //借书证操作结果
	int type = 1; //0 means aderministrator, 1 means student, 2 means teacher
	const char* userp;
	const char* userp2;
	int ifuser;
	char tablename[50] = "userinfo";
	reader_num = count("userinfo");
	book_num = count("book");
	while (1) {
		cout << "Welcome to the library——" << endl;
		cout <<  "退出：输入0" << endl;
		cout <<  "注册：输入1" << endl; //注册
		cout <<  "登录：输入2" << endl;//登录
		cin >> sign;
		getchar();
		if (sign == 0) break;
		else if (sign == 1) {
			cout << "卡号:";
			getline(cin, cardid);
			check = check_input(cardid);
			if (check == 1) continue;
			cout << "学院:";
			getline(cin, department);
			check = check_input(department);
			if (check == 1) continue;
			cout << "学生输入1,教师输入2" << endl << "用户类型: ";
			cin >> type;
			cout << "用户名:";
			getchar();
			getline(cin, username);
			check = check_input(username);
			if (check == 1) continue;
			cout << "密码:";
			getline(cin, userpassword);
			check = check_input(userpassword);
			if (check == 1) continue;
			cout << "确认密码:";
			getline(cin, userpassword2);
			userp = userpassword.c_str();
			userp2 = userpassword2.c_str();
			flag = strcmp(userp, userp2);
			while (flag) {
				cout << "确认密码错误!" << endl;
				cout << "卡号:";
				getline(cin, cardid);
				check = check_input(cardid);
				if (check == 1) continue;
				cout << "学院:";
				getline(cin, department);
				check = check_input(department);
				if (check == 1) continue;
				cout << "学生输入1,教师输入2" << endl << "用户类型: ";
				cin >> type;
				getchar();
				cout << "用户名:";
				getchar();
				getline(cin, username);
				check = check_input(username);
				if (check == 1) continue;
				cout << "密码:";
				getline(cin, userpassword);
				check = check_input(userpassword);
				if (check == 1) continue;
				cout << "确认密码:";
				getline(cin, userpassword2);
				userp = userpassword.c_str();
				userp2 = userpassword2.c_str();
				flag = strcmp(userp, userp2);
			}
			if (check == 1) continue;
			insert_reader_user(username, userpassword, cardid, department, type);
			continue;
		}
		else if (sign == 2) {
			cout << "卡号:";
			getline(cin, cardid);
			check = check_input(cardid);
			if (check == 1) continue;
			ifuser = search_if_user(cardid);
			if (ifuser == 0) {
				cout << "用户不存在——" << endl;
				continue;
			}
			cout << "密码:";
			getline(cin, userpassword);
			check = check_input(userpassword);
			if (check == 1) continue;
			userpassword2 = search_reader(cardid, 2);
			userp = userpassword.c_str();
			userp2 = userpassword2.c_str();
			flag = strcmp(userp, userp2);
			while (flag) {
				cout << "密码错误:(" << endl;
				cout << "卡号:";
				getline(cin, cardid);
				check = check_input(cardid);
				if (check == 1) continue;
				cout << "密码:";
				getline(cin, userpassword);
				check = check_input(userpassword);
				if (check == 1) continue;
				userpassword2 = search_reader(cardid, 2);
				userp = userpassword.c_str();
				userp2 = userpassword2.c_str();
				flag = strcmp(userp, userp2);
			}
			if (check == 1) continue;
			username = search_reader(cardid, 1);
			type = atoi(search_type(cardid, 4).c_str());
			cout << "Hello " << username << endl;
		}
		else continue;
		if (type == 0) { //adm
			while (1) {
				cout << "退出：输入0\n图书入库：输入1\n图书信息更新：输入2\n借书证管理：输入3" << endl;
				cin >> adop1;
				if (adop1 == 0) break;
				if (adop1 == 1) {
					cout << "单本入库：输入1\n批量入库：输入2" << endl;
					cin >> adop2;
					if (adop2 == 1) {
						cout << "输入书名，分类，出版社，作者，价格，年份\n使用空格隔开，格式如下：\n书名,分类,出版社,作者,价格,年份" << endl;
						//全改cin cout
						getchar();
						getline(cin, addbook);
						istringstream f(addbook);
						string w;
						for (i = 0; i < 6; i++) {
							getline(f, w, ',');
							trim(w);
							if (i == 0) {
								book_name = w;
							}
							if (i == 1) {
								category = w;
							}
							if (i == 2) {
								press = w;
							}
							if (i == 3) {
								author = w;
							}
							if (i == 4) {
								price = atof(w.c_str());
							}
							if (i == 5) {
								year = atoi(w.c_str());
							}
						}
						//要考虑书名和作者带空格，还是要改成输入一个长字符串后分割
						insert_one_book(book_name, category, press, author, price, year);
					}
					if (adop2 == 2) {
						cout << "输入文件名：" << endl << "格式如下：addbook.txt" << endl;
						getchar();
						getline(cin, filename);
						//icin.open(filename);
						ifstream fi(filename);
						while (getline(fi, addbook)) {
							istringstream f(addbook);
							string w;
							for (i = 0; i < 6; i++) {
								getline(f, w, ',');
								trim(w);
								if (i == 0) {
									book_name = w;
								}
								if (i == 1) {
									category = w;
								}
								if (i == 2) {
									press = w;
								}
								if (i == 3) {
									author = w;
								}
								if (i == 4) {
									price = atof(w.c_str());
								}
								if (i == 5) {
									year = atoi(w.c_str());
								}
							}
							insert_one_book(book_name, category, press, author, price, year);
						}
					}
				}
				if (adop1 == 2) {
					cout << "欢迎来到图书信息更新——\n请输入book_id：";
					getchar();
					getline(cin, bookid);
					cout << "输入需要更改的位置：\n更改图书名称：输入0\n更改图书类别：输入1\n更改出版社名：输入2\n更改图书作者：输入3\n更改图书价格：输入4\n更改图书年份：输入5\n更改书本总数：输入6\n更改书本当前馆内数目：输入7\n";
					cin >> up1;
					if (up1 == 0) cout << "输入更改后的图书名称：\n";
					else if (up1 == 1) cout << "输入更改后的图书类别：\n";
					else if (up1 == 2) cout << "输入更改后的出版社名：\n";
					else if (up1 == 3) cout << "输入更改后的图书作者：\n";
					else if (up1 == 4) cout << "输入更改后的图书价格：\n";
					else if (up1 == 5) cout << "输入更改后的图书年份：\n";
					else if (up1 == 6) cout << "输入更改后的书本总数：\n";
					else if (up1 == 7) cout << "输入更改后的书本当前馆内数目：\n";
					else {
						cout << "不正确输入" << endl;
						//?break;
					}
					getchar();
					getline(cin, updatebook);
					updateresult = update_book(up1, updatebook, bookid);
					if (updateresult) cout << "更改失败~" << endl;
					else cout << "更改成功！" << endl;
				}
				if (adop1 == 3) {
					cout << "删除一个借书证：输入0\n增加一个借书证：输入1" << endl;
					getchar();
					cin >> adcard;
					if (adcard == 0) {
						cout << "输入要删除的借书证卡号：" << endl;
						getchar();
						getline(cin, cardid);
						cardresult = delete_reader(cardid);
						if (cardresult) cout << "删除失败" << endl;
						else cout << "删除成功！" << endl;
					}
					else if (adcard == 1) {
						cout << "输入要插入的借书证信息：" << endl;
						cout << "卡号:";
						getchar();
						getline(cin, cardid);
						check = check_input(cardid);
						if (check == 1) continue;
						cout << "学院:";
						getline(cin, department);
						check = check_input(department);
						if (check == 1) continue;
						cout << "学生输入1,教师输入2" << endl << "用户类型: ";
						cin >> type;
						cout << "用户名:";
						getchar();
						getline(cin, username);
						check = check_input(username);
						if (check == 1) continue;
						cout << "密码:";
						getline(cin, userpassword);
						check = check_input(userpassword);
						if (check == 1) continue;
						cout << "确认密码:";
						getline(cin, userpassword2);
						userp = userpassword.c_str();
						userp2 = userpassword2.c_str();
						flag = strcmp(userp, userp2);
						while (flag) {
							cout << "确认密码错误!" << endl;
							cout << "卡号:";
							getchar();
							getline(cin, cardid);
							check = check_input(cardid);
							if (check == 1) continue;
							cout << "学院:";
							getline(cin, department);
							check = check_input(department);
							if (check == 1) continue;
							cout << "学生输入1,教师输入2" << endl << "用户类型: ";
							cin >> type;
							getchar();
							cout << "用户名:";
							getchar();
							getline(cin, username);
							check = check_input(username);
							if (check == 1) continue;
							cout << "密码:";
							getline(cin, userpassword);
							check = check_input(userpassword);
							if (check == 1) continue;
							cout << "确认密码:";
							getline(cin, userpassword2);
							userp = userpassword.c_str();
							userp2 = userpassword2.c_str();
							flag = strcmp(userp, userp2);
						}
						if (check == 1) continue;
						insert_reader_user(username, userpassword, cardid, department, type);
					}
				}
			}
		}
		if (type == 1 || type == 2) {
			while (1) {
				cout << "退出：输入0\n图书查询：输入1\n借阅书籍：输入2\n归还书籍：输入3" << endl;
				cin >> stop1;
				if (stop1 == 0) break;
				if (stop1 == 1) {
					while (1) {
						cout << "欢迎来图书查询——" << endl;
						cout << "退出：输入0\n按书本id查询：输入1\n按书名查询：输入2\n按书本类型查询：输入3\n按出版社查询：输入4\n按作者查询：输入5\n按书本价格查询：输入6\n按书本年份查询：输入7" << endl;
						cin >> stop2;
						if (stop2 == 0) break;
						if (stop2 == 1) {
							cout << "输入书本id：" << endl;
							getchar();
							getline(cin, bookid);
							search_book_string(0, bookid,1);
						}
						if (stop2 == 2) {
							cout << "输入书名：" << endl;
							getchar();
							getline(cin, book_name);
							search_book_string(1, book_name,1);
						}
						if (stop2 == 3) {
							cout << "输入书本类型：" << endl;
							getchar();
							getline(cin, category);
							search_book_string(2, category,1);
						}
						if (stop2 == 4) {
							cout << "输入出版社：" << endl;
							getchar();
							getline(cin, press);
							search_book_string(3, press,1);
						}
						if (stop2 == 5) {
							cout << "输入作者：" << endl;
							getchar();
							getline(cin, author);
							search_book_string(4, author,1);
						}
						if (stop2 == 6) {
							cout << "输入价格下限：" << endl;
							getchar();
							getline(cin, sprice1);
							cout << "输入价格上限：" << endl;
							getline(cin, sprice2);
							search_book_range(0, sprice1, sprice2);
						}
						if (stop2 == 7) {
							cout << "输入年份下限：" << endl;
							getchar();
							getline(cin, syear1);
							cout << "输入年份上限：" << endl;
							getline(cin, syear2);
							search_book_range(1, syear1, syear2);
						}
					}
				}
				if (stop1 == 2) {
					cout << "欢迎来借书——" << endl;
					cout << "已借书籍：" << endl;
					search_borrow_book(cardid);
					while (1) {
						cout << "退出：输入0\n继续借书：输入1" << endl;
						cin >> stop3;
						if (stop3 == 0) break;
						if (stop3 == 1) {
							cout << "输入书本id：";
							getchar();
							getline(cin, bookid);
							cout << "输入日期：";
							cout << "日期格式：yyyy/mm/dd" << endl;
							getline(cin,borrowdate);
							insert_borrow_book(cardid, bookid, borrowdate);
						}
						else continue;
					}
				}
				if (stop1 == 3) {
					cout << "欢迎来还书——" << endl;
					while (1) {
						cout << "退出：输入0" << endl;
						cout << "还书：输入1" << endl;
						cin >> stop2;
						if (stop2 == 0) break;
						if (stop2 == 1) {
							cout << "输入书本id：" << endl;
							getchar();
							getline(cin, bookid);
							cout << "输入日期：" << endl;
							cout << "日期格式：yyyy/mm/dd" << endl;
							getline(cin, returndate);
							//cout << cardid;
							insert_return_book(cardid, bookid, returndate);
						}
						else continue;
					}
				}
			}
		}
	}
	//system("pause");
	return 0;
}