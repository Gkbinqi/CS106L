#include "lec07_IntVector.h"

IntVector::IntVector()
{
    _data = new int[32];
    _capacity = 32;
    _size = 0;
}

IntVector::~IntVector()
{
  // IMPLEMENT
    delete[] _data;
}

void IntVector::resize()
{
  // IMPLEMENT
  _capacity *= 2;
  int* temp = new int[_capacity];
  for (int i = 0; i < _size; ++i) {
    temp[i] = _data[i];
  }
  delete[] _data;
  _data = temp;
}

void IntVector::push_back(const int& value)
{
  // IMPLEMENT
  _data[_size] = value;
  ++_size;
  if (_size == _capacity) resize();
}

// Provides runtime bounds checking; throws a std::out_of_range error
int& IntVector::at(size_t index)
{
  // IMPLEMENT
  if (index < 0 || index >= _size) {
    throw std::__throw_out_of_range;
  } else return _data[index];
}

int& IntVector::operator[](size_t index)
{
  // IMPLEMENT
  if (index < 0 || index >= _size) {
    throw std::__throw_out_of_range;
  } else return _data[index]; 
}

size_t IntVector::size()
{
  // IMPLEMENT
  return _size;
}

bool IntVector::empty()
{
  // IMPLEMENT
  return _size == 0;
}

IntVector::iterator IntVector::begin()
{
  // IMPLEMENT
  return _data;
}

IntVector::iterator IntVector::end()
{
  // IMPLEMENT
  return &(_data[_size]);
}