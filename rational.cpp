#include <iostream>
#include <cstring>
#include <stdexcept>
#include "rational.h"

int Rational::GCD(int32_t a, int32_t b) {
  while (a != 0 and b != 0) {
    if (a > b) {
      a = a % b;
    }
    else {
      b = b % a;
    }
  }
  return (a + b);
}
void Rational::Reduce() {
  int32_t gcd = GCD(a, b);
  a /= gcd;
  b /= gcd;
}

 Rational::Rational(int32_t a = 0, int32_t b = 1) {
    this->a = a;
    this->b = b;

    Reduce();
    if (b < 0) {
      this->a = -a;
      this->b = -b;
    }
  }
  Rational::Rational(const Rational& r) {
    a = r.a;
    b = r.b;
  }

  // double Rational::Dec() {
  //   double dec_a = a;
  //   double dec_b = b;
  //   return dec_a / dec_b;
  // }

  Rational& Rational::operator+=(const Rational& other) {
    a = a * other.b + b * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& Rational::operator-=(const Rational& other) {
    a = a * other.b - b * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& Rational::operator*=(const Rational& other) {
    a = a * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& Rational::operator/=(const Rational& other) {
    a = a * other.b;
    b = b * other.a;
    Reduce();
    return *this;
  }

  Rational& Rational::operator++() {
    a += b;
    return *this;
  }
  Rational Rational::operator++(int) {
    Rational copy(a, b);
    a += b;
    return copy;
  }
  Rational& Rational::operator--() {
    a -= b;
    return *this;
  }
  Rational Rational::operator--(int) {
    Rational copy(a, b);
    a -= b;
    return copy;
  }
  Rational Rational::operator-() {
    Rational opposite(-a, b);
    return opposite;
  }
  Rational Rational::operator+() {
    Rational number(a, b);
    return number;
  }

  int Rational::GetNumerator() const {
    return a;
  }
  int Rational::GetDenominator() const {
    return b;
  }
  void Rational::SetNumerator(int32_t a) {
    this->a = a;
    Reduce();
  }
  void Rational::SetDenominator(int32_t b) {
    if (b == 0) {
      throw RationalDivisionByZero();
    }
    this->b = b;
    Reduce();
  }

  int Rational::NumFromStr(char str[], int left, int right) {
    int32_t number = 0;
    int d = 1;
    bool is_minus = false;

    if (str[0] == '-') {
      is_minus = true;
    }
    else if (str[0] != '+') {
      d = 0;
    }

    for (int i = a + d; i < b; ++i) {
      number = (number * 10) + (str[i] - '0');
    }
    return (is_minus ? -number : number);
  }

///////////////////////

std::ostream& operator<<(std::ostream& os, Rational number) {
  if (number.GetDenominator() == 1) {
    os << number.GetNumerator();
  }
  else {
    os << number.GetNumerator() << "/" << number.GetDenominator();
  }
  return os;
}

std::istream& operator>>(std::istream& is, Rational number) {
  char str[100];
  for (int i = 0; i < 100; ++i) {
    str[i] = '\0';
  }
  bool is_minus = false;
  is >> str;
  int len = strlen(str);
  int i_slash;
  for (int i = 0; i < len; ++i) {
    if (str[i] == '/') {
      i_slash = i;
      break;
    }
  }

  number.SetNumerator(number.NumFromStr(str, 0, i_slash));
  number.SetDenominator(number.NumFromStr(str, i_slash + 1, len));

  return is;
}

Rational operator+(const Rational& number, const Rational& other) {
  Rational copy = number;
  copy += other;
  return copy;
}
Rational operator-(const Rational& number, const Rational& other) {
  Rational copy = number;
  copy -= other;
  return copy;
}
Rational operator*(const Rational& number, const Rational& other) {
  Rational copy = number;
  copy *= other;
  return copy;
}
Rational operator/(const Rational& number, const Rational& other) {
  Rational copy = number;
  copy /= other;
  return copy;
}

bool operator<(const Rational& left, const Rational& right) {
  return left.GetNumerator() * right.GetDenominator() < right.GetNumerator() * left.GetDenominator();
}
bool operator>(const Rational& left, const Rational& right) {
  return right < left;
}
bool operator==(const Rational& left, const Rational& right) {
  return !(right < left or right > left);
}
bool operator<=(const Rational& left, const Rational& right) {
  return (left < right or left == right);
}
bool operator>=(const Rational& left, const Rational& right) {
  return !(left > right or left == right);
}

Footer
© 2023 GitHub, Inc.
Footer navigation
Terms
Privacy
