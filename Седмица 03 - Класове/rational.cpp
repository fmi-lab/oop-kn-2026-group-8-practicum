#include "rational.hpp"
#include <algorithm>

Rational::Rational(int numerator, int denominator)
  : numerator(numerator), denominator(1) {
  set_numerator(numerator);
  set_denominator(denominator);
  normalize();
}

int Rational::get_numerator() const {
  return numerator;
}

int Rational::get_denominator() const {
  return denominator;
}

void Rational::set_numerator(/*this, */ int numerator) {
  this->numerator = numerator;
  normalize();
}

void Rational::set_denominator(int denominator) {
  if (denominator != 0) {
    this->denominator = denominator;
    normalize();
  }
}

int Rational::gcd() const {
  if (numerator == 0) {
    return 1;
  }

  int a = std::min(numerator, denominator);
  int b = std::max(numerator, denominator);

  while (a != 0) {
    int temp = a;
    a = b % a;
    b = temp;
  }

  return b;
}

void Rational::normalize() {
  int d = gcd();

  numerator /= d;
  denominator /= d;
}