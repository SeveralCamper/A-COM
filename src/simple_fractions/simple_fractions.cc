#include "simple_fractions.h"

SimpleFractions& SimpleFractions::operator=(const SimpleFractions& other) {
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;
}

void SimpleFractions::operator+=(const SimpleFractions& other) {
    if (denominator_ == other.denominator_) {
        numerator_ += other.numerator_;
    } else {
        long long int NOK = SearchNOK(denominator_, other.denominator_);
        long long int first_mult = NOK / denominator_, second_mult = NOK / other.denominator_;
        numerator_ *= first_mult;
        numerator_ += (other.numerator_ * second_mult);
        denominator_ = NOK;
    }
}

void SimpleFractions::operator-=(const SimpleFractions& other) {
    if (denominator_ == other.denominator_) {
        numerator_ -= other.numerator_;
    } else {
        long long int NOK = SearchNOK(denominator_, other.denominator_);
        long long int first_mult = NOK / denominator_, second_mult = NOK / other.denominator_;
        numerator_ *= first_mult;
        numerator_ -= (other.numerator_ * second_mult);
        denominator_ = NOK;
    }
}

void SimpleFractions::operator*=(const SimpleFractions& other) {
    numerator_ *= other.numerator_;
    denominator_ *= other.denominator_;
}

void SimpleFractions::operator/=(const SimpleFractions& other) {
    numerator_ *= other.denominator_;
    denominator_ *= other.numerator_;
}

SimpleFractions SimpleFractions::operator+(const SimpleFractions& other) {
    SimpleFractions new_frac(numerator_, denominator_);
    new_frac += other;
    return new_frac;
}

SimpleFractions SimpleFractions::operator-(const SimpleFractions& other) {
    SimpleFractions new_frac(numerator_, denominator_);
    new_frac -= other;
    return new_frac;
}

SimpleFractions SimpleFractions::operator*(const SimpleFractions& other) {
    SimpleFractions new_frac(numerator_, denominator_);
    new_frac *= other;
    return new_frac;
}

SimpleFractions SimpleFractions::operator/(const SimpleFractions& other) {
    SimpleFractions new_frac(numerator_, denominator_);
    new_frac /= other;
    return new_frac;
}

void SimpleFractions::ReduceFraction() {
    long long int NOD = SearchNOD(numerator_, denominator_);
    numerator_ /= NOD;
    denominator_ /= NOD;
}

SimpleFractions::SimpleFractions(double fraction) {
    int num = 0;
    double numerator_d = 0;
    long long int numerator = 0, denominator = 0;

    denominator = modf(fraction, &numerator_d);
    numerator = numerator_d;
    std::stringstream ss;
    ss << std::setprecision(8) <<  fraction;
    std::string strNum = ss.str();
    size_t pos = strNum.find('.');
    for (auto i = 0; i < strNum.size() - 1 - pos; i++) {
        denominator *= 10;
        num = (int) i;
    }
    numerator_ = numerator * pow(10, num) + denominator;
    denominator_ = pow(10, num);
}

void SimpleFractions::printSimpleFraction() {
    if (abs(numerator_) < EPS_CHECK) {
        std::cout << std::fixed << 0.0f;
    } else {
        std::cout << std::fixed << numerator_ << '/' << denominator_;
    }
}

void SimpleFractions::setNumenator(long long int new_numenator) {
    numerator_ = new_numenator;
}

void SimpleFractions::setDenominator(long long int new_denominator) {
    denominator_ = new_denominator;
}

long long SimpleFractions::getNumenator() {
    return numerator_;
}

long long SimpleFractions::getDenominator() {
    return denominator_;
}

double SimpleFractions::convertToDouble() {
    return numerator_ / denominator_;
}

long long int SimpleFractions::SearchNOD(long long int n1, long long int n2) {
  long long int div;
  if (n1 == n2)  return n1;
  long long int d = n1 - n2;
  if (d < 0) {
    d = -d;  div = SearchNOD(n1, d);
  } else
    div = SearchNOD(n2, d); 
  return div;
}

long long int SimpleFractions::SearchNOK(long long int n1, long long int n2) { 
  return n1*n2 / SearchNOD(n1, n2); 
}