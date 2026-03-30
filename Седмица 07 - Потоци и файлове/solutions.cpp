#include <cstddef>
#include <cstring>
#include <ios>
#include <iostream>
#include <fstream>

class Book {
public:
  Book(const char* name = "", const char* author = "", unsigned id = 0)
    : id(id) {
    strcpy(this->name, name);
    strcpy(this->author, author);
  }

  void serialize(std::ostream& os) const {
    os << name << '\n' << author << '\n' << id << '\n';
  }

  void deserialize(std::istream& is) {
    if (is.peek() == '\n') {
      is.ignore();
    }
    is.getline(name, MAX_NAME_SIZE);
    is.getline(author, MAX_AUTHOR_SIZE);
    is >> id;
  }

  void serialize_binary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(this), sizeof(Book));

    // os.write(name, MAX_NAME_SIZE);
    // os.write(author, MAX_AUTHOR_SIZE);
    // os.write(reinterpret_cast<const char*>(&id), sizeof(id));
  }

  void deserialize_binary(std::istream& is) {
    is.read(reinterpret_cast<char*>(this), sizeof(Book));
  }

  void serialize_at(std::ostream &os, std::size_t pos) const {
    os.seekp(0, std::ios::end);
    std::streampos size = os.tellp();
    std::size_t books_count = size / sizeof(Book);

    if (pos <= books_count) {
      os.seekp((pos - 1) * sizeof(Book));
      os.write(reinterpret_cast<const char*>(this), sizeof(Book));
    }
  }

private:
  static constexpr std::size_t MAX_NAME_SIZE = 100;
  static constexpr std::size_t MAX_AUTHOR_SIZE = 100;
  
  char name[MAX_NAME_SIZE], author[MAX_AUTHOR_SIZE];
  unsigned id;
};

int main() {
  Book book1("Hobbit", "J. R. R. Tolkien", 1);
  Book book2("The Lord of the Rings", "J. R. R. Tolkien", 2);
  Book book3("The Silmarilion", "J. R. R. Tolkien", 3);

  std::ofstream output("output.bin", std::ios::binary);
  book1.serialize_binary(output);
  book2.serialize_binary(output);

  book3.serialize_at(output, 2);
  output.close();
  
  // Book book1, book2;
  // // int a;

  std::ifstream input("output.bin", std::ios::binary);

  book1.deserialize_binary(input);
  // // input >> a;
  book2.deserialize_binary(input);

  // input.close();

  book1.serialize(std::cout);
  book2.serialize(std::cout);
  return 0;
}