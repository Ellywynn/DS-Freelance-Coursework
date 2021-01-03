#include <iostream>
#include <ctime>
#include <vector>

// ����������� ������ ���������
struct List
{
	List* next;			// ��������� �� ��������� ������� ���������
	char c;				// ������� ���������
	List() = default;
	List(char symbol, List* nextNode = nullptr) : next(nextNode), c(symbol) {	}
	~List() { delete next; }
};

// ������������� ��������� ��� ������
void test1()
{
	std::cout << "-----������������� ��������� ��� ������-----\n";
	clock_t start = clock();

	// ���������
	const int U = 26;					

	// ������� ���������
	char A[U] = { "axczbmfdsg" };
	char B[U] = { "zxcvbnmsdfz" };
	char C[U] = { "ghsdkflj" };
	char result[U] = {};

	std::cout << "�������� ���������:\n";
	std::cout << "A: " << A << '\n';
	std::cout << "B: " << B << '\n';
	std::cout << "C: " << C << '\n';

	// ������� ����������� ���� ��������
	int index = 0;
	for (int i = 0; i < U; i++)
	{
		for (int j = 0; j < U; j++)
		{
			// ���� �������� ����������, ��������� �� � ���������
			if (B[j] == A[i])
			{
				result[index] = A[i];
				index++;
				break;
			}
		}
	}

	std::cout << "A & B: " << result << '\n';

	for (int i = 0; i < U; i++)
		result[i] = '\0';

	// ������� ����������� ���� ��������
	index = 0;
	for (int i = 0; i < U; i++)
	{
		for (int j = 0; j < U; j++)
		{
			// ���� �������� ����������, ��������� �� � ���������
			if (C[j] == A[i])
			{
				result[index] = A[i];
				index++;
				break;
			}
		}
	}

	std::cout << "A & C: " << result << '\n';

	clock_t end = clock();
	std::cout << "�����: " << (end - start) / 1000.0 << " sec\n\n";
}

// ������������� ��������� ��� ������
void test2()
{
	std::cout << "-----������������� ��������� ��� ������-----\n";
	clock_t start = clock();

	// ���������� �������������� ���������
	List A('q', new List('w', new List('e', new List('r', new List('z', new List('l'))))));		// qwerw
	List B('z', new List('e', new List('c', new List('w', new List('k')))));					// zecw
	List C('f', new List('g', new List('j', new List('l',
		new List('p', new List('b', new List('q')))))));										// fgjlpbq
	
	// ��������� ����������
	List* result = new List();
	List* temp = result;

	std::cout << "�������� ���������:\n";

	std::cout << "A: ";
	for (List* l = &A; l; l = l->next)
		std::cout << l->c << " ";
	std::cout << "\nB: ";
	for (List* l = &B; l; l = l->next)
		std::cout << l->c << " ";
	std::cout << "\nC: ";
	for (List* l = &C; l; l = l->next)
		std::cout << l->c << " ";

	// ������� ����������� ���� ��������
	for (List* l1 = &A; l1; l1 = l1->next)
	{
		for (List* l2 = &B; l2; l2 = l2->next)
		{
			// ���� �������� ���������, ��������� �� � ��������� ����������
			if (l1->c == l2->c)
			{
				temp->c = l2->c;
				temp->next = new List();
				temp = temp->next;
			}
		}
	}

	std::cout << "\nA & B: ";

	for (List* l1 = result; l1; l1 = l1->next)
		std::cout << l1->c << ' ';

	// ������� ��������� � ����������� ���������
	delete result;
	result = new List();

	temp = result;
	// ������� ����������� ���� ��������
	for (List* l1 = &A; l1; l1 = l1->next)
	{
		for (List* l2 = &C; l2; l2 = l2->next)
		{
			// ���� �������� ���������, ��������� �� � ��������� ����������
			if (l1->c == l2->c)
			{
				temp->c = l2->c;
				temp->next = new List();
				temp = temp->next;
			}
		}
	}
	std::cout << "\nA & C: ";

	for (List* l1 = result; l1; l1 = l1->next)
		std::cout << l1->c << ' ';
	std::cout << '\n';
	clock_t end = clock();
	std::cout << "�����: " << (end - start) / 1000.0 << " sec\n\n";
}

// ������������� ��������� ��� ������ �����
void test3()
{
	std::cout << "-----������������� ��������� ��� ������ �����-----\n";
	clock_t start = clock();

	// ������� ��������� � �������������� ���
	const int U = 26;
	char uni[U + 1];
	for (int i = 0; i < U; i++)
		uni[i] = 'a' + i;

	// ������� ���������(�������������� ��� ���� ������)
	std::vector<bool> A(U, 0);
	std::vector<bool> B(U, 0);
	std::vector<bool> C(U, 0);

	// �������������� ���������
	A[uni[22] - 'a'] = 1;
	A[uni[5] - 'a'] = 1;
	A[uni[8] - 'a'] = 1;
	A[uni[9] - 'a'] = 1;
	A[uni[18] - 'a'] = 1;
	A[uni[14] - 'a'] = 1;

	B[uni[4] - 'a'] = 1;
	B[uni[2] - 'a'] = 1;
	B[uni[9] - 'a'] = 1;
	B[uni[5] - 'a'] = 1;
	B[uni[8] - 'a'] = 1;
	B[uni[7] - 'a'] = 1;

	C[uni[9] - 'a'] = 1;
	C[uni[18] - 'a'] = 1;
	C[uni[14] - 'a'] = 1;
	C[uni[3] - 'a'] = 1;
	C[uni[1] - 'a'] = 1;
	C[uni[2] - 'a'] = 1;
	C[uni[0] - 'a'] = 1;
	C[uni[10] - 'a'] = 1;
	C[uni[25] - 'a'] = 1;

	std::cout << "�������� ���������: \n";
	std::cout << "A: ";
	for (int i = 0; i < U; i++)
		std::cout << A[i] << " ";
	std::cout << "= ";
	for (int i = 0; i < U; i++)
		if (A[i] && uni[i])
			std::cout << uni[i] << " ";

	std::cout << "\nB: ";
	for (int i = 0; i < U; i++)
		std::cout << B[i] << " ";
	std::cout << "= ";
	for (int i = 0; i < U; i++)
		if (B[i] && uni[i])
			std::cout << uni[i] << " ";

	std::cout << "\nC: ";
	for (int i = 0; i < U; i++)
		std::cout << C[i] << " ";
	std::cout << "= ";
	for (int i = 0; i < U; i++)
		if (C[i] && uni[i])
			std::cout << uni[i] << " ";
	std::cout << '\n';

	std::cout << "A & B: ";
	for (int i = 0; i < U; i++)
	{
		if (A[i] && B[i])
			std::cout << uni[i] << " ";
	}
	std::cout << "\nA & C: ";
	for (int i = 0; i < U; i++)
	{
		if (A[i] && C[i])
			std::cout << uni[i] << " ";
	}
	std::cout << '\n';

	clock_t end = clock();
	std::cout << "�����: " << (end - start) / 1000.0 << " sec\n\n";
}

// ������������� ��������� ��� �������� �����
void test4()
{
	std::cout << "-----������������� ��������� ��� �������� �����-----\n";
	clock_t start = clock();

	// �������� ����������
	const int U = 26;
	char uni[U + 1] = {};
	for (int i = 0; i < U; i++)
		uni[i] = 'a' + i;

	// �������� �������� � �� ������������� ����� ���������� ������
	int A = 0;
	A |= (1 << (uni[2] - 'a'));
	A |= (1 << (uni[4] - 'a'));
	A |= (1 << (uni[5] - 'a'));
	A |= (1 << (uni[18] - 'a'));
	A |= (1 << (uni[7] - 'a'));
	A |= (1 << (uni[22] - 'a'));

	int B = 0;
	B |= (1 << (uni[7] - 'a'));
	B |= (1 << (uni[5] - 'a'));
	B |= (1 << (uni[3] - 'a'));
	B |= (1 << (uni[18] - 'a'));
	B |= (1 << (uni[22] - 'a'));
	B |= (1 << (uni[14] - 'a'));
	B |= (1 << (uni[10] - 'a'));
	B |= (1 << (uni[0] - 'a'));

	int C = 0;
	C |= (1 << (uni[0] - 'a'));
	C |= (1 << (uni[5] - 'a'));
	C |= (1 << (uni[2] - 'a'));
	C |= (1 << (uni[7] - 'a'));
	C |= (1 << (uni[13] - 'a'));

	std::cout << "�������� ���������:\n";

	std::cout << "A: ";
	for (int i = 0; i < U; i++)
		if ((A >> i) & 1)
			std::cout << uni[i];

	std::cout << "\nB: ";
	for (int i = 0; i < U; i++)
		if ((B >> i) & 1)
			std::cout << uni[i];

	std::cout << "\nC: ";
	for (int i = 0; i < U; i++)
		if ((C >> i) & 1)
			std::cout << uni[i];

	std::cout << '\n';

	// ���������� ����������� ��������
	std::cout << "A & B: ";
	for (int i = 0; i < U; i++)
		if ((A >> i) & 1 && (B>>i) & 1)
			std::cout << uni[i];

	std::cout << "\nA & C: ";
	for (int i = 0; i < U; i++)
		if ((A >> i) & 1 && (C >> i) & 1)
			std::cout << uni[i];

	std::cout << '\n';

	clock_t end = clock();
	std::cout << "�����: " << (end - start) / 1000.0 << " sec\n\n";
}

int main()
{
	setlocale(LC_ALL, "Rus");
	/*
		���������, ���������� �����, ����� ��� ��������� A � ������ �� �������� B, C � D
	*/

	// ������������� ��������� ��� ������
	test1();

	// ������������� ��������� ��� ������
	test2();

	// ������������� ��������� ������������ �� ���������
	test3();

	// ������������� ��������� ��� �������� �����
	test4();

	return 0;
}