#ifndef TYPETRAITS_h
#define TYPETRAITS_h
#include <tuple>

namespace utils {

struct True {
    enum { value = 1 };
};
struct False {
    enum {value = 0};
};

template< typename T1, typename T2>
struct IsSameType {
    typedef False Result;
};

template< typename T1>
struct IsSameType<T1,T1> {
    typedef True Result;
};

template<typename T>
struct StaticAssert;

template<>
struct StaticAssert< True > {};


template<class T>
struct Type2Type {
    typedef T Result;
};

template < uint N >
struct apply_t
{
    template < typename Functor, typename... ArgsT,  typename... Args >
    static void apply_tuple( Functor func, std::tuple<ArgsT...>& t, Args... args  )
    {
        apply_t<N-1>::apply_tuple( func,  t, std::get<N-1>(t),  args...);
    }
};

template <>
struct apply_t<0>
{
    template < typename Functor, typename... ArgsT, typename... Args>
    static void apply_tuple( Functor func,  std::tuple<ArgsT...> & t, Args... args )
    {
      	func( args... );
    }
};

template < typename Functor, typename... ArgsT >
void apply( Functor func, std::tuple<ArgsT...> const& t )
{
    apply_t<sizeof...(ArgsT)>::apply_tuple( func, t );
}

template<typename T>
struct hasArrowOperator
{
  template<typename C>
  static char hasArrow( decltype(&C::operator->) );
  
  template<typename C>
  static double hasArrow(...);
  
  //T t;
  enum {value = sizeof(hasArrow<T>(0) ) == sizeof(char) };
};
}

#endif
