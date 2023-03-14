#include<iostream>
#include <queue>
using namespace std;

struct ngay {
	short int day;
	short int month;
	short int year;
};
typedef struct ngay Ngay;

struct reader {
	char id_reader[6];
	char name_reader[31];
	Ngay birthday;
	char address[31];
	Ngay create_card_day;
};
typedef struct reader Reader;

struct node {
	Reader data;
	struct node* left, * right, *on;
	unsigned short int duyet = 0;
};
typedef struct node Node;

void Init(Node* root)
{
	root = NULL;
}

Node* GetNode(Reader read)
{
	Node* p = new Node;
	if (!p) return NULL;
	p->data = read;
	p->left = NULL;
	p->right = NULL;
	p->on = NULL;
	return p;
}

void Input_docgia_node(Node*& k)
{
	Reader Read;

	cout << "\nNhap id doc gia: ";
	rewind(stdin);
	fgets(Read.id_reader, 5, stdin);
	Read.id_reader[strlen(Read.id_reader) - 1] = '\0';

	cout << "\nNhap ten doc gia: ";
	rewind(stdin);
	fgets(Read.name_reader,30, stdin);
	Read.name_reader[strlen(Read.name_reader) - 1] = '\0';

	cout << "\nNhap ngay sinh: ";
	cin >> Read.birthday.day;
	cout << "\nNhap thang sinh: ";
	cin >> Read.birthday.month;
	cout << "\nNhap nam sinh: ";
	cin >> Read.birthday.year;

	cout << "\nNhap dia chi doc gia: ";
	rewind(stdin);
	fgets(Read.address, 30, stdin);
	Read.address[strlen(Read.address) - 1] = '\0';

	cout << "\nNhap ngay tao the: ";
	cin >> Read.create_card_day.day;
	cout << "\nNhap thang tao the: ";
	cin >> Read.create_card_day.month;
	cout << "\nNhap nam tao the: ";
	cin >> Read.create_card_day.year;

	k = GetNode(Read);
}

void InitTree(Node*& root)
{
	cout << "\nNhap data doc gia: \n";
	Input_docgia_node(root);
	queue<Node*>q;
	q.push(root);
	while (!q.empty())
	{
		Node* p = q.front();
		q.pop();

		short int number;
		do {
			cout << "\nNhap vao so luong con cua Node " << p->data.name_reader << " (0 hay 1 hay 2): ";
			cin >> number;

			if (number < 0 || number > 2)
				cout << "\nSo luong con chi co the la 0 hay 1 hay 2. Xin kiem tra va nhap lai!";
		} while (number < 0 || number > 2);

		if (number == 1)
		{
			bool LR;
			cout << "\nLa node trai hay node phai? (0: trai, 1: phai): ";
			cin >> LR;

			Node* k;
			if (LR)
			{
				Input_docgia_node(k);
				p->right = k;
				k->on = p;
			}
			else
			{
				Input_docgia_node(k);
				p->left = k;
				k->on = p;
			}
			q.push(k);
		}
		else if (number == 2)
		{
			Node* k;
			cout << "\nNhap data cho node trai: \n";
			Input_docgia_node(k);
			q.push(k);
			p->left = k;
			k->on = p;
			Node* m;
			cout << "\nNhap data cho node phai: \n";
			Input_docgia_node(m);
			q.push(m);
			p->right = m;
			m->on = p;
		}
	}
}

ostream& operator << (ostream& os, Reader& rd)
{
	os<<"ID: " << rd.id_reader << endl;
	os<<"Name: " << rd.name_reader << endl;
	os<<"BirthDay: " << rd.birthday.day << "/" << rd.birthday.month << "/" << rd.birthday.year << endl;
	os << "Address: " << rd.address << endl;
	os << "Day Create Card: " << rd.create_card_day.day << "/" << rd.create_card_day.month << "/" << rd.create_card_day.year << endl;
	return os;
}

void Output_docgia_node(Node* root)
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
					cout<<root->data<<endl;
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

void FreeTree(Node*& root)
{
	if (root != NULL)
	{
		FreeTree(root->left); // Xét tiếp qua nhánh con trái của Node hiện tại
		FreeTree(root->right); // Xét tiếp qua nhánh con phải của Node hiện tại
		delete root; // Giải phóng Node đang xét đến. Lưu ý: Phải giải phóng nó sau cùng (duyệt sau) chứ nếu dùng duyệt trước hay duyệt giữa thì sau khi giải phóng lấy gì mà tiếp tục trỏ? => LỖI
		root = NULL; // Sau khi giải phóng xong phải cập nhật cho Node đó giá trị NULL nếu không sẽ bị lỗi ngang nếu sau khi giải phóng xong người dùng có thao tác tiếp gì đó (vd: duyệt cây)
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
					// cout<<root->data<<" ";
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
	//Node* root;
	//InitTree(root);
	Reader rd1;
	strcpy_s(rd1.id_reader, "1");
	strcpy_s(rd1.name_reader, "Jennie");
	rd1.birthday.day = 12;
	rd1.birthday.month = 10;
	rd1.birthday.year = 1996;
	strcpy_s(rd1.address, "Korea");
	rd1.create_card_day.day = 12;
	rd1.create_card_day.month = 10;
	rd1.create_card_day.year = 2001;

	Reader rd2;
	strcpy_s(rd2.id_reader, "2");
	strcpy_s(rd2.name_reader, "Jisoo");
	rd2.birthday.day = 11;
	rd2.birthday.month = 5;
	rd2.birthday.year = 1995;
	strcpy_s(rd2.address, "Korea");
	rd2.create_card_day.day = 18;
	rd2.create_card_day.month = 2;
	rd2.create_card_day.year = 2002;

	Reader rd3;
	strcpy_s(rd3.id_reader, "3");
	strcpy_s(rd3.name_reader, "Lisa");
	rd3.birthday.day = 19;
	rd3.birthday.month = 4;
	rd3.birthday.year = 1997;
	strcpy_s(rd3.address, "Korea");
	rd3.create_card_day.day = 10;
	rd3.create_card_day.month = 3;
	rd3.create_card_day.year = 2003;

	Reader rd4;
	strcpy_s(rd4.id_reader, "4");
	strcpy_s(rd4.name_reader, "Rose");
	rd4.birthday.day = 22;
	rd4.birthday.month = 7;
	rd4.birthday.year = 1996;
	strcpy_s(rd4.address, "Korea");
	rd4.create_card_day.day = 1;
	rd4.create_card_day.month = 12;
	rd4.create_card_day.year = 2000;

	Reader rd5;
	strcpy_s(rd5.id_reader, "5");
	strcpy_s(rd5.name_reader, "Chi pu");
	rd5.birthday.day = 6;
	rd5.birthday.month = 4;
	rd5.birthday.year = 1995;
	strcpy_s(rd5.address, "Viet Nam");
	rd5.create_card_day.day = 11;
	rd5.create_card_day.month = 11;
	rd5.create_card_day.year = 2002;

	Node* root = GetNode(rd1);
	Node* root2 = GetNode(rd2);
	Node* root3 = GetNode(rd3);
	Node* root4 = GetNode(rd4);
	Node* root5 = GetNode(rd5);

	root->left = root2; root2->on = root;
	root->right = root3; root3->on = root;
	root2->left = root4; root4->on = root2;
	root3->right = root5; root5->on = root3;

	// =================== Bai tap xu ly cay ================= //


	Output_docgia_node(root);
	// ============== DELETE TREE ============= // 
	FreeTree(root);
	cout << "\n========= DELETE TREE =========";
	//FreeTree2(root);
	return 0;
}