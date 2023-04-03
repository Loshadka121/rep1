#include <iostream>

class RationalDivZero : public std::exception {};

class Rational {
private:
  int a = 1;
  int b = 1;

  int GCD(int a, int b) {
    while (a != 0 and b != 0) {
      if (a > b) {
        a = a % b;
      } else {
        b = b % a;
      }
    }
    return (a + b);
  }
  void Reduce() {
    int gcd = GCD(a, b);
    a /= gcd;
    b /= gcd;
  }

public:
  Rational(int a = 0, int b = 1) {
    this->a = a;
    this->b = b;

    Reduce();
    if (b < 0) {
      this->a = -a;
      this->b = -b;
    }
  }
  Rational(const Rational& r) {
    a = r.a;
    b = r.b;
  }

  double Dec() {
    double dec_a = a;
    double dec_b = b;
    return dec_a / dec_b;
  }

  Rational& operator+=(const Rational& other) {
    a = a * other.b + b * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& operator-=(const Rational& other) {
    a = a * other.b - b * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& operator*=(const Rational& other) {
    a = a * other.a;
    b = b * other.b;
    Reduce();
    return *this;
  }
  Rational& operator/=(const Rational& other) {
    a = a * other.b;
    b = b * other.a;
    Reduce();
    return *this;
  }

  Rational& operator++() {
    a += b;
    return *this;
  }
  Rational operator++(int) {
    Rational copy(a, b);
    a += b;
    return copy;
  }
  Rational& operator--() {
    a -= b;
    return *this;
  }
  Rational operator--(int) {
    Rational copy(a, b);
    a -= b;
    return copy;
  }
  Rational operator-() {
    Rational opposite(-a, b);
    return opposite;
  }
  Rational operator+() {
    Rational number(a, b);
    return number;
  }

  int GetA() const {
    return a;
  }
  int GetB() const {
    return b;
  }
  void SetA(int a) {
    this->a = a;
    Reduce();
  }
  void SetB(int b) {
    if (b == 0) {
      throw RationalDivZero();
    }
    this->b = b;
    Reduce();
  }
};

std::ostream& operator<<(std::ostream& os, Rational number) {
  if (number.GetB() == 1) {
    os << number.GetA();
  }
  else {
    os << number.GetA() << "/" << number.GetB();
  }
  return os;
}
std::istream& operator>>(std::istream& is, Rational number) {
  char str[101];
  str[100] = '\0';
  bool is_minus = false;
  is >> str;
  int c = 0, d = 0, len = strlen(str), i;
  for (i = 0; i < len; ++i) {
    if (str[i] == '-') {
      is_minus = !is_minus;
    }
    else if (str[i] == '+') {
      continue;
    }
    else if (str[i] != '/') {
      c = c * 10 + (str[i] - '0');
    }
    else {
      ++i;
      break;
    }
  }
  if (i == len) {
    d = 1;
  }
  for (; i < len; ++i) {
    if (str[i] == '-') {
      is_minus = !is_minus;
    }
    else if (str[i] != '+') {
      d = d * 10 + (str[i] - '0');
    }
  }
  if (is_minus) {
    c = -c;
  }
  number.SetB(1);
  number.SetA(c);
  number.SetB(d);
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
  return left.GetA() * right.GetB() < right.GetA() * left.GetB();
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

int main() {

  Rational r, l;
  std::cin >> r;
  std::cin >> l;

  std::cout << r << ' ' << l << '\n';


  return 0;
}
Footer
© 2023 GitHub, Inc.
Footer navigation
Terms
Privacy
