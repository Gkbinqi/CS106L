// Version 01: PPT page 51
#include <concepts>
#include <iterator>
// old find
// template <typename TIterator, typename TValue>
// TIterator find(TIterator begin, TIterator end, TValue value);

// new find using concept
template <std::input_iterator It, typename T>
It find(It begin, It end, const T& value);

// Version 02: 
template <typename T>
concept Comparable = requires(const T a, const T b) {
	{ a < b } -> std::convertible_to<bool>;
};

template <typename T> requires Comparable<T> // or template <Comparable T>
T min(const T& a, const T& b);

#include "lec09_find.cpp"