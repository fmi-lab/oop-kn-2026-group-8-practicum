#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

unsigned gcd(unsigned a, unsigned b) {
  if (b % a == 0) {
    return a;
  }

  if (a > b) {
    return gcd(b, a);
  }

  return gcd(b % a, a);
}

bool begins_with(const char* str, const char* substr) {
  while (*str && *substr && *str == *substr) {
    ++str;
    ++substr;
  }

  return *substr == '\0';
}

char* find_word(char* str, const char* substr) {
  while (*str) {
    if (begins_with(str, substr)) {
      return str;
    }

    ++str;
  }

  return nullptr;
}

void shift(char* str, std::size_t n) {
  while (str[n]) {
    std::iter_swap(str, str + n);
    ++str;
  }

  *str = '\0';
}

void remove_word(char* str, const char* substr) {
  char* occurence = find_word(str, substr);
  std::size_t size = strlen(substr);

  while (occurence) {
    shift(occurence, size);

    occurence = find_word(occurence, substr);
  }
}

bool equal(
  const int* first_begin, 
  const int* first_end, 
  const int* second_begin, 
  const int* second_end) {
  while (
    first_begin != first_end && 
    second_begin != second_end &&
    *first_begin == *second_begin
  ) {
    ++first_begin;
    ++second_begin;
  }

  return first_begin == first_end && second_begin == second_end;
}

const int* partition(int* begin, int* end, int element) {
  while (begin != end) {
    if (*begin < element) {
      ++begin;
    } else {
      std::iter_swap(begin, --end);
      // std::swap(*begin, *(end - 1));
    }
  }

  return begin;
}

void print(const int* begin, const int* end) {
  while (begin != end) {
    std::cout << *begin << ' ';
    ++begin;
  }
  std::cout << '\n';
}

constexpr std::size_t MAX_SIZE = 255;

bool is_valid(
  char matrix[][MAX_SIZE],
  int rows, 
  int cols,
  int x, int y,
  const char* word
) {
  return x >= 0 && x < rows && y >= 0 && y < cols && matrix[x][y] == *word;
}

bool find_words_in_crossword_helper(
  char matrix[][MAX_SIZE], 
  int rows, 
  int cols,
  int x, int y,
  const char* word,
  bool visited[][MAX_SIZE]
) {
  if (*word == '\0') {
    return true;
  }

  if (visited[x][y]) {
    return false;
  }

  visited[x][y] = true;

  if (
    is_valid(matrix, rows, cols, x + 1, y, word) && 
    find_words_in_crossword_helper(matrix, rows, cols, x + 1, y, word + 1, visited)
  ) {
    return true;
  }

  if (
    is_valid(matrix, rows, cols, x - 1, y, word) && 
    find_words_in_crossword_helper(matrix, rows, cols, x - 1, y, word + 1, visited)
  ) {
    return true;
  }

  if (
    is_valid(matrix, rows, cols, x, y + 1, word) && 
    find_words_in_crossword_helper(matrix, rows, cols, x, y + 1, word + 1, visited)
  ) {
    return true;
  }

  if (
    is_valid(matrix, rows, cols, x, y - 1, word) && 
    find_words_in_crossword_helper(matrix, rows, cols, x, y - 1, word + 1, visited)
  ) {
    return true;
  }

  visited[x][y] = false;

  return false;
}

unsigned find_words_in_crossword(
  char matrix[][MAX_SIZE], 
  std::size_t rows, 
  std::size_t cols, 
  char words[][MAX_SIZE], 
  std::size_t n
) {
  unsigned counter = 0;
  for (std::size_t i = 0; i < n; ++i) {
    bool visited[MAX_SIZE][MAX_SIZE]{};

    for (std::size_t x = 0; x < rows; ++x) {
      for (std::size_t y = 0; y < cols; ++y) {
        if (find_words_in_crossword_helper(matrix, rows, cols, x, y, words[i], visited)) {
          ++counter;
        }
      }
    } 
  }

  return counter;
}

int main() {
  char matrix[][255] = {{'c', 'a', 't'},
                      {'w', 'h', 'o'},
                      {'w', 'i', 'n'}};
  char words[][255] = {"cat", "hello", "what", "caca"};
  std::cout << find_words_in_crossword(matrix, 3, 3, words, 4) << '\n'; // -> 2
  // -> cat, what
  return 0;
}