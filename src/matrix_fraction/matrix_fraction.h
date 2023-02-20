#pragma once

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <limits.h>

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
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
                       
  void RemoveMatrix();
  void ReduceMatrix();
  void PrintMatrix();  
  void PrintSLAE() const; 
  void PrintResault() const;                           
  void FillMatrix(double iterator);

  int CalculateSLAE();

  void GetMatrix(std::string path);      

 private:
  int rows_, cols_;
  std::vector<std::vector<SimpleFractions>> matrix_;

  SimpleFractions FindAbsMaxElement(int shift, int pos);

  int PostProcessing(std::vector<int> *deleting_vector);

  void SetToIdentity();
  void AddingScalingFactors(int pos, SimpleFractions main_element);
};
