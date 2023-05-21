#pragma once

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#include "../simple_fractions/simple_fractions.h"

#define EPS 1e-7

class MatrixFractions {
public:
  MatrixFractions();
  MatrixFractions(int rows, int cols);
  ~MatrixFractions();

  SimpleFractions operator()(int i, int j) const;

  int GetRows() const;
  int GetCols() const;

  std::vector<double> GetNeeds();
  std::vector<double> GetReservers();

  std::vector<std::vector<SimpleFractions>> GetMatrix() const;
  SimpleFractions GetElement(int i, int j) const;

  MatrixFractions Transpose();

  void SetRows(int rows_);
  void SetCols(int cols_);
  void SetElement(int i, int j, SimpleFractions data);

  void PrintMatrix();
  void RemoveMatrix();
  void ReduceMatrix();
  void TransportTask();
  void BasesTransition();
  void PrintSLAE() const;
  void PrintNeeds(int new_cols);
  void PrintReserves(int new_rows);
  void PrintResult(std::vector<int> current_basis) const;
  void CheckAllPosibleBases();
  void PrintTransmitionMatrix();
  void FillMatrix(double iterator);

  int CheckBalance();
  int CalculateSLAE();

  void GetMatrix(std::string path);
  void GetTransportMatrix(std::string path);

private:
  int rows_, cols_, posible_bases = 1;

  std::vector<std::vector<SimpleFractions>> matrix_;
  std::vector<std::vector<int>> transition_matrix_;

  std::vector<double> needs_;
  std::vector<double> reserves_;

  SimpleFractions FindAbsMaxElement(int shift, int pos);

  bool NextSet(int *vector, int length, int sample);

  int PostProcessing(std::vector<int> *deleting_vector);

  void SetToIdentity();
  void PrintBasis(int *vector, int sample);
  void AddingScalingFactors(int pos, SimpleFractions main_element);
};
