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
  int n = matrix.size();
  int m = matrix[0].size();
  std::vector<std::vector<SimpleFractions>> nmatrix(n, std::vector<SimpleFractions>(m));
  for (int i = 0; i < n; ++i) {
    if (i == row) {
      for (int j = 0; j < m; ++j) {
        if (j == col) {
          nmatrix[i][j] = 1;
          continue;
        }
        nmatrix[i][j] = matrix[i][j] / matrix[row][col];
      }
      continue;
    }
    for (int j = 0; j < m; ++j) {
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

std::vector<std::vector<SimpleFractions>> SimplexMethod(std::vector<std::vector<SimpleFractions>> matrix, std::vector<int> &basiz,
              std::vector<bool> fakeCol) {
  int n = matrix.size();
  int m = matrix[0].size();

  bool flag = true;
  std::set<int> ignoredColumns;
  while (flag) {

    int col = -1;
    for (int i = 1; i < m; ++i) {
      if (ignoredColumns.count(i) > 0)
        continue;
      if (SimpleFractions(0) > matrix[n - 1][i] &&
          (col == -1 || matrix[n - 1][col] > matrix[n - 1][i])) {
        col = i;
      }
    }

    if (col == -1)
      break;

    std::vector<SimpleFractions> CO(matrix.size());
    int row = -1;

    for (int i = 0; i < n; ++i) {
      if (basiz[i] >= 0 && matrix[i][col] > 0) {
        SimpleFractions val = matrix[i][0] / matrix[i][col];
        CO[i] = val;
        if (row == -1 || CO[row] > val) {
          row = i;
        }
      }
    }
    if (row == -1)
      break;

    PrintTable(matrix, basiz, ignoredColumns, CO, col, row);

    std::vector<std::vector<SimpleFractions>> nmatrix = SquareMethod(matrix, row, col);

    if (fakeCol[basiz[row]]) {
      ignoredColumns.insert(basiz[row]);
    }
    basiz[row] = col;

    matrix = nmatrix;
  }
  std::vector<std::vector<SimpleFractions>> nmatrix(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < matrix[i].size(); ++j) {
      if (ignoredColumns.count(j) > 0) {
        continue;
      }
      nmatrix[i].push_back(matrix[i][j]);
    }
  }
  return nmatrix;
}

std::vector<std::vector<SimpleFractions>> GetInput(std::string filename) {
  std::vector<std::vector<SimpleFractions>> res;
  std::ifstream f(filename);
  std::string str;
  while (getline(f, str)) {
    std::vector<SimpleFractions> tmp;
    std::stringstream ss(str);
    SimpleFractions x;
    while (ss >> x) {
      tmp.push_back(x);
    }
    res.push_back(tmp);
  }

  return res;
}