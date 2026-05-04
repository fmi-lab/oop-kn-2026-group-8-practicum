#include <iostream>
#include "sorted.hpp"

int main() {
  int arr[] = {5, 1, 8, 4, 11};
  Sorted<int> s(arr, 5);
  s.add(6);

  std::cout << s;
  std::cout << std::boolalpha << s.search(8) << '\n';
  return 0;
}