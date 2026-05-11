#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>
#include <utility>

class Character {
public:
  Character(const char* name = "", double dmg = 0.0, double hp = 0.0)
    : name(new char[strlen(name) + 1]{}), dmg(dmg), hp(hp) {
    strcpy(this->name, name);
  }

  Character(const Character& other)
    : name(new char[strlen(other.name) + 1]{}), dmg(other.dmg), hp(other.hp) {
    strcpy(name, other.name);
  }

  Character(Character&& other)
    : name(std::exchange(other.name, nullptr)),
      dmg(std::move(other.dmg)),
      hp(std::move(other.hp)) {}

  virtual ~Character() {
    delete [] name;
  }

  Character& operator=(const Character& other) {
    Character copy(other);
    swap(copy);

    return *this;
  }

  Character& operator=(Character&& other) {
    Character copy(std::move(other));
    swap(copy);

    return *this;
  }

  virtual void take_damage(float points) {
    hp = std::max(hp - points, 0.0f);    
  }

  void deal_damage_to(Character& other) const {
    other.take_damage(attack_damage());
  }

  virtual void heal(float points) {
    hp += points;
  } 

  bool compare_name(const char* name) const {
    return strcmp(name, this->name) == 0;
  }

  std::ostream& print(std::ostream& os = std::cout) const {
    return os << "Name: " << name << '\n'
              << "Type: " << type() << '\n'
              << "HP: " << hp << '\n'
              << "DMG: " << dmg << '\n';
  }

private:
  char* name;
  float dmg, hp;

  void swap(Character& other) {
    std::swap(name, other.name);
    std::swap(dmg, other.dmg);
    std::swap(hp, other.hp);
  }

  virtual const char* type() const {
    return "Ordinary Character";
  }

protected:
  virtual float attack_damage() const {
    return dmg;
  }
};

class Knight : public Character {
public:
  Knight(const char* name = "", double dmg = 0.0, double hp = 0.0)
    : Character(name, dmg, hp) {}

  void take_damage(float points) final {
    Character::take_damage(points * 0.75);
  }

  void heal(float points) final {
    Character::heal(points * 1.05);
  }

private:
  const char* type() const {
    return "Knight";
  }
};

class Archer : public Character {
public:
  Archer(const char* name = "", double dmg = 0.0, double hp = 0.0)
    : Character(name, dmg, hp) {}

  void take_damage(float points) final {
    Character::take_damage(points * 1.15);
  }

private:
  const char* type() const {
    return "Archer";
  }

  float attack_damage() const {
    return Character::attack_damage() * 1.33;
  }
};

class Game {
public:
  Game() : characters(nullptr), size(0), capacity(0) {}

  Game(const Game& other)
    : characters(new Character*[other.capacity]),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      characters[i] = other.characters[i];
    }
  }

  ~Game() {
    delete [] characters;
  }

  // TODO: rule of 5

  void add(Character* character) {
    if (size == capacity) {
      resize();
    }

    characters[size++] = character;
  }

  void print() const {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i]->print() << '\n';
    }
  }

private:
  Character** characters;
  std::size_t size, capacity;

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Character** new_characters = new Character*[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_characters[i] = characters[i];
    }

    delete [] characters;
    characters = new_characters;
  }

};

int main() {
  Character c("Archibald", 20, 100);
  Knight k("Arthur", 30, 150);
  Archer a("Legolas", 50, 80);

  Game game;
  game.add(&c);
  game.add(&k);
  game.add(&a);

  game.print();

  return 0;
}