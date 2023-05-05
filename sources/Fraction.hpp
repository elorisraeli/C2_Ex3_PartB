#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

namespace ariel
{
    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        Fraction();
        explicit Fraction(int numer, int denom);
        explicit Fraction(float value);

        int getNumerator();
        int getDenominator();

        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        Fraction operator+=(const Fraction &other);
        Fraction operator-=(const Fraction &other);
        Fraction operator*=(const Fraction &other);
        Fraction operator/=(const Fraction &other);

        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        friend bool operator==(const Fraction &other, float rightSide);
        friend bool operator!=(const Fraction &other, float rightSide);
        friend bool operator<(const Fraction &other, float rightSide);
        friend bool operator<=(const Fraction &other, float rightSide);
        friend bool operator>(const Fraction &other, float rightSide);
        friend bool operator>=(const Fraction &other, float rightSide);

        friend bool operator==(float leftSide, const Fraction &other);
        friend bool operator!=(float leftSide, const Fraction &other);
        friend bool operator<(float leftSide, const Fraction &other);
        friend bool operator<=(float leftSide, const Fraction &other);
        friend bool operator>(float leftSide, const Fraction &other);
        friend bool operator>=(float leftSide, const Fraction &other);

        friend Fraction operator+(float leftSide, const Fraction &rightSide);
        friend Fraction operator-(float leftSide, const Fraction &rightSide);
        friend Fraction operator*(float leftSide, const Fraction &rightSide);
        friend Fraction operator/(float leftSide, const Fraction &rightSide);

        Fraction operator+(float rightSide) const;
        Fraction operator-(float rightSide) const;
        Fraction operator*(float rightSide) const;
        Fraction operator/(float rightSide) const;
        Fraction operator+=(float rightSide);
        Fraction operator-=(float rightSide);
        Fraction operator*=(float rightSide);
        Fraction operator/=(float rightSide);

        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);
        Fraction &operator++();

        friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);
        friend std::istream &operator>>(std::istream &istream, Fraction &frac);

        void reduce();
        int lcm(int num_a, int num_b) const;
    };
}

#endif // FRACTION_HPP