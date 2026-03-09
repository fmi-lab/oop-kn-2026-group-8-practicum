#include <cstddef>
#include <cstring>
#include <iostream>

class Person {
public:
  Person(const char* name)
    : name(new char[strlen(name) + 1]) {
    strcpy(this->name, name);
  }

  ~Person() {
    delete [] name;
  }

  void info() const {
    std::cout << "Name: " << name << '\n';
  }

private:
  char* name;
};

enum class Genre {
  comedy = 5,
  action = 'a',
  animation,
  romance,
  fantasy
};

const char* genre_to_string(const Genre& genre) {
  switch (genre) {
    case Genre::comedy:
      return "comedy";
    case Genre::action:
      return "action";
    case Genre::animation:
      return "animation";
    case Genre::romance:
      return "romance";
    case Genre::fantasy:
      return "fantasy";
    }
}

int add(int a, int b) {
  return a + b;
}

enum class State {
  not_started,
  in_progress,
  completed
};

const char* state_to_string(State state) {
  switch (state) {
  case State::not_started:
    return "Not Started";
  case State::in_progress:
    return "In Progress";
  case State::completed:
    return "Completed";
  }
}

class Task {
public:
  Task(
    const char* name, 
    const char* description, 
    State state
  )
    : name(new char[strlen(name) + 1]{}),
      description(new char[strlen(description) + 1]{}),
      state(state) {
    strcpy(this->name, name);
    strcpy(this->description, description);
  }

  ~Task() {
    delete [] name;
    delete [] description;
  }

  void print() const {
    std::cout << "Task: " << name << '\n'
              << "Description: " << description << '\n'
              << "State: " << state_to_string(state) << '\n';
  }

  void update_state(State state) {
    this->state = state;
  }

  const char* get_name() const {
    return name;
  }

  State get_state() const {
    return state;
  }

private:
  char *name, *description;
  State state;
};

class TasksArray {
public:
  TasksArray() : tasks(nullptr), size(0), capacity(0) {}

  ~TasksArray() {
    delete [] tasks;
  }

  void add_task(Task* task) {
    if (size == capacity) {
      resize();
    }

    tasks[size++] = task;
  }

  std::size_t length() const {
    return size;
  }

  Task* get(std::size_t index) const {
    return tasks[index];
  }

private:
  Task** tasks;
  std::size_t size, capacity;

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Task** new_tasks = new Task*[capacity *= 2]{};
    for (std::size_t i = 0; i < size; ++i) {
      new_tasks[i] = tasks[i];
    }

    delete [] tasks;
    tasks = new_tasks;
  }
};

class TodoList {
public:
  TodoList& add_task(Task* task) {
    for (std::size_t i = 0; i < tasks.length(); ++i) {
      if (strcmp(task->get_name(), tasks.get(i)->get_name()) == 0) {
        return *this;
      }
    }
    
    tasks.add_task(task);
    
    return *this;
  }

  void print() const {
    std::cout << "Number of tasks: " << tasks.length() << '\n';
    for (std::size_t i = 0; i < tasks.length(); ++i) {
      tasks.get(i)->print();
      std::cout << '\n';
    }
  }

  TasksArray find_by_state(State state) const {
    TasksArray result;

    for (std::size_t i = 0; i < tasks.length(); ++i) {
      Task* task = tasks.get(i);
      if (task->get_state() == state) {
        result.add_task(task);
      }
    }

    return result;
  }

private:
  TasksArray tasks;
};

int main() {
  Task t1("Clean the dishes", "Clean thoroughly with soap", State::not_started);
  Task t2("Take out the trash", "Please, it smells", State::not_started);
  Task t3("Do the laundry", "Use only high-temperature", State::in_progress);
  Task t4("Do the laundry", "Use only high-temperature", State::not_started);

  TodoList list;
  list.add_task(&t1).add_task(&t2).add_task(&t3).add_task(&t4);

  list.print();

  std::cout << "Only not started:\n";
  TasksArray not_started = list.find_by_state(State::not_started);
  for (std::size_t i = 0; i < not_started.length(); ++i) {
    not_started.get(i)->print();
    std::cout << '\n';
  }

  return 0;
}