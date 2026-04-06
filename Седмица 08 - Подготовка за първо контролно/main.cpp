#include <cstdlib>
#include <iostream>
#include <fstream>
#include "shopping_cart.hpp"

int main() {
  Product p1(1, "Apples", 1.99);
  Product p2(2, "Carrots", 3.99);
  Product p3(1, "Apples", 2.99);

  p1.print(std::cout);
  std::cout << '\n';
  p2.print(std::cout);
  std::cout << '\n';
  p3.print(std::cout);
  std::cout << std::boolalpha << '\n' << (p1 == p3) << "\n\n";

  ShoppingCart cart(10);
  cart.add_product(p1, 2).add_product(p2, 4).add_product(p3, 3);
  
  std::fstream file("products.bin", std::ios::out | std::ios::binary);
  p1.serialize(file);
  p2.serialize(file);
  p3.serialize(file);
  file.close();

  file.open("products.bin", std::ios::in | std::ios::binary);
  cart.import_products(file);
  file.close();
  
  cart.print(std::cout);
  std::cout << '\n' << cart.total_price() << '\n';
  return 0;
}