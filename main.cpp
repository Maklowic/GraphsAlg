#include <time.h>

#include "bell-ford_alg.h"



template<typename Type>
std::ostream& test_l(std::ostream& file, int (&tab_vertices)[5], double (&tab_density)[4], int loops) {
	
	for (double density : tab_density) { 
		file << density << "\n";
		for (int vertices : tab_vertices) { 
			double sum = 0;
			for (int i = 0; i < loops; i++) { 

				std::shared_ptr<Type> graph = std::make_shared<Type>(vertices, density); 
				int startv = rand() % vertices; 

				graph->graph_fill(true); 

				sum += bell_ford(std::move(graph), startv, false); 
				std::cout << (i * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			file << "  " << vertices << "  ";
			file << sum / loops << "\n";
			std::cout << vertices << " V_DONE!" << std::endl;
		}
		std::cout << "\n" << density << " D_DONE!\n" << std::endl;

	}
	file << "\n";
	return file;
}

template<typename Type>
std::ostream& test_m(std::ostream& file, int(&tab_vertices)[5], double(&tab_density)[4], int loops) {

	for (double density : tab_density) {
			file << density << "\n";
		for (int vertices : tab_vertices) {
			double sum = 0;
			for (int i = 0; i < loops; i++) {

				std::shared_ptr<Type> graph = std::make_shared<Type>(vertices, density);
				int startv = rand() % vertices;

				graph->graph_fill(true);

				sum += bell_ford(std::move(graph), startv, false);
				std::cout << (i * 100 / loops) + 1 << "%" << "\r" << std::flush;
			}
			file <<"  " << vertices << "  ";
			file << sum / loops << "\n";
			std::cout << vertices << " V_DONE!" << std::endl;
		}
		std::cout << "\n" << density << " D_DONE!\n" << std::endl;
	}
	file << "\n";
	return file;
}

int main() {

	srand(static_cast<unsigned int>(time(NULL)));

	typedef	List L_GRAPH;
	
	bool allowLoops = true;		

	std::shared_ptr<L_GRAPH> graph;

	int option;

	do {
		std::cout << "|=================== MENU ===================|" << std::endl;
		std::cout << "|      Choose option:                        |" << std::endl;
		std::cout << "|  1. Test the bell-ford algorithm           |" << std::endl;
		std::cout << "|  2. Read from wejscie.txt file             |" << std::endl;
		std::cout << "|  3. Make own graph to a file               |" << std::endl;
		std::cout << "|                                            |" << std::endl;
		std::cout << "|  0. Exit                                   |" << std::endl;
		std::cout << "|=====================================.M.M.==|" << std::endl;
		std::cout << "   Your choice:  ";
		std::cin >> option;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		switch (option) {

		case 1: {
			int tab_vertices[5] = { 5, 10, 50, 100, 500 };
			double tab_density[4] = { 0.25, 0.5, 0.75, 1 };
			int loops = 100;

			std::ofstream file_l("czasy_lista.txt");
			std::ofstream file_m("czasy_macierz.txt");
			if (!file_l.is_open()) {

				std::cerr << "File error!" << std::flush;
				return 1;
			}

			if (!file_m.is_open()) {

				std::cerr << "File error!" << std::flush;
				return 1;
			}

			test_l<List>(file_l, tab_vertices, tab_density, loops);
			std::cout << "LIST DONE\n" << std::endl;
			test_m<Matrix>(file_m, tab_vertices, tab_density, loops);
			std::cout << "MATRIX DONE" << std::endl;

			file_l.close();
			file_m.close();

			break;
		}
		case 2: {
			int startv=2;
			std::shared_ptr<L_GRAPH> tmp = std::make_shared<L_GRAPH>();
			graph = tmp;
			try {
				startv = tmp->graph_from_file();
			}
			catch (const char* msg) {
				std::cerr << msg << std::flush;
				return 1;
			}
			graph->graph_print();
			bell_ford(std::move(graph), startv, true);
			break;
		}
		case 3: {
			int vertices = 7;
			double density = 0.5;
			int startv = 2;
			std::cout << "Number of vertices: ";
			std::cin >> vertices; std::cout << std::endl;
			std::cout << "Percent of density: ";
			std::cin >> density; std::cout << std::endl;
			std::cout << "Set a starting vertex: ";
			std::cin >> startv; std::cout << std::endl;

			std::shared_ptr<L_GRAPH> tmp = std::make_shared<L_GRAPH>(vertices, density);
			graph = tmp;
			tmp->graph_fill(allowLoops);
			graph->graph_print();
			graph->graph_make_file(startv);
			bell_ford(std::move(graph), startv, true);
			break;
		}
		case 0: {
			
			std::cout << "The End!" << std::endl;
			return 0;
		}
		default: {
			std::cerr << "Error: Incorect option! Try again." << std::endl;
			option = -1;
			break;
		}
		}
	} while (option != 0);
}