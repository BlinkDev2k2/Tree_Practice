#include<iostream>
#include<conio.h>
#include<cmath>
using namespace std;

struct node {
	char data;
	struct node* on, *left, *right;
	unsigned short int duyet = 0;
};
typedef struct node Node;

Node* Getnode(char Data)
{
	Node* p = new Node;
	if (!p) return NULL;
	p->left = p->right = p->on = NULL;
	p->data = Data;
}

short int High_Tree(Node* root)
{
	if (!root) return 0;
	short int left = High_Tree(root->left);
	short int right = High_Tree(root->right);
	return left > right ? left + 1 : right + 1;
}

void QuayTrai(Node*& root)
{
	Node* o = root->on;
	Node* Pivot = root->right;
	root->right = Pivot->left;
	if (Pivot->left) Pivot->left->on = root;
	Pivot->left = root;
	root->on = Pivot;
	root = Pivot;
	root->on = o;
}

void QuayPhai(Node*& root)
{
	Node* o = root->on;
	Node* Pivot = root->left;
	root->left = Pivot->right;
	if (Pivot->right) Pivot->right->on = root;
	Pivot->right = root;
	root->on = Pivot;
	root = Pivot;
	root->on = o;
}

unsigned short int LevelOfNode(Node* X)
{
	unsigned short int dem = 0;
	while (true)
	{
		X = X->on;

		if (X == NULL)
			break;

		++dem;
	}
	return dem + 1;
}

unsigned short int HighOfTree2(Node* root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt
	unsigned short int DoSauMax = 1;
	if (root != NULL)
	{
		Node* o = root->on;
		root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (root->duyet <= 2)
			{
				if (s[root->duyet] == 'N' || s[root->duyet] == 'n')
				{
					unsigned short int DoSauNode = LevelOfNode(root);
					if (DoSauNode > DoSauMax)
						DoSauMax = DoSauNode;
					++root->duyet;
				}
				else if (s[root->duyet] == 'L' || s[root->duyet] == 'l')
				{
					++root->duyet;
					if (root->left) root = root->left;
				}
				else if (s[root->duyet] == 'R' || s[root->duyet] == 'r')
				{
					++root->duyet;
					if (root->right) root = root->right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				root->duyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa
				if (root->on == NULL)
				{
					root->on = o; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					root = root->on;
			}
		}
	}
	return DoSauMax; // CHIỀU CAO Cây
}

short int Balance_Tree(Node*& root)
{
	short int High_left = 0;
	short int High_right = 0;
	if (root->left) High_left = High_Tree(root->left);
	if (root->right) High_right = High_Tree(root->right);

	if (abs(High_left - High_right) > 1)
	{
		cout << "\nCay bi mat can bang tai node " << root->data;
		if (High_left > High_right)
		{
			short int left2 = 0, right2 = 0;

			if (root->left->left)
			{
				left2 = High_Tree(root->left->left);
			}
			if (root->left->right)
			{
				right2 = High_Tree(root->left->right);
			}

			if (left2 >= right2)
			{
				cout << "\nCay bi lech trai - trai tai node " << root->data << " -> tien hanh quay phai";
				QuayPhai(root);
			}
			else
			{
				cout << "\nCay bi lech trai - phai" << " ->tien hanh quay trai tai node " << root->left->data << " va quay phai tai node " << root->data;
				QuayTrai(root->left);
				QuayPhai(root);
			}
		}
		else
		{
			short int left2 = 0, right2 = 0;

			if (root->right->left)
			{
				left2 = High_Tree(root->right->left);
			}
			if (root->right->right)
			{
				right2 = High_Tree(root->right->right);
			}

			if (right2 >= left2)
			{
				cout << "\nCay bi lech phai - phai tai node " << root->data << " -> tien hanh quay trai";
				QuayTrai(root);
			}
			else
			{
				cout << "\nCay bi lech phai - trai" << " -> tien hanh quay phai tai node " << root->right->data << " va quay trai tai node " << root->data;
				QuayPhai(root->right);
				QuayTrai(root);
			}
		}
		return 1;
	}
	return 0;
}

short int Balance_Tree2(Node*& root, Node*&Root)
{
	short int High_left = 0;
	short int High_right = 0;
	if (root->left) High_left = HighOfTree2(root->left);
	if (root->right) High_right = HighOfTree2(root->right);

	if (abs(High_left - High_right) > 1)
	{
		cout << "\nCay bi mat can bang tai node " << root->data;
		Node* o = NULL;
		if (root->on)
			o = root->on;
		if (High_left > High_right)
		{
			short int left2 = 0, right2 = 0;

			if (root->left->left)
			{
				left2 = HighOfTree2(root->left->left);
			}
			if (root->left->right)
			{
				right2 = HighOfTree2(root->left->right);
			}

			if (left2 >= right2)
			{
				cout << "\nCay bi lech trai - trai tai node " << root->data << " -> tien hanh quay phai";
				QuayPhai(root);
				if (!root->on) Root = root;
			}
			else
			{
				cout << "\nCay bi lech trai - phai" << " ->tien hanh quay trai tai node " << root->left->data << " va quay phai tai node " << root->data;
				QuayTrai(root->left);
				QuayPhai(root);
				if (!root->on) Root = root;
			}
		}
		else
		{
			short int left2 = 0, right2 = 0;

			if (root->right->left)
			{
				left2 = HighOfTree2(root->right->left);
			}
			if (root->right->right)
			{
				right2 = HighOfTree2(root->right->right);
			}

			if (right2 >= left2)
			{
				cout << "\nCay bi lech phai - phai tai node " << root->data << " -> tien hanh quay trai";
				QuayTrai(root);
				if (!root->on) Root = root;
			}
			else
			{
				cout << "\nCay bi lech phai - trai" << " -> tien hanh quay phai tai node " << root->right->data << " va quay trai tai node " << root->data;
				QuayPhai(root->right);
				QuayTrai(root);
				if (!root->on) Root = root;
			}
		}
		if (o)
		{
			if (root->data < o->data)
				o->left = root;
			else if (root->data > o->data)
				o->right = root;
		}
		return 1;
	}
	return 0;
}

short int Insert_Node(Node*& root, char x, Node*prev)
{
	short int ketqua;
	if (root)
	{
		if (root->data > x)
			ketqua = Insert_Node(root->left, x, root);
		else if (root->data < x)
			ketqua = Insert_Node(root->right, x,root);
		else
			return 0;
	}
	else
	{
		root = Getnode(x);
		if (!root) return -1;
		root->on = prev;
		return 1;
	}

	if (ketqua == 1) // thêm node thành công tiến hành kiểm tra cây có bị lệch không 
	{
		short int High_left = 0;
		short int High_right = 0;
		if (root->left) High_left = High_Tree(root->left);
		if (root->right) High_right = High_Tree(root->right);

		if (abs(High_left - High_right) > 1)
		{
			//cout << "\nCay bi mat can bang tai node " << root->data;
			if (High_left > High_right)
			{
				short int left2 = 0, right2 = 0;

				if (root->left->left)
				{
					left2 = High_Tree(root->left->left);
				}
				if (root->left->right)
				{
					right2 = High_Tree(root->left->right);
				}

				if (left2 >= right2)
				{
					//cout << "\nCay bi lech trai - trai tai node " << root->data<<" -> tien hanh quay phai";
					QuayPhai(root);
				}
				else
				{
					//cout << "\nCay bi lech trai - phai" << " ->tien hanh quay trai tai node "<<root->left->data<<" va quay phai tai node "<<root->data;
					QuayTrai(root->left);
					QuayPhai(root);
				}
			}
			else
			{
				short int left2 = 0, right2 = 0;

				if (root->right->left)
				{
					left2 = High_Tree(root->right->left);
				}
				if (root->right->right)
				{
					right2 = High_Tree(root->right->right);
				}

				if (right2 >= left2)
				{
					//cout << "\nCay bi lech phai - phai tai node " << root->data << " -> tien hanh quay trai";
					QuayTrai(root);
				}
				else
				{
					//cout << "\nCay bi lech phai - trai" << " -> tien hanh quay phai tai node " << root->right->data << " va quay trai tai node " << root->data;
					QuayPhai(root->right);
					QuayTrai(root);
				}
			}
			return 2;
		}
		return 1;
		/*ketqua = Balance_Tree(root);
		if (ketqua == 1)
			return 2;
		else
			return 1;*/
	}
}

short int Insert_Node2(Node*& root, char x)
{
	if (!root)
	{
		root = Getnode(x);
	}
	else
	{
		Node* p = root;
		Node* q = p;
		while (p)
		{
			q = p;
			if (p->data < x)
				p = p->right;
			else if (p->data > x)
				p = p->left;
			else
			{
				cout << "\nTrung data";
				return 0;
			}
		}
		Node* k = Getnode(x);
		if (q->data < x)
		{
			q->right = k;
			if (!q->right) return -1;
			k->on = q;
		}
		else if (q->data > x)
		{
			q->left = k;
			if (!q->left) return -1;
			k->on = q;
		}

		while (k->on != NULL)
		{
			k = k->on;
			short int High_left = 0;
			short int High_right = 0;
			if (k->left) High_left = HighOfTree2(k->left);
			if (k->right) High_right = HighOfTree2(k->right);

			if (abs(High_left - High_right) > 1)
			{
				cout << "\nCay bi mat can bang tai node " << k->data;
				Node* o = NULL;
				if (k->on)
					o = k->on;
				if (High_left > High_right)
				{
					short int left2 = 0, right2 = 0;

					if (k->left->left)
					{
						left2 = HighOfTree2(k->left->left);
					}
					if (k->left->right)
					{
						right2 = HighOfTree2(k->left->right);
					}

					if (left2 >= right2)
					{
						cout << "\nCay bi lech trai - trai tai node " << k->data << " -> tien hanh quay phai";
						QuayPhai(k);
						if (!k->on) root = k;
					}
					else
					{
						cout << "\nCay bi lech trai - phai" << " ->tien hanh quay trai tai node " << k->left->data << " va quay phai tai node " << k->data;
						QuayTrai(k->left);
						QuayPhai(k);
						if (!k->on) root = k;
					}
				}
				else
				{
					short int left2 = 0, right2 = 0;

					if (k->right->left)
					{
						left2 = HighOfTree2(k->right->left);
					}
					if (k->right->right)
					{
						right2 = HighOfTree2(k->right->right);
					}

					if (right2 >= left2)
					{
						cout << "\nCay bi lech phai - phai tai node " << k->data << " -> tien hanh quay trai";
						QuayTrai(k);
						if (!k->on) root = k;
					}
					else
					{
						cout << "\nCay bi lech phai - trai" << " -> tien hanh quay phai tai node " << k->right->data << " va quay trai tai node " << k->data;
						QuayPhai(k->right);
						QuayTrai(k);
						if (!k->on) root = k;
					}
				}
				if (o)
				{
					if (k->data < o->data)
						o->left = k;
					else if (k->data > o->data)
						o->right = k;
				}
				break;
			}
		}
	}
	return 1;
}

//short int Find_SwapNode(Node*& root, Node*& p)
//{
//  short int kq;
//	if (root->right)
//	{
//		kq = Find_SwapNode(root->right, p);
//	}
//	else
//	{
//		Node* o = root->on; // luu lai node cha cua node the mang
//		p->data = root->data; // gan gia tri cua node the mang sang node can xoa
//		p = root; // cho node can xoa nhay sang node the mang de delete node the mang
//		root = root->left; // tro sang trai giu lien kiet cua cac node con cua node the mang truoc khi xoa
//		if (root)
//			root->on = o;
//		return 1;
//	}
//	
//  if (kq == 1)
//	{
//	Balance_Tree(root);
//	return 1;
//	}
//}

short int Find_SwapNode(Node*& root, Node*& p)
{
	short int kq;
	if (root->left)
	{
		kq = Find_SwapNode(root->left, p);
	}
	else
	{
		Node* o = root->on; // luu lai node cha cua node the mang
		p->data = root->data; // gan gia tri cua node the mang sang node can xoa
		p = root; // cho node can xoa nhay sang node the mang de delete node the mang
		root = root->right; // tro sang trai giu lien kiet cua cac node con cua node the mang truoc khi xoa
		if (root)
			root->on = o;

		return 1;
	}

	if (kq == 1)
	{
		Balance_Tree(root);
		return 1;
	}
}

short int DeleteNode(Node*& root, char deleteData)
{
	if (!root) return 0;
	short int kq;
	if (root->data < deleteData)
		kq = DeleteNode(root->right, deleteData);
	else if (root->data > deleteData)
		kq = DeleteNode(root->left, deleteData);
	else
	{
		Node* p = root; Node* o = root->on;
		if (!p->left)
		{
			root = p->right;
			if (root)
				root->on = o;
		}
		else if (!p->right)
		{
			root = p->left;
			if (root)
				root->on = o;
		}
		else
		{
			//Find_SwapNode(root->left, p);
			Find_SwapNode(root->right, p);
			Balance_Tree(root);
		}
		delete p;
		return 1;
	}

	if (kq == 1)
	{
		Balance_Tree(root);
		return 1;
	}
}

//void Find_SwapNode2(Node*& R, Node*& p)
//{
//	Node* q = R;
//	while (q->right)
//	{
//		q = q->right;
//	}
//	Node* o = q->on;
//
//	if (q->data > o->data)
//	{
//		o->right = q->left;
//		if (q->left) q->left->on = o;
//	}
//	else if (q->data < o->data)
//	{
//		o->left = q->left;
//		if (q->left) q->left->on = o;
//	}
//
//	p->data = q->data;
//	p = q;
//}

void Find_SwapNode2(Node*& R, Node*& p)
{
	Node* q = R;
	while (q->left)
	{
		q = q->left;
	}
	Node* o = q->on;

	if (q->data > o->data)
	{
		o->right = q->right;
		if (q->right) q->right->on = o;
	}
	else if (q->data < o->data)
	{
		o->left = q->right;
		if (q->right) q->right->on = o;
	}

	p->data = q->data;
	p = q;
}

short int DeleteNode2(Node*& root, char deleteData)
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
				if (!o)
				{
					root = root->right;
					if (root)
						root->on = NULL;
				}
				else
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
			}
			else if (!p->right)
			{
				if (!o)
				{
					root = root->left;
					if (root)
						root->on = NULL;
				}
				else
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
			}
			else
			{
				/*Find_SwapNode2(R->left, p);*/
				Find_SwapNode2(R->right, p);
			}

			Node* ON = NULL;
			if (p->on) ON = p->on;
			delete p;

			while (ON)
			{
				Balance_Tree2(ON, root);
				ON = ON->on;
			}
			return 1;
		}
	}
	return 0;
}

void LNR(Node* root)
{
	if (root)
	{
		LNR(root->left);
		cout << root->data << " ";
		LNR(root->right);
	}
}

void NLR(Node* root)
{
	if (root)
	{
		cout << root->data << " ";
		NLR(root->left);
		NLR(root->right);
	}
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
	Node* root = NULL;
	char s[] = "ABCDEFWZUTKNGHML";
	//char s[] = "FDNBEKUAHMTWGLZ";
	//char s[] = "ABCD";
	short int len = sizeof(s) - 1;
	for (unsigned short int i = 0; i < len; ++i)
	{
		Insert_Node2(root, s[i]);
	}
	cout << "\n";
	NLR(root);
	system("pause");

	//while (1)
	//{
	//re:
	//	cout << "\nNhap vao data can them vao cay: ";
	//	char x;
	//	cin >> x;
	//	if (x<'A' || x>'Z')
	//		goto re;

	//	short int Add = Insert_Node2(root, x);
	//	//cout << "\nChieu cao cay: " << High_Tree(root);
	//	if (Add == -1)
	//		cout << "\nThem khong thanh cong do khong du bo nho";
	//	else if (Add == 0)
	//		cout << "\nThem khong thanh cong do bi trung data";
	//	else
	//	{
	//		cout << "\nThem thanh cong";
	//		cout << "\nNLR: ";
	//		NLR(root);
	//	}

	//	cout << "\nNhap them data nhan phim x\n";
	//	char c = _getch();
	//	if (c != 'x') break;
	//}

	while (1)
	{
	re:
		cout << "\nNhap vao data can xoa: ";
		char x;
		cin >> x;
		if (x < 'A' || x>'Z')
			goto re;

		short int Add = DeleteNode2(root, x);
		//cout << "\nChieu cao cay: " << High_Tree(root);
		if (Add == 0)
			cout << "\nXoa khong thanh cong";
		else
		{
			cout << "\nXoa thanh cong";
			cout << "\nNLR: ";
			NLR(root);
		}

		cout << "\nXoa them data nhan phim x\n";
		char c = _getch();
		if (c != 'x') break;
	}

	Remove_Tree(root);
	return 0;
}