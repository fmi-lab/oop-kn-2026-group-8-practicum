#include <cstddef>
#include <cstring>
#include <iostream>

constexpr std::size_t MAX_FN_SIZE = 11;
constexpr std::size_t MAX_MARKS_SIZE = 100;
constexpr std::size_t MAX_STRING_SIZE = 256;

struct Mark {
  char subject[MAX_STRING_SIZE];
  float grade;
};

struct Student {
  char name[MAX_STRING_SIZE];
  char fn[MAX_FN_SIZE];
  unsigned year;
  Mark marks[MAX_MARKS_SIZE];
  std::size_t marks_count;

  double grade() {
    float sum = 0;

    for (std::size_t i = 0; i < marks_count; ++i) {
      sum += marks[i].grade;
    }

    return sum / marks_count;
  }

  void print() {
    std::cout << "Name: " << name << '\n'
              << "Faculty number: " << fn << '\n'
              << "Year: " << year << '\n'
              << "Average grade: " << grade() << '\n';
  }
};

struct StudentArray {
  Student* data;
  std::size_t capacity, size;

  void push_back(Student student) {
    if (size == capacity) {
      resize();
    }

    data[size++] = student;
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Student* new_data = new Student[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }

    delete [] data;
    data = new_data;
  }
};

struct University {
  char name[MAX_STRING_SIZE];
  StudentArray students;

  void add_student(Student student) {
    students.push_back(student);
  }

  Student* find_student(const char* fn) {
    for (std::size_t i = 0; i < students.size; ++i) {
      Student& student = students.data[i];

      if (strcmp(fn, student.fn) == 0) {
        return &student;
      }
    }

    return nullptr;
  }

  void print() {
    std::cout << "Name: " << name << '\n'
              << "Students:\n";
    
    for (std::size_t i = 0; i < students.size; ++i) {
      students.data[i].print();
      std::cout << '\n';
    }
  }

  StudentArray get_by_year(unsigned year) {
    StudentArray result{nullptr, 0, 0};

    for (std::size_t i = 0; i < students.size; ++i) {
      Student student = students.data[i];

      if (year == student.year) {
        result.push_back(student);
      }
    }

    return result;
  }
};

int main() {
  Student student_ivan{
    .name = "Ivan Ivanov",
    .fn = "3MI0800092",
    .year = 2,
    .marks = {
      {"Linear algebra", 5.56},
      {"Intro to programming", 5.84},
      {"Discrete structures", 4.35}
    },
    .marks_count = 3
  };

  StudentArray students{
    .data = new Student[0],
    .capacity = 0,
    .size = 0
  };

  Student student_petkan{
    .name = "Petkan Georgiev",
    .fn = "5MI0800145",
    .year = 1,
    .marks = {
      {"Discrete structures", 3.75},
      {"Mathematical analysis", 4.25}
    },
    .marks_count = 2
  };

  students.push_back(student_ivan);
  students.push_back(student_petkan);

  University university{
    .name = "Sofia University \"St. Kliment Ohridski\"",
    .students = students
  };

  university.print();

  Student* student = university.find_student("5MI0800145");

  if (student) {
    std::cout << "Found student:\n";
    student->print();
  } else {
    std::cout << "Missing student with faculty number: 5MI0800145\n"; 
  }

  std::cout << '\n';
  StudentArray arr = university.get_by_year(2);
  for (std::size_t i = 0; i < arr.size; ++i) {
    std::cout << arr.data[i].name << '\n';
  }

  delete [] students.data;
  delete [] arr.data;
  return 0;
}