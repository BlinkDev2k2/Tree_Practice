#pragma warning (disable: 4996)
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<cmath>
#include<Windows.h>
#include<conio.h>
using namespace std;

//============= đặt màu cho chữ =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

struct node {
	string data;
	struct node* left, * right, * on;
	unsigned short int duyet = 0;
	//long double value = 0;
	float value = 0;
	bool color = false;
};
typedef struct node Node;

Node* GetNode(string Data)
{
	Node* p = new Node;
	if (!p) return NULL;
	p->data = Data;
	p->left = NULL;
	p->right = NULL;
	p->on = NULL;
	return p;
}

bool Kiemtramongoac(string &x)
{
	return x == "(";
}
bool Kiemtradongngoac(string& x)
{
	return x == ")";
}
bool Kiemtraso(string& x)
{
	return x[x.length() - 1] >= '0' && x[x.length() - 1] <= '9';
}
bool Kiemtratoantu(string& x)
{
	return x == "+" || x == "-" || x == "*" || x == "/" || x == "^" || x == "abs" || x == "sin" || x == "cos" || x == "tan" || x == "cot" || x ==  "log" || x == "sqrt" || x == "sqrtn" || x == "logn";
}
short int Uutienpheptoan(string& x)
{
	if (x == "abs" || x == "sin" || x == "cos" || x == "tan" || x == "cot" || x == "log" || x == "sqrt" || x == "!" || x == "sqrtn" || x == "logn") return 4;
	if (x == "^") return 3;
	if (x == "*" || x == "/") return 2;
	if (x == "+" || x == "-") return 1;
	return 0;
}

unsigned long long int TinhGiaiThua(float& x)
{
	if (x == 0) return 1;
	unsigned long long int GiaiThua = 1;
	for (unsigned short int i = 1; i <= x; ++i)
		GiaiThua *= i;
	return GiaiThua;
}

// xu ly chuoi co dinh dang khong chuan
vector<string> DinhDangLaiChuoiDauVao(string& s)
{
	vector<string>s2;
	unsigned short int length_s = s.length();
	unsigned short int idx = 0;

	for (unsigned short int i = 0; i < length_s; ++i)
	{
		if (s[i] != ' ')
		{
			string t;
			t.push_back(s[i]);
			s2.push_back(t);
			idx = i;
			break;
		}
	}

	for (unsigned short int i = idx + 1; i < length_s; ++i)
	{
		if (s[i] != ' ')
		{
			if (s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '-' || s[i] == '^' || s[i] == '!' || s[i] == ',')
			{
				string t;
				t.push_back(s[i]);
				s2.push_back(t);
			}
			else if (s[i] >= '0' && s[i] <= '9')
			{
				string phantucuoi = s2[s2.size() - 1];
				char kytucuoi = phantucuoi[phantucuoi.length() - 1];

				if ((kytucuoi >= '0' && kytucuoi <= '9') || kytucuoi == '.')
				{
					s2[s2.size() - 1].push_back(s[i]);
				}
				else if (kytucuoi == '-')
				{
					if (s2.size() <= 1)
					{
						s2[s2.size() - 1].push_back(s[i]);
					}
					else
					{
						string phantuapcuoi = s2[s2.size() - 2];
						if (Kiemtramongoac(phantuapcuoi) || Kiemtratoantu(phantuapcuoi) || phantuapcuoi == ",")
						{
							s2[s2.size() - 1].push_back(s[i]);
						}
						else if (Kiemtradongngoac(phantuapcuoi) || Kiemtraso(phantuapcuoi) || phantuapcuoi == "!")
						{
							string t;
							t.push_back(s[i]);
							s2.push_back(t);
						}
					}
				}
				else
				{
					string t;
					t.push_back(s[i]);
					s2.push_back(t);
				}
			}
			else if (s[i] == '.')
			{
				s2[s2.size() - 1].push_back(s[i]);
			}
			else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			{
				string phantucuoi = s2[s2.size() - 1];
				char kytucuoi = phantucuoi[phantucuoi.length() - 1];

				if ((kytucuoi >= 'a' && kytucuoi <= 'z') || (kytucuoi >= 'A' && kytucuoi <= 'Z'))
				{
					s2[s2.size() - 1].push_back(s[i]);
				}
				else
				{
					string t;
					t.push_back(s[i]);
					s2.push_back(t);
				}
			}
		}
	}
	return s2;
}

// chuyen bieu thuc tu trung to sang hau to de chuan bi tao cay nhi phan
void XuLyChuoiDauVao(string& s, vector<string> &v, vector<string> &kq)
{
	// xu ly chuoi dau vao chuan khoang trang
	//char* s1 = strtok((char*)s.c_str(), " ");

	//while (s1)
	//{
	//	//cout << s1 << endl;
	//	v.push_back(s1);
	//	s1 = strtok(NULL, " ");
	//}

	// tien hanh xu ly chuoi de cho ra chuoi kq la bieu thuc hau to
	stack<string> st;
	unsigned short int length = v.size();
	for (unsigned short int i = 0; i < length; ++i)
	{
		if (v[i] == ",") continue;
		if (Kiemtratoantu(v[i]) || v[i] == "!")
		{
			bool check = false;
			while (!st.empty())
			{
				string top = st.top();
				if (Uutienpheptoan(v[i]) > Uutienpheptoan(top))
				{
					check = true;
					st.push(v[i]);
					break;
				}
				else
				{
					st.pop();
					kq.push_back(top);
				}
			}
			if (!check) st.push(v[i]);
		}
		else if (v[i] == "(")
		{
			st.push(v[i]);
		}
		else if (v[i] == ")")
		{
			while (!st.empty())
			{
				string ss = st.top();
				if (ss == "(")
				{
					st.pop();
					break;
				}
				else
				{
					kq.push_back(ss);
					st.pop();
				}
			}
		}
		else
		{
			kq.push_back(v[i]);
		}
	}

	while (!st.empty())
	{
		if (st.top() != "(")
			kq.push_back(st.top());
		st.pop();
	}
}

void Taocaynhiphan(Node*&root, vector<string>&kq)
{
	stack<Node*>st;
	unsigned short int lenght = kq.size();
	for (unsigned short int i = 0; i < lenght; ++i)
	{
		Node* p = GetNode(kq[i]);
		if (Kiemtratoantu(kq[i]) == true || kq[i] == "!") {

			if (kq[i] == "abs" || kq[i] == "sin" || kq[i] == "cos" || kq[i] == "tan" || kq[i] == "cot" || kq[i] == "log" || kq[i] == "sqrt")
			{
				Node* y = st.top();
				st.pop();
				p->right = y; y->on = p;
			}
			else if (kq[i] == "!")
			{
				Node* x = st.top();
				st.pop();
				p->left = x; x->on = p;
			}
			else
			{
				Node* y = st.top();
				st.pop();
				Node* x = st.top();
				st.pop();

				p->left = x; x->on = p;
				p->right = y; y->on = p;
			}
		}
		st.push(p);
	}
	root = st.top();
}

void PostOrder(Node* root)
{
	if (root)
	{
		const char s[] = "LRN";
		Node* R = root->on;
		root->on = NULL;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					cout << root->data << " ";
					++root->duyet;
				}
				else if (s[root->duyet] == 'L')
				{
					++root->duyet;
					if (root->left) root = root->left;
				}
				else if (s[root->duyet] == 'R')
				{
					++root->duyet;
					if (root->right) root = root->right;
				}
			}
			else
			{
				root->duyet = 0;
				if (!root->on)
				{
					root->on = R;
					break;
				}
				else
				{
					root = root->on;
				}
			}
		}
	}
}

void Cacbuoctinhtoan(Node* Root)
{
	if (Root)
	{
		if (Root->left || Root->data == "abs" || Root->data == "sqrt" || Root->data == "log" || Root->data == "sin" || Root->data == "cos" || Root->data == "tan" || Root->data == "cot") cout << "(";
		Cacbuoctinhtoan(Root->left);
		if (Root->color) SetColor(13);
		cout<< Root->data;
		SetColor(7);
		Cacbuoctinhtoan(Root->right);
		if (Root->right) cout << ")";
	}
}

void InOrder(Node* root)
{
	if (root)
	{
		const char s[] = "LNR";
		Node* R = root->on;
		root->on = NULL;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					cout << root->data << " ";
					++root->duyet;
				}
				else if (s[root->duyet] == 'L')
				{
					++root->duyet;
					if (root->left) root = root->left;
				}
				else if (s[root->duyet] == 'R')
				{
					++root->duyet;
					if (root->right) root = root->right;
				}
			}
			else
			{
				root->duyet = 0;
				if (!root->on)
				{
					root->on = R;
					break;
				}
				else
				{
					root = root->on;
				}
			}
		}
	}
}

// xu ly cac phep tinh
void Tinhtoan(Node* root)
{
	if (root)
	{
		unsigned short int dem = 1;
		Node* Root = root;
		const char s[] = "LRN";
		Node* R = root->on;
		root->on = NULL;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					if (Kiemtraso(root->data))
					{
						root->value = stof(root->data);
					}
					else if (Kiemtratoantu(root->data) || root->data == "!")
					{
						float x = 0;
						float y = 0;
						if(root->left)
							x = root->left->value;
						if(root->right)
							y = root->right->value;
						if (root->data == "+")
							root->value = x + y;
						else if (root->data == "-")
							root->value = x - y;
						else if (root->data == "*")
							root->value = x * y;
						else if (root->data == "/")
							root->value = x / y;
						else if (root->data == "^")
							root->value = pow(x, y);
						else if (root->data == "abs")
							root->value = abs(y);
						else if (root->data == "sin")
							root->value = sin(y);
						else if (root->data == "cos")
							root->value = cos(y);
						else if (root->data == "tan")
							root->value = tan(y);
						else if (root->data == "cot")
							root->value = 1 / tan(y);
						else if (root->data == "sqrt")
							root->value = sqrt(y);
						else if (root->data == "log")
							root->value = log10(y);
						else if (root->data == "!")
							root->value = TinhGiaiThua(x);
						else if (root->data == "sqrtn")
							root->value = pow(y, 1.0 / x);
						else if (root->data == "logn")
							root->value = log(y) / log(x);

						// in tung buoc thuc hien phep toan 
						//_getch();
						root->color = true;
						if (root->left) root->left->color = true;
						if (root->right) root->right->color = true;

						cout<<"Buoc "<<dem<<":" << "\nXu ly phep toan duoc to mau: ";
						Cacbuoctinhtoan(Root);
						
						cout << "\nKet qua sau khi xu ly: ";
						root->data = to_string(root->value);
						root->left = root->right = NULL;
						Cacbuoctinhtoan(Root);
						cout << "\n\n";

						// tra lai co hieu mau
						root->color = false;
						++dem;
						// -------------------------------- //
					}
					++root->duyet;
				}
				else if (s[root->duyet] == 'L')
				{
					++root->duyet;
					if (root->left) root = root->left;
				}
				else if (s[root->duyet] == 'R')
				{
					++root->duyet;
					if (root->right) root = root->right;
				}
			}
			else
			{
				root->duyet = 0;
				if (!root->on)
				{
					root->on = R;
					break;
				}
				else
				{
					root = root->on;
				}
			}
		}
	}
}

void FreeTree2(Node*& root)
{
	if (root)
	{
		const char s[] = "NLR";
		Node* R = root->on;
		root->on = NULL;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					++root->duyet;
				}
				else if (s[root->duyet] == 'L')
				{
					++root->duyet;
					if (root->left) root = root->left;
				}
				else if (s[root->duyet] == 'R')
				{
					++root->duyet;
					if (root->right) root = root->right;
				}
			}
			else
			{
				root->duyet = 0;
				if (!root->on)
				{
					root->on = R;
					delete root;
					root = NULL;
					break;
				}
				else
				{
					Node* d = root;
					root = root->on;
					delete d;
					d = NULL;
				}
			}
		}
	}
}

int main()
{
	string s = "6^2 + 2";
	//cout << "\nNhap bieu thuc toan hoc vd: ( 1 + 4 * 7 ) - 6 / 2 ";
	//getline(cin, s);
	
	// xu ly voi bat ky chuoi bieu thuc toan hoc 
	vector<string> v = DinhDangLaiChuoiDauVao(s);
	vector<string> kq; // vector chua bieu thuc hau to
	XuLyChuoiDauVao(s, v, kq); // xu ly cho ra vector hau to

	cout << "\nBieu thuc can tinh: ";
	unsigned short int len = v.size();
	for (unsigned short int i = 0; i < len; ++i)
		cout << v[i] << " ";
	cout << "\n\n";

	/*for (unsigned short int i = 0; i < kq.size(); ++i)
		cout << kq[i] << " ";
	cout << "\n";*/

	// dung cay nhi phan bieu thuc toan hoc
	Node* root = NULL;
	Taocaynhiphan(root, kq);
	//PostOrder(root); cout << "\n";
	//InOrder(root);

	// thuc hien cac phep toan
	Tinhtoan(root);
	cout << "Ket qua cuoi cung la: " << root->value<<endl;
	
	FreeTree2(root);
	return 0;
}