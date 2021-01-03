#include <iostream>

class SetArray
{
public:
	// ����������� �� ���������
	SetArray(char t)
	{
		// ��������� ������ ���������:
		N = 0;				// �������� ����� ����
		S = nullptr;		// ��������� ���
		tag = t;			// ����� ��������� 
	}
	// ����������� �����������
	SetArray(const SetArray& s)
	{
		// �������� ��� ���������� ��������� 
		N = s.N;
		S = new char[N];
		for (int i = 0; i < N; i++)
			S[i] = s.S[i];
		tag = s.tag;
	}
	// ����������
	~SetArray()
	{
		delete[] S;		// ������� ��������
	}

	// �������� ����������� ��������
	SetArray operator &(const SetArray& s) const
	{
		// ������� ��������� ���������
		SetArray temp('U');
		// ������� ���������� �������� ���� ��������
		for (int i = 0; i < N; i++)
			for (int j = 0; j < s.power(); j++)
				if (S[i] == s[j])	// ���� �������� �����
				{
					// ��������� ���� ������� � ��������� � ��������� ���� � ������ ������
					temp.addElement(s[j]);
					break;
				}

		return temp; // ���������� ������ ���������� ���������
	}

	// �������� ������� � ��������� ��������� �� �������
	char& operator[](int index)
	{
		return S[index];
	}

	const char& operator[](int index) const
	{
		return S[index];
	}

	SetArray& operator=(const SetArray& s)
	{
		N = s.N;
		S = new char[N];
		for (int i = 0; i < N; i++)
			S[i] = s.S[i];
		tag = s.tag;
		return *this;
	}

	// �������� ���������
	int power() const { return N; }

	// ��������� ������� � ���������
	void addElement(const char element)
	{
		// ���� ����� ������� ��� ���� � ���������, �� ��������� ���
		for (int i = 0; i < N; i++)
			if (S[i] == element)
				return;

		// ���� ������ �������� ���, ������� ����� ������ � �������������� ������ ��� ����� �������
		char* newSet = new char[N + 1];

		// �������� ������ ������ � �����
		for (int i = 0; i < N; i++)
			newSet[i] = S[i];

		newSet[N] = element;	// ��������� ����� �������
		delete[] S;				// ������� ������ ������
		S = newSet;				// ����������� ��������� �� ����� ������
		N++;					// ����������� ��������
	}

	// ����� ��������� 
	void print() const
	{
		std::cout << tag << ": { ";
		for (int i = 0; i < N; i++)
		{
			std::cout << S[i];
			if (i != N - 1)
				std::cout << ", ";
			else
				std::cout << " ";
		}
		std::cout << "}; Power: " << N << '\n';
	}

	// �������� ���������(�������� ���� ��� ���������)
	void clear()
	{
		delete[] S;
		S = nullptr;
		N = 0;
	}
private:
	int N;			// �������� ���������
	char* S;		// �������� ���������
	char tag;		// ��� ���������
};

class SetList
{
public:
	SetList() : list(nullptr) {};
	~SetList() = default;

	void addElement(char c)
	{
		// ���� ������ ����, ��������� ������ ������
		if (!list)
		{
			list = new List(c);
			return;
		}
		// ���� � ������ ��� ���� ��������, �� ������� ���������
		// � ��������� � ����� ������ ����� �������
		List* temp = list;
		while (temp->next != nullptr)
		{
			// ���� ����� ������� ��� ���� � ���������, �� �� ��������� ���
			if (temp->c == c)
			{
				std::cout << "HEHE\n";
				return;
			}
			temp = temp->next;
		}

		temp->next = new List(c);
	}

	void print()
	{
		List* temp = list;
		// �������� �� ����� ������ � ������� �������
		while (temp)
		{
			std::cout << temp->c << ' ';
			temp = temp->next;
		}
		std::cout << '\n';
	}

	SetList operator &(const SetList& s) const
	{
		// ������� ��������� ���������
		SetList temp;

		// ������� ���������� �������� ���� ��������
		for (List* l1 = list; l1; l1 = l1->next)
		{
			for (List* l2 = s.list; l2; l2 = l2->next)
				if (l1->c == l2->c)	// ���� �������� �����
				{
					// ��������� ���� ������� � ��������� � ��������� ���� � ������ ������
					temp.addElement(l2->c);
					break;
				}
		}

		return temp; // ���������� ������ ���������� ���������
	}

	SetList& operator=(const SetList& s)
	{
		List* l1 = s.list;
		List* l2 = list;
		while (l1)
		{
			l2->next = new List(l1->c);
			l1 = l1->next;
			l2 = l2->next;
		}
		return *this;
	}
private:
	// ����������� ������ ���������
	struct List
	{
		List* next;			// ��������� �� ��������� ������� ���������
		char c;				// ������� ���������
		List() = default;
		List(char symbol, List* nextNode = nullptr) : next(nextNode), c(symbol) {	}
		~List() { delete next; }
	};

	List* list;
};

// ������������� ��������� ��� ������
void test1()
{
	std::cout << "-----������������� ��������� ��� ������-----\n";
	clock_t start = clock();
	SetArray A('A'), B('B'), C('C'), D('D'), E('E');

	A.addElement('a');
	A.addElement('b');
	A.addElement('c');
	A.addElement('d');
	A.addElement('z');
	A.addElement('x');
	A.addElement('c');

	B.addElement('b');
	B.addElement('d');
	B.addElement('f');

	for (int i = 0; i < 10; i++)
		C.addElement('z' - i);

	D.addElement('h');
	D.addElement('c');

	std::cout << "�������� ���������:\n";
	A.print();
	B.print();
	C.print();
	D.print();

	std::cout << "A & B: ";
	E = A & B;
	E.print();

	std::cout << "A & C: ";
	E = A & C;
	E.print();

	std::cout << "A & D: ";
	E = A & D;
	E.print();

	clock_t end = clock();
	std::cout << "�����: " << (end - start) / 1000.0 << " sec\n";
}

void test2()
{
	SetList A, B, C;
	int count;
	count = std::rand() % 6 + 5;
	for (int i = 0; i < count; i++)
		A.addElement('a' + std::rand() % 26);
	count = std::rand() % 10 + 5;
	for (int i = 0; i < count; i++)
		B.addElement('a' + std::rand() % 26);
	count = std::rand() % 16 + 5;
	for (int i = 0; i < count; i++)
		C.addElement('a' + std::rand() % 26);

	std::cout << "A: ";
	A.print();
	std::cout << "B: ";
	B.print();
	std::cout << "C: ";
	C.print();

	std::cout << "A & B: ";
	SetList result = A & B;
	result.print();

	std::cout << "A & C: ";
	result = A & C;
	result.print();
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	test2();
	return 0;
}