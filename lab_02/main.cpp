#include <iostream>
#include <vector>
#include <stack>
#include <queue>

namespace Graph {

	struct Edges {

		int vertexInitial;
		int vertexFinal;
	};

	// Out
	void outputMoveChain(const std::vector<int>& chain);

	//V — количество вершин
	//E — количество рёбер

	//Список смежности:
	//	время: O(V+E)
	//	память: O(V+E)

	//Матрица смежности:
	//	время: O(V^2)
	//	память: O(V^2)

	//Список рёбер:
	//	время: O(VE)
	//	память: O(E)

	// Convert to List AdjacencyGraph

	std::vector<std::vector<int>> convertToListAdjacencyGraph(std::vector<Graph::Edges> listEdgesGraph, int size);

	// Breadth First Search

	std::vector<int> bfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start, int& O);
	std::vector<int> bfs(std::vector<std::vector<int>> listAdjacencyGraph, int start, int& O);

	// Depth First Search
	std::vector<int> dfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start, int& O);
	std::vector<int> dfs(std::vector<std::vector<int>> listAdjacencyGraph, int start, int& O);
}

int main() {

	setlocale(LC_ALL, "ru");

	std::vector<std::vector<bool>> matrixAdjacencyGraph = {

	   //1,2,3,4,5,6,7,8,9,10
		{0,1,0,0,1,0,0,0,0,0}, //1
		{1,0,0,0,0,0,1,1,0,0}, //2
		{0,0,0,0,0,0,0,1,0,0}, //3
		{0,0,0,0,0,1,0,0,1,0}, //4
		{1,0,0,0,0,1,0,0,0,0}, //5
		{0,0,0,1,1,0,0,0,1,0}, //6
		{0,1,0,0,0,0,0,1,0,0}, //7
		{0,1,1,0,0,0,1,0,0,0}, //8
		{0,0,0,1,0,1,0,0,0,1}, //9
		{0,0,0,0,0,0,0,0,1,0}  //10
	};

	std::vector<std::vector<int>> listAdjacencyGraph = {

		{2,5}, //1
		{1,7,8}, //2
		{8}, //3
		{6,9}, //4
		{1,6}, //5
		{4,5,9}, //6
		{2,8}, //7
		{2,3,7}, //8
		{4,6,10}, //9
		{9}, //10
	};

	std::vector<Graph::Edges> listEdgesGraph = {

		{1,2}, {1,5},
		{2,7}, {2,8},
		{3,8}, {4,6},
		{4,9}, {5,6},
		{6,9}, {7,8},
		{9,10}
	};

	int o1{}, o2{}, o3{}, o4{}, o5{}, o6{};

	std::cout << "Матрица смежности (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(matrixAdjacencyGraph, 1, o2));

	std::cout << "O-большое: " << o2 << std::endl;

	std::cout << "Список смежности (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(listAdjacencyGraph, 1, o1));

	std::cout << "O-большое: " << o1 << std::endl;

	std::cout << "Список рёбер (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(listAdjacencyGraph, 1, o3));

	std::cout << "O-большое: " << o3 << std::endl;
	
	std::cout << "Матрица смежности (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(matrixAdjacencyGraph, 1, o4));

	std::cout << "O-большое: " << o4 << std::endl;

	std::cout << "Список смежности (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(listAdjacencyGraph, 1, o5));

	std::cout << "O-большое: " << o5 << std::endl;

	std::cout << "Список рёбер (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(listAdjacencyGraph, 1, o6));
	std::cout << "O-большое: " << o6 << std::endl;

	return 0;
}

// Convert

std::vector<std::vector<int>> Graph::convertToListAdjacencyGraph(std::vector<Graph::Edges> listEdgesGraph, int size)
{
	std::vector<std::vector<int>> listAdjacencyGraph(size);

	for (int i = 0, j = listEdgesGraph.size(); i < j; i++) {

		int tmp = listEdgesGraph.at(i).vertexInitial - 1;
		listAdjacencyGraph.at(tmp).push_back(listEdgesGraph.at(i).vertexFinal);
	}

	return listAdjacencyGraph;
}

// Out

void Graph::outputMoveChain(const std::vector<int>& chain) {

	for (auto vertex : chain) {

		std::cout << vertex << " --> ";
	}

	std::cout << " end.\n";
}

// List Adjacency Graph

std::vector<int> Graph::bfs(std::vector<std::vector<int>> listAdjacencyGraph, int start, int& O) {

	std::vector<bool> visitedVertex;
	std::vector<int> orderVisitingVertex;

	for (int i = 0, b = listAdjacencyGraph.size(); i < b; i++) {
		visitedVertex.push_back(false);
	}

	std::queue<int> queueVertex;
	int currentVertex{};
	O = -1;

	queueVertex.push(start);
	--start;
	visitedVertex.at(start) = true;

	while (!queueVertex.empty()) {

		currentVertex = queueVertex.front();
		orderVisitingVertex.push_back(currentVertex);
		queueVertex.pop();

		--currentVertex;

		for (int i = 0, j = listAdjacencyGraph[currentVertex].size(); i < j; i++) {

			++O;

			int tmp = listAdjacencyGraph[currentVertex].at(i) - 1;

			if (!visitedVertex.at(tmp)) {

				queueVertex.push(listAdjacencyGraph[currentVertex].at(i));
				visitedVertex.at(tmp) = true;

			}
		}
	}

	return orderVisitingVertex;
}

std::vector<int> Graph::dfs(std::vector<std::vector<int>> listAdjacencyGraph, int start, int& O) {

	std::vector<bool> visitedVertex;
	std::vector<int> orderVisitingVertex;

	for (int i = 0, b = listAdjacencyGraph.size(); i < b; i++) {
		visitedVertex.push_back(false);
	}

	std::queue<int> stackVertex;
	int currentVertex{};
	O = -1;

	stackVertex.push(start);
	--start;
	visitedVertex.at(start) = true;

	while (!stackVertex.empty()) {

		currentVertex = stackVertex.front();
		orderVisitingVertex.push_back(currentVertex);
		stackVertex.pop();

		--currentVertex;

		for (int i = listAdjacencyGraph[currentVertex].size() - 1; i >= 0; i--) {

			++O;

			int tmp = listAdjacencyGraph[currentVertex].at(i) - 1;

			if (!visitedVertex.at(tmp)) {

				stackVertex.push(listAdjacencyGraph[currentVertex].at(i));
				visitedVertex.at(tmp) = true;

			}
		}
	}

	return orderVisitingVertex;
}

// Matrix Adjacency Graph

std::vector<int> Graph::bfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start, int& O) {

	std::vector<bool> visitedVertex;
	std::vector<int> orderVisitingVertex;

	for (int i = 0, b = matrixAdjacencyGraph.size(); i < b; i++) {
		visitedVertex.push_back(false);
	}

	std::queue<int> queueVertex;
	int currentVertex{};
	O = 0;

	queueVertex.push(start);
	--start;
	visitedVertex.at(start) = true;


	while (!queueVertex.empty()) {

		currentVertex = queueVertex.front();
		orderVisitingVertex.push_back(currentVertex);
		queueVertex.pop();

		--currentVertex;

		for (int i = 0; i < matrixAdjacencyGraph.at(currentVertex).size(); i++) {

			++O;

			if (matrixAdjacencyGraph.at(currentVertex).at(i)) {

				int tmp = i + 1;

				if (!visitedVertex.at(i)) {

					queueVertex.push(tmp);
					visitedVertex.at(i) = true;

				}
			}
		}
	}

	return orderVisitingVertex;
}

std::vector<int> Graph::dfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start, int& O) {

	std::vector<bool> visitedVertex;
	std::vector<int> orderVisitingVertex;

	for (int i = 0, b = matrixAdjacencyGraph.size(); i < b; i++) {
		visitedVertex.push_back(false);
	}

	std::stack<int> stackVertex;
	int currentVertex{};
	O = 0;

	stackVertex.push(start);
	--start;
	visitedVertex.at(start) = true;

	while (!stackVertex.empty()) {

		currentVertex = stackVertex.top();
		orderVisitingVertex.push_back(currentVertex);
		stackVertex.pop();

		--currentVertex;

		for (int i = matrixAdjacencyGraph.at(currentVertex).size() - 1; i >= 0; i--) {

			++O;

			if (matrixAdjacencyGraph.at(currentVertex).at(i)) {

				int tmp = i + 1;

				if (!visitedVertex.at(i)) {

					stackVertex.push(tmp);
					visitedVertex.at(i) = true;
				}
			}
		}
	}
	return orderVisitingVertex;
}