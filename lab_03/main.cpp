#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <queue>

#define ERROR_ENTER_DATA "Error: введите правильную вершину."

namespace Graph {

	enum class Vertex { A = 0, B, C, D, E, F, G, H, I };

	struct Edge {
		int to;
		int weight;
	};

	std::vector<int> dijkstra(std::vector<std::vector<Graph::Edge>> graph, int countVertex, int startVertex);
	void printDistancesVertex(std::vector<int> distancesVertex);
}

int main() {

	setlocale(LC_ALL, "ru");

	std::vector<std::vector<Graph::Edge>> graph = {
	 
		/*A*/{ { (int)Graph::Vertex::B,  7 }, { (int)Graph::Vertex::C, 10 }},
		/*B*/{ { (int)Graph::Vertex::A,  7 }, { (int)Graph::Vertex::F,  9 }, { (int)Graph::Vertex::G, 27 } },
		/*C*/{ { (int)Graph::Vertex::A, 10 }, { (int)Graph::Vertex::F,  8 }, { (int)Graph::Vertex::E, 31 } },
		/*D*/{ { (int)Graph::Vertex::E, 32 }, { (int)Graph::Vertex::H, 17 }, { (int)Graph::Vertex::I, 21 } },
		/*E*/{ { (int)Graph::Vertex::C, 31 }, { (int)Graph::Vertex::D, 32 }},
		/*F*/{ { (int)Graph::Vertex::B,  9 }, { (int)Graph::Vertex::C,  8 }, { (int)Graph::Vertex::H, 11 } },
		/*G*/{ { (int)Graph::Vertex::B, 27 }, { (int)Graph::Vertex::I, 15 }},
		/*H*/{ { (int)Graph::Vertex::F, 11 }, { (int)Graph::Vertex::D, 17 }, { (int)Graph::Vertex::I, 15 } },
		/*I*/{ { (int)Graph::Vertex::D, 21 }, { (int)Graph::Vertex::H, 15 }, { (int)Graph::Vertex::G, 15 } }
	};

	char startVertex;

	try {

		std::cout << "¬ведите стартовую вершину(A-I):";
		std::cin >> startVertex;

		if ( ((int)startVertex < 65) || ((int)startVertex > 73) ) {
			throw std::string(ERROR_ENTER_DATA);
		}

		std::vector<int> distancesVertex = Graph::dijkstra(graph, 9, (int)(startVertex - 65));

		Graph::printDistancesVertex(distancesVertex);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

void Graph::printDistancesVertex(std::vector<int> distancesVertex) {

	for (int i = 0, j = distancesVertex.size(); i < j; i++) {
		std::cout << (char)(65 + i) << " - " << distancesVertex.at(i) << std::endl;
	}
}

std::vector<int> Graph::dijkstra(std::vector<std::vector<Graph::Edge>> graph, int countVertex, int startVertex) {

	std::vector<std::vector<int>> pathMatrices;
	pathMatrices.push_back(std::vector<int>(countVertex, std::numeric_limits<int>::max()));
	pathMatrices.at(0).at(startVertex) = 0;

	std::queue<int> queueVertex;
	std::vector<bool> visitedVertex(countVertex, false);

	queueVertex.push(startVertex);
	int vertexCurrent{};

	while (!queueVertex.empty()) {

		vertexCurrent = queueVertex.front();
		visitedVertex.at(vertexCurrent) = true;
		pathMatrices.push_back(pathMatrices.back());
		queueVertex.pop();

		for (int i = 0, j = graph.at(vertexCurrent).size() ; i < j; i++) {

			if (pathMatrices.back().at(vertexCurrent) + graph.at(vertexCurrent).at(i).weight < pathMatrices.back().at(graph.at(vertexCurrent).at(i).to)) {
				pathMatrices.back().at(graph.at(vertexCurrent).at(i).to) = pathMatrices.back().at(vertexCurrent) + graph.at(vertexCurrent).at(i).weight;
			}

			if (!visitedVertex.at(graph.at(vertexCurrent).at(i).to)) {
				queueVertex.push(graph.at(vertexCurrent).at(i).to);
			}
		}
	}

	return pathMatrices.back();
}
