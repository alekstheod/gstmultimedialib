#ifndef Tuple_h
#define Tuple_h
#include <tuple>

namespace utils
{

namespace detail
{

template < uint N >
struct for_each_t {
    template < typename Functor, typename... ArgsT >
    static void exec ( std::tuple<ArgsT...>& t, Functor func ) {
        func ( std::get<N-1> ( t ) );
        for_each_t<N-1>::exec ( t, func );
    }
};

template <>
struct for_each_t<0> {
    template < typename Functor, typename... ArgsT>
    static void exec ( std::tuple<ArgsT...>& t, Functor func ) {
    }
};

template <class T, std::size_t N, class... Args>
struct get
{
    static constexpr auto value = N;
};

template <class T, std::size_t N, class... Args>
struct get<T, N, T, Args...>
{
    static constexpr auto value = N;
};

template <class T, std::size_t N, class U, class... Args>
struct get<T, N, U, Args...>
{
    static constexpr auto value = get<T, N + 1, Args...>::value;
};

} // namespace detail

template <class T, class... Args>
T& get(std::tuple<Args...>& t)
{
    return std::get<detail::get<T, 0, Args...>::value>(t);
}

template < typename Functor, typename... ArgsT >
void for_each( std::tuple<ArgsT...>& t, Functor func )
{
    detail::for_each_t<sizeof...(ArgsT)>::exec( t, func );
}

}

#endif
