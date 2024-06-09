#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <iostream>
#include <vector>

/**
 * Diese Klasse repräsentiert eine Matrix und bietet Methoden, um auf die Elemente
 * der Matrix zuzugreifen und diese zu verändern.
 */
class Matrix {
private:
  std::vector<double> _data;
  size_t _cols, _rows;

public:
  /**
   * Erstellt eine Matrix mit den übergebenen Werten.
   */
  Matrix(std::initializer_list<std::initializer_list<double>> init);

  /**
   * Erstellt eine Matrix mit der angegebenen Anzahl an Zeilen und Spalten.
   * Die Matrix wird mit Nullen initialisiert.
   */
  Matrix(size_t rows, size_t cols);

  /**
   * Wird genutzt um auf ein einziges Element der Matrix zugreifen zu können. Hierbei
   * wird ein nicht-const-double zurückgegeben, damit das Element verändert werden kann.
   */
  double &operator()(size_t row, size_t col);

  /**
   * Wird genutzt um auf ein einziges Element der Matrix zugreifen zu können. Hierbei
   * wird ein const-double zurückgegeben, damit das Element nicht verändert werden kann.
   */
  double operator()(size_t row, size_t col) const;

  /**
   * Wird genutzt um die Matrix Zeile für Zeile einzulesen.
   */
  friend std::istream &operator>>(std::istream &input, Matrix &matrix);

  /**
   * Wird genuzt um die Matrix auf der Konsole auszugeben. Hierbei werden immer 2 Nachkommastellen
   * ausgegeben.
   */
  friend std::ostream &operator<<(std::ostream &output, Matrix &matrix);

  /**
   * Prüft ob die übergebene Zeile nur Nullen enthält. Zudem kann mit einem Offset
   * angegeben werden, ab welcher Spalte geprüft werden soll.
   */
  bool is_row_zero(size_t row, size_t col_offset = 0);

  /**
   * Tauscht zwei angegebene Zeilen miteinander.
   */
  void swap_rows(size_t first, size_t second);

  /**
   * Gibt die Anzahl an Spalten der Matrix zurück.
   */
  size_t cols() const { return this->_cols; }

  /**
   * Gibt die Anzahl an Zeilen der Matrix zurück.
   */
  size_t rows() const { return this->_rows; }
};

#endif /* MATRIX_H_ */
