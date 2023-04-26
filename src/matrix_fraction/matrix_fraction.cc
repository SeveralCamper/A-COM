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

void MatrixFractions::AddingScalingFactors(int pos, SimpleFractions max_element) {
  SimpleFractions scaling_factor(1, 1), zero(0, 1);
  for (int i = 0; i < rows_; i++) {
    if (max_element != zero) {
      scaling_factor = matrix_[i][pos] / max_element;
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
    PrintMatrix();
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
    PrintMatrix();
    res = 1;
  } else {
    PrintMatrix();
    std::cout << std::endl;
  }
  deleting_vector.clear();

  return res;
}

int MatrixFractions::PostProcessing(std::vector<int> *deleting_vector) {
  SimpleFractions zero(0, 1);
  bool flag_zero_row = 1;
  int res = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_ - 1; j++) {
      if (matrix_[i][j] != zero) {
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
        break;
      }
    }
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

void MatrixFractions::PrintResult(std::vector<int> current_basis) const {
  SimpleFractions zero(0, 1);
  for (int i = 0; i < rows_; i++) {
    bool flag = 0, first_after = 0;
    for (int j = 0; j < cols_; j++) {
      SimpleFractions simple_element(matrix_[i][j]);
      if (simple_element == zero) {
        if (j + 1 == cols_ && !first_after) {
          std::cout << "0";
        }
        continue;
      } else {
        if (!flag) {
          simple_element.PrintSimpleFraction();
          if (j > 2) {
            std::cout << "x" << j + 1 << " = ";
          } else {
            std::cout << "x" << current_basis[j] << " = ";
          }
          flag = 1;
        } else {
          if (!first_after) {
            if (j + 1 == cols_) {
              if (simple_element == zero) {
                std::cout << " 0";
              } else {
                simple_element.PrintSimpleFraction();
              }
              first_after = 1; 
            } else {
              simple_element.PrintSimpleFraction();
              if (j > 2) {
                std::cout << "x" << j + 1 << " ";
              } else {
                std::cout << "x" << current_basis[j] << " ";
              }
              first_after = 1;
            }
          } else {
            if (simple_element < zero) {
              if (j + 1 == cols_) {
                simple_element.PrintSimpleFraction();
               first_after = 1; 
              } else {
                simple_element.PrintSimpleFraction();
                if (j > 2) {
                  std::cout << "x" << j + 1 << " ";
                } else {
                  std::cout << "x" << current_basis[j] << " ";
                }
              }
            } else {
              if (j + 1 == cols_) {
                std::cout << "+ ";
                simple_element.PrintSimpleFraction();
                first_after = 1; 
              } else {
                std::cout << "+ ";
                simple_element.PrintSimpleFraction();
                if (j > 2) {
                  std::cout << "x" << j + 1 << " ";
                } else {
                  std::cout << "x" << current_basis[j] << " ";
                }
              }
            }
          }

        }
      }
    }
    std::cout << std::endl;
  }
}

void MatrixFractions::CheckAllPosibleBases() {
  std::cout << std::endl;
  std::cout << "All posible bases are: " << std::endl;
  std::cout << std::endl;
  int it = 1;
  int vector[cols_ - 1];
  for (int i = 0; i < cols_ - 1; i++, it++) {
    vector[i] = it;
  } 

  std::vector<int> vec = {1, 2, 3};
  transition_matrix_.push_back(vec);
  PrintBasis(vector, 3);
  while (NextSet(vector, cols_ - 1, 3)) {
    PrintBasis(vector, 3);
    vec[0] = vector[0];
    vec[1] = vector[1];
    vec[2] = vector[2];
    transition_matrix_.push_back(vec);
  }
}

MatrixFractions MatrixFractions::Transpose() {
  MatrixFractions Resault(cols_, rows_);
  for (int i = 0; i < Resault.rows_; i++) {
    for (int j = 0; j < Resault.cols_; j++) {
      Resault.matrix_[i][j] = matrix_[j][i];
    }
  }
  return Resault;
}

bool MatrixFractions::NextSet(int *vector, int length, int sample) {
  int k = sample;
  for (int i = k - 1; i >= 0; --i)
    if (vector[i] < length - k + i + 1) {
      ++vector[i];
      for (int j = i + 1; j < k; ++j)
        vector[j] = vector[j - 1] + 1;
      return true;
    }
  return false;
}

void MatrixFractions::PrintBasis(int *vector, int sample)  {
  static int num = 1; 
  std::cout << "Basis #" << num++ << ": ";
  for (int i = 0; i < sample; i++)
    std::cout << vector[i] << " ";
  std::cout << std::endl;
}

void MatrixFractions::PrintTransmitionMatrix() {
  std::cout << std::endl;
  std::cout << "Transmition Matrix" << std::endl;
  std::cout << std::endl;
  for (int i = 0; i < transition_matrix_.size(); i++) {
    std::cout << "Basis #" << i + 1 << ": ";
    for (int j = 0; j < transition_matrix_[i].size(); j++) {
      std::cout << transition_matrix_[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

void MatrixFractions::BasesTransition() {
  for (int i = 0; i < transition_matrix_.size(); i++) {
    std::vector<int> current_basis = transition_matrix_[i];
    std::cout << "Basis " << current_basis[0] << ' ' << current_basis[1] << ' ' << current_basis[2] << ':' << std::endl;
    MatrixFractions NewBasis(rows_, 4);
    int k = 0;
    for (int i = 0; i < current_basis.size(); i++) {
      k = 0;
      std::vector<SimpleFractions> current_mat = matrix_[i];
      for (int j = 0; j < NewBasis.cols_; j++) {
        NewBasis.matrix_[i][j] = matrix_[i][current_basis[k] - 1];
        k++;
      }
    }

    for (int j = 0; j < NewBasis.rows_; j++) {
      NewBasis.matrix_[j][3] = matrix_[j][cols_ - 1 ];
    }

    NewBasis.PrintMatrix();
    if (NewBasis.CalculateSLAE() != 2) {
        std::cout << "RESULT:" << std::endl << std::endl;
        NewBasis.PrintResult(current_basis);
    }
    std::cout << std::endl;
  }
}

std::vector<double> MatrixFractions::GetNeeds() {
  return needs_;
}

std::vector<double> MatrixFractions::GetReservers() {
  return reserves_;
}

void MatrixFractions::PrintNeeds() {
  for (int i = 0; i < rows_; i++) {
    std::cout << needs_[i] << ' ';
  }
  std::cout << std::endl;
}

void MatrixFractions::PrintReservers() {
  for (int i = 0; i < cols_; i++) {
    std::cout << reserves_[i] << ' ';
  }
  std::cout << std::endl;
}

void MatrixFractions::GetTransportMatrix(std::string path) {
  std::ifstream matrix_file(path);
  double value = 0.0;
  for (int i = 0; i <= rows_; i++) {
    for (int j = 0; j <= cols_; j++) {
      matrix_file >> value;
      if (i == rows_) {
        reserves_.push_back(value);
        continue;
      } 

      if (j == cols_) {
        needs_.push_back(value);
        continue;
      }

      SimpleFractions frac(value);
      matrix_[i][j] = frac;
    }
  }
  matrix_file.close();
} 

bool MatrixFractions::CheckBalance() {
  double needs = 0, reserves = 0;
  for (int i = 0; i < rows_; i++) {
    needs += needs_[i];
  }

  for (int i = 0; i < cols_; i++) {
    reserves += reserves_[i];
  }

  return (needs == reserves) ? true : false;
}

void MatrixFractions::TransportTask() {
  if (CheckBalance()) {
    std::cout << "hehe" << std::endl;
    int needs_i = 0, reservers_i = 0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {

      }
    }
  } else {
    std::cout << "not hehe" << std::endl;
  }
}
