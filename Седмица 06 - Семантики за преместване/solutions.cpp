#include <cstring>
#include <iostream>
#include <utility>

class A {
public:
  A (int x) : x(x) {}
  A (const A& other) : x(other.x) {
    std::cout << "copy constructor\n";
  }
  A (A&& other) : x(std::exchange(other.x, 0)) {
    std::cout << "move constructor\n";
  }

private:
  int x;
};

A foo() {
  return A(7);
}

class String {
public:
private:
  char* str;
};

class Dish {
public:
  Dish(const char* name, float price, unsigned quantity, unsigned calories)
    : name(new char[strlen(name) + 1]{}), 
      price(price), 
      quantity(quantity),
      calories(calories) {
    strcpy(this->name, name);
  }

  Dish(const Dish& other)
    : name(new char[strlen(other.name) + 1]{}), 
      price(other.price), 
      quantity(other.quantity),
      calories(other.calories) {
    strcpy(name, other.name);
  }

  Dish(Dish&& other)
    : name(std::exchange(other.name, nullptr)),
      price(std::move(other.price)),
      quantity(std::move(other.quantity)),
      calories(std::move(other.calories)) {}

  ~Dish() {
    delete [] name;
  }

  Dish& operator=(const Dish& other) {
    Dish copy(other);
    swap(copy);

    return *this;
  }

  Dish& operator=(Dish&& other) {
    Dish copy(std::move(other));
    swap(copy);

    return *this;
  }

  bool operator<(const Dish& other) const {
    float ratio_this = price / quantity;
    float ratio_other = other.price / other.quantity;

    if (ratio_this == ratio_other) {
      return calories < other.calories;
    }

    return ratio_this < ratio_other;
  }

private:
  char* name;
  float price;
  unsigned quantity, calories;

  void swap(Dish& other) {
    std::swap(name, other.name);
    std::swap(price, other.price);
    std::swap(quantity, other.quantity);
    std::swap(calories, other.calories);
  }
};

int main() {
  return 0;
}