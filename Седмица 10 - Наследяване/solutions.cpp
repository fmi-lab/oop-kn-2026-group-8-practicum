#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <utility>

class Person {
public:
  Person(const char* name, const char* email, unsigned age)
    : name(new char[strlen(name) + 1]{}),
      email(new char[strlen(email) + 1]{}),
      age(age) {
    strcpy(this->name, name);
    strcpy(this->email, email);
  }

  Person(const Person& other)
    : name(new char[strlen(other.name) + 1]{}),
      email(new char[strlen(other.email) + 1]{}),
      age(other.age) {
    strcpy(name, other.name);
    strcpy(email, other.email);
  }

  Person(Person&& other)
    : name(std::exchange(other.name, nullptr)),
      email(std::exchange(other.email, nullptr)),
      age(std::move(other.age)) {}

  Person& operator=(const Person& other) {
    Person copy(other);
    swap(copy);

    return *this;
  }  

  Person& operator=(Person&& other) {
    Person copy(std::move(other));
    swap(copy);

    return *this;
  }  

  ~Person() {
    delete [] name;
    delete [] email;
  }

  void print() const {
    std::cout << "Name: " << name << '\n'
              << "Email: " << email << '\n'
              << "Age: " << age << '\n';
  }

  // void send_mail(const char* message) const {
  //   std::ofstream inbox(email, std::ios::app);
  //   greet(inbox) << ":\n" << message << '\n';
  //   inbox.close();
  // }

  void send_mail(const char* message) const {
    std::ofstream inbox(email, std::ios::app);
    inbox << "To " << name << ":\n" << message << '\n';
    inbox.close();
  }

  void view_inbox() const {
    std::ifstream inbox(email);
    std::cout << inbox.rdbuf() << '\n';
    // char buff[101]{};
    // while (inbox.good()) {
    //   inbox.read(buff, 100);
    //   std::cout << buff;
    // }
    inbox.close();
  }

private:
  unsigned age;

protected:
  char *name, *email;
  
  void swap(Person& other) {
    std::swap(name, other.name);
    std::swap(email, other.email);
    std::swap(age, other.age);
  }

  // std::ostream& greet(std::ostream& os) const {
  //   return os << "To " << name;
  // }
};

class Student : public Person {
public:
  Student(const char* name, const char* email, unsigned age, const char* fn)
    : Person(name, email, age), fn(new char[strlen(fn) + 1]{}) {
    strcpy(this->fn, fn);
  }

  Student(const Student& other)
    : Person(other), fn(new char[strlen(other.fn) + 1]{}) {
    strcpy(fn, other.fn);
  }

  Student(Student&& other)
    : Person(std::move(other)), fn(std::exchange(other.fn, nullptr)) {}

  ~Student() {
    delete [] fn;
  }

  Student& operator=(const Student& other) {
    Student copy(other);
    swap(copy);

    return *this;
    // Person::operator=(other);
    // if (this != &other) {
    //   delete [] fn;
    //   fn = new char[strlen(other.fn) + 1]{};
    //   strcpy(fn, other.fn);
    // }

    // return *this;
  }

  Student& operator=(Student&& other) {
    Student copy(std::move(other));
    swap(copy);

    return *this;
  }

  void print() const {
    Person::print();
    std::cout << "Faculty number: " << fn <<'\n';
  }

  void send_mail(const char* message) const {
    std::ofstream inbox(email, std::ios::app);
    inbox << "To " << name << ", " << fn << ":\n" << message << '\n';
    inbox.close();
  }

private:
  char *fn;

  void swap(Student& other) {
    Person::swap(other);
    std::swap(fn, other.fn);
  }

  // std::ostream& greet(std::ostream& os) const {
  //   return Person::greet(os) << ", " << fn;
  // }
};

int main() {
  Person p("Pesho", "pesho@gmail.com", 20);
  p.send_mail("Zdr kpr");
  p.send_mail("Ko staa");

  p.print();
  std::cout << '\n';
  p.view_inbox();

  Student s("Marko", "marko@gmail.com", 19, "3MI0824534");
  s.print();
  std::cout << '\n';
  s.send_mail("Zdr kp");
  s.view_inbox();

  Person ps = static_cast<Person>(s);
  ps.print();
  std::cout << '\n';
  ps.send_mail("Zvunni mi");
  ps.view_inbox();
  return 0;
}