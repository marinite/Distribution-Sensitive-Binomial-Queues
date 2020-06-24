#include <iostream>
#include <cstdlib>
using namespace std;

//структура узла
struct node
{
	int key; //значение
	int degree; //степень
	node* parent; //родитель
	node* child; //ребёнок
	node* sibling; //родной брат
};

//структура биномиальной пирамиды
class BinomialHeap
{
private:
	node* H;
	node* Hr;
	int count;
public:
	node* Initializeheap(); //инициализация пирамиды(узла)
	void Binomial_link(node*, node*); //объединение узлов в биномиальной куче
	node* Create_node(int); //создание узла в биномиальной куче
	node* Heapify(node*, node*); //объединение узлов в биномиальной куче
	node* Insert(node*, node*); //вставка узла в биномиальную кучу
	node* Merge(node*, node*); //слияние узлов в биномиальной куче
	node* Delete_Min(node*); //извлечение минимума
	void Revert_list(node*); //обратный список
	int Display(node*); //вывод
	void Output_Child(node*); //вывод детей
	node* Search(node*, int); //поиск узла в биномиальной куче
	int Decrease_node(node*, int, int); //уменьшение значения узла
	int Delete(node*, int); //удаление узла в биномиальной куче

	BinomialHeap()
	{
		H = Initializeheap();
		Hr = Initializeheap();
		int count = 1;
	}
};


 node* BinomialHeap::Initializeheap()
{
	node* np;
	np = NULL;
	return np;
}


void BinomialHeap::Binomial_link(node* y, node* z)  
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree = z->degree + 1;
}


node* BinomialHeap::Create_node(int k)
{
	node* p = new node;
	p->key = k;
	return p;
}


node* BinomialHeap::Insert(node* H, node* x)
{
	node* H1 = Initializeheap();
	x->parent = NULL;
	x->child = NULL;
	x->sibling = NULL;
	x->degree = 0;
	H1 = x;
	H = Heapify(H, H1);
	return H;
}


node* BinomialHeap::Heapify(node* H1, node* H2)
{
	node* H = Initializeheap();
	H = Merge(H1, H2);
	if (H == NULL)
		return H;
	node* prev_x;
	node* next_x;
	node* x;
	prev_x = NULL;
	x = H;
	next_x = x->sibling;
	while (next_x != NULL)
	{
		if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->key <= next_x->key)
			{
				x->sibling = next_x->sibling;
				Binomial_link(next_x, x);
			}
			else
			{
				if (prev_x == NULL)
					H = next_x;
				else
					prev_x->sibling = next_x;
				Binomial_link(x, next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return H;
}


node* BinomialHeap::Merge(node* H1, node* H2)
{
	node* H = Initializeheap();
	node* y;
	node* z;
	node* a;
	node* b;
	y = H1;
	z = H2;
	if (y != NULL)
	{
		if (z != NULL)
		{
			if (y->degree <= z->degree)
				H = y;
			else if (y->degree > z->degree)
				H = z;
		}
		else
			H = y;
	}
	else
		H = z;
	while (y != NULL && z != NULL)
	{
		if (y->degree < z->degree)
		{
			y = y->sibling;
		}
		else if (y->degree == z->degree)
		{
			a = y->sibling;
			y->sibling = z;
			y = a;
		}
		else
		{
			b = z->sibling;
			z->sibling = y;
			z = b;
		}
	}
	return H;
}


int BinomialHeap::Display(node* H)
{
	if (H == NULL)
	{
		cout << "The Heap is empty" << endl;
		return 0;
	}
	cout << "The root nodes are: " << endl;
	node* p;
	p = H;
	bool count = 1;
	while (p != NULL)
	{
		do
		{
			cout << p->key;
			if(p->child!=NULL)
				Output_Child(p->child);
			
			if (p->sibling != NULL)
			{
				count = 1;
				cout << endl << "|" << endl;
			}
			else count = 0;
			p = p->sibling;
		} while (count);
	}
	cout << endl;
}


void BinomialHeap::Output_Child(node* H1)
{
	node* ch;
	ch = H1;
	bool count = 1;
	do
	{
		cout << " -> "<<ch->key ;
		if (ch->sibling != NULL) Output_Child(ch->sibling);
		if (ch->child != NULL)
			count = 1;
		else count = 0;
		ch = ch->child;
	} while (count);
}


node* BinomialHeap::Delete_Min(node* H1)
{
	Hr = NULL;
	node* t = NULL;
	node* x = H1;
	if (x == NULL)
	{
		cout << "Heap is empty" << endl;
		return x;
	}
	int min = x->key;
	node* p = x;
	while (p->sibling != NULL)
	{
		if ((p->sibling)->key < min)
		{
			min = (p->sibling)->key;
			t = p;
			x = p->sibling;
		}
		p = p->sibling;
	}
	if (t == NULL && x->sibling == NULL)
		H1 = NULL;
	else if (t == NULL)
		H1 = x->sibling;
	else if (t->sibling == NULL)
		t = NULL;
	else
		t->sibling = x->sibling;
	if (x->child != NULL)
	{
		Revert_list(x->child);
		(x->child)->sibling = NULL;
	}
	H = Heapify(H1, Hr);
	cout << "The node with minimum key: " << min << endl;
	return H;
}


void BinomialHeap::Revert_list(node* y)
{
	if (y->sibling != NULL)
	{
		Revert_list(y->sibling);
		(y->sibling)->sibling = y;
	}
	else
	{
		Hr = y;
	}
}


node* BinomialHeap::Search(node* H, int k)
{
	node* x = H;
	node* p = NULL;
	if (x->key == k)
	{
		p = x;
		return p;
	}
	if (x->child != NULL && p == NULL)
		p = Search(x->child, k);
	if (x->sibling != NULL && p == NULL)
		p = Search(x->sibling, k);
	return p;
}


int BinomialHeap::Decrease_node(node* H, int i, int k)
{
	int temp;
	node* p;
	node* y;
	node* z;
	p = Search(H, i);
	if (p == NULL)
	{
		cout << "Invalid choice of key" << endl;
		return 0;
	}
	if (k > p->key)
	{
		cout << "Error!! New key is greater than current key" << endl;
		return 0;
	}
	p->key = k;
	y = p;
	z = p->parent;
	while (z != NULL && y->key < z->key)
	{
		temp = y->key;
		y->key = z->key;
		z->key = temp;
		y = z;
		z = z->parent;
	}
	cout << "Key reduced successfully" << endl;
}


int BinomialHeap::Delete(node* H, int k)
{
	node* np;
	if (H == NULL)
	{
		cout << "\nHEAP EMPTY!!!!!";
		return 0;
	}
	Decrease_node(H, k, -1000);
	np = Delete_Min(H);
	if (np != NULL)
		cout << "Node Deleted Successfully" << endl;
}


int main()
{
	int n, m, l, i, choice;
	BinomialHeap bh;
	node* p;
	node* H;
	H = bh.Initializeheap();
	char ch;
	while (1)
	{
		cout << "Operations on binomial heap:" << endl << "1)Insert element" << endl << "2)Delete minimum"  << endl << "3)Display Heap" << endl << "4)Exit" << endl << "Enter action: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter the element: ";
			cin >> m;
			p = bh.Create_node(m);
			H = bh.Insert(H, p);
			break;
		case 2:
			H = bh.Delete_Min(H);
			break;
		case 3:
			cout << "The Heap is: " << endl;
			bh.Display(H);
			break;
		case 4:
			exit(1);
		default:
			cout << "Wrong Choice";
		}
	}
	return 0;
}