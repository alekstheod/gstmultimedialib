#ifndef DECORATED_H
#define DECORATED_H
#include <Utilities/MPL/TypeTraits.h>

namespace utils
{

template<typename InternalType, template< class> class DecorationType>
class Decorated {
private:
  typedef DecorationType<InternalType> Decoration;
  typedef typename Decoration::Arguments Arguments;

private:
    Arguments m_args;
    InternalType m_internal;

public:
    Decorated () : Decorated( Arguments() ){}
    Decorated ( Arguments args ) :m_args ( args )
    {
      static_assert( utils::hasArrowOperator< Decoration >::value, "Wrong decoration (operator -> has not been found)");
      typedef decltype( ((Decoration*)nullptr)->operator->() ) ReturnType;
      static_assert( utils::IsSameType<InternalType*, ReturnType>::Result::value, "Invalid return type in decoration" );
    }

    Decoration operator ->() {
        Decoration decoration ( m_internal, m_args );
        return decoration;
    }

    ~Decorated() {}
};

}

#endif
