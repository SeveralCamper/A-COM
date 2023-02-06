#include "simple_fractions.h"

SimpleFractions::SimpleFractions(double fraction) {
    int i;
    double numerator = 0, denominator = 0;

    denominator = modf(fraction, &numerator);
    std::stringstream ss;
    ss << std::setprecision(8) <<  fraction;
    std::string strNum = ss.str();
    size_t pos = strNum.find('.');
    for (i = 0; i < strNum.size() - 1 - pos; i++) {
        denominator *= 10;
    }
    numerator_ = numerator * pow(10, i) + denominator;
    denominator_ = pow(10, i);
}

void SimpleFractions::printSimpleFraction() {
    std::cout << std::fixed << numerator_ << '/' << denominator_ << ' ';
}

void SimpleFractions::setNumenator(double new_numenator) {
    numerator_ = new_numenator;
}

void SimpleFractions::setDenominator(double new_denominator) {
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