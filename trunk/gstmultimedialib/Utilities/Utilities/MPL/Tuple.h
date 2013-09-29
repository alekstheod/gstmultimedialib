#ifndef TUPLE_H
#define TYPLE_H
#include <tuple>

namespace std
{

namespace Private 
{
  
template < uint N >
struct apply_t
{
    template < typename Functor, typename... ArgsT >
    static void apply_tuple( Functor func, std::tuple<ArgsT...> const& t  )
    {
	auto filter = std::get<N-1>(t);
        func(filter);
        apply_t<N-1>::apply_tuple( func,  t );
    }
};

template <>
struct apply_t<0>
{
    template < typename Functor, typename... ArgsT>
    static void apply_tuple( Functor func,  std::tuple<ArgsT...> const& t)
    {
    }
};

}

template < typename Functor, typename... ArgsT >
void for_each( std::tuple<ArgsT...> const& t, Functor func )
{
    Private::apply_t<sizeof...(ArgsT)>::apply_tuple( func, t );
}

}

#endif
