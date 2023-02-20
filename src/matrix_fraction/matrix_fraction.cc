#include "matrix_fraction.h"

SimpleFractions MatrixFractions::operator()(int i, int j) const {
  if ((i < 0 || i > rows_) || j < 0 || j > cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

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
    for (int j = 0; j < cols_; j++) {
        matrix_[i][j].ReduceFraction();
    }
  }
}

void MatrixFractions::FillMatrix(double iterator) {
  double iter = 0;
  for (int i = 0; i < rows_; i++) {
    std::vector<SimpleFractions> vec;
    for (int j = 0; j < cols_; j++) {
      SimpleFractions frac(0, 1);
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
        std::cout << std::setw(16);
      } else {
        std::cout << std::setw(16);
        matrix_[i][j].PrintSimpleFraction();
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

SimpleFractions MatrixFractions::GetElement(int i, int j) const {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

void MatrixFractions::SetElement(int i, int j, SimpleFractions value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  matrix_[i][j] = value;
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

SimpleFractions MatrixFractions::FindAbsMaxElement(int shift, int pos) {
  bool sign = 0;
  SimpleFractions max_element(-LONG_LONG_MAX, 1), zero(0, 1), minus_one(-1, 1);
  int max_element_pos = 0;
  for (int i = shift; i < rows_; i++) {
    if (matrix_[i][pos].AbsFraction() > max_element) {
      if (matrix_[i][pos] < zero) {
        sign = 1;
      } else {
        sign = 0;
      }
      max_element_pos = i;
      max_element = matrix_[i][pos].AbsFraction();
    }
  }

  for (int i = shift; i < cols_; i++) {
    std::swap(matrix_[pos][i], matrix_[max_element_pos][i]);
  }

  return sign == 1 ? max_element * minus_one : max_element;
}

void MatrixFractions::AddingScalingFactors(int pos, SimpleFractions main_element) {
  SimpleFractions scaling_factor(1, 1), zero(0, 1);
  for (int i = 0; i < rows_; i++) {
    if (main_element != zero) {
      scaling_factor = matrix_[i][pos] / main_element;
      scaling_factor.ReduceFraction();
    }

    if (i != pos) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] - scaling_factor * matrix_[pos][j];
      } 
    }
  }
}

void MatrixFractions::SetToIdentity() {
  for (int i = 0; i < rows_; i++) {
    SimpleFractions main_element(1, 1);
    for (int j = 0; j < cols_; j++) {
      if (i == j) {
        main_element = matrix_[i][j];
      }
      if (main_element != 0) {
        matrix_[i][j] /= main_element;
      }
    }
    main_element.SetNumenator(1);
    main_element.SetDenominator(1);
  }
}

int MatrixFractions::CalculateSLAE() {
  int min = 0, i = 0, j = 0, res = 0;
  if (rows_ < cols_) {
    min = rows_;
  } else {
    min = cols_;
  }

  while(i < min) {
    AddingScalingFactors(i, FindAbsMaxElement(i, j));
    ReduceMatrix();
    PrintSLAE();
    std::cout << std::endl;
    i++;
    j++;
  }

  std::cout << std::endl << "Set To Identity" << std::endl << std::endl;

  SetToIdentity();

  std::vector<int> deleting_vector; 
  int post_res = PostProcessing(&deleting_vector);
  int new_size = rows_ - deleting_vector.size();
  if (post_res == 2) {
    std::cout << "The matrix has not any solutions" << std::endl;
    res = 2;
  } else if (post_res == 1) {
    for (auto it_i = matrix_.begin(); it_i != matrix_.end(); ++it_i) {
      for (auto it_j = deleting_vector.begin(); it_j != deleting_vector.end(); ++it_j) {
        if (*it_j == i) {
          matrix_.erase(it_i);
        }
      }
    }
    rows_ = new_size;
    PrintSLAE();
    res = 1;
  } else {
    PrintSLAE();
    std::cout << std::endl;
  }
  deleting_vector.clear();

  return res;
}

int MatrixFractions::PostProcessing(std::vector<int> *deleting_vector) {
  SimpleFractions zero(0, 1);
  bool flag_zero_row = 1, flag_zero = 1;
  int res = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_ - 1; j++) {
      if (matrix_[i][j] != zero) {
        flag_zero = 0;
        flag_zero_row = 0;
        break;
      }
    }

    if (flag_zero_row == 1) {
      if (matrix_[i][cols_ - 1] == zero) {
        res = 1;
        deleting_vector->push_back(i);
      } else if (matrix_[i][cols_ - 1] != zero) {
        deleting_vector->push_back(i);
        res = 2;
      }
    }
    flag_zero = 1;
    flag_zero_row = 1;
  }

  return res;
}

void MatrixFractions::PrintSLAE() const {
  for (int j = 0; j < rows_; j++) {
    for (int i = 0; i < cols_; i++) {
      SimpleFractions simple_element(matrix_[j][i]);
      if (i == 0) {
        std::cout << std::fixed;
        simple_element.PrintSimpleFraction();
        std::cout << "x" << i + 1;
      } else {
        if (i == rows_) {
          std::cout << " = ";
          simple_element.PrintSimpleFraction();
        } else {
          if (i == cols_ - 1) {
            std::cout << " + ";
            simple_element.PrintSimpleFraction();
          } else {
            std::cout << " + ";
            simple_element.PrintSimpleFraction();
            std::cout << "x" << i + 1;
          }
        }
      }
    }
    std::cout << std::endl;
  }
}

void MatrixFractions::PrintResault() const {
  SimpleFractions zero(0, 1);
  for (int i = 0; i < rows_; i++) {
    bool flag = 0, first_after = 0;
    for (int j = 0; j < cols_; j++) {
      SimpleFractions simple_element(matrix_[i][j]);
      if (simple_element == zero) {
        continue;
      } else {
        if (!flag) {
          simple_element.PrintSimpleFraction();
          std::cout << "x" << j + 1 << " = ";
          flag = 1;
        } else {
          if (!first_after) {
            if (j == cols_ - 1) {
              simple_element.PrintSimpleFraction();
              first_after = 1; 
            } else {
              simple_element.PrintSimpleFraction();
              std::cout << "x" << j + 1 << " ";
              first_after = 1;
            }
          } else {
            if (simple_element < zero) {
              simple_element.PrintSimpleFraction();
              std::cout << "x" << j + 1 << " ";
            } else {
              std::cout << "+ ";
              simple_element.PrintSimpleFraction();
              std::cout << "x" << j + 1 << " ";
            }
          }

        }
      }
    }
    std::cout << std::endl;
  }
}
