#include "matrix_fraction.h"

void PrintTable(const std::vector<std::vector<SimpleFractions>> &matrix,
                std::vector<int> bazis) {
  std::cout << std::setw(WIDTH) << "  #"
       << "  ";
  for (int i = 0; i < matrix[0].size(); ++i) {
    std::string str = "X";
    if (i == 0) {
      str = "1";
    } else {
      str += i + '0';
    }
    std::cout << std::setw(WIDTH) << str << "  ";
  }
  std::cout << std::endl;
  bool flag = true;
  for (int rowIndex = 0; rowIndex < matrix.size(); ++rowIndex) {
    auto &row = matrix[rowIndex];
    std::string str = "X";
    if (bazis[rowIndex] >= 0) {
      str += bazis[rowIndex] + '0';
    } else {
      if (flag) {
        flag = false;
        str = "Z";
      } else {
        str = "M";
      }
    }
    std::cout << std::setw(WIDTH) << str << "  ";
    for (int j = 0; j < row.size(); ++j) {
      std::cout << std::setw(WIDTH) << row[j] << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void PrintTable(const std::vector<std::vector<SimpleFractions>> &matrix,
                std::vector<int> bazis, std::set<int> ignoredColumns,
                std::vector<SimpleFractions> CO, int selectedColumns,
                int selectedRows) {
  std::cout << std::setw(WIDTH) << "  #"
       << "  ";
  for (int i = 0; i < matrix[0].size(); ++i) {
    if (ignoredColumns.count(i))
      continue;
    std::string str = "X";
    if (i == 0) {
      str = "1";
    } else {
      str += i + '0';
    }
    std::cout << std::setw(WIDTH) << str << "  ";
  }
  std::cout << std::setw(WIDTH) << "CO"
       << "  ";
  std::cout << std::endl;
  bool flag = true;
  for (int rowIndex = 0; rowIndex < matrix.size(); ++rowIndex) {
    auto &row = matrix[rowIndex];
    std::string str = "X";
    if (bazis[rowIndex] >= 0) {
      str += bazis[rowIndex] + '0';
    } else {
      if (flag) {
        flag = false;
        str = "Z";
      } else {
        str = "M";
      }
    }
    std::cout << std::setw(WIDTH) << str << "  ";
    for (int j = 0; j < row.size(); ++j) {
      if (ignoredColumns.count(j))
        continue;
      std::cout << std::setw(WIDTH) << row[j] << "  ";
    }
    if (CO[rowIndex] == 0) {
      std::cout << std::setw(WIDTH) << "-"
           << "  ";
    } else {
      std::cout << std::setw(WIDTH) << CO[rowIndex] << "  ";
    }
    if (rowIndex == selectedRows) {
      std::cout << "<--";
    }

    std::cout << std::endl;
  }
  for (int i = 0; i <= matrix[0].size(); ++i) {
    if (selectedColumns + 1 == i) {
      std::cout << std::setw(WIDTH) << "/|\\"
           << "  ";
      continue;
    }
    std::cout << std::setw(WIDTH) << "  "
         << "  ";
  }
  std::cout << std::endl;
  for (int i = 0; i <= matrix[0].size(); ++i) {
    if (selectedColumns + 1 == i) {
      std::cout << std::setw(WIDTH) << "| "
           << "  ";
      continue;
    }
    std::cout << std::setw(WIDTH) << " "
         << "  ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

std::vector<std::vector<SimpleFractions>> SquareMethod(const std::vector<std::vector<SimpleFractions>> &matrix, int row, int col) {
  int rows_size = matrix.size();
  int cols_size = matrix[0].size();
  std::vector<std::vector<SimpleFractions>> nmatrix(rows_size, std::vector<SimpleFractions>(cols_size));
  for (int i = 0; i < rows_size; ++i) {
    if (i == row) {
      for (int j = 0; j < cols_size; ++j) {
        if (j == col) {
          nmatrix[i][j] = 1;
          continue;
        }
        nmatrix[i][j] = matrix[i][j] / matrix[row][col];
      }
      continue;
    }
    for (int j = 0; j < cols_size; ++j) {
      if (j == col) {
        nmatrix[i][j] = 0;
        continue;
      }
      nmatrix[i][j] =
          matrix[i][j] - (matrix[i][col] * matrix[row][j]) / matrix[row][col];
    }
  }
  return nmatrix;
}

std::vector<std::vector<SimpleFractions>> SimplexMethod(std::vector<std::vector<SimpleFractions>> matrix, std::vector<int> &basis,
              std::vector<bool> fake_col) {
  int rows_size = matrix.size();
  int cols_size = matrix[0].size();

  bool flag = true;
  std::set<int> ignoredColumns;
  while (flag) {

    int col = -1;
    for (int i = 1; i < cols_size; ++i) {
      if (ignoredColumns.count(i) > 0)
        continue;
      if (SimpleFractions(0) > matrix[rows_size - 1][i] &&
          (col == -1 || matrix[rows_size - 1][col] > matrix[rows_size - 1][i])) {
        col = i;
      }
    }

    if (col == -1)
      break;

    std::vector<SimpleFractions> CO(matrix.size());
    int row = -1;

    for (int i = 0; i < rows_size; ++i) {
      if (basis[i] >= 0 && matrix[i][col] > 0) {
        SimpleFractions val = matrix[i][0] / matrix[i][col];
        CO[i] = val;
        if (row == -1 || CO[row] > val) {
          row = i;
        }
      }
    }
    if (row == -1)
      break;

    PrintTable(matrix, basis, ignoredColumns, CO, col, row);

    std::vector<std::vector<SimpleFractions>> nmatrix = SquareMethod(matrix, row, col);

    if (fake_col[basis[row]]) {
      ignoredColumns.insert(basis[row]);
    }
    basis[row] = col;

    matrix = nmatrix;
  }
  std::vector<std::vector<SimpleFractions>> nmatrix(rows_size);
  for (int i = 0; i < rows_size; ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      if (ignoredColumns.count(j) > 0) {
        continue;
      }
      nmatrix[i].push_back(matrix[i][j]);
    }
  }
  return nmatrix;
}

std::vector<std::vector<SimpleFractions>> GetZLP(std::string filpe_path) {
  std::vector<std::vector<SimpleFractions>> result;
  std::ifstream file_path_(filpe_path);
  std::string str;
  while (getline(file_path_, str)) {
    std::vector<SimpleFractions> new_row;
    std::stringstream string_stream(str);
    SimpleFractions new_fraction;
    while (string_stream >> new_fraction) {
      new_row.push_back(new_fraction);
    }
    result.push_back(new_row);
  }

  return result;
}