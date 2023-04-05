#include <iostream>
#include <cstring>
#include <stdexcept>

#ifndef RATIONAL_H
#define RATIONAL_H

class RationalDivisionByZero : public std::runtime_error {
public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
private:
  int32_t a = 1;
  int32_t b = 1;

  int GCD(int32_t a, int32_t b);
  void Reduce();

public:
  Rational(int32_t a = 0, int32_t b = 1);
  Rational(const Rational& r);

 // double Dec();

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational operator-();
  Rational operator+();

  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int32_t a);
  void SetDenominator(int32_t b);

  int NumFromStr(char str[], int left, int right);
};

std::ostream& operator<<(std::ostream& os, Rational number);

std::istream& operator>>(std::istream& is, Rational number);

Rational operator+(const Rational& number, const Rational& other);
Rational operator-(const Rational& number, const Rational& other);
Rational operator*(const Rational& number, const Rational& other);
Rational operator/(const Rational& number, const Rational& other);

bool operator<(const Rational& left, const Rational& right);
bool operator>(const Rational& left, const Rational& right);
bool operator==(const Rational& left, const Rational& right);
bool operator<=(const Rational& left, const Rational& right);
bool operator>=(const Rational& left, const Rational& right);

#endif
