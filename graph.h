#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>


class Graph {

protected:
	int amount_of_vertices;
	int amount_of_edges;
	double g_density;

public:
	Graph() {};
	explicit Graph(int v, int e, double d) : amount_of_vertices(v), amount_of_edges(e), g_density(d) {}
	virtual ~Graph() {};

	/* Methods to get variables of class Graph outside */
	const int& get_vertices() const { return amount_of_vertices; }
	const int& get_edges() const { return amount_of_edges; }
	
	virtual const int graph_from_file() = 0;

	virtual void graph_fill(const bool loop) const = 0;
	virtual void graph_print() const =  0;
	virtual void graph_make_file(const int startv) const = 0;
};				