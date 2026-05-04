#ifndef SORTED_HPP
#define SORTED_HPP

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <utility>

template <typename T>
class Sorted {
public:
  Sorted();
  Sorted(const T* arr, std::size_t size);

  Sorted(const Sorted& other);
  Sorted(Sorted&& other);
  ~Sorted();
  Sorted<T>& operator=(const Sorted& other);
  Sorted<T>& operator=(Sorted&& other);

  Sorted<T>& add(const T& element);
  bool search(const T& element);
  const T& operator[](std::size_t index) const;
  std::size_t get_size() const { return size; }

  // template <typename U>
  // friend std::ostream& operator<<(std::ostream& os, const Sorted<U>& sorted);

private:
  T* data;
  std::size_t size, capacity;

  void swap(Sorted& other);
  void resize();
  void insert(const T& element);
  T* binary_search(const T& element) const;
};

template <typename T>
Sorted<T>::Sorted() : data(nullptr), size(0), capacity(0) {}

template <typename T>
Sorted<T>::Sorted(const T* arr, std::size_t size)
  : data(new T[size]), size(0), capacity(size) {
  for (std::size_t i = 0; i < size; ++i) {
    add(arr[i]);
  }
}

template <typename T>
Sorted<T>::Sorted(const Sorted& other)
  : data (new T[other.capacity]{}),
    size(other.size),
    capacity(other.capacity) {
  for (std::size_t i = 0; i < other.size; ++i) {
    data[i] = other.data[i];
  }
}

template <typename T>
Sorted<T>::Sorted(Sorted&& other)
  : data(std::exchange(other.data, nullptr)),
    size(std::move(other.size)),
    capacity(std::move(other.capacity)) {}

template <typename T>
Sorted<T>::~Sorted() {
  delete [] data;
}

template <typename T>
Sorted<T>& Sorted<T>::operator=(const Sorted& other) {
  Sorted<T> copy(other);
  swap(copy);

  return *this;
}

template <typename T>
Sorted<T>& Sorted<T>::operator=(Sorted&& other) {
  Sorted<T> copy(std::move(other));
  swap(copy);

  return *this;
}

template <typename T>
Sorted<T>& Sorted<T>::add(const T& element) {
  if (size == capacity) {
    resize();
  }

  insert(element);
  return *this;
}

template <typename T>
void Sorted<T>::swap(Sorted& other) {
  std::swap(data, other.data);
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
}

template <typename T>
void Sorted<T>::resize() {
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

template <typename T>
void Sorted<T>::insert(const T& element) {
  data[size++] = element;

  int i = size - 1;
  while (i >= 1 && data[i - 1] > data[i]) {
    std::iter_swap(data + i - 1, data + i);
    --i;
  }
}

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Sorted<T>& sorted) {
//   for (std::size_t i = 0; i < sorted.size; ++i) {
//     os << sorted.data[i] << ' ';
//   }

//   return os << '\n';
// }

template <typename T>
bool Sorted<T>::search(const T& element) {
  return binary_search(element);
}

template <typename T>
T* Sorted<T>::binary_search(const T& element) const {
  T *begin = data, *end = data + size;

  while (begin < end) {
    T* mid = begin + (end - begin) / 2;
    if (*mid == element) {
      return mid;
    } else if (*mid < element) {
      begin = mid + 1;
    } else {
      end = mid;
    }
  }

  return nullptr;
}

template <typename T>
const T& Sorted<T>::operator[](std::size_t index) const {
  return data[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Sorted<T>& sorted) {
  for (std::size_t i = 0; i < sorted.get_size(); ++i) {
    os << sorted[i] << ' ';
  }
  return os << '\n';
}

#endif