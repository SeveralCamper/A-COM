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
        
        bool operator>(const SimpleFractions& other);
        bool operator<(const SimpleFractions& other);
        bool operator!=(const SimpleFractions& other);

        SimpleFractions AbsFraction();

        SimpleFractions() = delete;
        SimpleFractions(long long int numerator, long long int denominator);
        SimpleFractions(double fraction);
        ~SimpleFractions() {}

        void ReduceFraction();
        void PrintSimpleFraction();
        void SetNumenator(long long int new_numenator);
        void SetDenominator(long long int new_denominator);

        long long GetNumenator();
        long long GetDenominator();
        double ConvertToDouble();

        long long int SearchNOK(long long int n1, long long int n2);
        long long int SearchNOD(long long int n1, long long int n2);

    private:
        long long int numerator_;
        long long int denominator_;
};