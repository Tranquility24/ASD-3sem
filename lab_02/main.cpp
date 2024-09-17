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

	// Breadth First Search
	bool checkQueueVertex(std::queue<int> queueVertex, const int& variable);
	std::vector<int> bfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start);
	std::vector<int> bfs(std::vector<std::vector<int>> listAdjacencyGraph, int start);
	std::vector<int> bfs(std::vector<Graph::Edges> listEdgesGraph, int start);

	// Depth First Search
	bool checkStackVertex(std::stack<int> stackVertex, const int& variable);
	std::vector<int> dfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start);
	std::vector<int> dfs(std::vector<std::vector<int>> listAdjacencyGraph, int start);
	std::vector<int> dfs(std::vector<Graph::Edges> listEdgesGraph, int start);
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

		{1,2}, {2,1},
		{1,5}, {5,1},
		{2,7}, {7,2},
		{2,8}, {8,2},
		{3,8}, {8,3},
		{4,6}, {6,4},
		{4,9}, {9,4},
		{5,6}, {6,5},
		{6,9}, {9,6},
		{7,8}, {8,7},
		{9,10}, {10,9}
	};

	std::cout << "Список смежности (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(listAdjacencyGraph, 1));

	std::cout << "Матрица смежности (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(matrixAdjacencyGraph, 1));

	std::cout << "Список рёбер (bfs):" << std::endl;
	Graph::outputMoveChain(Graph::bfs(listEdgesGraph, 1));

	std::cout << "Матрица смежности (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(matrixAdjacencyGraph, 1));

	std::cout << "Список смежности (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(listAdjacencyGraph, 1));

	std::cout << "Список рёбер (dfs):" << std::endl;
	Graph::outputMoveChain(Graph::dfs(listEdgesGraph, 1));

	return 0;
}

void Graph::outputMoveChain(const std::vector<int>& chain) {

	for (auto vertex : chain) {

		std::cout << vertex << " --> ";
	}

	std::cout << " end.\n";
}

bool Graph::checkStackVertex(std::stack<int> stackVertex, const int& variable) {

	while (!stackVertex.empty()) {

		int tmp = stackVertex.top();
		stackVertex.pop();

		if (variable == tmp) {

			return false;
		}
	}

	return true;
}

bool Graph::checkQueueVertex(std::queue<int> queueVertex, const int& variable) {

	while (!queueVertex.empty()) {

		int tmp = queueVertex.front();
		queueVertex.pop();
		
		if (variable == tmp) {

			return false;
		}
	}

	return true;
}

std::vector<int> Graph::bfs(std::vector<std::vector<int>> listAdjacencyGraph, int start) {

	std::vector<int> visitedVertex;
	std::queue<int> queueVertex;
	int currentVertex{};

	queueVertex.push(start);

	while (!queueVertex.empty()) {

		currentVertex = queueVertex.front();
		queueVertex.pop();
		visitedVertex.push_back(currentVertex);

		--currentVertex;

		for (std::vector<int>::iterator vertex = listAdjacencyGraph[currentVertex].begin(); vertex != listAdjacencyGraph[currentVertex].end(); vertex++) {

			bool checkAddingVertex = true;

			for (auto checkVisited : visitedVertex) {

				*vertex == checkVisited ? checkAddingVertex = false : true;
			}

			if (checkAddingVertex && checkQueueVertex(queueVertex, *vertex)) {

				queueVertex.push(*vertex);

			}
		}
	}

	return visitedVertex;
}

std::vector<int> Graph::bfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start) {

	std::vector<int> visitedVertex;
	std::queue<int> queueVertex;
	int currentVertex{};

	queueVertex.push(start);

	while (!queueVertex.empty()) {

		currentVertex = queueVertex.front();
		queueVertex.pop();
		visitedVertex.push_back(currentVertex); 

		--currentVertex;

		for (int i = 0; i < matrixAdjacencyGraph.at(currentVertex).size(); i++) {

			if (matrixAdjacencyGraph.at(currentVertex).at(i)) {

				int tmp = i + 1;
				
				bool checkAddingVertex = true;

				for (auto checkVisited : visitedVertex) {

					tmp == checkVisited ? checkAddingVertex = false : true;
				}

				if (checkAddingVertex && checkQueueVertex(queueVertex, tmp)) {

					queueVertex.push(tmp);

				}
			}
		}
	}

	return visitedVertex;
}

std::vector<int> Graph::bfs(std::vector<Graph::Edges> listEdgesGraph, int start) {

	std::vector<int> visitedVertex;
	std::queue<int> queueVertex;
	int currentVertex{};

	queueVertex.push(start);

	--currentVertex;

	while (!queueVertex.empty()) {

		currentVertex = queueVertex.front();
		queueVertex.pop();
		visitedVertex.push_back(currentVertex);

		for (std::vector<Graph::Edges>::iterator vertex = listEdgesGraph.begin(); vertex != listEdgesGraph.end(); vertex++) {

			if ((*vertex).vertexInitial == currentVertex) {

				bool checkAddingVertex = true;

				for (auto checkVisited : visitedVertex) {

					(*vertex).vertexFinal == checkVisited ? checkAddingVertex = false : true;
				}

				if (checkAddingVertex && checkQueueVertex(queueVertex, (*vertex).vertexFinal)) {

					queueVertex.push((*vertex).vertexFinal);
				}
			}
		}
	}

	return visitedVertex;
}

std::vector<int> Graph::dfs(std::vector<std::vector<bool>> matrixAdjacencyGraph, int start)
{
	std::vector<int> visitedVertex;
	std::stack<int> stackVertex;
	int currentVertex{};

	stackVertex.push(start);

	while (!stackVertex.empty()) {

		currentVertex = stackVertex.top();
		stackVertex.pop();
		visitedVertex.push_back(currentVertex);

		--currentVertex;

		for (int i = matrixAdjacencyGraph.at(currentVertex).size() - 1; i >= 0; i--) {

			if (matrixAdjacencyGraph.at(currentVertex).at(i)) {

				int tmp = i + 1;

				bool checkAddingVertex = true;

				for (auto checkVisited : visitedVertex) {

					tmp == checkVisited ? checkAddingVertex = false : true;
				}

				if (checkAddingVertex && checkStackVertex(stackVertex, tmp)) {

					stackVertex.push(tmp);

				}
			}
		}
	}

	return visitedVertex;
}

std::vector<int> Graph::dfs(std::vector<std::vector<int>> listAdjacencyGraph, int start) {

	std::vector<int> visitedVertex;
	std::stack<int> stackVertex;
	int currentVertex{};

	stackVertex.push(start);

	while (!stackVertex.empty()) {

		currentVertex = stackVertex.top();
		stackVertex.pop();
		visitedVertex.push_back(currentVertex);

		--currentVertex;

		for (std::vector<int>::reverse_iterator vertex = listAdjacencyGraph[currentVertex].rbegin(); vertex != listAdjacencyGraph[currentVertex].rend(); vertex++) {

			bool checkAddingVertex = true;

			for (auto checkVisited : visitedVertex) {

				*vertex == checkVisited ? checkAddingVertex = false : true;
			}

			if (checkAddingVertex && checkStackVertex(stackVertex, *vertex)) {

				stackVertex.push(*vertex);
			}
		}
	}

	return visitedVertex;
}

std::vector<int> Graph::dfs(std::vector<Graph::Edges> listEdgesGraph, int start)
{
	std::vector<int> visitedVertex;
	std::stack<int> stackVertex;
	int currentVertex{};

	stackVertex.push(start);

	--currentVertex;

	while (!stackVertex.empty()) {

		currentVertex = stackVertex.top();
		stackVertex.pop();
		visitedVertex.push_back(currentVertex);

		for (std::vector<Graph::Edges>::reverse_iterator vertex = listEdgesGraph.rbegin(); vertex != listEdgesGraph.rend(); vertex++) {

			if ((*vertex).vertexInitial == currentVertex) {

				bool checkAddingVertex = true;

				for (auto checkVisited : visitedVertex) {

					(*vertex).vertexFinal == checkVisited ? checkAddingVertex = false : true;
				}

				if (checkAddingVertex && checkStackVertex(stackVertex, (*vertex).vertexFinal)) {

					stackVertex.push((*vertex).vertexFinal);
				}
			}
		}
	}

	return visitedVertex;
}