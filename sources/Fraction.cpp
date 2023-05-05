#include <iostream>
#include <cmath>
#include <limits>

#include "Fraction.hpp"

using namespace std;

namespace ariel
{
    Fraction::Fraction()
    {
        numerator = 1;
        denominator = 1;
    }

    Fraction::Fraction(int numer, int denom) : numerator(numer), denominator(denom)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero, deviding by zero is illegal");
        }
        if (numerator == 0)
        {
            denominator = 1;
        }
        // make the denominator positive
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }
        reduce();
    }

    // as i remember from the Numbers Algorithems Course
    int gcd_f(int num_a, int num_b)
    {
        if (num_b == 0)
            return num_a;
        else
            return gcd_f(num_b, num_a % num_b);
    }

    // functionality to lcm of 2 numbers
    int Fraction::lcm(int num_a, int num_b) const
    {
        return (num_a / gcd_f(num_a, num_b)) * num_b;
    }

    Fraction::Fraction(float value)
    {
        if (value == 0)
        {
            numerator = 0;
            denominator = 1;
            return;
        }

        float rounded_value = round(value * 1000.0f) / 1000.0f;
        numerator = static_cast<int>(rounded_value * 1000);
        denominator = 1000;

        if (numerator == 0)
        {
            denominator = 1;
        }
        reduce();
    }

    int Fraction::getNumerator()
    {
        return numerator;
    }
    int Fraction::getDenominator()
    {
        return denominator;
    }

    void Fraction::reduce()
    {
        int numer = (numerator < 0) ? -numerator : numerator; // to give the function positive number
        int gcd_num = gcd_f(numer, denominator);
        numerator /= gcd_num;
        denominator /= gcd_num;
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        long long num = (long long)numerator * other.denominator + (long long)denominator * other.numerator;
        long long den = (long long)denominator * other.denominator;
        if (num > numeric_limits<int>::max() || num < numeric_limits<int>::min())
        {
            throw overflow_error("Addition overflow.");
        }
        return Fraction(num, den);
    }
    Fraction Fraction::operator-(const Fraction &other) const
    {
        long long num = (long long)numerator * other.denominator - (long long)denominator * other.numerator;
        long long den = (long long)denominator * other.denominator;
        if (num > numeric_limits<int>::max() || num < numeric_limits<int>::min()) {
            throw overflow_error("Subtraction overflow.");
        }
        return Fraction(num, den);
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;

        if (((numerator != 0) && (newNumerator / numerator != other.numerator)) ||
            ((denominator != 0) && (newDenominator / denominator != other.denominator)))
        {
            throw overflow_error("Cannot complete the calculation, OVERFLOW ACCURE");
        }
        int gcd_new = gcd_f(newNumerator, newDenominator);
        return Fraction(newNumerator / gcd_new, newDenominator / gcd_new);
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
        {
            throw runtime_error("Cannot proccess the operator /");
        }

        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;

        if (((numerator != 0) && (newNumerator / numerator != other.denominator)) ||
            ((denominator != 0) && (newDenominator / denominator != other.numerator)))
        {
            throw overflow_error("Cannot complete the calculation, OVERFLOW ACCURE");
        }
        return Fraction(newNumerator, newDenominator);
    }

    Fraction Fraction::operator+=(const Fraction &other)
    {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator-=(const Fraction &other)
    {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator = denominator * other.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator*=(const Fraction &other)
    {
        numerator *= other.numerator;
        denominator *= other.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator/=(const Fraction &other)
    {
        numerator *= other.denominator;
        denominator *= other.numerator;
        reduce();
        return *this;
    }

    bool Fraction::operator==(const Fraction &other) const
    {
        float my_float = static_cast<float>(numerator) / static_cast<float>(denominator);
        float other_float = static_cast<float>(other.numerator) / static_cast<float>(other.denominator);
        Fraction my_frac = Fraction(my_float);
        Fraction other_frac = Fraction(other_float);
        return ((my_frac.numerator == other_frac.numerator) && (my_frac.denominator == other_frac.denominator));
    }

    bool Fraction::operator!=(const Fraction &other) const
    {
        return !(*this == other); // this '==' is from this class
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return numerator * other.denominator < denominator * other.numerator;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return (numerator * other.denominator <= denominator * other.numerator);
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return numerator * other.denominator > denominator * other.numerator;
    }
    bool Fraction::operator>=(const Fraction &other) const
    {
        return (numerator * other.denominator >= denominator * other.numerator);
    }

    bool operator==(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) == rightSide;
    }
    bool operator!=(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) != rightSide;
    }
    bool operator<(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) < rightSide;
    }
    bool operator<=(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) <= rightSide;
    }
    bool operator>(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) > rightSide;
    }
    bool operator>=(const Fraction &other, float rightSide)
    {
        return (static_cast<float>(other.numerator) / other.denominator) >= rightSide;
    }

    bool operator==(float leftSide, const Fraction &other)
    {
        return (static_cast<float>(other.numerator) / other.denominator) == leftSide;
    }
    bool operator!=(float leftSide, const Fraction &other)
    {
        return (static_cast<float>(other.numerator) / other.denominator) != leftSide;
    }
    bool operator<(float leftSide, const Fraction &other)
    {
        return leftSide < (static_cast<float>(other.numerator) / other.denominator);
    }
    bool operator<=(float leftSide, const Fraction &other)
    {
        return leftSide <= (static_cast<float>(other.numerator) / other.denominator);
    }
    bool operator>(float leftSide, const Fraction &other)
    {
        return leftSide > (static_cast<float>(other.numerator) / other.denominator);
    }
    bool operator>=(float leftSide, const Fraction &other)
    {
        return leftSide >= (static_cast<float>(other.numerator) / other.denominator);
    }

    Fraction operator+(float leftSide, const Fraction &other)
    {
        Fraction f_num = Fraction(leftSide);
        int newNumerator = f_num.numerator * other.denominator + other.numerator * f_num.denominator;
        int newDenominator = f_num.denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator-(float leftSide, const Fraction &other)
    {
        Fraction f_num = Fraction(leftSide);
        int newNumerator = f_num.numerator * other.denominator - other.numerator * f_num.denominator;
        int newDenominator = f_num.denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator*(float leftSide, const Fraction &other)
    {
        Fraction f_num = Fraction(leftSide);
        int newNumerator = f_num.numerator * other.numerator;
        int newDenominator = f_num.denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator/(float leftSide, const Fraction &other)
    {
        Fraction f_num = Fraction(leftSide);
        int newNumerator = f_num.numerator * other.denominator;
        int newDenominator = f_num.denominator * other.numerator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction Fraction::operator+(float rightSide) const
    {
        float my_float = static_cast<float>(numerator) / static_cast<float>(denominator);
        Fraction my_frac = Fraction(my_float);

        Fraction f_num = Fraction(rightSide);
        int newNumerator = f_num.numerator * my_frac.denominator + my_frac.numerator * f_num.denominator;
        int newDenominator = f_num.denominator * my_frac.denominator;

        return Fraction(newNumerator, newDenominator);
    }
    Fraction Fraction::operator-(float rightSide) const
    {
        Fraction f_num = Fraction(rightSide);
        int newNumerator = numerator * f_num.denominator - f_num.numerator * denominator;
        int newDenominator = f_num.denominator * denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction Fraction::operator*(float rightSide) const
    {
        Fraction f_num = Fraction(rightSide);
        int newNumerator = f_num.numerator * numerator;
        int newDenominator = f_num.denominator * denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction Fraction::operator/(float rightSide) const
    {
        if (rightSide == 0)
        {
            throw runtime_error("Cannot proccess the operator /");
        }

        Fraction f_num = Fraction(rightSide);
        int newNumerator = f_num.denominator * numerator;
        int newDenominator = f_num.numerator * denominator;
        return Fraction(newNumerator, newDenominator);
    }
    Fraction Fraction::operator+=(float rightSide)
    {
        Fraction f_num = Fraction(rightSide);
        numerator = numerator * f_num.denominator + f_num.numerator * denominator;
        denominator = denominator * f_num.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator-=(float rightSide)
    {
        Fraction f_num = Fraction(rightSide);
        numerator = numerator * f_num.denominator - f_num.numerator * denominator;
        denominator = denominator * f_num.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator*=(float rightSide)
    {
        Fraction f_num = Fraction(rightSide);
        numerator *= f_num.numerator;
        denominator *= f_num.denominator;
        reduce();
        return *this;
    }
    Fraction Fraction::operator/=(float rightSide)
    {
        Fraction f_num = Fraction(rightSide);
        numerator *= f_num.denominator;
        denominator *= f_num.numerator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction result(*this);
        numerator += denominator;
        reduce();
        return result;
    }

    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        reduce();
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction result(*this);
        numerator -= denominator;
        reduce();
        return result;
    }

    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        reduce();
        return *this;
    }

    ostream &operator<<(ostream &out, const Fraction &frac)
    {
        out << frac.numerator << '/' << frac.denominator;
        return out;
    }

    istream &operator>>(istream &istream, Fraction &frac)
    {
        int numer, denom;
        if ((istream >> numer) && (istream >> denom))
        {
            if (denom == 0)
            {
                throw runtime_error("Cannot proccess the istream");
            }
            if (numer == 0)
            {
                denom = 1;
            }
            if (denom < 0)
            {
                numer *= -1;
                denom *= -1;
            }
            frac.numerator = numer;
            frac.denominator = denom;
        }
        else
        {
            throw runtime_error("Cannot proccess the istream");
        }

        return istream;
    }
}