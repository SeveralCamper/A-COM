#pragma once 

#include <cmath>
#include <iomanip> 
#include <sstream>
#include <iostream>

#define EPS_CHECK 0.0001

class SimpleFractions {
    public:

        SimpleFractions() = delete;
        SimpleFractions(double numerator, double denominator) : numerator_(numerator),
            denominator_(denominator) {}
        SimpleFractions(double fraction);
        ~SimpleFractions() {}

        void printSimpleFraction();
        void setNumenator(double new_numenator);
        void setDenominator(double new_denominator);

        long long getNumenator();
        long long getDenominator();
        double convertToDouble();

    private:
        double numerator_;
        double denominator_;
};