#pragma once

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <limits.h>

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <stdexcept>

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
               
  std::vector<std::vector<SimpleFractions>> GetMatrix() const;
  SimpleFractions GetElement(int i, int j) const;

  void SetRows(int rows_);                               
  void SetCols(int cols_);
  void SetElement(int i, int j, SimpleFractions data);

  void PrintMatrix();            
  void RemoveMatrix();
  void ReduceMatrix();
  void PrintSLAE() const; 
  void PrintResault() const;           
  void CheckAllPosibleBases(); 
  void PrintTransmitionMatrix();
  void FillMatrix(double iterator);
  void GoToNextBasis(std::vector<int> prev_basis, std::vector<int> next_basis);

  int CalculateSLAE();

  void GetMatrix(std::string path);      

 private:
  int rows_, cols_, posible_bases = 1;
  std::vector<std::vector<SimpleFractions>> matrix_;
  std::vector<std::vector<int>> transition_matrix_;

  SimpleFractions FindAbsMaxElement(int shift, int pos);

  bool NextSet(int *vector, int length, int sample);

  int PostProcessing(std::vector<int> *deleting_vector);

  void SetToIdentity();
  void PrintBasis(int *vector, int sample);
  void AddingScalingFactors(int pos, SimpleFractions main_element);
};
