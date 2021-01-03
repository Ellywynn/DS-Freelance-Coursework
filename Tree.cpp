#include <iostream>
#include <ctime>

/*
	ƒвоичное
	«ависимость: ќбратна€
	—пособ обхода: ¬нутренний
	¬ычислить: кол-во предков у каждой из вершин
*/

struct Node
{
	static int s_n;	// количество узлов
	char tag;		// им€ узла
	Node* left;		// левый узел
	Node* right;	// правый узел
	Node() : left(nullptr), right(nullptr)
	{
		tag = 'A' + s_n;
		s_n++;
	}
};

class BinaryTree
{
public:
	BinaryTree()
		:root(nullptr)
	{
	}
	~BinaryTree()
	{
		deleteTree();
	}

	// возвращает корень дерева
	Node* getRoot() const { return root; }

	// обход дерева в глубину(внутренний)
	void inDepth()
	{
		std::cout << "ѕуть обхода в глубину: ";
		clock_t start = clock();
		inDepth(root);
		clock_t end = clock();
		std::cout << "\nќбход в глубину: " << (end - start) / 1000.0 << " sec\n";
	}

	// создание дерева
	void createTree(int nodes)
	{
		std::cout << "—оздание дерева: ";
		clock_t start = clock();

		// создание корн€
		if (!root)
			root = new Node();

		// создание N узлов
		for (int i = 0; i < nodes; i++)
		{
			Node* temp = root;						// создаем временный узел дл€ обхода дерева
			int direction = rand() % 2;				// рандомное направление
			while (temp->left && temp->right)		// пока не нашли пустой узел(достигли листа дерева)
			{
				// рандомное направление
				direction = rand() % 2;				// на каждом узле поворачиваем с лучайную сторону
				if (direction)
					temp = temp->left;				// поворот налево
				else
					temp = temp->right;				// поворот направо
			}

			if (!temp->left)		
				temp->left = new Node();			// если узел пуст слева, создаем там новый узел
			else
				temp->right = new Node();			// если узел справа пуст, создаем там новый узел
		}
		clock_t end = clock();
		std::cout << (end - start) / 1000.0 << " sec\n";
	}

	// вывод дерева в консоль
	void printTree()
	{
		clock_t start = clock();
		std::cout << "---------ƒ≈–≈¬ќ------------\n";

		if (!root)
		{
			std::cout << "ƒерево пустое\n";
			return;
		}
		else
		{
			printNode(root, 0);
		}

		std::cout << "---------------------------\n";
		clock_t end = clock();
		std::cout << "¬ывод дерева: " << (end - start) / 1000.0 << " sec\n";
	}

	// пересоздание дерева
	void recreateTree(int nodes)
	{
		deleteTree();
		createTree(nodes);
	}

	// тест дерева
	void test(int nodes)
	{
		std::cout << "-------“ест из " << nodes << " вершин-------\n";
		clock_t start = clock();
		recreateTree(nodes);
		printTree();
		inDepth();
		nodeParents();
		clock_t end = clock();
		std::cout << "ќбщее врем€ теста: " << (end - start) / 1000.0 << " sec\n";
		std::cout << "----------------------------------\n\n";
	}

	// удаление дерева
	void deleteTree()
	{
		deleteNode(root);
		Node::s_n = 0;
		root = nullptr;
	}

	// поиск количества предков у каждой из вершин дерева
	void nodeParents()
	{
		std::cout << "ѕоиск предков каждой из вершин:\n";
		clock_t start = clock();
		calculateNodeParents(root, 0);
		clock_t end = clock();
		std::cout << "ѕоиск количества предков у каждой вершины: ";
		std::cout << (end - start) / 1000.0 << " sec\n";
	}
private:
	// удаление узла
	void deleteNode(Node* node)
	{
		if (node)
		{
			deleteNode(node->left);
			deleteNode(node->right);
			delete node;
		}
	}

	// вывод каждого узла
	void printNode(Node* node, int level)
	{
		if (node)
		{
			printNode(node->right, level + 1);
			for (int i = 0; i < level; i++) std::cout << "   ";
			std::cout << node->tag << std::endl;
			printNode(node->left, level + 1);
		}
	}

	// поиск в глубину
	void inDepth(Node* node) const
	{
		if (node != nullptr)
		{
			inDepth(node->left);
			std::cout << node->tag << " -> ";
			inDepth(node->right);
		}
	}

	// вычисление количества предков каждого узла
	void calculateNodeParents(Node* node, int level)
	{
		if (node)
		{
			calculateNodeParents(node->right, level + 1);
			std::cout << node->tag << ": " << level << std::endl;
			calculateNodeParents(node->left, level + 1);
		}
	}
private:
	Node* root; // корень дерева
};

// статические переменные
int Node::s_n = 0;

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	BinaryTree tree;

	// тесты деревьев с различными элементами
	//tree.test(5);
	//tree.test(10);
	tree.test(15);
	//tree.test(20);
	//tree.test(40);
	//tree.test(60);

	return 0;
}