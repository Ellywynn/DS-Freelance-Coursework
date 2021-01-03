#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <fstream>

/*
	ѕостроение глубинного ст€гивающего леса дл€ неориентированного графа
*/

// вершина графа
struct Node
{
	static int maxNode;		// максимальна€ вершина
	int n;					// номер вершины
	Node(int num) : n(num) {
		// определ€ем максимальную вершину
		if (n > maxNode) maxNode = n;
	}
};

// ребро графа
struct Edge
{
	Node n1, n2;	// вершины ребра
	Edge(int v1, int v2) : n1(v1), n2(v2) {}
	// оператор сравнени€ ребер
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
		// если такое ребро уже есть в графе, то не добавл€ем переданное
		for (size_t i = 0; i < edges.size(); i++)
			if (edges[i] == edge)
				break;
		// иначе добавл€ем ребро в граф
		edges.push_back(edge);
		// если была добавлена нова€ вершина, то расшир€ем матрицу смежности
		if (matrix.size() < Node::maxNode)
		{
			matrix.resize(Node::maxNode);
			for (int i = 0; i < matrix.size(); i++)
				matrix[i].resize(matrix.size());
		}

		// добавл€ем инцидентность в матрицу смежности данное ребро
		matrix[edge.n1.n - 1][edge.n2.n - 1] = 1;
		matrix[edge.n2.n - 1][edge.n1.n - 1] = 1;
	}

	// выводит матрицу смежности графа
	void printMatrix()
	{
		std::cout << "ћатрица смежности графа:\n";
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

	// поиск в глубину
	void DFS()
	{
		// обновл€ем размер массива посещенных вершин
		visited.resize(Node::maxNode, false);
		std::vector<int> DFS_nodes;		// путь поиска в глубину
		DFS(DFS_nodes);					// поиск в глубину
		printDFSpath(DFS_nodes);		// вывод пути
	}

	// удаление графа(очищение)
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
			std::cout << "“ест " << filename << ":\n";
			int v1, v2, count = 0;
			std::cout << "–ебра:\n";
			while(file >> v1 >> v2)
			{
				count++;
				std::cout << v1 << " " << v2 << '\n';
				addEdge(v1, v2);
			}
			std::cout << " оличество ребер: " << count << "\n\n";
			printMatrix();
			DFS();
			clear();
			clock_t end = clock();
			std::cout << "¬рем€: " << (end - start) / 1000.0 << '\n';
			std::cout << "-----------------------------------\n";
		}
		else {
			std::cout << "Ќевозможно открыть файл " << filename << '\n';
		}

		file.close();
	}
private:
	// реализаци€ поиска в глубину
	void DFS(std::vector<int>& path, int start = 0)
	{
		visited[start] = true; // текущую вершину помечаем посещенной

		// дл€ каждой вершины
		for (int i = 0; i < matrix.size(); i++)
		{
			// если матрица смежности не равна нулю(есть ребро)
			// и эта вершина не посещена, то проводим поиск дальше(рекурсивно)
			if (matrix[start][i] != 0 && !visited[i])
				DFS(path, i);
		}

		// добавл€ем вершину в список пути
		path.push_back(start + 1);
	}

	// выводит путь поиска в глубину
	void printDFSpath(std::vector<int>& dfs)
	{
		std::cout << "√лубинный ст€гивающий лес неориентированного графа:\n";
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
	std::vector<Edge> edges;				// ребра графа
	std::vector<std::vector<int>> matrix;	// матрица смежности
	std::vector<bool> visited;				// посещенные вершины поиска в глубину
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