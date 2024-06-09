#ifndef SOLVER_H_
#define SOLVER_H_

#include "matrix.h"

/**
 * Löst das Gleichungssystem mithilfe des Gauss-Jordan-Verfahrens. Die übergebene
 * Matrix wird dabei verändert.
 */
void solve_matrix(Matrix &matrix);

/**
 * Prüft den Algorithmus auf die Stabilität, indem n Matrizen mit den gegebenen 
 * Dimensionen  erstellt werden, die leicht verändert werden. Die Differenz der Matrix
 * gibt hierbei die durchschnittliche Fehlerrate an, welche auch zurückgegeben wird.
 */
double stability(size_t amount, size_t rows, size_t cols, double lower_bound,
                 double upper_bound);

#endif /* SOLVER_H_ */
