#include<iostream>
#include <queue>
#include <time.h>
#include <vector>
#include <stack>
using namespace std;

/* Khai báo cấu trúc dữ liệu cây nhị phân */
struct Node
{
	short int Data; // dữ liệu trong Node là ký tự
	//char Data;
	struct Node* Left, * Right; // con trỏ trỏ đến liên kết Node trái và Node phải
	bool TinhTrangDuyet = false;
	short int ThuTuDuyet = 0;
	short int level; // tầng mà node này đang đứng
	struct Node* on;
	short int sumtree = 0;
};
typedef struct Node NODE;
//typedef NODE* Tree;

/* ===================================== */

/* Khởi tạo cây */
void INit(NODE*& Root) // Tree &Root
{
	Root = NULL;
}

/* ================= */

/* Tạo node */
// Hàm này sẽ khởi tạo ra 1 Node mới và đưa x vào Data của Node đó sau đó trả Node đó về
NODE* GetNode(int x) // x là dữ liệu đưa vào trong Node
{
	NODE* p = new Node;

	// Trường hợp máy tính hết bộ nhớ để cấp phát
	if (p == NULL)
		return NULL;

	// Nếu còn chạy được xuống dưới này tức là Node không rỗng => khởi tạo thành công
	p->Data = x; // x được cập nhật vô Data của Node p
	p->Left = p->Right = NULL; // Khởi tạo liên kết con trái và con phải của Node p là NULL
	p->on = NULL;
	p->level = 1;
	return p; // Trả về Node p sau khi được tạo ra và cập nhật dữ liệu
}

void Input_Data_Node(NODE*& k,const char* s)
{
	rewind(stdin); // Xóa bộ nhớ đệm
	char x;
	do {
		cout << "\nNhap vao du lieu Node " << s;
		cin >> x;

		if (x < 'A' || x > 'Z' && x < 'a' || x > 'z') // Xử lý bắt phải có dữ liệu
			cout << "\nDu lieu nhap cho Node phai la ky tu trong bang chu cai. Xin kiem tra nhap lai!";
	} while (x < 'A' || x > 'Z' && x < 'a' || x > 'z');
	k = GetNode(x);
}

void Init_Tree(NODE*& Root)
{
	Input_Data_Node(Root, "goc");
	queue<NODE*> q;
	q.push(Root);

	while (!q.empty()) // Sẽ lặp liên tục khi nào hàng đợi còn khác rỗng
	{
		NODE* p = q.front(); // Lấy Node đầu tiên đang chờ được xử lý
		q.pop(); // Bỏ nó ra khỏi hàng đợi

		short int SoCon;
		do {
			cout<<"\nNhap vao so luong con cua Node " <<p->Data<<" (0 hay 1 hay 2): ";
			cin >> SoCon;

			if (SoCon < 0 || SoCon > 2)
				cout << "\nSo luong con chi co the la 0 hay 1 hay 2. Xin kiem tra va nhap lai!";
		} while (SoCon < 0 || SoCon > 2);

		if (SoCon == 1)
		{
			char LoaiCon;

			do {
				rewind(stdin); // Xóa bộ nhớ đệm

				cout << "\nBan muon con cua Node " << p->Data << " la con trai hay con phai (L: Left, R: Right)";
				cin >> LoaiCon;

				if (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r')
					cout << "\nNeu la con trai thi nhap L - Neu la con phai thi nhap R. Khong duoc nhap khac ky tu quy dinh";
			} while (LoaiCon != 'L' && LoaiCon != 'R' && LoaiCon != 'l' && LoaiCon != 'r');

			NODE* k;
			if (LoaiCon == 'L' || LoaiCon == 'l') // là con trái
			{
				Input_Data_Node(k, "con trai");
				p->Left = k;
			}
			else // Là con phải
			{
				Input_Data_Node(k, "con phai");
				p->Right = k;
			}
			q.push(k);
		}
		else if (SoCon == 2)
		{
			NODE* l, * r;

			Input_Data_Node(l, "con trai");
			p->Left = l;
			q.push(l);

			Input_Data_Node(r, "con phai");
			p->Right = r;
			q.push(r);
		}
	}
}

/* =========== Cac thao tac duyet cay ==================================== */

// 1: left -> right, khác 1: right->left
void DuyetTheoChieuRong(NODE* Root, short int thutu = 1)
{
	queue<NODE*> q;

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if (Root != NULL)
		q.push(Root);

	while (!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		NODE* p = q.front(); // Lấy ra Node đầu hàng đợi
		cout << p->Data;
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if (thutu == 1)
		{
			if (p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi

			if (p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi
		}
		else
		{
			if (p->Right != NULL) // có tồn tại Node con phải của p
				q.push(p->Right); // Đưa con phải vào hàng đợi

			if (p->Left != NULL) // có tồn tại Node con trái của p
				q.push(p->Left); // Đưa con trái vào hàng đợi
		}
	}
}

// Phép duyệt trước
// 1: left -> right, khác 1: right->left
void PreOrder(NODE* Root, short int thutu = 1)
{
	if (Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		cout << Root->Data << " "; // duyệt in ra N

		if (thutu == 1)
		{
			PreOrder(Root->Left, thutu);
			PreOrder(Root->Right, thutu);
		}
		else
		{
			PreOrder(Root->Right, thutu);
			PreOrder(Root->Left, thutu);
		}
	}
}

// Phép duyệt giữa
// 1: left -> right, khác 1: right->left
void InOrder(NODE* Root,short int thutu = 1)
{
	if (Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if (thutu == 1)
		{
			InOrder(Root->Left, thutu);
			cout << Root->Data << " "; // duyệt in ra N
			InOrder(Root->Right, thutu);
		}
		else
		{
			InOrder(Root->Right, thutu);
			cout << Root->Data << " "; // duyệt in ra N
			InOrder(Root->Left, thutu);
		}
	}
}

// Phép duyệt sau
// 1: left -> right, khác 1: right->left
void PostOrder(NODE* Root,short int thutu = 1)
{
	if (Root != NULL) // điều kiện để được đệ quy => nếu Root = NULL thì không đệ quy nữa
	{
		if (thutu == 1)
		{
			PostOrder(Root->Left, thutu);
			PostOrder(Root->Right, thutu);
			cout << Root->Data << " ";; // duyệt in ra N
		}
		else
		{
			PostOrder(Root->Right, thutu);
			PostOrder(Root->Left, thutu);
			cout << Root->Data << " "; // duyệt in ra N
		}
	}
}

void CountNode_DeQuyDuoi(NODE* Root,unsigned short int& dem)
{
	if (Root != NULL)
	{
		++dem; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		CountNode_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		CountNode_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

void FreeTree(NODE*& Root)
{
	if (Root != NULL)
	{
		FreeTree(Root->Left); // Xét tiếp qua nhánh con trái của Node hiện tại
		FreeTree(Root->Right); // Xét tiếp qua nhánh con phải của Node hiện tại
		delete Root; // Giải phóng Node đang xét đến. Lưu ý: Phải giải phóng nó sau cùng (duyệt sau) chứ nếu dùng duyệt trước hay duyệt giữa thì sau khi giải phóng lấy gì mà tiếp tục trỏ? => LỖI
		Root = NULL; // Sau khi giải phóng xong phải cập nhật cho Node đó giá trị NULL nếu không sẽ bị lỗi ngang nếu sau khi giải phóng xong người dùng có thao tác tiếp gì đó (vd: duyệt cây)
	}
}

unsigned short int CountNode_DeQuyThuong(NODE* Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if (Root == NULL)
		return 0;

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return 1 + CountNode_DeQuyThuong(Root->Left) + CountNode_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

unsigned short int CountNode_KhongDeQuy(NODE* Root)
{
	queue<NODE*> q;

	// Phải có tồn tại Node gốc thì mới đưa Node gốc đó vào hàng đợi
	if (Root != NULL)
		q.push(Root);

	unsigned short int dem = 0;
	while (!q.empty()) // lặ[ liên tục khi hàng đợi còn phần tử
	{
		NODE* p = q.front(); // Lấy ra Node đầu hàng đợi
		//printf("%d ", p->Data); 
		++dem;
		q.pop(); // bỏ Node ra khỏi hàng đợi

		if (p->Left != NULL) // có tồn tại Node con trái của p
			q.push(p->Left); // Đưa con trái vào hàng đợi

		if (p->Right != NULL) // có tồn tại Node con phải của p
			q.push(p->Right); // Đưa con phải vào hàng đợi
	}
	return dem;
}

// Node lá: Là node không có con
unsigned short int CountNodeLeaf_DeQuyThuong(NODE* Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if (Root == NULL)
		return 0;

	unsigned short int dem = 0;
	if (Root->Left == NULL && Root->Right == NULL) // Root là node lá => cho dem = 1
	{
		cout << Root->Data;
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + CountNodeLeaf_DeQuyThuong(Root->Left) + CountNodeLeaf_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

// Node lá: Là node không có con
void CountNodeLeaf_DeQuyDuoi(NODE* Root,unsigned short int& dem)
{
	if (Root != NULL)
	{
		if (Root->Left == NULL && Root->Right == NULL) // Root là node lá => cho dem = 1
		{
			//printf("%c ", Root->Data);
			dem++; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		CountNodeLeaf_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		CountNodeLeaf_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

unsigned short int CountNode_Has2Node_DeQuyThuong(NODE* Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if (Root == NULL)
		return 0;

	unsigned short int dem = 0;
	if (Root->Left != NULL && Root->Right != NULL)
	{
		cout << Root->Data;
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + CountNode_Has2Node_DeQuyThuong(Root->Left) + CountNode_Has2Node_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

void CountNode_Has2Node_DeQuyDuoi(NODE* Root,unsigned short int& dem)
{
	if (Root != NULL)
	{
		if (Root->Left != NULL && Root->Right != NULL)
		{
			//cout << Root->Data;
			++dem; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		CountNode_Has2Node_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		CountNode_Has2Node_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

unsigned short int CountNode_Has1Node_DeQuyThuong(NODE* Root)
{
	// Điều kiện dừng là khi nút đó không tồn tại => nếu không có sẽ chạy vào 1 vùng nhớ không hợp lệ và báo lỗi
	if (Root == NULL)
		return 0;

	unsigned short int dem = 0;
	if ((Root->Left != NULL && Root->Right == NULL) || (Root->Right != NULL && Root->Left == NULL))
	{
		cout << Root->Data;
		dem = 1;
	}

	// Bước đệ quy => tức là khi nút đó có tồn tại
	return dem + CountNode_Has1Node_DeQuyThuong(Root->Left) + CountNode_Has1Node_DeQuyThuong(Root->Right); // nhớ là mỗi lần đi đến 1 node có tồn tại thì phải tính là 1 lần cho nó chứ nếu quên là cuối cùng chạy cho đã kết quả vẫn là 0
}

void CountNode_Has1Node_DeQuyDuoi(NODE* Root,unsigned short int& dem)
{
	if (Root != NULL)
	{
		if ((Root->Left != NULL && Root->Right == NULL) || (Root->Right != NULL && Root->Left == NULL))
		{
			cout << Root->Data;
			++dem; // Cứ đến 1 Node là sẽ tăng biến đếm lên 1
		}

		CountNode_Has1Node_DeQuyDuoi(Root->Left, dem); // Xét tiếp qua nhánh con trái của Node hiện tại
		CountNode_Has1Node_DeQuyDuoi(Root->Right, dem); // Xét tiếp qua nhánh con phải của Node hiện tại
	}
}

unsigned short int LevelOfNode(NODE*& X)
{
	unsigned short int DemCon = 0;

	if (X->Left != NULL)
		DemCon++;

	if (X->Right != NULL)
		DemCon++;

	return DemCon;
}

void LevelOfTree(NODE* Root,short int& MaxBac)
{
	if (Root != NULL)
	{
		cout << Root->Data;

		// xử lý
		unsigned short int bac = LevelOfNode(Root);
		if (bac > MaxBac)
		{
			MaxBac = bac;

			if (MaxBac == 2) // nhận thấy cây luôn có bậc tối đa là 2 nên khi tìm được 1 node có bậc là 2 rồi thì chúng ta dừng lại không cần duyệt gọi đệ quy tiếp nữa
				return;
		}

		LevelOfTree(Root->Left, MaxBac);
		LevelOfTree(Root->Right, MaxBac);
	}
}

unsigned short int HighOfTree_DeQuyThuong(NODE* Root)
{
	if (Root == NULL)
		return 0;

	unsigned short int left = HighOfTree_DeQuyThuong(Root->Left);
	unsigned short int right = HighOfTree_DeQuyThuong(Root->Right);

	return left > right ? left + 1 : right + 1;
}

void HighOfTree_DeQuyDuoi(NODE* Root, short int& max, short int level = 1)
{
	if (Root != NULL)
	{
		// xử lý Root
		//printf("\nNode %c nam o level: %d", Root->Data, level);
		if (level > max)
			max = level;

		level++;
		HighOfTree_DeQuyDuoi(Root->Left, max, level);
		HighOfTree_DeQuyDuoi(Root->Right, max, level);
	}
}

void FindNode_X(NODE* Root, bool& Check, char x,short int& dosau,short int level)
{
	if (Root != NULL && Check == false) // chỉ đệ quy khi Node có tồn tại và trạng thái tìm kiếm là chưa được tìm thấy
	{
		cout << Root->Data;
		if (Root->Data == x)
		{
			Check = true;
			dosau = level;

			// Nếu dùng exit(0) là tắt luôn toàn bộ chương trình => chỉ dùng khi đằng sau bài này mình không còn phải làm bài nào nữa, còn nếu còn yêu cầu thì không dùng cách này được
			/*printf("\nDa tim thay node co data la %c", x);
			system("pause");
			exit(0);*/
			return; // kết thúc tìm kiếm khi đã thấy
		}

		++level;
		FindNode_X(Root->Left, Check, x, dosau, level);
		FindNode_X(Root->Right, Check, x, dosau, level);
	}
}

void OutputAndCountNodeOnLevelK(NODE* Root,short int k,unsigned short int& count,unsigned short int level = 1)
{
	if (Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if (level == k)
		{
			++count;
			cout << Root->Data;
		}

		++level;
		OutputAndCountNodeOnLevelK(Root->Left, k, count, level);
		OutputAndCountNodeOnLevelK(Root->Right, k, count, level);
	}
}

void CountNodeOnLevelK(NODE* Root,short int k, unsigned short int& count, unsigned short int level = 1)
{
	if (Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if (level == k)
			++count;

		++level;
		CountNodeOnLevelK(Root->Left, k, count, level);
		CountNodeOnLevelK(Root->Right, k, count, level);
	}
}

void OutputNodeOnEveryLevel(NODE* Root)
{
	short int ChieuCaoCay = 0;
	HighOfTree_DeQuyDuoi(Root, ChieuCaoCay);

	for (int i = 1; i <= ChieuCaoCay; ++i)
	{
		printf("\nTang thu %d: ", i);
		unsigned short int count = 0;
		OutputAndCountNodeOnLevelK(Root, i, count);
		cout << "\n=> co " << count << " Node";
	}
}

// s là operator giữa tầng của node hiện tại với tầng k
// vd: Xuất tất cả các node nằm trên tầng k => s = "=="
// vd: Xuất tất cả các node có tầng lớn hơn tầng k => s = ">"
void OutputAndCountNode_WithK(NODE* Root, char* s,short int k, unsigned short int& count, unsigned short int level = 1)
{
	if (Root != NULL)
	{
		bool Check;
		if (strcmp(s, "==") == 0)
			Check = (level == k);
		else if (strcmp(s, ">") == 0)
			Check = (level > k);
		else if (strcmp(s, "<") == 0)
			Check = (level < k);
		else if (strcmp(s, ">=") == 0)
			Check = (level >= k);
		else if (strcmp(s, "<=") == 0)
			Check = (level <= k);
		else if (strcmp(s, "!=") == 0)
			Check = (level != k);

		if (Check)
		{
			++count;
			cout << Root->Data;
		}

		level++;
		OutputAndCountNode_WithK(Root->Left, s, k, count, level);
		OutputAndCountNode_WithK(Root->Right, s, k, count, level);
	}
}

// Nếu trả về true => là cây nhị phân đầy đủ
// Nếu trả về false => không phải là cây nhị phân đầy đủ
bool Check_PerfectTree1(NODE* Root)
{
	short int ChieuCaoCay = 0;
	HighOfTree_DeQuyDuoi(Root, ChieuCaoCay);

	for (int i = 1; i <= ChieuCaoCay; ++i)
	{
		//printf("\nTang thu %d: ", i);
		unsigned short int count = 0;
		CountNodeOnLevelK(Root, i, count);
		//printf(" => co %d node", count);

		if (count != pow(2.0, i - 1))
			return false;
	}
	return true;
}

void InputNodeOnEveryLevelInVector(NODE* Root, vector<short int>& a,unsigned short int level = 1)
{
	if (Root != NULL)
	{
		//printf("\nNode %c co level la: %d", Root->Data, level);
		if (level > a.size()) // Nếu level đang xét mà vector chưa có thì tạo mới ra ô tương ứng trong vector với giá trị khởi tạo ban đầu là 0
			a.push_back(0);

		++a[level - 1]; // ô tương ứng level trong vector sẽ được cập nhật đếm lên 1 đơn vị

		++level;
		InputNodeOnEveryLevelInVector(Root->Left, a, level);
		InputNodeOnEveryLevelInVector(Root->Right, a, level);
	}
}

bool Check_PerfectTree2(NODE* Root)
{
	vector<short int> a;

	InputNodeOnEveryLevelInVector(Root, a);

	unsigned short int SoLuong = a.size();
	for (unsigned short int i = 0; i < SoLuong; ++i)
	{
		if (a[i] != pow(2.0, i))
			return false;
	}
	return true;
}

// thống kê số lượng node và danh sách node ở tầng h và tầng h-1
void InitVector2D_Node(NODE* Root, vector<vector<NODE*>>& Mang2ChieuNode,unsigned short int level = 1)
{
	if (Root != NULL)
	{
		if (level > Mang2ChieuNode.size())
		{
			vector<NODE*> temp;
			temp.push_back(Root);
			Mang2ChieuNode.push_back(temp);
		}
		else
		{
			Mang2ChieuNode[level - 1].push_back(Root);
		}

		++level;
		InitVector2D_Node(Root->Left, Mang2ChieuNode, level);
		InitVector2D_Node(Root->Right, Mang2ChieuNode, level);
	}
}

// trả về true nếu thỏa là cây nhị phân hoàn chỉnh - trả về false nếu không thỏa là cây nhị phân hoàn chỉnh
bool Check_CompleteTree(NODE* Root)
{
	vector<vector<NODE*>> Mang2ChieuNode;
	InitVector2D_Node(Root, Mang2ChieuNode);
	short int ChieuCaoCay = Mang2ChieuNode.size();

	for (unsigned short int i = 1; i < ChieuCaoCay; ++i)
	{
		if (Mang2ChieuNode[i - 1].size() != pow(2.0, i - 1))
			return false;
	}

	// Xét riêng số lượng node của tầng cuối cùng phải không đầy đủ thì mới xét xem có là hoàn chỉnh hay không (chứ nếu đầy đủ luôn thì đó là cây đầy đủ rồi)
	if (Mang2ChieuNode[ChieuCaoCay - 1].size() == pow(2.0, ChieuCaoCay - 1))
		return false;

	// Nếu chạy đến đây rồi thì tức là tiêu chí 1 đầu tiên đã thỏa
	for (unsigned short int j = 0; j < Mang2ChieuNode[ChieuCaoCay - 1].size(); ++j)
	{
		NODE* Con = Mang2ChieuNode[ChieuCaoCay - 1][j];
		NODE* Cha = Mang2ChieuNode[ChieuCaoCay - 2][j / 2];

		if (j % 2 == 0) // chẵn => con trái
		{
			if (Cha->Left != Con)
				return false;
		}
		else // lẻ => con phải
		{
			if (Cha->Right != Con)
				return false;
		}
	}
	return true;
}

// 1: là cây đầy đủ - 2: là cây hoàn chỉnh - 0: không là cây gì
short int Check_CompleteOrPerfect_Tree(NODE* Root)
{
	vector<vector<NODE*>> Mang2ChieuNode;
	InitVector2D_Node(Root, Mang2ChieuNode);
	unsigned short int ChieuCaoCay = Mang2ChieuNode.size();

	// kiểm tra các node từ tầng 1 đến h - 1 phải đầy đủ thì mới xét tiếp
	for (int i = 1; i < ChieuCaoCay; ++i)
	{
		if (Mang2ChieuNode[i - 1].size() != pow(2.0, i - 1))
			return 0; // la cay nhi phan binh thuong
	}

	// Nếu xuống đây được tức là cây này các node ở tầng 1 đến h-1 đều đầy đủ => xét tiếp số lượng các node ở tầng h
	if (Mang2ChieuNode[ChieuCaoCay - 1].size() == pow(2.0, ChieuCaoCay - 1))
		return 1; // là cây hoàn hảo 

	// Nếu xuống đây được tức là không đầy đủ các node (tức là không thể là cây đầy đủ chỉ có thể là cây hoàn chỉnh hoặc là không) thì sẽ xét tiếp tiêu chí 2 xem các node có được sắp đều từ trái qua phải không để kết luận có thể là cây hoàn chỉnh
	for (int j = 0; j < Mang2ChieuNode[ChieuCaoCay - 1].size(); ++j)
	{
		NODE* Con = Mang2ChieuNode[ChieuCaoCay - 1][j];
		NODE* Cha = Mang2ChieuNode[ChieuCaoCay - 2][j / 2];

		if (j % 2 == 0) // chẵn => con trái
		{
			if (Cha->Left != Con)
				return 0;
		}
		else // lẻ => con phải
		{
			if (Cha->Right != Con)
				return 0;
		}
	}
	return 2; // là cây hoàn chỉnh
}

/* =============================== KHÔNG ĐỆ QUY ================================== */

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void PreOrder_KhuDeQuyDungStack(NODE* Root,unsigned short int thutu = 1)
{
	stack<NODE*> s;
	s.push(Root);

	//thutu == 1 ? printf("\nNLR: ") : printf("\nNRL: ");

	while (!s.empty())
	{
		NODE* p = s.top();
		s.pop();
		//printf("%c ", p->Data);

		if (thutu == 1) // left -> right
		{
			if (p->Right != NULL)
				s.push(p->Right);

			if (p->Left != NULL)
				s.push(p->Left);
		}
		else // right -> left
		{
			if (p->Left != NULL)
				s.push(p->Left);

			if (p->Right != NULL)
				s.push(p->Right);
		}
	}
}

// thutu = 1 (left -> right), thutu = 2 (right -> left)
void InOrder_KhuDeQuyDungStack(NODE* Root, unsigned short int thutu = 1)
{
	stack<NODE*> s;
	s.push(Root);
	Root->TinhTrangDuyet = true;

	//thutu == 1 ? printf("\nLNR: ") : printf("\nRNL: ");

	while (!s.empty())
	{
		NODE* p = s.top(); // p là Node ở đỉnh stack
		bool Check = false;

		if (thutu == 1)
		{
			if (p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Right); // đưa con phải vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if (p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Left); // đưa con trái vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}
		else
		{
			if (p->Left != NULL && p->Left->TinhTrangDuyet == false) // có tồn tại con phải và con phải chưa được duyệt
			{
				s.pop(); // xóa phần tử đầu stack hiện tại
				s.push(p->Left); // đưa con phải vào stack
				p->Left->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				s.push(p); // trả lại phần tử đầu stack trước đó
				Check = true; // kiểm tra có con được thêm vào
			}

			if (p->Right != NULL && p->Right->TinhTrangDuyet == false) // có tồn tại con trái và con trái chưa được duyệt
			{
				s.push(p->Right); // đưa con trái vào stack
				p->Right->TinhTrangDuyet = true; // đánh dấu là đã được duyệt
				Check = true; // kiểm tra có con được thêm vào
			}
		}

		// Nếu sau 1 quá trình xét mà không có con nào được thêm vào => in ra node đầu stack hiện tại và bỏ đi
		if (Check == false)
		{
			//cout << p->Data;
			s.pop();
		}
	}
}

// thutu = 1 (left -> right); thutu = 2 (right -> left)
void PostOrder_KhuDeQuyDungStack(NODE* Root, unsigned short int thutu = 1)
{
	stack<NODE*> s;
	s.push(Root);

	while (!s.empty())
	{
		NODE* p = s.top();
		bool Check = false; // biến cờ hiệu mục đích để biết xem từ node hiện tại đầu stack có node con nào của nó hợp lệ để được thêm vào tiếp. Nếu trải qua 2 cái if mà Check vẫn là false tức là không có node con nào của node đang xét được thêm vào stack => lấy node đó ra khỏi stack và in ra

		if (thutu == 1)
		{
			if (p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if (p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}
		else
		{
			if (p->Left != NULL && p->Left->TinhTrangDuyet == false) // xét có con trái và chưa được thêm vào stack
			{
				s.push(p->Left); // tiến hành thêm vào
				p->Left->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}

			if (p->Right != NULL && p->Right->TinhTrangDuyet == false) // xét có con phải và chưa được thêm vào stack
			{
				s.push(p->Right); // tiến hành thêm vào
				p->Right->TinhTrangDuyet = true; // cập nhật tình trạng thêm
				Check = true;
			}
		}

		if (Check == false)
		{
			//cout << p->Data;
			s.pop(); // bỏ ra khỏi stack
		}
	}
}

void DuyetCayKhongDeQuyKhongStack(NODE* Root,const char* s) // s = "NLR" hoặc "LNR" hoặc "LRN" hoặc "NRL" hoặc "RNL" hoặc "RLN"
{
	short int length = strlen(s);
	if(length != 3)
	{
		cout << "\nChuoi phep duyet khong hop le. Xin kiem tra lai!";
	}
	else
	{
		unsigned short int dem_N = 0;
		unsigned short int dem_L = 0;
		unsigned short int dem_R = 0;

		for(int i = 0; i < length; ++i)
		{
			if(s[i] == 'N' || s[i] == 'n')
				dem_N++;
			else if(s[i] == 'L' || s[i] == 'l')
				dem_L++;
			else if(s[i] == 'R' || s[i] == 'r')
				dem_R++;
		}

		if(dem_L != 1 || dem_N != 1 || dem_R != 1)
		{
			cout << "\nChuoi phep duyet khong hop le. Xin kiem tra lai!";
		}
		else
		{
			if (Root != NULL)
			{
				NODE* cha = Root->on;
				Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

				while (true)
				{
					if (Root->ThuTuDuyet <= 2)
					{
						if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
						{
							cout << Root->Data;
							Root->ThuTuDuyet++;
						}
						else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
						{
							Root->ThuTuDuyet++;

							if (Root->Left != NULL)
								Root = Root->Left;
						}
						else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
						{
							Root->ThuTuDuyet++;

							if (Root->Right != NULL)
								Root = Root->Right;
						}
					}
					else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
					{
						Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

						if (Root->on == NULL)
						{
							Root->on = cha; // trả lại cha ban đầu của Root;
							break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
						}
						else
							Root = Root->on;
					}
				}
			}
		}
	}
}

// Tính tầng mà node đó đang đứng
unsigned short int LevelOfNode_KhongDeQuyKhongStack(NODE* X)
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

unsigned short int HighOfTree_KhongDeQuyKhongStack(NODE* Root)
{
	char s[] = "NLR"; // quy ước thao tác duyệt

	unsigned short int DoSauMax = 1;

	if (Root != NULL)
	{
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					unsigned short int DoSauNode = LevelOfNode_KhongDeQuyKhongStack(Root);
					if (DoSauNode > DoSauMax)
						DoSauMax = DoSauNode;

					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
					{
						int level_cha = Root->level;
						Root = Root->Left;
						Root->level = level_cha + 1;
					}
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
					{
						int level_cha = Root->level;
						Root = Root->Right;
						Root->level = level_cha + 1;
					}
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->on;
			}
		}
	}
	return DoSauMax; // CHIỀU CAO Cây
}

vector<vector<NODE*>> UpdateLevelForNode_And_InitVector2DNode_KhongDeQuyKhongStack(NODE*& Root)
{
	vector<vector<NODE*>> arr;

	char s[] = "NLR"; // quy ước thao tác duyệt

	if (Root != NULL)
	{
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					if (Root->level > arr.size())
					{
						vector<NODE*> temp;
						temp.push_back(Root);
						arr.push_back(temp);
					}
					else
					{
						arr[Root->level - 1].push_back(Root);
					}

					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
					{
						short int level_Cha = Root->level;
						Root = Root->Left;
						Root->level = level_Cha + 1;
					}
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
					{
						short int level_Cha = Root->level;
						Root = Root->Right;
						Root->level = level_Cha + 1;
					}
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->on;
			}
		}
	}
	return arr;
}

void TimDoLechLonNhatTrenCay_DeQuy(NODE* Root, int& DoLechMax, NODE*& p)
{
	if (Root != NULL)
	{
		short int docaocontrai = 0;
		HighOfTree_DeQuyDuoi(Root->Left, docaocontrai);

		short int docaoconphai = 0;
		HighOfTree_DeQuyDuoi(Root->Right, docaoconphai);

		int dolech = abs(docaocontrai - docaoconphai);

		if (dolech > DoLechMax)
		{
			DoLechMax = dolech;
			p = Root;
		}

		TimDoLechLonNhatTrenCay_DeQuy(Root->Left, DoLechMax, p);
		TimDoLechLonNhatTrenCay_DeQuy(Root->Right, DoLechMax, p);
	}
}

short int TimDoLechLonNhatTrenCay_KhuDeQuy(Node* Root)
{
	if (Root != NULL)
	{
		const char s[] = "NLR";
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		short int dolechmax = 0;
		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//cout << Root->Data;
					short int dolechtrai = 0;
					if (Root->Left)
						dolechtrai = HighOfTree_KhongDeQuyKhongStack(Root->Left);
					short int dolechphai = 0;
					if (Root->Right)
						dolechphai = HighOfTree_KhongDeQuyKhongStack(Root->Right);

					short int dolech = abs(dolechtrai - dolechphai);
					if (dolech > dolechmax) dolechmax = dolech;
					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
						Root = Root->Left;
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->on;
			}
		}
		return dolechmax;
	}
}

void SumTree(Node*& X, short int& sum)
{
	if (X)
	{
		sum += X->Data;
		SumTree(X->Left, sum);
		SumTree(X->Right, sum);
	}
}

short int SumTree2(Node* X)
{
	const char s[] = "NLR";
	short int Sum = 0;
	if (X != NULL)
	{
		NODE* cha = X->on;
		X->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (X->ThuTuDuyet <= 2)
			{
				if (s[X->ThuTuDuyet] == 'N' || s[X->ThuTuDuyet] == 'n')
				{
					Sum += X->Data;
					X->ThuTuDuyet++;
				}
				else if (s[X->ThuTuDuyet] == 'L' || s[X->ThuTuDuyet] == 'l')
				{
					X->ThuTuDuyet++;

					if (X->Left != NULL)
						X = X->Left;
				}
				else if (s[X->ThuTuDuyet] == 'R' || s[X->ThuTuDuyet] == 'r')
				{
					X->ThuTuDuyet++;

					if (X->Right != NULL)
						X = X->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				X->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (X->on == NULL)
				{
					X->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					X = X->on;
			}
		}
	}
	return Sum;
}

short int FindNodeHas_MaxSum1(Node* Root, Node*&p)
{
	const char s[] = "NLR";
	short int Sum = 0;
	if (Root != NULL)
	{
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					short int sum = SumTree2(Root);
					//SumTree(Root, sum);
					if (sum > Sum)
					{
						Sum = sum;
						p = Root;
					}
					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
						Root = Root->Left;
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->on;
			}
		}
	}
	return Sum;
}

void FindNodeHas_MaxSum2(Node*& Root, Node*& p, short int &TongMax)
{
	if (Root)
	{
		FindNodeHas_MaxSum2(Root->Left, p, TongMax);
		FindNodeHas_MaxSum2(Root->Right, p, TongMax);
		
		short int Tong = Root->Data;
		if (Root->Left) Tong += Root->Left->Data;
		if (Root->Right) Tong += Root->Right->Data;
		Root->sumtree = Tong;
		if (Tong > TongMax)
		{
			TongMax = Tong;
			p = Root;
		}
	}
}

Node* FindNodeHas_MaxSum3(Node* Root, short int &SumMax)
{
	const char s[] = "LRN";
	Node* p = NULL;
	if (Root != NULL)
	{
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)

		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					short int Tong = Root->Data;
					if (Root->Left) Tong += Root->Left->Data;
					if (Root->Right) Tong += Root->Right->Data;
					Root->sumtree = Tong;
					if (Tong > SumMax)
					{
						SumMax = Tong;
						p = Root;
					}

					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
						Root = Root->Left;
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
					Root = Root->on;
			}
		}
	}
	return p;
}

void DeleteTree_KhuDeQuy(NODE*& Root)
{
	const char s[] = "NLR";
	if (Root != NULL)
	{
		NODE* cha = Root->on;
		Root->on = NULL; // quy ước Root chính là gốc của cây đang xét (nó có thể là cây nhỏ cho nên phải cho điều kiện dừng là Root->Cha = NULL)
		while (true)
		{
			if (Root->ThuTuDuyet <= 2)
			{
				if (s[Root->ThuTuDuyet] == 'N' || s[Root->ThuTuDuyet] == 'n')
				{
					//
					Root->ThuTuDuyet++;
				}
				else if (s[Root->ThuTuDuyet] == 'L' || s[Root->ThuTuDuyet] == 'l')
				{
					Root->ThuTuDuyet++;

					if (Root->Left != NULL)
						Root = Root->Left;
				}
				else if (s[Root->ThuTuDuyet] == 'R' || s[Root->ThuTuDuyet] == 'r')
				{
					Root->ThuTuDuyet++;

					if (Root->Right != NULL)
						Root = Root->Right;
				}
			}
			else // khi đi vào đây tức là 1 node đã đi hết thang thứ tự duyệt rồi, lúc này không đi tới được nữa mà phải lùi về cha của nó để xét theo hướng khác
			{
				Root->ThuTuDuyet = 0; // trước khi trở về cha thì sẽ reset lại thứ tự duyệt của node đó về 0 để có thể sau hàm này còn nhu cầu duyệt tiếp kiểu khác nữa

				if (Root->on == NULL)
				{
					Root->on = cha; // trả lại cha ban đầu của Root;
					delete Root;
					Root = NULL;
					break; // ĐIỀU KIỆN DỪNG => TỪ GỐC TRỎ VỀ CHA SẼ LÀ NULL => DỪNG LẠI
				}
				else
				{
					NODE* q = Root;
					Root = Root->on;
					delete q;
					q = NULL;
				}
			}
		}
	}
}

int main()
{
	/* Nhập dữ liệu cho cây (Tạo cây) */
	// Bước 1: Tạo ra bấy nhiêu Node tương ứng với các Node có trong cây
	//NODE *A = GetNode('A'); // Đây chính là Node gốc
	//NODE *B = GetNode('B');
	//NODE *C = GetNode('C');
	//NODE *D = GetNode('D');
	//NODE *E = GetNode('E');
	//NODE *F = GetNode('F');
	//NODE *G = GetNode('G');
	//NODE *H = GetNode('H');
	//NODE *I = GetNode('I');
	//NODE *J = GetNode('J');
	//NODE *K = GetNode('K');
	//NODE *L = GetNode('L');

	NODE* A = GetNode(-9); // Đây chính là Node gốc
	NODE* B = GetNode(2);
	NODE* C = GetNode(-50);
	NODE* D = GetNode(-1);
	NODE* E = GetNode(0);
	NODE* F = GetNode(-16);
	NODE* G = GetNode(-7);
	NODE* H = GetNode(6);
	NODE* I = GetNode(3);
	NODE* J = GetNode(-4);
	NODE* K = GetNode(-10);
	NODE* L = GetNode(-9);

	// Bước 2: Tạo ra các mối liên kết giữa các Node với nhau
	A->Left = B; B->on = A;
	A->Right = C; C->on = A;
	
	B->Left = D; D->on = B;
	B->Right = E; E->on = B;
	
	C->Left = F; F->on = C;
	C->Right = G; G->on = C;
	
	D->Left = H; H->on = D;
	D->Right = I; I->on = D;
	
	E->Right = J; J->on = E;

	F->Left = K; K->on = F;

	G->Right = L; L->on = G;

	// Tinh do lech lon nhat cua cay
	//cout << "\nDo lech lon nhat cua cay la: " << TimDoLechLonNhatTrenCay_KhuDeQuy(A);

	/*Node* p1 = NULL; short int TongMax1 = INT_MIN;
	cout << "\nCay con co tong lon nhat la: "<<FindNodeHas_MaxSum1(A, p1) << " la node "<<p1->Data;
	p1 = NULL; TongMax1 = A->INT_MIN;
	FindNodeHas_MaxSum2(A, p1, TongMax1);
	cout << "\nCay con co tong lon nhat la: " << p1->Data << " co tong la: " << TongMax1;*/
	/*short int SumMax = INT_MIN;
	Node* p = FindNodeHas_MaxSum3(A, SumMax);
	cout << "\nCay con co tong lon nhat la: " << p->Data << " co tong la: " << SumMax;*/

	cout << "\nGiai phong cay\n";
	//FreeTree(A); // giải phóng bộ nhớ đã cấp phát cho cây
	DeleteTree_KhuDeQuy(A);
	return 0;
}