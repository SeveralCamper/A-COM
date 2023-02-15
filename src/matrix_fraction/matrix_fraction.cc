#include "matrix_fraction.h"

MatrixFractions::MatrixFractions() {
  cols_ = 1;
  rows_ = 1;
  FillMatrix(0);
}

MatrixFractions::MatrixFractions(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input, index is out of range");
  }
  cols_ = cols;
  rows_ = rows;
  FillMatrix(0);
}

MatrixFractions::~MatrixFractions() {
  if (!matrix_.empty()) {
    RemoveMatrix();
  }
  cols_ = 0;
  rows_ = 0;
}

void MatrixFractions::RemoveMatrix() {
    for (int i = 0; i < rows_; i++) {
        matrix_[i].clear();
    }
    matrix_.clear();
}

void MatrixFractions::ReduceMatrix() {
  for (int i = 0; i < rows_; i++) {
    std::cout << "helay" << std::endl;
    for (int j = 0; j < cols_; j++) {
        matrix_[i][j].PrintSimpleFraction();
        std::cout << "haloy" << std::endl;
        matrix_[i][j] += matrix_[i][j];
        matrix_[i][j].PrintSimpleFraction();
    }
  }
}

void MatrixFractions::FillMatrix(double iterator) {
  double iter = 0;
  for (int i = 0; i < rows_; i++) {
    std::vector<SimpleFractions> vec;
    for (int j = 0; j < cols_; j++) {
      SimpleFractions frac(iter);
      vec.push_back(frac);
      iter += iterator;
    }
    matrix_.push_back(vec);
  }
}

void MatrixFractions::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (j == 0) {
        matrix_[i][j].PrintSimpleFraction();
      } else {
        std::cout << std::setw(16);
        matrix_[i][j].PrintSimpleFraction();
      }
    }
    std::cout << std::endl;
  }
}

int MatrixFractions::GetRows() const { return rows_; }

int MatrixFractions::GetCols() const { return cols_; }

std::vector<std::vector<SimpleFractions>> MatrixFractions::GetMatrix() const { return matrix_; }

void MatrixFractions::GetMatrix(std::string path) {
  std::ifstream matrix_file(path);
  double value = 0.0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
        matrix_file >> value;
        SimpleFractions frac(value);
        matrix_[i][j] = frac;
    }
  }
  matrix_file.close();
}