#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

class MathExpression {
public:
  virtual float evaluate() const = 0;
  virtual std::ostream& print(std::ostream& = std::cout) const = 0;
  virtual MathExpression* clone() const = 0;
  virtual ~MathExpression() = default;
};

template <typename T>
class Vector {
public:
  explicit Vector(std::size_t capacity = 0)
    : data(new T[capacity]), size(0), capacity(capacity) {}

  Vector(const Vector& other)
    : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      data[i] = other.data[i];
    }
  }

  Vector(Vector&& other)
    : data(std::exchange(other.data, nullptr)),
      size(std::move(other.size)),
      capacity(std::move(other.capacity)) {}

  ~Vector() {
    delete [] data;
  }

  Vector<T>& operator=(const Vector& other) {
    Vector<T> copy(other);
    swap(copy);

    return *this;
  }

  Vector<T>& operator=(Vector&& other) {
    Vector<T> copy(std::move(other));
    swap(copy);

    return *this;
  }

  void push_back(const T& element) {
    if (size == capacity) {
      resize();
    }

    data[size++] = element;
  }

  const T& operator[](std::size_t index) const {
    return data[index];
  }
  T& operator[](std::size_t index) {
    return data[index];
  }
  std::size_t length() const {
    return size;
  }
  
  void swap(Vector& other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

private:
  T* data;
  std::size_t size, capacity;

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    T* new_data = new T[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;
  }
};

class Constant : public MathExpression {
public:
  Constant(float value) : value(value) {}

  float evaluate() const final {
    return value;
  }

  std::ostream& print(std::ostream& os = std::cout) const final {
    return os << value;
  }

  Constant* clone() const final {
    return new Constant(*this);
  }

private:
  float value;
};

class Sum : public MathExpression {
public:
  Sum() = default;

  Sum(const Sum& other): expresssions(other.expresssions) {
    for (std::size_t i = 0; i < other.expresssions.length(); ++i) {
      expresssions[i] = other.expresssions[i]->clone();
    }
  }

  Sum(Sum&& other)
    : expresssions(std::exchange(other.expresssions, Vector<MathExpression*>())) {}

  ~Sum() {
    for (std::size_t i = 0; i < expresssions.length(); ++i) {
      delete expresssions[i];
    }
  }

  Sum& operator=(const Sum& other) {
    Sum copy(other);
    swap(copy);

    return *this;
  }

  Sum& operator=(Sum&& other) {
    Sum copy(std::move(other));
    swap(copy);

    return *this;
  }

  Sum& add(const MathExpression& expresssion) {
    expresssions.push_back(expresssion.clone());
    return *this;
  }

  float evaluate() const final {
    float result = 0.0;
    
    for (std::size_t i = 0; i < expresssions.length(); ++i) {
      result += expresssions[i]->evaluate();
    }

    return result;
  }

  std::ostream& print(std::ostream& os = std::cout) const final {
    if (expresssions.length() == 0) {
      return os;
    }

    os << '(';
    expresssions[0]->print(os);

    for (std::size_t i = 1; i < expresssions.length(); ++i) {
      os << " + ";
      expresssions[i]->print(os);
    }

    return os << ')';
  }
  
  Sum* clone() const final {
    return new Sum(*this);
  }

private:
  Vector<MathExpression*> expresssions;

  void swap(Sum& other) {
    expresssions.swap(other.expresssions);
  }
};

class Power : public MathExpression {
public:
  Power(const MathExpression& base, int exponent)
    : base(base.clone()), exponent(exponent) {}

  Power(const Power& other)
    : base(other.base->clone()), exponent(other.exponent) {}

  Power(Power&& other)
    : base(std::exchange(other.base, nullptr)),
      exponent(std::move(other.exponent)) {}

  ~Power() {
    delete base;
  }

  Power& operator=(const Power& other) {
    Power copy(other);
    swap(copy);

    return *this;
  }

  Power& operator=(Power&& other) {
    Power copy(std::move(other));
    swap(copy);

    return *this;
  }

  float evaluate() const final {
    int current_exponent = exponent;
    float result = 1, current_base = base->evaluate();
    
    if (current_exponent < 0) {
      current_exponent = std::abs(current_exponent);
      current_base = 1 / current_base;
    }

    while (current_exponent > 0) {
      if (current_exponent % 2 == 0) {
        current_base *= current_base;
        current_exponent /= 2;
      } else {
        --current_exponent;
        result *= current_base;
      }
    }

    return result;
  }

  std::ostream& print(std::ostream& os = std::cout) const final {
    os << '(';
    return base->print(os) << ")^" << exponent;
  }

  Power* clone() const final {
    return new Power(*this);
  }

private:
  MathExpression* base;
  int exponent;

  void swap(Power& other) {
    std::swap(base, other.base);
    std::swap(exponent, other.exponent);
  }
};

int main() {
  Constant c1(4), c2(7), c3(5);
  Sum s1, s2;

  s1.add(c1);

  s2.add(c2);
  s2.add(c3);

  s1.add(s2);

  Power p(s1, -2);
  p.print() << " = " << p.evaluate() << '\n';
  return 0;
}