#include <iostream>
#include <ctime>

/*
	��������
	�����������: ��������
	������ ������: ����������
	���������: ���-�� ������� � ������ �� ������
*/

struct Node
{
	static int s_n;	// ���������� �����
	char tag;		// ��� ����
	Node* left;		// ����� ����
	Node* right;	// ������ ����
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

	// ���������� ������ ������
	Node* getRoot() const { return root; }

	// ����� ������ � �������(����������)
	void inDepth()
	{
		std::cout << "���� ������ � �������: ";
		clock_t start = clock();
		inDepth(root);
		clock_t end = clock();
		std::cout << "\n����� � �������: " << (end - start) / 1000.0 << " sec\n";
	}

	// �������� ������
	void createTree(int nodes)
	{
		std::cout << "�������� ������: ";
		clock_t start = clock();

		// �������� �����
		if (!root)
			root = new Node();

		// �������� N �����
		for (int i = 0; i < nodes; i++)
		{
			Node* temp = root;						// ������� ��������� ���� ��� ������ ������
			int direction = rand() % 2;				// ��������� �����������
			while (temp->left && temp->right)		// ���� �� ����� ������ ����(�������� ����� ������)
			{
				// ��������� �����������
				direction = rand() % 2;				// �� ������ ���� ������������ � �������� �������
				if (direction)
					temp = temp->left;				// ������� ������
				else
					temp = temp->right;				// ������� �������
			}

			if (!temp->left)		
				temp->left = new Node();			// ���� ���� ���� �����, ������� ��� ����� ����
			else
				temp->right = new Node();			// ���� ���� ������ ����, ������� ��� ����� ����
		}
		clock_t end = clock();
		std::cout << (end - start) / 1000.0 << " sec\n";
	}

	// ����� ������ � �������
	void printTree()
	{
		clock_t start = clock();
		std::cout << "---------������------------\n";

		if (!root)
		{
			std::cout << "������ ������\n";
			return;
		}
		else
		{
			printNode(root, 0);
		}

		std::cout << "---------------------------\n";
		clock_t end = clock();
		std::cout << "����� ������: " << (end - start) / 1000.0 << " sec\n";
	}

	// ������������ ������
	void recreateTree(int nodes)
	{
		deleteTree();
		createTree(nodes);
	}

	// ���� ������
	void test(int nodes)
	{
		std::cout << "-------���� �� " << nodes << " ������-------\n";
		clock_t start = clock();
		recreateTree(nodes);
		printTree();
		inDepth();
		nodeParents();
		clock_t end = clock();
		std::cout << "����� ����� �����: " << (end - start) / 1000.0 << " sec\n";
		std::cout << "----------------------------------\n\n";
	}

	// �������� ������
	void deleteTree()
	{
		deleteNode(root);
		Node::s_n = 0;
		root = nullptr;
	}

	// ����� ���������� ������� � ������ �� ������ ������
	void nodeParents()
	{
		std::cout << "����� ������� ������ �� ������:\n";
		clock_t start = clock();
		calculateNodeParents(root, 0);
		clock_t end = clock();
		std::cout << "����� ���������� ������� � ������ �������: ";
		std::cout << (end - start) / 1000.0 << " sec\n";
	}
private:
	// �������� ����
	void deleteNode(Node* node)
	{
		if (node)
		{
			deleteNode(node->left);
			deleteNode(node->right);
			delete node;
		}
	}

	// ����� ������� ����
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

	// ����� � �������
	void inDepth(Node* node) const
	{
		if (node != nullptr)
		{
			inDepth(node->left);
			std::cout << node->tag << " -> ";
			inDepth(node->right);
		}
	}

	// ���������� ���������� ������� ������� ����
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
	Node* root; // ������ ������
};

// ����������� ����������
int Node::s_n = 0;

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	BinaryTree tree;

	// ����� �������� � ���������� ����������
	//tree.test(5);
	//tree.test(10);
	tree.test(15);
	//tree.test(20);
	//tree.test(40);
	//tree.test(60);

	return 0;
}