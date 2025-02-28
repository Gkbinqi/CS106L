//lec08_Vector.h
#pragma once

#include <cstddef>

template <typename T>
class Vector {
public:
  using iterator = T*;

  Vector();
  Vector(const Vector& other);
  Vector(Vector&& other) noexcept;
  ~Vector();

  void push_back(const T& value);

  const T& at (size_t index) const;
  T& at (size_t index);

  const T& operator[](size_t index) const;
  T& operator[](size_t index);

  T& front();
  T& back();

  size_t size () const;
  size_t capacity() const;
  bool empty () const;

  iterator begin();
  iterator end();
private:
  size_t _size;
  size_t _capacity;
  T* _data;

  void resize();
};
#include "lec08_Vector.cpp"