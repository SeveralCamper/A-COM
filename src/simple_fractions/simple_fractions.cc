#include "simple_fractions.h"

SimpleFractions& SimpleFractions::operator=(const SimpleFractions& other) {
    numerator_ = other.numerator_;
    denominator_ = other.denominator_;
}

void SimpleFractions::operator+=(const SimpleFractions& other) {
    if (denominator_ == other.denominator_) {
        numerator_ += other.numerator_;
    } else {

    }
}

SimpleFractions SimpleFractions::operator+(const SimpleFractions& other) {

}

void SimpleFractions::operator-=(const SimpleFractions& other) {

}

SimpleFractions SimpleFractions::operator-(const SimpleFractions& other) {

}

void SimpleFractions::operator*=(const SimpleFractions& other) {

}

SimpleFractions SimpleFractions::operator*(const SimpleFractions& other) {

}

void SimpleFractions::operator/=(const SimpleFractions& other) {
    
}

SimpleFractions SimpleFractions::operator/(const SimpleFractions& other) {

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