// template <typename TIterator, typename TValue>
// TIterator find(TIterator begin, TIterator end, TValue value) {
//   // Logic to find and return the iterator 
//   // in this container whose element is value.
//   // Should return end if no such element is found.
//   TIterator it = begin;
//   for (; it != end; ++it) {
//     if (*it == value) break;
//   }
//   return it;
// }

template <std::input_iterator It, typename T>
It find(It begin, It end, const T& value) {
  It it = begin;
  for (; it != end; ++it) {
    if (*it == value) break;
  }
  return it;
}

template <typename T> requires Comparable<T>
T min(const T& a, const T& b) {
    return a < b ? a : b;
}