#ifndef RATIONAL_HPP
#define RATIONAL_HPP

class Rational {
public:
  Rational(int numerator, int denominator = 1);

  int get_numerator() const;
  int get_denominator() const;

  void set_numerator(int);
  void set_denominator(int);

private:
  int numerator;
  int denominator;

  int gcd() const;
  void normalize();
};

#endif