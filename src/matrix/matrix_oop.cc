#include "matrix_oop.h"

Matrix::Matrix() {
  cols_ = 1;
  rows_ = 1;
  MemoryAllocation();
}

Matrix::Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input, index is out of range");
  }
  cols_ = cols;
  rows_ = rows;
  MemoryAllocation();
}

Matrix::~Matrix() {
  if (matrix_) {
    RemoveMatrix();
  }
  cols_ = 0;
  rows_ = 0;
}

// operators overloads

double Matrix::operator()(int i, int j) const {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

// public

void Matrix::PrintMatrix() const {
  std::cout << "!!!!! " << rows_ << " ! " << cols_ << std::endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (j == 0) {
        std::cout << matrix_[i][j];
      } else {
        std::cout << std::setw(16) << matrix_[i][j];
      }
    }
    std::cout << std::endl;
  }
}

double Matrix::GetElement(int i, int j) const {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

void Matrix::SetElement(int i, int j, double value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  matrix_[i][j] = value;
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  double** buffer = new double*[new_rows];
  for (int i = 0; i < rows_; i++) {
    buffer[i] = matrix_[i];
  }
  delete[] this->matrix_;
  this->matrix_ = buffer;
  buffer = nullptr;
  if (new_rows > rows_) {
    for (int i = rows_; i < new_rows; i++) {
      this->matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j += 1) {
        matrix_[i][j] = 0;
      }
    }
  }
  rows_ = new_rows;
}

void Matrix::SetCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  double* buffer = nullptr;
  for (int i = 0; i < rows_; i++) {
    buffer = new double[new_cols];
    for (int j = 0; j < cols_; j += 1) {
      buffer[j] = matrix_[i][j];
    }
    for (int j = cols_; j < new_cols; j++) {
      buffer[j] = 0;
    }
    delete[] matrix_[i];
    matrix_[i] = buffer;
    buffer = nullptr;
  }
  cols_ = new_cols;
}

double **Matrix::GetMatrix() const { return matrix_; }

void Matrix::MemoryAllocation() {
  matrix_ = new double*[rows_];
  if (matrix_) {
    for (int i = 0; i < rows_; i += 1) {
      matrix_[i] = new double[cols_];
    }
  }
  FillMatrix(0);
}

void Matrix::FillMatrix(double iterator) {
  double iter = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      iter += iterator;
      matrix_[i][j] = iter;
    }
  }
}

void Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void Matrix::GetMatrix(std::string path) {
  std::ifstream matrix_file(path);

  for (int i = 0; i < GetRows(); i++)
    for (int j = 0; j < GetCols(); j++) matrix_file >> matrix_[i][j];
  matrix_file.close();
}

void Matrix::PrintSLAE(int model) const {
  for (int j = 0; j < rows_; j++) {
    for (int i = 0; i < cols_; i++) {
      SimpleFractions simple_element(matrix_[j][i]);
      if (i == 0) {
        if (model == 1) {
          std::cout << std::fixed;
          simple_element.PrintSimpleFraction();
          std::cout << "x" << i + 1;
        } else {
          std::cout << std::fixed << matrix_[j][i] << "x" << i + 1;
        }
      } else {
        if (i == rows_) {
          if (model == 1) {
            std::cout << " = ";
            simple_element.PrintSimpleFraction();
          } else {
            std::cout << " = " << matrix_[j][i];
          }
        } else {
          if (i == cols_ - 1) {
            std::cout << " + " << matrix_[j][i];
          } else {
            if (model == 1) {
              std::cout << " + ";
              simple_element.PrintSimpleFraction();
              std::cout << "x" << i + 1;
            } else {
              std::cout << " + " << matrix_[j][i] << "x" << i + 1;
            }
          }
        }
      }
    }
    std::cout << std::endl;
  }
}

double Matrix::FindAbsMaxElement(int shift, int pos) {
  bool sign = 0;
  double max_element = -DBL_MAX;
  int max_element_pos = 0;
  for (int i = shift; i < rows_; i++) {
    if (abs(matrix_[i][pos]) > max_element) {
      if (matrix_[i][pos] < 0) {
        sign = 1;
      } else {
        sign = 0;
      }
      max_element_pos = i;
      max_element = abs(matrix_[i][pos]);
    }
  }

  for (int i = shift; i < cols_; i++) {
    std::swap(matrix_[pos][i], matrix_[max_element_pos][i]);
  }

  return sign == 1 ? max_element * (-1) : max_element;
}

void Matrix::AddingScalingFactors(int pos, double main_element) {
  double scaling_factor = 1;
  // PrintSLAE(1);
  // std::cout << "POS: " << pos << std::endl;
  for (int i = 0; i <= rows_ - 1; i++) {
    if (main_element != 0) {
      scaling_factor = matrix_[i][pos] / main_element;
    }
    // std::cout << matrix_[i][pos] << " / " << main_element << " = " << scaling_factor << std::endl;
    if (i != pos) {
      for (int j = 0; j < cols_; j++) {
        // std::cout << "!!! " << matrix_[i][j] << " = " << matrix_[i][j] << " - " << scaling_factor << " * " << matrix_[pos][j] << std::endl;
        matrix_[i][j] = matrix_[i][j] - scaling_factor * matrix_[pos][j];
      } 
    }

    //PrintSLAE(1);
    //std::cout << std::endl;
  }
}

void Matrix::SetToIdentity() {
  for (int i = 0; i < rows_; i++) {
    double main_element = 1;
    for (int j = 0; j < cols_; j++) {
      if (i == j) {
        main_element = matrix_[i][j];
      }
      if (main_element != 0) {
        matrix_[i][j] /= main_element;
      }
    }
    main_element = 1;
  }
}

void Matrix::CalculateSLAE(int model) {
  int min = 0, i = 0, j = 0;
  if (rows_ < cols_) {
    min = rows_;
  } else {
    min = cols_;
  }

  while(i < min) {
    AddingScalingFactors(i, FindAbsMaxElement(i, j));
    std::cout << std::endl;
    PrintSLAE(model);
    i++;
    j++;
  }

  std::cout << std::endl << "Set To Identity" << std::endl << std::endl;

  SetToIdentity();

  int row_for_del = -1, post_res = PostProcessing(&row_for_del);
  if (post_res == 2) {
    std::cout << "The matrix has not any solutions" << std::endl;
  } else if (post_res == 1) {
    int i_new = 0, j_new = 0;
    Matrix new_matrix(rows_ - 1, cols_);
    for (int i = 0; i < GetRows(); i++) {
      if (row_for_del == i) {
        continue;
      }
      for (int j = 0; j < GetCols(); j++) {
        new_matrix.SetElement(i_new, j_new, matrix_[i][j]);
        j_new++;
      }
      i_new++;
      j_new = 0; 
    }
    new_matrix.PrintSLAE(model);
    std::cout << std::endl; 
    PrintResault();
  } else {
    PrintSLAE(model);
    std::cout << std::endl;
    PrintResault();
    std::cout << std::endl;
  }
}

int Matrix::PostProcessing(int *row_for_del) {
  bool flag_zero_row = 1, flag_zero = 1;
  int res = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_ - 1; j++) {
      if (matrix_[i][j] != 0) {
        flag_zero = 0;
        flag_zero_row = 0;
        break;
      }
    }
    if (flag_zero_row == 1) {
      if (matrix_[i][cols_ - 1] == 0) {
        res = 1;
        *row_for_del = i;
        break;
      } else if (matrix_[i][cols_ - 1] != 0 ) {
        res = 2;
        break;
      }
    }
    flag_zero = 1;
    flag_zero_row = 1;
  }

  return res;
}

void Matrix::PrintResault() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] > -1 && matrix_[i][j] < 1) {
        if (matrix_[i][j] < 0) {
          matrix_[i][j ]*= -1;
        }
      }
    }
  }

  int count = 0;
  int flag = 0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if ((matrix_[i][j] - EPS > 0 || matrix_[i][j] < 0) && flag != 1) {
        if (i == j) {
          std::cout << matrix_[i][j] << "x" << j + 1 << " = ";
        } else {
          if (j + 1 != cols_) {
            if (count == 0) {
              std::cout << matrix_[i][j] << "x" << j + 1; 
            } else {
              std::cout << " + " << matrix_[i][j] << "x" << j + 1; 
            }
          } else {
            std::cout << matrix_[i][j]; 
          }
        }
      } else if (i == j) {
        std::cout << i << " ! " << j << std::endl;
        while (matrix_[i][j] - EPS > 0) {
          j++;
        }
        std::cout << i << " ! " << j << std::endl;
        std::cout << matrix_[i][j] << "x" << j + 1 << " = ";
        flag = 1;
      }
    }
    std::cout << std::endl;
  }
}
