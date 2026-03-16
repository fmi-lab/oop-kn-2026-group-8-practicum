#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <type_traits>

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
    const char* name = "",
    const char* description = "",
    State state = State::not_started
  )
    : name(new char[strlen(name) + 1]{}),
      description(new char[strlen(description) + 1]{}),
      state(state) {
    strcpy(this->name, name);
    strcpy(this->description, description);
  }

  Task(const Task& other)
    : name(new char[strlen(other.name) + 1]{}),
      description(new char[strlen(other.description) + 1]{}),
      state(other.state) {
    strcpy(name, other.name);
    strcpy(description, other.description);
  }

  ~Task() {
    delete [] name;
    delete [] description;
  }

  Task& operator=(const Task& other) {
    // if (this != &other) {
    //   delete [] name;
    //   delete [] description;

    //   name = new char[strlen(other.name) + 1]{};
    //   strcpy(name, other.name);
    //   description = new char[strlen(other.description) + 1]{};
    //   strcpy(description, other.description);
    //   state = other.state;
    // }

    Task copy(other);
    swap(copy);

    return *this;
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

  void swap(Task& other) {
    std::swap(name, other.name);
    std::swap(description, other.description);
    std::swap(state, other.state);
  }
};

class TasksArray {
public:
  TasksArray() : tasks(nullptr), size(0), capacity(0) {}

  TasksArray(const TasksArray& other)
    : tasks(new Task[other.capacity]),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      tasks[i] = other.tasks[i];
    }
  }

  TasksArray& operator=(const TasksArray& other) {
    TasksArray copy(other);
    swap(copy);

    return *this;
  }

  ~TasksArray() {
    delete [] tasks;
  }

  void add_task(const Task& task) {
    if (size == capacity) {
      resize();
    }

    tasks[size++] = task;
  }

  std::size_t length() const {
    return size;
  }

  const Task& get(std::size_t index) const {
    return tasks[index];
  }

  Task& get(std::size_t index) {
    return tasks[index];
  }

  void remove(std::size_t index) {
    for (int i = index + 1; i < size; ++i) {
      std::iter_swap(tasks + i - 1, tasks + i);
    }

    --size;
  }

private:
  Task* tasks;
  std::size_t size, capacity;

  void swap(TasksArray& other) {
    std::swap(tasks, other.tasks);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Task* new_tasks = new Task[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_tasks[i] = tasks[i];
    }

    delete [] tasks;
    tasks = new_tasks;
  }
};

class TodoList {
public:
  TodoList& add_task(const Task& task) {
    for (std::size_t i = 0; i < tasks.length(); ++i) {
      if (strcmp(task.get_name(), tasks.get(i).get_name()) == 0) {
        return *this;
      }
    }
    
    tasks.add_task(task);
    
    return *this;
  }

  void print() const {
    std::cout << "Number of tasks: " << tasks.length() << '\n';
    for (std::size_t i = 0; i < tasks.length(); ++i) {
      tasks.get(i).print();
      std::cout << '\n';
    }
  }

  TasksArray find_by_state(State state) const {
    TasksArray result;

    for (std::size_t i = 0; i < tasks.length(); ++i) {
      const Task& task = tasks.get(i);
      if (task.get_state() == state) {
        result.add_task(task);
      }
    }

    return result;
  }

  void remove(const char* name) {
    int index = index_of(name);

    if (index == -1) {
      return;
    }

    tasks.remove(index);
  }

private:
  TasksArray tasks;

  int index_of(const char* name) const {
    for (std::size_t i = 0; i < tasks.length(); ++i) {
      if (strcmp(tasks.get(i).get_name(), name) == 0) {
        return i;
      }
    }

    return -1;
  }
};

int main() {
  Task t1("Clean the dishes", "Clean thoroughly with soap", State::not_started);
  Task t2("Take out the trash", "Please, it smells", State::not_started);
  Task t3("Do the laundry", "Use only high-temperature", State::in_progress);

  t1.print();

  Task t4(t1);
  Task t5("Do your homework", "OOP", State::not_started);

  TodoList list;
  list.add_task(t1).add_task(t2).add_task(t3).add_task(t4).add_task(t5);

  list.print();

  list.remove("Take out the trash");

  std::cout << "Only not started:\n";
  TasksArray not_started = list.find_by_state(State::not_started);
  for (std::size_t i = 0; i < not_started.length(); ++i) {
    not_started.get(i).print();
    std::cout << '\n';
  }

  return 0;
}