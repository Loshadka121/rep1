#include <iostream>
#include <cstring>

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

  int NumFromStr(char str[], int left, int right) {
    int number = 0;
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
  char str[100];
  for (int i = 0; i < 100; ++i) {
    str[i] = '\0' ;
  }
  int len = strlen(str);
  bool is_minus = false;
  is >> str;
  int i_slash;
  for (int i = 0; i < len; ++i) {
    if (str[i] == '/') {
      i_slash = i;
      break;
    }
  }

  number.SetA(number.NumFromStr(str, 0, i_slash));
  number.SetB(number.NumFromStr(str, i_slash + 1, len));

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
