#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class SimpleFractions {
private:
  long long numerator_, denominator_;
  long long ABS_ll(long long x);
  long long NOD(long long numerator, long long denominator);

public:
  SimpleFractions(const SimpleFractions &x);
  SimpleFractions(long long numerator = 0, long long denominator = 1);

  friend std::ostream &operator<<(std::ostream &s, const SimpleFractions &x);
  friend std::istream &operator>>(std::istream &s, SimpleFractions &fraction);

  void Simplify();

  SimpleFractions operator/=(const SimpleFractions &x);

  SimpleFractions operator-() const;
  SimpleFractions operator+(const SimpleFractions &x) const;
  SimpleFractions operator-(const SimpleFractions &x) const;
  SimpleFractions operator*(const SimpleFractions &x) const;
  SimpleFractions operator/(const SimpleFractions &x) const;

  bool operator<(long long x) const;
  bool operator>(long long x) const;
  bool operator!=(long long x) const;
  bool operator==(long long &x) const;

  bool operator>(const SimpleFractions &x) const;
  bool operator<(const SimpleFractions &x) const;
  bool operator==(const SimpleFractions &x) const;

  SimpleFractions ABS_sf();
};