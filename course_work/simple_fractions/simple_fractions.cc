#include "simple_fractions.h"

long long numerator_,denominator_;
long long SimpleFractions::NOD(long long numerator, long long denominator) {
    if(denominator == 0) return numerator;
    return NOD(denominator, numerator % denominator);
}

long long SimpleFractions::ABS_ll(long long x) {
    if(x<0)
        x=-x;
    return x;
}

SimpleFractions::SimpleFractions(long long numerator, long long denominator) {
    if(denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
    this->numerator_ = numerator;
    this->denominator_ = denominator;
    Simplify();
}

SimpleFractions::SimpleFractions(const SimpleFractions &x) {
    numerator_=x.numerator_;
    denominator_=x.denominator_;
}

void SimpleFractions::Simplify() {
    long long c=NOD(ABS_ll(numerator_),ABS_ll(denominator_));
    numerator_/=c;
    denominator_/=c;
}

SimpleFractions SimpleFractions::operator+(const SimpleFractions &x) const {
    SimpleFractions res(numerator_*x.denominator_ + x.numerator_*denominator_, denominator_*x.denominator_);
    
    return res;
}

SimpleFractions SimpleFractions::operator-(const SimpleFractions &x) const {
    return (*this)+SimpleFractions(-x.numerator_, x.denominator_);
}

SimpleFractions SimpleFractions::operator*(const SimpleFractions &x) const {
    SimpleFractions res(numerator_*x.numerator_, denominator_*x.denominator_);
    
    return res;
}

SimpleFractions SimpleFractions::operator/(const SimpleFractions &x) const {
    return (*this)*SimpleFractions(x.denominator_,x.numerator_);
}

SimpleFractions SimpleFractions::operator/=(const SimpleFractions &x) {
    (*this)=(*this)/x;
    
    return *this;
}

bool SimpleFractions::operator>(const SimpleFractions &x) const {
    return this->numerator_*x.denominator_ > x.numerator_*this->denominator_;
}

bool SimpleFractions::operator>(long long x) const {
    return (*this)>SimpleFractions(x);
}

bool SimpleFractions::operator<(const SimpleFractions &x) const {
    return this->numerator_*x.denominator_ < x.numerator_*this->denominator_;
}

bool SimpleFractions::operator<(long long x) const {
    return (*this)<SimpleFractions(x);
}

bool SimpleFractions::operator==(const SimpleFractions &x) const {
    return numerator_==x.numerator_ && denominator_==x.denominator_;
}

bool SimpleFractions::operator==(long long &x) const {
    return (*this)==SimpleFractions(x);
}

bool SimpleFractions::operator!=(long long x) const {
    return !((*this)==x);
}

SimpleFractions SimpleFractions::operator-() const {
    return SimpleFractions(-numerator_, denominator_);
}



SimpleFractions SimpleFractions::ABS_sf() {
    long long f=numerator_;
    if(f<0) f=-f;
    
    return SimpleFractions(f, denominator_);
}


std::ostream& operator<<(std::ostream& s, const SimpleFractions &x) {
	std::stringstream ss;
	ss << x.numerator_;
	if(x.denominator_!=1) {
		 ss<<"/"<<x.denominator_;
	}
	s << ss.str();
	return s;
}

std::istream& operator>>(std::istream& s, SimpleFractions& fraction) {
	std::string str;
	s >> str;
	for(auto it = str.rbegin(); it!=str.rend(); it++) {

		s.putback(*it);
	}
	int index=0;
	if((index = str.find('/'))>=0) {
		s >> fraction.numerator_;
		s >> fraction.denominator_;
		fraction.Simplify();
	} else {
		s >> fraction.numerator_;
		fraction.denominator_=1;
		fraction.Simplify();
	}
	return s;
}
