#include <iostream>

class SetArray
{
public:
	// конструктор по умолчанию
	SetArray(char t)
	{
		// создается пустое множество:
		N = 0;				// мощность равна нулю
		S = nullptr;		// элементов нет
		tag = t;			// буква множества 
	}
	// конструктор копирования
	SetArray(const SetArray& s)
	{
		// копируем все содержимое множества 
		N = s.N;
		S = new char[N];
		for (int i = 0; i < N; i++)
			S[i] = s.S[i];
		tag = s.tag;
	}
	// деструктор
	~SetArray()
	{
		delete[] S;		// удаляем элементы
	}

	// операция объединения множеств
	SetArray operator &(const SetArray& s) const
	{
		// создаем временное множество
		SetArray temp('U');
		// находим одинаковые элементы двух множеств
		for (int i = 0; i < N; i++)
			for (int j = 0; j < s.power(); j++)
				if (S[i] == s[j])	// если элементы равны
				{
					// добавляем этот элемент в множество и завершаем цикл с данной буквой
					temp.addElement(s[j]);
					break;
				}

		return temp; // возвращаем объект временного множества
	}

	// оператор доступа к элементам множества по индексу
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

	// мощность множества
	int power() const { return N; }

	// добавляет элемент в множество
	void addElement(const char element)
	{
		// если такой элемент уже есть в множестве, не добавляем его
		for (int i = 0; i < N; i++)
			if (S[i] == element)
				return;

		// если такого элемента нет, создаем новый массив с дополнительным слотом под новый элемент
		char* newSet = new char[N + 1];

		// копируем старый массив в новый
		for (int i = 0; i < N; i++)
			newSet[i] = S[i];

		newSet[N] = element;	// добавляем новый элемент
		delete[] S;				// удаляем старый массив
		S = newSet;				// присваиваем указатель на новый массив
		N++;					// увеличиваем мощность
	}

	// вывод множества 
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

	// очищение множества(удаление всех его элементов)
	void clear()
	{
		delete[] S;
		S = nullptr;
		N = 0;
	}
private:
	int N;			// мощность множества
	char* S;		// элементы множества
	char tag;		// имя множества
};

class SetList
{
public:
	SetList() : list(nullptr) {};
	~SetList() = default;

	void addElement(char c)
	{
		// если список пуст, добавляем первый объект
		if (!list)
		{
			list = new List(c);
			return;
		}
		// если в списке уже есть элементы, то находим последний
		// и добавляем в конец списка новый элемент
		List* temp = list;
		while (temp->next != nullptr)
		{
			// если такой элемент уже есть в множестве, то не добавляем его
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
		// проходим по всему списку и выводим элемент
		while (temp)
		{
			std::cout << temp->c << ' ';
			temp = temp->next;
		}
		std::cout << '\n';
	}

	SetList operator &(const SetList& s) const
	{
		// создаем временное множество
		SetList temp;

		// находим одинаковые элементы двух множеств
		for (List* l1 = list; l1; l1 = l1->next)
		{
			for (List* l2 = s.list; l2; l2 = l2->next)
				if (l1->c == l2->c)	// если элементы равны
				{
					// добавляем этот элемент в множество и завершаем цикл с данной буквой
					temp.addElement(l2->c);
					break;
				}
		}

		return temp; // возвращаем объект временного множества
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
	// односвязный список множества
	struct List
	{
		List* next;			// указатель на следующий элемент множества
		char c;				// элемент множества
		List() = default;
		List(char symbol, List* nextNode = nullptr) : next(nextNode), c(symbol) {	}
		~List() { delete next; }
	};

	List* list;
};

// Представление множества как массив
void test1()
{
	std::cout << "-----Представление множества как массив-----\n";
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

	std::cout << "Исходные множества:\n";
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
	std::cout << "Время: " << (end - start) / 1000.0 << " sec\n";
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