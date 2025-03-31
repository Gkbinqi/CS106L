#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

// Part1 overload <<
// exapmle output: User(name=Alice, friends=[Bob, Charlie])
std::ostream& operator << (std::ostream& os, const User& user) {
  os << "User(name=" << user._name << ", friends=[";
  for(size_t i = 0; i < user._size; ++i) {
    os << user._friends[i];
    if (i != user._size - 1) os << ", ";
  }
  os << "])";
  return os;
}

// Part 2: Unfriendly Behaviour
// destructor
User::~User() {
  delete[] _friends;
}

// copy constructor
User::User(const User& user) {
  this->_capacity = user._capacity;
  this->_name = user._name;
  this->_size = user._size;
  this->_friends = new std::string[this->_capacity];
  for (size_t i = 0; i < user._size; ++i) {
    this->_friends[i] = user._friends[i];
  }
}

// copy assign
// 注意这里由于不是constructor, this的_friend可能存了东西的
User& User::operator=(const User& user) {
  if (this->_friends) delete[] this->_friends;

  this->_capacity = user._capacity;
  this->_name = user._name;
  this->_size = user._size;
  this->_friends = new std::string[this->_capacity];
  for (size_t i = 0; i < user._size; ++i) {
    this->_friends[i] = user._friends[i];
  }

  return *this;
}

// Part 3: Always Be Friending
User& operator += (User& l, User& r) {
  l.add_friend(r.get_name());
  r.add_friend(l.get_name());
  return l;
}

bool operator < (const User& l, const User& r) {
  return l.get_name() < r.get_name();
}