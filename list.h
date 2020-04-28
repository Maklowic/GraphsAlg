#pragma once

#include "graph.h"
#include "edge.h"
 
class List : public Graph {

	Edge* l_edge; 

public:
	List() : Graph() {};
	~List() { delete[] l_edge; }
	explicit List(int v, double d) : Graph(v, static_cast<int>(d* v* (v - 1)), d), l_edge(new Edge[static_cast<int>(d * v * (v - 1))]) {}

	const Edge* get_EDGE() const { return l_edge; }

	void put_EDGE(int startv, int endv, int w, int position) const {
		l_edge[position].start_vertex = startv; 
		l_edge[position].end_vertex = endv;
		l_edge[position].edge_weight = w; 
	}
	
	bool check_connection(int startv, int endv) const {
		for (int i = 0; i < amount_of_edges; i++) {
			if (l_edge[i].end_vertex == endv && l_edge[i].start_vertex == startv) return true;
		} return false;
	}

	const int graph_from_file() override;

	void graph_fill(const bool loop) const override; 
	void graph_print() const override;
	void graph_make_file(const int startv) const override;

	
};

const int List::graph_from_file() {

	std::ifstream file("wejscie.txt");
	if (!file.is_open()) {
		std::cerr << "File error!";
		return 1;
	}

	int start;
	int source;
	int end;
	int w;

	file >> amount_of_edges >> amount_of_vertices >> start;
	l_edge = new Edge[amount_of_edges];

	for (int i = 0; i < amount_of_edges; i++) {

		file >> source >> end >> w;
		put_EDGE(source, end, w, i);
	}
	file.close();
	return start; 
}


void List::graph_fill(const bool loop) const {

	if (g_density == 1) {

		int position = 0;
		for (int start = 0; start < amount_of_vertices; ++start) {
			for (int end = 0; end < amount_of_vertices; ++end) {

				if (start != end) {

					int w = rand() % 20 + (-1);
					do { w = rand() % 20 + (-1); } while (w == 0);

					put_EDGE(start, end, w, position++);
				}
			}
		}
	}
	else {
		int e = 0;

		while (e < amount_of_edges) {

			int start_node = rand() % amount_of_vertices;
			int end_node = rand() % amount_of_vertices;
			if (!check_connection(start_node, end_node)) {

				int w = rand() % 20 + (-1);
				do { w = rand() % 20 + (-1); } while (w == 0);

				if (start_node != end_node) {
					put_EDGE(start_node, end_node, w, e++);
				}
				else if (loop) {
					put_EDGE(start_node, end_node, w, e++);
				}
			}
		}
	}
}


void List::graph_print() const {

	std::cout << std::string(30, '-') << "\n  Graph as a list\n\n";
	for (int start = 0; start < amount_of_vertices; ++start) {

		std::cout << start;
		for (int i = 0; i < amount_of_edges; i++) {

			if (l_edge[i].start_vertex == start)
				std::cout << "->" << "[" << l_edge[i].end_vertex << "|" << l_edge[i].edge_weight << "]";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}


void List::graph_make_file(const int startv) const {

	std::ofstream file("nowewejscie.txt");
	if (!file.is_open()) {
		std::cerr << "File error!";
		return;
	}

	file << amount_of_edges << " " << amount_of_vertices << " " << startv << "\n";
	for (int i = 0; i < amount_of_edges; i++) {

		file << l_edge[i].start_vertex << " ";
		file << l_edge[i].end_vertex << " ";
		file << l_edge[i].edge_weight << "\n";
	}
	file.close();
}
