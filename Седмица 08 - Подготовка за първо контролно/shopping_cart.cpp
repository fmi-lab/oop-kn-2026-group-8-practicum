#include "shopping_cart.hpp"
#include "product.hpp"
#include <cstddef>
#include <utility>

ShoppingCart::ShoppingCart(std::size_t N)
  : products(new ShoppingCartProduct[N]),
    N(N), size(0) {}

ShoppingCart::ShoppingCart(const ShoppingCart& other)
  : products(new ShoppingCartProduct[other.N]),
    N(other.N), size(other.size) {
  for (std::size_t i = 0; i < other.size; ++i) {
    products[i] = other.products[i];
  }
}

ShoppingCart::ShoppingCart(ShoppingCart&& other)
  : products(std::exchange(other.products, nullptr)),
    N(std::move(other.N)),
    size(std::move(other.size)) {}

ShoppingCart::~ShoppingCart() {
  delete [] products;
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other) {
  ShoppingCart copy(other);
  swap(copy);

  return *this;
}

ShoppingCart& ShoppingCart::operator=(ShoppingCart&& other) {
  ShoppingCart copy(std::move(other));
  swap(copy);

  return *this;
}

ShoppingCart& ShoppingCart::add_product(const Product& p, unsigned quantity) {
  ShoppingCartProduct* existing = find_product(p);

  if (existing) {
    existing->quantity += quantity;
  } else if (size < N) {
    products[size++] = {
      .product = p,
      .quantity = quantity
    };
  }

  return *this;
}

double ShoppingCart::total_price() const {
  double price = 0.0;

  for (std::size_t i = 0; i < size; ++i) {
    ShoppingCartProduct& current = products[i];
    price += current.product.get_price() * current.quantity;
  }

  return price;
}

void ShoppingCart::print(std::ostream& output) const {
  for (std::size_t i = 0; i < size; ++i) {
    ShoppingCartProduct& current = products[i];

    current.product.print(output);
    output << '\n' << current.quantity << '\n';
  }
}

void ShoppingCart::import_products(std::istream& input) {
  Product product;

  while (input.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
    add_product(product, 1);
  }
}

void ShoppingCart::swap(ShoppingCart& other) {
  std::swap(products, other.products);
  std::swap(N, other.N);
  std::swap(size, other.size);
}

ShoppingCart::ShoppingCartProduct* ShoppingCart::find_product(const Product& p) const {
  for (std::size_t i = 0; i < size; ++i) {
    ShoppingCartProduct& current = products[i];
    
    if (current.product == p) {
      return &current;
    }
  }

  return nullptr;
}
