#pragma once

#include <cstdlib>
#include <memory>
#include "graph.h" 
#include "edge.h" 

static int inf = 1000000;

class Matrix : public Graph {

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;
														
public:
	Matrix() : Graph() {};
	explicit Matrix(int v, double d); /* v - vertices, d - density*/
	
	const int& get_weight(int i, int j) const { return matrix[i][j]; }

	const int graph_from_file() override;

	void graph_fill(const bool i) const override;
	void graph_print() const override;
	void graph_make_file(const int loop) const override;
};


Matrix::Matrix(int v, double d)
	: Graph(v, static_cast<int>(d* v* (v - 1)), d),
	matrix(std::make_unique<std::unique_ptr<int[]>[]>(v)) {

	for (int j = 0; j < amount_of_vertices; ++j) {
		matrix[j] = std::make_unique<int[]>(v);

		for (int i = 0; i < amount_of_vertices; ++i) {
			if (j == i) matrix[j][i] = 0; 
			else matrix[j][i] = inf;
		}
	}
}

const int Matrix::graph_from_file() {

	std::ifstream file("wejcie.txt");
	if (!file.is_open()) {
		std::cerr << "File error!";
		return 1;
	}

	int start;
	int source;
	int end;
	int w;

	file >> amount_of_edges >> amount_of_vertices >> start;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(amount_of_vertices);

	for (int i = 0; i < amount_of_vertices; i++) {

		matrix[i] = std::move(std::make_unique<int[]>(amount_of_vertices));
		for (int j = 0; j < amount_of_vertices; j++) {

			if (i == j) matrix[i][j] = 0;
			else matrix[i][j] = inf;
		}
	}

	for (int e = 0; e < amount_of_edges; e++) {

		file >> source >> end >> w;
		matrix[source][end] = w;;
	}
	file.close();
	return start;
}


void Matrix::graph_fill(const bool loop) const {

	if (g_density == 1) {
		for (int i = 0; i < amount_of_vertices; ++i) {
			for (int j = 0; j < amount_of_vertices; ++j) {
				if (i != j)
				{
					int w = rand() % 20 + (-1);
					do { w = rand() % 20 + (-1); } while (w == 0);

					matrix[i][j] = w;
				}
			}
		}
	}
	else {
		int e = amount_of_edges;

		while (e) { 

			int start_node = rand() % amount_of_vertices;
			int end_node = rand() % amount_of_vertices;

			if (matrix[start_node][end_node] == 0 || matrix[start_node][end_node] == inf) {

				int w = rand() % 20 + (-1);

				do { w = rand() % 20 + (-1); } while (w == 0);

				if (start_node != end_node) {

					matrix[start_node][end_node] = w;
					--e;
				}
				else if (loop) {

					matrix[start_node][end_node] = w;
					--e;
				}
			}
		}
	}
}


void Matrix::graph_print() const {

	std::cout << std::string(33, '-') << "\n  Graph as a Matrix\n\n ";

	for (int i = 0; i < amount_of_vertices; i++) {

		if (i <= 10) std::cout << "    " << i;
		else if (i <= 100) std::cout << "   " << i;
		else std::cout << "  " << i;
	}
	std::cout << "\n\n";

	for (int j = 0; j < amount_of_vertices; j++) {

		if (j < 10) std::cout << j << "   |";
		else if (j < 100) std::cout << j << "  |";
		else std::cout << j << " |";

		for (int k = 0; k < amount_of_vertices; ++k) {

			int tmp = matrix[j][k];

			if (tmp == inf) std::cout << "*"; 
			else std::cout << tmp;

			if (abs(tmp) < 10 || abs(tmp) == inf) std::cout << "    ";
			else if (abs(tmp) < 100) std::cout << "   ";
			else std::cout << "  ";

			if (tmp < 0) std::cout << '\b'; 
		}
		std::cout << "|\n";
	}
	std::cout << std::endl;
}


void Matrix::graph_make_file(const int startv) const {

	std::ofstream file("nowewejcie.txt");
	if (!file.is_open()) {
		std::cerr << "File error!";
		return;
	}

	file << amount_of_edges << " " << amount_of_vertices << " " << startv << "\n";
	for (int j = 0; j < amount_of_vertices; j++) {
		for (int i = 0; i < amount_of_vertices; i++) {

			if (matrix[j][i] != inf && matrix[j][i] != 0) {

				file << j << " ";
				file << i << " ";
				file << matrix[j][i] << "\n";
			}
		}
	}
	file.close();
}
