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
	int adop1, adop2; //����Ա������־
	int stop1, stop2,stop3; //ѧ����ʦ������־
	int up1, up2;
	int adcard; //����֤����
	int cardresult; //����֤�������
	int type = 1; //0 means aderministrator, 1 means student, 2 means teacher
	const char* userp;
	const char* userp2;
	int ifuser;
	char tablename[50] = "userinfo";
	reader_num = count("userinfo");
	book_num = count("book");
	while (1) {
		cout << "Welcome to the library����" << endl;
		cout <<  "�˳�������0" << endl;
		cout <<  "ע�᣺����1" << endl; //ע��
		cout <<  "��¼������2" << endl;//��¼
		cin >> sign;
		getchar();
		if (sign == 0) break;
		else if (sign == 1) {
			cout << "����:";
			getline(cin, cardid);
			check = check_input(cardid);
			if (check == 1) continue;
			cout << "ѧԺ:";
			getline(cin, department);
			check = check_input(department);
			if (check == 1) continue;
			cout << "ѧ������1,��ʦ����2" << endl << "�û�����: ";
			cin >> type;
			cout << "�û���:";
			getchar();
			getline(cin, username);
			check = check_input(username);
			if (check == 1) continue;
			cout << "����:";
			getline(cin, userpassword);
			check = check_input(userpassword);
			if (check == 1) continue;
			cout << "ȷ������:";
			getline(cin, userpassword2);
			userp = userpassword.c_str();
			userp2 = userpassword2.c_str();
			flag = strcmp(userp, userp2);
			while (flag) {
				cout << "ȷ���������!" << endl;
				cout << "����:";
				getline(cin, cardid);
				check = check_input(cardid);
				if (check == 1) continue;
				cout << "ѧԺ:";
				getline(cin, department);
				check = check_input(department);
				if (check == 1) continue;
				cout << "ѧ������1,��ʦ����2" << endl << "�û�����: ";
				cin >> type;
				getchar();
				cout << "�û���:";
				getchar();
				getline(cin, username);
				check = check_input(username);
				if (check == 1) continue;
				cout << "����:";
				getline(cin, userpassword);
				check = check_input(userpassword);
				if (check == 1) continue;
				cout << "ȷ������:";
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
			cout << "����:";
			getline(cin, cardid);
			check = check_input(cardid);
			if (check == 1) continue;
			ifuser = search_if_user(cardid);
			if (ifuser == 0) {
				cout << "�û������ڡ���" << endl;
				continue;
			}
			cout << "����:";
			getline(cin, userpassword);
			check = check_input(userpassword);
			if (check == 1) continue;
			userpassword2 = search_reader(cardid, 2);
			userp = userpassword.c_str();
			userp2 = userpassword2.c_str();
			flag = strcmp(userp, userp2);
			while (flag) {
				cout << "�������:(" << endl;
				cout << "����:";
				getline(cin, cardid);
				check = check_input(cardid);
				if (check == 1) continue;
				cout << "����:";
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
				cout << "�˳�������0\nͼ����⣺����1\nͼ����Ϣ���£�����2\n����֤��������3" << endl;
				cin >> adop1;
				if (adop1 == 0) break;
				if (adop1 == 1) {
					cout << "������⣺����1\n������⣺����2" << endl;
					cin >> adop2;
					if (adop2 == 1) {
						cout << "�������������࣬�����磬���ߣ��۸����\nʹ�ÿո��������ʽ���£�\n����,����,������,����,�۸�,���" << endl;
						//ȫ��cin cout
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
						//Ҫ�������������ߴ��ո񣬻���Ҫ�ĳ�����һ�����ַ�����ָ�
						insert_one_book(book_name, category, press, author, price, year);
					}
					if (adop2 == 2) {
						cout << "�����ļ�����" << endl << "��ʽ���£�addbook.txt" << endl;
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
					cout << "��ӭ����ͼ����Ϣ���¡���\n������book_id��";
					getchar();
					getline(cin, bookid);
					cout << "������Ҫ���ĵ�λ�ã�\n����ͼ�����ƣ�����0\n����ͼ���������1\n���ĳ�������������2\n����ͼ�����ߣ�����3\n����ͼ��۸�����4\n����ͼ����ݣ�����5\n�����鱾����������6\n�����鱾��ǰ������Ŀ������7\n";
					cin >> up1;
					if (up1 == 0) cout << "������ĺ��ͼ�����ƣ�\n";
					else if (up1 == 1) cout << "������ĺ��ͼ�����\n";
					else if (up1 == 2) cout << "������ĺ�ĳ���������\n";
					else if (up1 == 3) cout << "������ĺ��ͼ�����ߣ�\n";
					else if (up1 == 4) cout << "������ĺ��ͼ��۸�\n";
					else if (up1 == 5) cout << "������ĺ��ͼ����ݣ�\n";
					else if (up1 == 6) cout << "������ĺ���鱾������\n";
					else if (up1 == 7) cout << "������ĺ���鱾��ǰ������Ŀ��\n";
					else {
						cout << "����ȷ����" << endl;
						//?break;
					}
					getchar();
					getline(cin, updatebook);
					updateresult = update_book(up1, updatebook, bookid);
					if (updateresult) cout << "����ʧ��~" << endl;
					else cout << "���ĳɹ���" << endl;
				}
				if (adop1 == 3) {
					cout << "ɾ��һ������֤������0\n����һ������֤������1" << endl;
					getchar();
					cin >> adcard;
					if (adcard == 0) {
						cout << "����Ҫɾ���Ľ���֤���ţ�" << endl;
						getchar();
						getline(cin, cardid);
						cardresult = delete_reader(cardid);
						if (cardresult) cout << "ɾ��ʧ��" << endl;
						else cout << "ɾ���ɹ���" << endl;
					}
					else if (adcard == 1) {
						cout << "����Ҫ����Ľ���֤��Ϣ��" << endl;
						cout << "����:";
						getchar();
						getline(cin, cardid);
						check = check_input(cardid);
						if (check == 1) continue;
						cout << "ѧԺ:";
						getline(cin, department);
						check = check_input(department);
						if (check == 1) continue;
						cout << "ѧ������1,��ʦ����2" << endl << "�û�����: ";
						cin >> type;
						cout << "�û���:";
						getchar();
						getline(cin, username);
						check = check_input(username);
						if (check == 1) continue;
						cout << "����:";
						getline(cin, userpassword);
						check = check_input(userpassword);
						if (check == 1) continue;
						cout << "ȷ������:";
						getline(cin, userpassword2);
						userp = userpassword.c_str();
						userp2 = userpassword2.c_str();
						flag = strcmp(userp, userp2);
						while (flag) {
							cout << "ȷ���������!" << endl;
							cout << "����:";
							getchar();
							getline(cin, cardid);
							check = check_input(cardid);
							if (check == 1) continue;
							cout << "ѧԺ:";
							getline(cin, department);
							check = check_input(department);
							if (check == 1) continue;
							cout << "ѧ������1,��ʦ����2" << endl << "�û�����: ";
							cin >> type;
							getchar();
							cout << "�û���:";
							getchar();
							getline(cin, username);
							check = check_input(username);
							if (check == 1) continue;
							cout << "����:";
							getline(cin, userpassword);
							check = check_input(userpassword);
							if (check == 1) continue;
							cout << "ȷ������:";
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
				cout << "�˳�������0\nͼ���ѯ������1\n�����鼮������2\n�黹�鼮������3" << endl;
				cin >> stop1;
				if (stop1 == 0) break;
				if (stop1 == 1) {
					while (1) {
						cout << "��ӭ��ͼ���ѯ����" << endl;
						cout << "�˳�������0\n���鱾id��ѯ������1\n��������ѯ������2\n���鱾���Ͳ�ѯ������3\n���������ѯ������4\n�����߲�ѯ������5\n���鱾�۸��ѯ������6\n���鱾��ݲ�ѯ������7" << endl;
						cin >> stop2;
						if (stop2 == 0) break;
						if (stop2 == 1) {
							cout << "�����鱾id��" << endl;
							getchar();
							getline(cin, bookid);
							search_book_string(0, bookid,1);
						}
						if (stop2 == 2) {
							cout << "����������" << endl;
							getchar();
							getline(cin, book_name);
							search_book_string(1, book_name,1);
						}
						if (stop2 == 3) {
							cout << "�����鱾���ͣ�" << endl;
							getchar();
							getline(cin, category);
							search_book_string(2, category,1);
						}
						if (stop2 == 4) {
							cout << "��������磺" << endl;
							getchar();
							getline(cin, press);
							search_book_string(3, press,1);
						}
						if (stop2 == 5) {
							cout << "�������ߣ�" << endl;
							getchar();
							getline(cin, author);
							search_book_string(4, author,1);
						}
						if (stop2 == 6) {
							cout << "����۸����ޣ�" << endl;
							getchar();
							getline(cin, sprice1);
							cout << "����۸����ޣ�" << endl;
							getline(cin, sprice2);
							search_book_range(0, sprice1, sprice2);
						}
						if (stop2 == 7) {
							cout << "����������ޣ�" << endl;
							getchar();
							getline(cin, syear1);
							cout << "����������ޣ�" << endl;
							getline(cin, syear2);
							search_book_range(1, syear1, syear2);
						}
					}
				}
				if (stop1 == 2) {
					cout << "��ӭ�����顪��" << endl;
					cout << "�ѽ��鼮��" << endl;
					search_borrow_book(cardid);
					while (1) {
						cout << "�˳�������0\n�������飺����1" << endl;
						cin >> stop3;
						if (stop3 == 0) break;
						if (stop3 == 1) {
							cout << "�����鱾id��";
							getchar();
							getline(cin, bookid);
							cout << "�������ڣ�";
							cout << "���ڸ�ʽ��yyyy/mm/dd" << endl;
							getline(cin,borrowdate);
							insert_borrow_book(cardid, bookid, borrowdate);
						}
						else continue;
					}
				}
				if (stop1 == 3) {
					cout << "��ӭ�����顪��" << endl;
					while (1) {
						cout << "�˳�������0" << endl;
						cout << "���飺����1" << endl;
						cin >> stop2;
						if (stop2 == 0) break;
						if (stop2 == 1) {
							cout << "�����鱾id��" << endl;
							getchar();
							getline(cin, bookid);
							cout << "�������ڣ�" << endl;
							cout << "���ڸ�ʽ��yyyy/mm/dd" << endl;
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