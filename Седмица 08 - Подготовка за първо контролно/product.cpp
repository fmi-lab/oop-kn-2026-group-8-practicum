#include "product.hpp"
#include <cstring>

Product::Product(unsigned id, const char* name, double price) 
  : id(id), price(price) {
  strcpy(this->name, name);
}

double Product::get_price() const {
  return price;
}

bool Product::operator==(const Product& other) const {
  return id == other.id;
}

void Product::print(std::ostream& output) const {
  output << id << '\n'
         << name << '\n'
         << price;
}

void Product::serialize(std::ostream& output) const {
  output.write(reinterpret_cast<const char*>(this), sizeof(Product));
}
