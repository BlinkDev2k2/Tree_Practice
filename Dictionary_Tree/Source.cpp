#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
using namespace std;

struct word {
	string eng, vie;
};
typedef struct word Word;

struct node {
	Word data;
	struct node* left, * right, * on;
	unsigned short int duyet = 0;
};
typedef struct node Node;

Node* Getnode(Word W)
{
	Node* n = new Node;
	if (!n) return NULL;
	n->data = W;
	n->left = n->right = n->on = NULL;
	return n;
}

void Chuanhoachuoi(string& x)
{
	unsigned short int len = x.length();
	for (unsigned short int i = 0; i < len; ++i)
	{
		if (x[i] >= 'A' && x[i] <= 'Z')
			x[i] += 32;
	}
}

bool operator > (Word& a, Word& b)
{
	return a.eng > b.eng;
}
bool operator < (Word& a, Word& b)
{
	return a.eng < b.eng;
}
bool operator == (Word& a, Word& b)
{
	return a.eng == b.eng;
}
bool operator != (Word& a, Word& b)
{
	return a.eng != b.eng;
}

void InputWord(Word& x)
{
	cout << "\nNhap tu tieng anh: ";
	getline(cin, x.eng);
	cout << "\nNhap nghia tieng viet: ";
	getline(cin, x.vie);

	Chuanhoachuoi(x.eng);
	Chuanhoachuoi(x.vie);
}

void InputDeleteWord(Word& d)
{
	cout << "\nNhap tu tieng anh can xoa: ";
	rewind(stdin);
	getline(cin, d.eng);

	Chuanhoachuoi(d.eng);
}

void AddNode2(Node*& root, Word& W, Node* Root)
{
	if(root)
	{
		Node* p = NULL;
		while (root)
		{
			p = root;
			if (root->data < W)
				root = root->right;
			else if (root->data > W)
				root = root->left;
			else
			{
				root = Root;
				cout << "\nTu da ton tai, vui long nhap tu khac";
				return;
			}
		}
		if (p->data < W)
		{
			p->right = Getnode(W);
			Node* r = p->right;
			r->on = p;
		}
		else if (p->data > W)
		{
			p->left = Getnode(W);
			Node* l = p->left;
			l->on = p;
		}
		root = Root;
	}
	else
	{
		root = Getnode(W);
	}
}

void Create_Dic(Node*& root)
{
	while (1)
	{
		Word w;
		InputWord(w);
		AddNode2(root, w, root);
		cout << "\nDe tiep tuc nhap vui long bam phim 'a'";
		char a = _getch();
		if (a != 'a') break;
		cout << "\n";
		rewind(stdin);
	}
	system("cls");
}

void DuyetTuDien(Node* root)
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
					cout << "\n- " << root->data.eng << ": " << root->data.vie;
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

void Find_SwapNode2(Node*& R, Node*& p)
{
	Node* q = R;
	while (q->right)
	{
		q = q->right;
	}
	Node* o = q->on;

	if (q->data > o->data)
	{
		o->right = q->left;
		if (q->left) q->left->on = o;
	}
	else if (q->data < o->data)
	{
		o->left = q->left;
		if (q->left) q->left->on = o;
	}
	p->data = q->data;
	p = q;
}

void DeleteNode2(Node*& root)
{
	Word deleteData;
	InputDeleteWord(deleteData);
	Node* R = root;
	bool check = false;
	while (R)
	{
		if (R->data < deleteData)
			R = R->right;
		else if (R->data > deleteData)
			R = R->left;
		else
		{
			check = true;
			Node* p = R; Node* o = R->on;
			if (!p->left)
			{
				if (p->data < o->data)
				{
					o->left = R->right;
					if (o->left)
						R->right->on = o;
				}
				else
				{
					o->right = R->right;
					if (o->right)
						R->right->on = o;
				}

			}
			else if (!p->right)
			{
				if (p->data < o->data)
				{
					o->left = R->left;
					if (o->left)
						R->left->on = o;
				}
				else
				{
					o->right = R->left;
					if (o->right)
						R->left->on = o;
				}
			}
			else
			{
				Find_SwapNode2(R->left, p);
			}
			delete p;
			return;
		}
	}
	if (!check) cout << "\nKhong tim thay tu can tim trong tu dien\n";
	else cout << "\nXoa thanh cong\n";
}

void Update_Vie(Node* root)
{
	cout << "\nNhap tu tieng anh can cap nhat lai nghia: ";
	string up;
	rewind(stdin);
	getline(cin, up);

	if (root)
	{
		bool check = false;
		while (root)
		{
			if (root->data.eng < up)
				root = root->right;
			else if (root->data.eng > up)
				root = root->left;
			else
			{
				cout << "\nTim thay node " << up;
				check = true;
				cout << "\nNhap nghia tieng viet: ";
				string s;
				getline(cin, s);
				root->data.vie = s;
				cout << "\nCap nhat thanh cong";
				return;
			}
		}
		if (!check) cout << "\nKhong tim thay";
	}
}

void removeDic(Node*& root)
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
	Node* root = NULL;
	Create_Dic(root);
	DuyetTuDien(root);
	
	//DeleteNode2(root);
	//Update_Vie(root);
	//DuyetTuDien(root);
	

	removeDic(root);
	return 0;
}