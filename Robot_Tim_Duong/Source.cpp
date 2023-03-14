#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#define N 20
#define M 20
using namespace std;

struct robot {
	short int row, col;
	char huong;
};
typedef struct robot Robot;

struct huongdi {
	short int row, col;
};
typedef struct huongdi Huong;

struct node {
	struct node* on, * left, * right;
	Robot Data;
};
typedef struct node Node;

Node* Getnode(Robot data)
{
	Node* p = new Node;
	if (!p) return NULL;

	p->left = p->right = p->on = NULL;
	p->Data = data;

	return p;
}

bool check_robot(const Robot& x, const short int& n, const short int& m, const vector<vector<short int>>& v, const bool check_location[4][N][M])
{
	short int huong;
	if (x.huong == 'A') huong = 0;
	else if (x.huong == 'S') huong = 1;
	else if (x.huong == 'W') huong = 2;
	else huong = 3;

	if (x.row < 0 || x.row >n - 1 || x.col <0 || x.col >m - 1 || v[x.row][x.col] == 1 || check_location[huong][x.row][x.col] == true)
		return false;
	
	return true;
}

void Remove_Tree(Node*& root)
{
	if (root)
	{
		Remove_Tree(root->left);
		Remove_Tree(root->right);
		delete root;
		root = NULL;
	}
}

int main()
{
	// doc thong tin map va dich tu file
	ifstream ifile;
	ifile.open("map1.txt", ios_base::in);
	if (!ifile) return -1;

	short int n, m; // so hang so cot
	ifile >> n >> m;

	vector<vector<short int>> v;
	v.resize(n);
	unsigned short int len = v.size();

	for (unsigned short int i = 0; i < len; ++i)
		v[i].resize(m);

	for (unsigned short int i = 0; i < n; ++i)
		for (unsigned short int j = 0; j < m; ++j)
			ifile >> v[i][j];

	short int n_dich, m_dich; // toa do cot dich va dong dich
	ifile >> n_dich >> m_dich;

	ifile.close();

	Node* root = NULL; // khoi tao cay

	Robot r;
	r.col = r.row = 0;
	r.huong = 'S';
	root = Getnode(r); // tao node goc
	
	queue<Node*>q;
	q.push(root); // dua node goc vao hang doi

	// tao mang 3 chieu kiem tra vitri robot da di qua hay chua 
	bool check_location[4][N][M] = {false};
	vector<Huong>h;
	check_location[1][0][0] = true;
	while (!q.empty())
	{
		Node* p = q.front(); // lay node dau ra de xet
		q.pop(); // bo node dau ra khoi hang doi

		Robot turn_left; // xet huong di ben trai
		Robot go_ahead; // xet huong di phia truoc
		if (p->Data.huong == 'A')
		{
			turn_left.huong = 'S';
			turn_left.col = p->Data.col;
			turn_left.row = p->Data.row + 1;

			go_ahead.huong = 'A';
			go_ahead.col = p->Data.col - 1;
			go_ahead.row = p->Data.row;
		}
		else if (p->Data.huong == 'S')
		{
			turn_left.huong = 'D';
			turn_left.col = p->Data.col + 1;
			turn_left.row = p->Data.row;

			go_ahead.huong = 'S';
			go_ahead.col = p->Data.col;
			go_ahead.row = p->Data.row + 1;
		}
		else if (p->Data.huong == 'W')
		{
			turn_left.huong = 'A';
			turn_left.col = p->Data.col - 1;
			turn_left.row = p->Data.row;

			go_ahead.huong = 'W';
			go_ahead.col = p->Data.col;
			go_ahead.row = p->Data.row - 1;
		}
		else if (p->Data.huong == 'D')
		{
			turn_left.huong = 'W';
			turn_left.col = p->Data.col;
			turn_left.row = p->Data.row - 1;

			go_ahead.huong = 'D';
			go_ahead.col = p->Data.col + 1;
			go_ahead.row = p->Data.row;
		}

		// xet dieu kien de dua node vao hang doi vao tao nhanh trai phai cho node goc
		if (check_robot(turn_left, n, m, v, check_location) == true)
		{
			p->left = Getnode(turn_left);
			p->left->on = p;
			q.push(p->left);
			
			if (p->left->Data.col == m_dich - 1 && p->left->Data.row == n_dich - 1)
			{
				Node* o = p->left;
				while (o)
				{
					Huong a;
					a.col = o->Data.col + 1;
					a.row = o->Data.row + 1;

					h.push_back(a);
					o = o->on;
				}
				break;
			}

			short int huong;
			if (p->left->Data.huong == 'A') huong = 0;
			else if (p->left->Data.huong == 'S') huong = 1;
			else if (p->left->Data.huong == 'W') huong = 2;
			else huong = 3;

			check_location[huong][p->left->Data.row][p->left->Data.col] = true;
		}
		if (check_robot(go_ahead, n, m, v, check_location) == true)
		{
			p->right = Getnode(go_ahead);
			p->right->on = p;
			q.push(p->right);

			if (p->right->Data.col == m_dich - 1 && p->right->Data.row == n_dich - 1)
			{
				Node* o = p->right;
				while (o)
				{
					Huong a;
					a.col = o->Data.col + 1;
					a.row = o->Data.row + 1;

					h.push_back(a);
					o = o->on;
				}
				break;
			}

			short int huong;
			if (p->right->Data.huong == 'A') huong = 0;
			else if (p->right->Data.huong == 'S') huong = 1;
			else if (p->right->Data.huong == 'W') huong = 2;
			else huong = 3;

			check_location[huong][p->right->Data.row][p->right->Data.col] = true;
		}
	}

	short int length = h.size();
	if (length == 0)
		cout << "0";
	else
	{
		cout << length << endl;
		reverse(h.begin(), h.end());
		for (auto x : h)
			cout << x.row << " " << x.col << endl;
	}

	Remove_Tree(root); // giai phong cay
	return 0;
}