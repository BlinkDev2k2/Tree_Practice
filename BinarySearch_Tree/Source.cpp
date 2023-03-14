#include<iostream>
using namespace std;

struct node {
	short int data;
	// char data;
	// char *data;
	struct node* left, *right, *on;
	unsigned short int duyet = 0;
	unsigned short int trung = 1;
};
typedef struct node Node;

Node* Getnode(short int Data)
{
	Node* n = new Node;
	if (!n) return NULL;
	n->data = Data;
	n->left = n->right = n->on = NULL;
	return n;
}

void AddNode(Node*& root, short int data, Node* p)
{
	if (root)
	{
		if (data > root->data)
		{
			p = root;
			AddNode(root->right, data, p);
		}
		else if (data < root->data)
		{
			p = root;
			AddNode(root->left, data, p);
		}
	}
	else
	{
		root = Getnode(data);
		root->on = p;
	}
}

void AddNode2(Node*& root, short int data, Node*Root)
{
	//if(root)
	//{
		Node* p = NULL;
		while (root)
		{
			p = root;
			if (root->data < data)
				root = root->right;
			else if (root->data > data)
				root = root->left;
			else
			{
				root = Root;
				return;
			}
		}
		if (p->data < data)
		{
			p->right = Getnode(data);
			Node* r = p->right;
			r->on = p;
		}
		else if (p->data > data)
		{
			p->left = Getnode(data);
			Node* l = p->left;
			l->on = p;
		}
		root = Root;
	//}
}

void CreateTree(Node*& root, short int* a, const unsigned short int &n)
{
	root = Getnode(a[0]);
	Node* Root = root;
	for (unsigned short int i = 1; i < n; ++i)
	{
		AddNode2(root, a[i], Root);
	}
}

Node* FindNode(Node* root, short int findData)
{
	if (!root) return NULL;
	else if (root->data == findData) return root;
	else
	{
		if (root->data < findData)
			return FindNode(root->right, findData);
		else if (root->data > findData)
			return FindNode(root->left, findData);
	}
}

void FindNode2(Node* root, short int findData)
{
	bool check = false;
	while (root)
	{
		if (root->data < findData)
			root = root->right;
		else if (root->data > findData)
			root = root->left;
		else
		{
			cout << "\nTim thay node " << findData;
			check = true;
			return;
		}
	}
	if (!check) cout << "\nKhong tim thay";
}

void swapData(short int& x, short int& y)
{
	short int t = x;
	x = y;
	y = t;
}

void Find_SwapNode(Node*& root, Node*& p)
{
	if (root->right)
	{
		Find_SwapNode(root->right, p);
	}
	else
	{
		Node* o = root->on; // luu lai node cha cua node the mang
		p->data = root->data; // gan gia tri cua node the mang sang node can xoa
		p = root; // cho node can xoa nhay sang node the mang de delete node the mang
		root = root->left; // tro sang trai giu lien kiet cua cac node con cua node the mang truoc khi xoa
		if(root)
			root->on = o;
	}
}

void DeleteNode(Node*& root, short int deleteData)
{
	if (!root) return;

	if (root->data < deleteData)
		DeleteNode(root->right, deleteData);
	else if (root->data > deleteData)
		DeleteNode(root->left, deleteData);
	else
	{
		Node* p = root; Node* o = root->on;
		if (!p->left)
		{
			root = p->right;
			if(root)
				root->on = o;
		}
		else if (!p->right)
		{
			root = p->left;
			if(root)
				root->on = o;
		}
		else
		{
			Find_SwapNode(root->left, p);
		}
		delete p;
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
	else if(q->data < o->data)
	{
		o->left = q->left;
		if (q->left) q->left->on = o;
	}

	p->data = q->data;
	p = q;
}

//void Find_SwapNode2(Node*& R, Node*& p)
//{
//	while (R->right)
//	{
//		R = R->right;
//	}
//	Node* o = R->on;
//
//	if (R->data > o->data)
//	{
//		o->right = R->left;
//		if (R->left) R->left->on = o;
//	}
//	else if (R->data < o->data)
//	{
//		o->left = R->left;
//		if (R->left) R->left->on = o;
//	}
//
//	p->data = R->data;
//	p = R;
//}

void DeleteNode2(Node*& root, short int deleteData)
{
	Node* R = root;
	while (R)
	{
		if (R->data < deleteData)
			R = R->right;
		else if (R->data > deleteData)
			R = R->left;
		else
		{
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
}

void InOrder(Node* root)
{
	if (root)
	{
		InOrder(root->left);
		cout << root->data<<" ";
		InOrder(root->right);
	}
}

void InOrder2(Node* root)
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

void FindMaxNode(Node* root, short int& max)
{
	if (!root) return;
	if (root->right)
	{
		FindMaxNode(root->right, max);
	}
	else
		max = root->data;
}

short int FindMaxNode2(Node* root)
{
	while (root->right)
		root = root->right;
	return root->data;
}

void Count_SoAm(Node* root, unsigned short int& dem)
{
	if (root)
	{
		if (root->data >= 0)
		{
			Count_SoAm(root->left, dem);
		}
		else
		{
			++dem;
			Count_SoAm(root->right, dem);
			Count_SoAm(root->left, dem);
		}
	}
}

void Count_SoAm_LNR(Node* root, unsigned short int& dem)
{
	if (!root) return;
	Count_SoAm_LNR(root->left, dem);
	if (root->data < 0) ++dem;
	else
		return;
	Count_SoAm_LNR(root->right, dem);
}

unsigned short int Count_SoAm2(Node* root)
{
	if (root)
	{
		unsigned short int dem = 0;
		const char s[] = "LNR";
		Node* R = root->on;
		root->on = NULL;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					if (root->data < 0) ++dem;
					else
					{
						root->duyet = 0;
						while (root->on)
						{
							root = root->on;
							root->duyet = 0;
						}
						return dem;
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
		return dem;
	}
}

bool Check_BinarySearchTree(Node* root)
{
	if (root)
	{
		const char s[] = "LNR";
		Node* R = root->on;
		root->on = NULL;
		int min = INT_MIN;
		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N')
				{
					short int value = root->data;
					if (value <= min)
					{
						root->duyet = 0;
						while (root->on)
						{
							root = root->on;
							root->duyet = 0;
						}
						return false;
					}
					else min = value;
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
		return true;
	}
}

void DeleteTree(Node*& root)
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
	short int a[] = { 1, 9, 6, 5, 0, -4, 3, 8, 12, -29, -33 };
	//short int a[] = { 1, 9, 6, 5, 2, 4, 3, 8, 12, 29, 33 };
	unsigned short int n = 11;

	CreateTree(root, a, n);
	////InOrder(root); cout << "\n";
	//InOrder2(root);
	////FindNode2(root, 1);
	///*Node* findnode = FindNode(root, 5);
	//if (!findnode) cout << "\nKhong tim thay";
	//else cout << "\nTim thay ";*/
	//DeleteNode(root, 1); cout << "\n";
	DeleteNode2(root, 6); cout << "\n";
	//InOrder(root);

	/*short int max;
	FindMaxNode(root, max);
	cout << "\nMax = " << max;*/
	//cout << "\nMax = " << FindMaxNode2(root);

	/*unsigned short int dem = 0;
	Count_SoAm(root, dem);
	cout << "\nCo " << dem << " so am trong cay";*/
	//cout << Count_SoAm2(root);

	//Check_BinarySearchTree ? cout << "\nLa cay nhi phan tim kiem" : cout << "\nKo la cay nhi phan tim kiem";



	DeleteTree(root);
	return 0;
}