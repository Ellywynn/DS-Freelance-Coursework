#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <fstream>

/*
	���������� ���������� ������������ ���� ��� ������������������ �����
*/

// ������� �����
struct Node
{
	static int maxNode;		// ������������ �������
	int n;					// ����� �������
	Node(int num) : n(num) {
		// ���������� ������������ �������
		if (n > maxNode) maxNode = n;
	}
};

// ����� �����
struct Edge
{
	Node n1, n2;	// ������� �����
	Edge(int v1, int v2) : n1(v1), n2(v2) {}
	// �������� ��������� �����
	bool operator==(const Edge& e) const
	{
		return ((n1.n == e.n1.n) && (n2.n == e.n2.n) || (n1.n == e.n2.n && n2.n == e.n1.n));
	}
};

class Graph
{
public:
	Graph() = default;
	~Graph() = default;

	void addEdge(int v1, int v2)
	{
		addEdge(Edge(v1, v2));
	}

	void addEdge(const Edge& edge)
	{
		// ���� ����� ����� ��� ���� � �����, �� �� ��������� ����������
		for (size_t i = 0; i < edges.size(); i++)
			if (edges[i] == edge)
				break;
		// ����� ��������� ����� � ����
		edges.push_back(edge);
		// ���� ���� ��������� ����� �������, �� ��������� ������� ���������
		if (matrix.size() < Node::maxNode)
		{
			matrix.resize(Node::maxNode);
			for (int i = 0; i < matrix.size(); i++)
				matrix[i].resize(matrix.size());
		}

		// ��������� ������������� � ������� ��������� ������ �����
		matrix[edge.n1.n - 1][edge.n2.n - 1] = 1;
		matrix[edge.n2.n - 1][edge.n1.n - 1] = 1;
	}

	// ������� ������� ��������� �����
	void printMatrix()
	{
		std::cout << "������� ��������� �����:\n";
		std::cout << "# ";
		for (int i = 0; i < matrix.size(); i++)
		{
			std::cout << i + 1 << " ";
		}
		std::cout << '\n';
		for (size_t i = 0; i < matrix.size(); i++)
		{
			std::cout << i + 1 << " ";
			for (size_t j = 0; j < matrix.size(); j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	// ����� � �������
	void DFS()
	{
		// ��������� ������ ������� ���������� ������
		visited.resize(Node::maxNode, false);
		std::vector<int> DFS_nodes;		// ���� ������ � �������
		DFS(DFS_nodes);					// ����� � �������
		printDFSpath(DFS_nodes);		// ����� ����
	}

	// �������� �����(��������)
	void clear()
	{
		for (int i = 0; i < edges.size(); i++)
			edges.clear();
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].clear();
		matrix.clear();
		visited.clear();
	}

	void test(const std::string& filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			clock_t start = clock();
			std::cout << "-----------------------------------\n";
			std::cout << "���� " << filename << ":\n";
			int v1, v2, count = 0;
			std::cout << "�����:\n";
			while(file >> v1 >> v2)
			{
				count++;
				std::cout << v1 << " " << v2 << '\n';
				addEdge(v1, v2);
			}
			std::cout << "���������� �����: " << count << "\n\n";
			printMatrix();
			DFS();
			clear();
			clock_t end = clock();
			std::cout << "�����: " << (end - start) / 1000.0 << '\n';
			std::cout << "-----------------------------------\n";
		}
		else {
			std::cout << "���������� ������� ���� " << filename << '\n';
		}

		file.close();
	}
private:
	// ���������� ������ � �������
	void DFS(std::vector<int>& path, int start = 0)
	{
		visited[start] = true; // ������� ������� �������� ����������

		// ��� ������ �������
		for (int i = 0; i < matrix.size(); i++)
		{
			// ���� ������� ��������� �� ����� ����(���� �����)
			// � ��� ������� �� ��������, �� �������� ����� ������(����������)
			if (matrix[start][i] != 0 && !visited[i])
				DFS(path, i);
		}

		// ��������� ������� � ������ ����
		path.push_back(start + 1);
	}

	// ������� ���� ������ � �������
	void printDFSpath(std::vector<int>& dfs)
	{
		std::cout << "��������� ����������� ��� ������������������ �����:\n";
		for (int i = 0; i < dfs.size(); i++)
		{
			if (i < dfs.size() - 1)
				std::cout << dfs[i] << " -> ";
			else
				std::cout << dfs[i];
		}
		std::cout << std::endl;
	}
private:
	std::vector<Edge> edges;				// ����� �����
	std::vector<std::vector<int>> matrix;	// ������� ���������
	std::vector<bool> visited;				// ���������� ������� ������ � �������
};

int Node::maxNode = 0;

int main()
{
	setlocale(LC_ALL, "Rus");
	Graph graph;
	graph.test("graph_test1.txt");
	graph.test("graph_test2.txt");
	graph.test("graph_test3.txt");
	return 0;
}