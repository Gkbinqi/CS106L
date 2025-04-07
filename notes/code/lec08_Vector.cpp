// lec08_Vector.cpp
#include <stdexcept>
#include <iostream>

template <class T>
Vector<T>::Vector()
{
  _size = 0;
  _capacity = 16;
  _data = new T[_capacity];
}

template <typename T>
Vector<T>::Vector(const Vector& other)
: _size(other._size), _capacity(other._capacity), _data(new T[_capacity]) {
  for (size_t i = 0; i < _size; ++i) {
    this->_data[i] = other._data[i];
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  this->_capacity = other._capacity;
  this->_size = other._size;
  this->_data = new T[_capacity];
  for (size_t i = 0; i < _size; ++i) {
    this->_data[i] = other._data[i];
  }
  return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept 
: _size(other._size), _capacity(other._capacity), _data(other._data) {
  other._data = nullptr;
  other._size = 0;
  other._capacity = 0;
  std::cout << "Move sematic called" << '\n';
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this == &other) return *this;
  if (!this->_data) delete[] _data;
  
  this->_capacity = other._capacity;
  this->_size = other._size;
  this->_data = other._data;
  std::cout << "Move sematic called" << '\n';
};

template <class T>
Vector<T>::~Vector()
{
  delete[] _data;
}

template <class T>
void Vector<T>::resize()
{
    _capacity *= 2;
    auto newData = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        newData[i] = _data[i];
    }
    delete[] _data;
    _data = newData;
    std::cout << "resize one. capcity now: " << _capacity << '\n';
}

template <class T>
void Vector<T>::push_back(const T& value)
{
  if (_size == _capacity) {
    resize();
  }
  _data[_size] = value;
  ++_size;
}

template <class T>
T& Vector<T>::at (size_t index) {
  if (index < 0 || index >= _size)
  {
    throw std::out_of_range("Index out of range!");
  }
  return _data[index];
}
template <class T>
const T& Vector<T>::at (size_t index) const
{
  return const_cast<Vector<T>&>(*this).at(index);
}

template <class T>
T& Vector<T>::operator[](size_t index) {
  if (index < 0 || index >= _size)
  {
    throw std::out_of_range("Index out of range!");
  }
  return _data[index];
}
template <class T>
const T& Vector<T>::operator[](size_t index) const
{
  return const_cast<Vector<T>&>(*this)[index];
}

template <typename T>
T& Vector<T>::front() {
  return _data[0];
}

template <typename T>
T& Vector<T>::back() {
  if (_size == 0) {
    this->front();
  } else return _data[_size - 1];
}

template <class T>
size_t Vector<T>::size () const
{
  return _size;
}

template <typename T>
size_t Vector<T>::capacity() const {
  return _capacity;
}

template <class T>
bool Vector<T>::empty () const
{
  return _size == 0;
}

template <class T>
Vector<T>::iterator Vector<T>::begin()
{
  return _data;
}

template <class T>
Vector<T>::iterator Vector<T>::end()
{
  return _data + _size;
}