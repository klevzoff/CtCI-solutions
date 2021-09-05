#include <ostream>
#include <utility>
#include <iterator>
#include <type_traits>

#ifndef CTCI_SOLUTIONS_PRINTING_HPP
#define CTCI_SOLUTIONS_PRINTING_HPP

namespace printing
{
  template<typename Tuple, size_t ... Is>
  void print_tuple(std::ostream & os, Tuple const & t, std::index_sequence<Is...>)
  {
    os << '{' << std::get<0>(t) << ((',' << std::get<Is+1>(t)) << ...) << '}';
  }
}

/**
 * @brief Printing for std::pair.
 * @tparam T first element type
 * @tparam U second element type
 * @param os the stream
 * @param p the pair
 * @return the stream P os
 */
template<typename T, typename U>
std::ostream & operator<<(std::ostream & os, std::pair<T, U> p)
{
  os << '{' << p.first << ',' << p.second << '}';
  return os;
}

/**
 * @brief Printing for std::tuple.
 * @tparam Ts types of tuple elements
 * @param os the stream
 * @param t the tuple
 * @return the stream @p os
 */
template<typename ... Ts>
std::ostream & operator<<(std::ostream & os, std::tuple<Ts...> const & t)
{
  if constexpr (sizeof...(Ts) > 0)
  {
    ::printing::print_tuple(os, t, std::make_index_sequence<sizeof...(Ts) - 1>{});
  }
  else
  {
    os << "{}";
  }
  return os;
}

/**
 * @brief Printing for range-like types (std::vector, std::list, std::map, std::array, etc.).
 * @tparam R range type
 * @param os the stream
 * @param rng the range object
 * @return the stream @p os
 */
template<typename R, // below is VERY simplified SFINAE check for a range-like type (only allows common ranges, actually)
         typename = std::enable_if_t<std::is_same_v<decltype(std::cbegin(std::declval<R>())), decltype(std::cend(std::declval<R>()))> && !std::is_array_v<R>>>
std::ostream & operator<<(std::ostream & os, R const & rng)
{
  auto it = std::cbegin(rng);
  auto const e = std::cend(rng);
  os << '{';
  if (it != e)
  {
    os << *it;
  }
  for (++it; it != e; ++it)
  {
    os << ',' <<*it;
  }
  return os;
}

#endif //CTCI_SOLUTIONS_PRINTING_HPP
