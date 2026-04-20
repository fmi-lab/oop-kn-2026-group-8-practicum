#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

class Polynomial {
public:
  Polynomial() 
    : coefficients(nullptr), size(0), capacity(0) {}
  Polynomial(const Polynomial& other)
    : coefficients(new float[other.capacity]),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      coefficients[i] = other.coefficients[i];
    }
  }
  Polynomial(Polynomial&& other)
    : coefficients(std::exchange(other.coefficients, nullptr)),
      size(std::move(other.size)),
      capacity(std::move(other.capacity)) {}
  ~Polynomial() {
    delete[] coefficients;
  }
  Polynomial& operator=(const Polynomial& other) {
    Polynomial copy(other);
    swap(copy);

    return *this;
  }
  Polynomial& operator=(Polynomial&& other) {
    Polynomial copy(std::move(other));
    swap(copy);

    return *this;
  }

  Polynomial& add_coefficient(float coef) {
    if (size == capacity) {
      resize();
    }

    coefficients[size++] = coef;

    return *this;
  }

  float operator()(float x) const {
    float result = 0;

    for (std::size_t i = 0; i < size; ++i) {
      result += coefficients[i] * std::pow(x, i);
    }

    return result;
  }

  float& operator[](std::size_t i) {
    return coefficients[i];
  }

  float operator[](std::size_t i) const {
    return coefficients[i];
  }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial result;

    std::size_t min_degree = std::min(size, other.size);
    std::size_t max_degree = std::max(size, other.size);

    for (std::size_t i = 0; i < min_degree; ++i) {
      result.add_coefficient(coefficients[i] + other.coefficients[i]);
    }

    const Polynomial& poly = max_degree == size ? *this : other;
    for (std::size_t i = min_degree; i < max_degree; ++i) {
      result.add_coefficient(poly.coefficients[i]);
    }

    return result;
  }

  bool operator==(const Polynomial& other) const {
    if (size != other.size) {
      return false;
    }

    if (size == 0) {
      return true;
    }

    std::size_t i = 0;
    while (i < size && coefficients[i] == other.coefficients[i] && coefficients[i] == 0) {
      ++i;
    }

    if (i == size) {
      return true;
    }

    if (coefficients[i] == 0 || other.coefficients[i] == 0) {
      return false;
    }

    float ratio = coefficients[i] / other.coefficients[i];
    for (i += 1; i < size; ++i) {
      if (other.coefficients[i] * ratio != coefficients[i]) {
        return false;
      }
    }

    return true;
  }

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

private:
  float *coefficients;
  std::size_t size, capacity;

  void swap(Polynomial& other) {
    std::swap(coefficients, other.coefficients);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    float* new_coefficients = new float[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_coefficients[i] = coefficients[i];
    }

    delete [] coefficients;
    coefficients = new_coefficients;
  }
};

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
  for (int i = p.size - 1; i >= 1; --i) {
    os << p.coefficients[i] << "x^" << i << " + ";
  }
  return os << p.coefficients[0];
}

int main() {
  Polynomial p1, p2;
  p1.add_coefficient(2).add_coefficient(3).add_coefficient(1);
  p2.add_coefficient(5).add_coefficient(6).add_coefficient(3).add_coefficient(1);

  p1[0] = 5;

  std::cout << "p1(x) = " << p1 << '\n';
  std::cout << "p2(x) = " << p2 << '\n';

  std::cout << "p1(1) = " << p1(1) << '\n';
  std::cout << "p2(2) = " << p2(2) << '\n';

  std::cout << "(p1 + p2)(x) = " << p1 + p2 << '\n';

  Polynomial p3;
  p3.add_coefficient(10).add_coefficient(6).add_coefficient(2);

  // p3[0] = 0; p3[1] = 0; p3[2] = 0;
  // p1[0] = 0; p1[1] = 0; p1[2] = 0;

  std::cout << std::boolalpha << (p1 == p3) << '\n';
  return 0;
}