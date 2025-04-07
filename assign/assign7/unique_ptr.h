#pragma once

#include <cstddef>
#include <utility>

/*
For our purposes, you may assume that unique_ptr points to a single element of type T.
You will not have to call delete[] at any point or handle pointers to dynamically allocated arrays.
*/

/*
Remember, a unique_ptr should look and behave like a regular pointer
, supporting operations like dereferencing (operator*) and member access (operator->). 
*/

namespace cs106l {

/**
 * @brief A smart pointer that owns an object and deletes it when it goes out of scope.
 * @tparam T The type of the object to manage.
 * @note This class is a simpler version of `std::unique_ptr`.
 */
template <typename T> class unique_ptr {
private:
  /* STUDENT TODO: What data must a unique_ptr keep track of? */
  T* _data;

public:
  /**
   * @brief Constructs a new `unique_ptr` from the given pointer.
   * @param ptr The pointer to manage.
   * @note You should avoid using this constructor directly and instead use `make_unique()`.
   */
  unique_ptr(T* ptr) {
    /* STUDENT TODO: Implement the constructor */
    // throw std::runtime_error("Not implemented: unique_ptr(T* ptr)");
    _data = ptr;
  }

  /**
   * @brief Constructs a new `unique_ptr` from `nullptr`.
   */
  unique_ptr(std::nullptr_t) {
    /* STUDENT TODO: Implement the nullptr constructor */
    // throw std::runtime_error("Not implemented: unique_ptr(std::nullptr_t)");
    _data = nullptr;
  }

  /**
   * @brief Constructs an empty `unique_ptr`.
   * @note By default, a `unique_ptr` points to `nullptr`.
   */
  unique_ptr() : unique_ptr(nullptr) {}

  /**
   * @brief Dereferences a `unique_ptr` and returns a reference to the object.
   * @return A reference to the object.
   */
  T& operator*() {
    /* STUDENT TODO: Implement the dereference operator */
    //  throw std::runtime_error("Not implemented: operator*()");
    return *(_data);
  }

  /**
   * @brief Dereferences a `unique_ptr` and returns a const reference to the object.
   * @return A const reference to the object.
   */
  const T& operator*() const {
    /* STUDENT TODO: Implement the dereference operator (const) */
    // throw std::runtime_error("Not implemented: operator*() const");
    return *(_data);
  }

  /**
   * @brief Returns a pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A pointer to the object.
   */
  T* operator->() {
    /* STUDENT TODO: Implement the arrow operator */
    // throw std::runtime_error("Not implemented: operator->()");
    return _data;
  }

  /**
   * @brief Returns a const pointer to the object managed by the `unique_ptr`.
   * @note This allows for accessing the members of the managed object through the `->` operator.
   * @return A const pointer to the object.
   */
  const T* operator->() const {
    /* STUDENT TODO: Implement the arrow operator */
    // throw std::runtime_error("Not implemented: operator->() const");
    return _data;
  }

  /**
   * @brief Returns whether or not the `unique_ptr` is non-null.
   * @note This allows us to use a `unique_ptr` inside an if-statement.
   * @return `true` if the `unique_ptr` is non-null, `false` otherwise.
   */
  operator bool() const {
    /* STUDENT TODO: Implement the boolean conversion operator */
    // throw std::runtime_error("Not implemented: operator bool() const");
    return _data != nullptr;
  }

  /** STUDENT TODO: In the space below, do the following:
   * - Implement a destructor
   * - Delete the copy constructor
   * - Delete the copy assignment operator
   * - Implement the move constructor
   * - Implement the move assignment operator
   */
  ~unique_ptr() {
    delete _data;
  }

  unique_ptr(const unique_ptr& other) = delete;
  unique_ptr& operator=(const unique_ptr& other) = delete;

  unique_ptr(unique_ptr&& other) : _data(other._data) {
    other._data = nullptr;
  }
  
  // 这一步需要考虑较多的情况
  unique_ptr& operator=(unique_ptr&& other) {
    if (this == &other) return *this;
    if (_data != nullptr) delete _data;

    this->_data = other._data;
    other._data = nullptr;
    return *this;
  }
};

/**
 * @brief Creates a new unique_ptr for a type with the given arguments.
 * @example auto ptr = make_unique<int>(5);
 * @tparam T The type to create a unique_ptr for.
 * @tparam Args The types of the arguments to pass to the constructor of T.
 * @param args The arguments to pass to the constructor of T.
 */
template <typename T, typename... Args> 
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}