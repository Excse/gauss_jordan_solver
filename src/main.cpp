#include <iostream>

#include "matrix.h"
#include "solver.h"
#include "pbma.h"

void print_help() {
	std::cout << "Es können nur folgende zusätzliche Flags verwendet werden: " << std::endl;
	std::cout << "	-s=<AMOUNT>	Prüfen auf die Stabilität des Algorithmus." << std::endl;
	std::cout << "	-r=<NUMBER>	Setzt die Anzahl der Zeilen für die Stabilitätstests." << std::endl;
	std::cout << "	-c=<NUMBER>	Setzt die Anzahl der Reihen für die Stabilitätstests." << std::endl;
	std::cout << "	-l=<NUMBER>	Setzt die untere Grenze für die Stabilitätstests." << std::endl;
	std::cout << "	-u=<NUMBER>	Setzt die obere Grenze für die Stabilitätstests." << std::endl;
}

void check_stability(size_t amount, size_t rows, size_t cols, double lower_bound, double upper_bound) {
  double result = stability(amount, rows, cols, lower_bound, upper_bound);
  std::cout << "Stabilität: " << result << std::endl;
}

void solve() {
	size_t rows, columns;

	std::cout << "Enter the number of rows: ";
	std::cin >> rows;
	std::cout << "Enter the number of columns: ";
	std::cin >> columns;

	std::cout << "Enter the matrix elements row by row:" << std::endl;
	Matrix matrix(rows, columns);
	std::cin >> matrix;

	std::cout << "Solving using Gauss-Jordan:" << std::endl;
	solve_matrix(matrix);
	std::cout << matrix;
}

int main(int argc, const char *argv[]) {
  args_t args(argc, argv);
    
  if(args.has_option("s")) {
    int amount = args.int_option("s");
    double lower_bound = args.double_option("l", 1e-12);
    double upper_bound = args.double_option("u", 1e-10);
    size_t rows = args.int_option("r", 3);
    size_t cols = args.int_option("c", 4);

    check_stability(amount, rows, cols, lower_bound, upper_bound);
  } else {
    solve();
  }
}
