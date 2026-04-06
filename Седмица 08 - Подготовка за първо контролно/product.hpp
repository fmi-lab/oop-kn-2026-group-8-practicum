#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <cstddef>
#include <ostream>

class Product {
public:
  Product(unsigned id = 0, const char* name = "", double price = 0.0);

  double get_price() const;
  bool operator==(const Product& other) const;
  void print(std::ostream& output) const;
  void serialize(std::ostream& output) const;

private:
  static constexpr std::size_t MAX_NAME_SIZE = 101;

  unsigned id;
  char name[MAX_NAME_SIZE];
  double price;
};

#endif