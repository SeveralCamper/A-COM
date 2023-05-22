#pragma once

#include "../simple_fractions/simple_fractions.h"

const int WIDTH = 8;

void PrintTable(const std::vector<std::vector<SimpleFractions>> &matrix,
                std::vector<int> bazis);

void PrintTable(const std::vector<std::vector<SimpleFractions>> &matrix,
                std::vector<int> bazis, std::set<int> ignoredColumns,
                std::vector<SimpleFractions> CO, int selectedColumns,
                int selectedRows);

std::vector<std::vector<SimpleFractions>> SquareMethod(const std::vector<std::vector<SimpleFractions>> &matrix, int row, int col);
std::vector<std::vector<SimpleFractions>> SimplexMethod(std::vector<std::vector<SimpleFractions>> matrix, std::vector<int> &basiz,
              std::vector<bool> fakeCol);
std::vector<std::vector<SimpleFractions>> GetZLP(std::string filpe_path);