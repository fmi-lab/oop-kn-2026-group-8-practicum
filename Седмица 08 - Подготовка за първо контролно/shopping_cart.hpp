#ifndef SHOPPING_CART_HPP
#define SHOPPING_CART_HPP

#include "product.hpp"
#include <cstddef>
#include <istream>
#include <ostream>

class ShoppingCart {
public:
  ShoppingCart(std::size_t N);
  ShoppingCart(const ShoppingCart& other);
  ShoppingCart(ShoppingCart&& other);
  ~ShoppingCart();
  ShoppingCart& operator=(const ShoppingCart& other);
  ShoppingCart& operator=(ShoppingCart&& other);

  ShoppingCart& add_product(const Product& p, unsigned quantity);
  double total_price() const;
  void print(std::ostream& output) const;
  void import_products(std::istream& input);

private:
  struct ShoppingCartProduct {
    Product product;
    unsigned quantity;
  };

  ShoppingCartProduct* products;
  size_t size, N;

  void swap(ShoppingCart& other);
  ShoppingCartProduct* find_product(const Product& p) const;
};

#endif