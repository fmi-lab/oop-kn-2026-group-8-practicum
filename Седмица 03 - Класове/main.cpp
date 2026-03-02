#include <iostream>
#include <cmath>
#include "rational.hpp"
#include "temp.hpp"

int main() {
  Rational r(1, 0);

  r.set_numerator(3);
  r.set_numerator(5);

  Rational r1(2);
  Rational r2(2, 4);

  r2.set_denominator(16);
  r2.set_numerator(8);

  std::cout << r.get_numerator() << '/' << r.get_denominator() << '\n';
  std::cout << r1.get_numerator() << '/' << r1.get_denominator() << '\n';
  std::cout << r2.get_numerator() << '/' << r2.get_denominator() << '\n';
  return 0;
}