#include "List.hpp"

#include <variant>
#include <string>
#include <cassert>

struct Cat
{
  std::string name;

  void meow() {};
};

struct Dog
{
  std::string name;

  void bark() {};
};

class AnimalShelter
{
public:

  AnimalShelter() = default;

  void enqueue(Dog dog)
  {
    m_queue.add_tail(dog);
    m_dogs.add_tail(m_queue.tail);
  }

  void enqueue(Cat cat)
  {
    m_queue.add_tail(cat);
    m_cats.add_tail(m_queue.tail);
  }

  std::variant<Cat, Dog> dequeueAny()
  {
    assert(!m_queue.empty());
    auto animal = m_queue.head->val;
    std::visit([this](auto const & val)
               {
                 using T = std::decay_t<decltype(val)>;
                 if constexpr (std::is_same_v<T, Cat>) m_cats.rem_head();
                 else if constexpr (std::is_same_v<T, Dog>) m_dogs.rem_head();
               }, animal);
    m_queue.rem_head();
    return animal;
  }

  Cat dequeueCat()
  {
    assert(!m_cats.empty());
    Cat cat = std::get<Cat>(m_cats.head->val->val);
    m_queue.rem(m_cats.head->val);
    m_cats.rem_head();
    return cat;
  }

  Dog dequeueDog()
  {
    assert(!m_dogs.empty());
    Dog dog = std::get<Dog>(m_dogs.head->val->val);
    m_queue.rem(m_dogs.head->val);
    m_dogs.rem_head();
    return dog;
  }

private:

  using element_type = std::variant<Cat, Dog>;
  using node_type = List<element_type>::Node;

  List<element_type> m_queue;
  List<node_type *> m_dogs;
  List<node_type *> m_cats;
};

int main()
{
  AnimalShelter s;
  s.enqueue(Cat{"Barsik"});
  s.enqueue(Cat{"Pushok"});
  s.enqueue(Dog{"Sharik"});
  s.enqueue(Cat{"Maple"});
  s.enqueue(Dog{"Strelka"});
  s.enqueue(Dog{"Belka"});
  s.enqueue(Cat{"Snezhok"});
  s.enqueue(Cat{"Hosiko"});
  s.enqueue(Dog{"Bobik"});

  auto a1 = s.dequeueAny();
  assert(std::holds_alternative<Cat>(a1));
  assert(std::get<Cat>(a1).name == "Barsik");

  Cat a2 = s.dequeueCat();
  assert(a2.name == "Pushok");

  Dog a3 = s.dequeueDog();
  assert(a3.name == "Sharik");

  Dog a4 = s.dequeueDog();
  assert(a4.name == "Strelka");

  auto a5 = s.dequeueAny();
  assert(std::holds_alternative<Cat>(a5));
  assert(std::get<Cat>(a5).name == "Maple");

  auto a6 = s.dequeueAny();
  assert(std::holds_alternative<Dog>(a6));
  assert(std::get<Dog>(a6).name == "Belka");

  Dog a7 = s.dequeueDog();
  assert(a7.name == "Bobik");

  Cat a8 = s.dequeueCat();
  assert(a8.name == "Snezhok");

  auto a9 = s.dequeueAny();
  assert(std::holds_alternative<Cat>(a9));
  assert(std::get<Cat>(a9).name == "Hosiko");
}
