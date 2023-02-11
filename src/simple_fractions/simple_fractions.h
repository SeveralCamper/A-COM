#pragma once 

#include <cmath>
#include <iomanip> 
#include <sstream>
#include <iostream>

#define EPS_CHECK 0.0001

class SimpleFractions {
    public:
        SimpleFractions& operator=(const SimpleFractions& other);
        void operator+=(const SimpleFractions& other);
        SimpleFractions operator+(const SimpleFractions& other);
        void operator-=(const SimpleFractions& other);
        SimpleFractions operator-(const SimpleFractions& other);
        void operator*=(const SimpleFractions& other);
        SimpleFractions operator*(const SimpleFractions& other);
        void operator/=(const SimpleFractions& other);
        SimpleFractions operator/(const SimpleFractions& other);


        SimpleFractions() = delete;
        SimpleFractions(long long int numerator, long long int denominator) : numerator_(numerator),
            denominator_(denominator) {}
        SimpleFractions(double fraction);
        ~SimpleFractions() {}

        void printSimpleFraction();
        void setNumenator(long long int new_numenator);
        void setDenominator(long long int new_denominator);

        long long getNumenator();
        long long getDenominator();
        double convertToDouble();

    private:
        long long int numerator_;
        long long int denominator_;
};