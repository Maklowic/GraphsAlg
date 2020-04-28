#pragma once

#include <chrono>
#include <string> 

#include "list.h"
#include "matrix.h"

static int minus_inf = -1000000;


void result(std::string tab_path[], int tab_end[], int t_n, int startv) {

	std::ofstream file("wynik.txt");

	std::cout << std::string(20, '-') << "\n   Result \n\n";
	std::cout << "Start vertex -> " << startv << "\n\n";

	file << std::string(20, '-') << "\n   Result \n\n";
	file << "Start vertex -> " << startv << "\n\n";

	for (int i = 0; i < t_n; i++) {

		if (tab_end[i] == minus_inf) {
			std::cout << i << "->" << "-inf\n";
			file << i << "->" << "-inf\n";
			continue;
		}
		else if (tab_end[i] == inf) {
			std::cout << i << "->" << "inf\n";
			file << i << "->" << "inf\n";
			continue; 
		}
		else {
			std::cout << i << "->" << tab_end[i];
			file << i << "->" << tab_end[i];
			
		}
		if (i < 10) {
			std::cout << "   ";
			file << "   ";
		}
		else if (i < 100) {
			std::cout << "  ";
			file << "  ";
		}
		else {
			std::cout << " ";
			file << " ";
		}
		if ((tab_end[i] >= 100 && tab_end[i] < 1000) || (-100 > tab_end[i] && tab_end[i] <= -10)) {

			std::cout << "\n  The shortest path: " << tab_path[i] << i;
			file << "\n  The shortest path: " << tab_path[i] << i;
		}
		else if (0 <= tab_end[i] && tab_end[i] < 10) {

			std::cout << "\n   The shortest path: " << tab_path[i] << i;
			file << "\n   The shortest path: " << tab_path[i] << i;
		}
		else if ((tab_end[i] >= 10 && tab_end[i] < 100) || (-10 < tab_end[i] && tab_end[i] < 0)) {

			std::cout << "\n  The shortest path: " << tab_path[i] << i;
			file << "\n  The shortest path: " << tab_path[i] << i;
		}
		else {

			std::cout << "\n  The shortest path: " << tab_path[i] << i;
			file << "\n  The shortest path: " << tab_path[i] << i;
		}
		std::cout << std::endl;
		file << std::endl;
	}
	std::cout << std::endl;
	file.close();
}

/* For list */
double bell_ford(std::shared_ptr<List> l_graph, int startv, bool print_result) {

	std::string* path = new std::string[l_graph->get_vertices()];

	auto time_start = std::chrono::high_resolution_clock::now();

	int* distance = new int[l_graph->get_vertices()];

	for (int k = 0; k < l_graph->get_vertices(); k++) {

		distance[k] = inf;
	}

	distance[startv] = 0;

	for (int i = 1; i < l_graph->get_vertices(); i++) {
		for (int j = 0; j < l_graph->get_edges (); j++) {

			int u = l_graph->get_EDGE()[j].start_vertex;
			int v = l_graph->get_EDGE()[j].end_vertex;
			int weight = l_graph->get_EDGE()[j].edge_weight;

			if (distance[u] + weight < distance[v]) {
				distance[v] = distance[u] + weight;

				if (print_result) {

					path[v].clear();
					path[v].append(path[u] + std::to_string(u) + "->");
				}
			}
		}
	}

	for (int i = 1; i < l_graph->get_vertices(); ++i) {
		for (int j = 0; j < l_graph->get_edges (); ++j) {

			int u = l_graph->get_EDGE()[j].start_vertex;
			int v = l_graph->get_EDGE()[j].end_vertex;
			int weight = l_graph->get_EDGE()[j].edge_weight;
			if (distance[u] + weight < distance[v]) {

				if (distance[u] > inf / 2) distance[u] = inf; 
				else distance[v] = minus_inf;				
			}
			else if (distance[u] > inf / 2) distance[u] = inf;
		}
	}
	auto time_end = std::chrono::high_resolution_clock::now();

	if (print_result) result(std::move(path), std::move(distance), l_graph->get_vertices(), startv);
	delete[] distance;
	delete[] path;
	return std::chrono::duration<double, std::milli>(time_end - time_start).count();
}

/* For matrix */
double bell_ford(std::shared_ptr<Matrix> m_graph, int startv, bool print_result) {

	std::string* path = new std::string[m_graph->get_vertices()];

	auto time_start = std::chrono::high_resolution_clock::now();

	int* distance = new int[m_graph->get_vertices()];

	for (int iCell = 0; iCell < m_graph->get_vertices(); ++iCell) {

		distance[iCell] = inf;
	}

	distance[startv] = 0;

	for (int i = 1; i < m_graph->get_vertices(); i++) {
		for (int j = 0; j < m_graph->get_vertices(); j++) {
			for (int w = 0; w < m_graph->get_vertices(); w++) {

				int u = j;
				int v = w;
				int weight = m_graph->get_weight(j, w);
				if (distance[u] + weight < distance[v]) {

					distance[v] = distance[u] + weight;
					if (print_result) {

						path[v].clear();
						path[v].append(path[u] + std::to_string(u) + "->");
					}
				}
			}
		}
	}
	for (int i = 1; i < m_graph->get_vertices(); i++) {
		for (int j = 0; j < m_graph->get_vertices(); j++) {
			for (int w = 0; w < m_graph->get_vertices(); w++) {

				int u = j;
				int v = w;
				int weight = m_graph->get_weight(j, w);
				if (distance[u] + weight < distance[v]) {

					if (distance[u] > inf / 2) distance[u] = inf;
					else if (weight == inf) continue;
					else distance[v] = minus_inf;
				}
				else if (distance[u] > inf / 2) distance[u] = inf;
			}
		}
	}
	auto time_end = std::chrono::high_resolution_clock::now();

	if (print_result) result(std::move(path), std::move(distance), m_graph->get_vertices(), startv);
	delete[] distance;
	delete[] path;
	return std::chrono::duration<double, std::milli>(time_end - time_start).count();
}
