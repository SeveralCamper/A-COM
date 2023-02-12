#pragma once

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <limits.h>

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../simple_fractions/simple_fractions.h"

#define EPS 1e-7

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  ~Matrix();

  double operator()(int i, int j) const;    

  int GetRows() const;                   
  int GetCols() const;
               
  double** GetMatrix() const;
  double GetElement(int i, int j) const;

  void SetRows(int rows_);                               
  void SetCols(int cols_);
  void SetElement(int i, int j, double data);
                       
  void RemoveMatrix();
  void PrintSLAE(int model) const;
  void MemoryAllocation();  
  void PrintMatrix() const;                             
  void FillMatrix(double iterator);

  void CalculateSLAE(int model);

  void GetMatrix(std::string path);      

 private:
  int rows_, cols_;
  double** matrix_;

  double FindAbsMaxElement(int shift, int pos);

  bool PostProcessing();

  void SetToIdentity();
  void AddingScalingFactors(int pos, double main_element);
};
