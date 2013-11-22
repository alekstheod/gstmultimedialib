#ifndef DECORATED_H
#define DECORATED_H
#include <Utilities/MPL/TypeTraits.h>

namespace utils
{

template<typename InternalType, template< class> class Decoration>
class Decorated {
private:
  typedef typename Decoration<InternalType>::Arguments Arguments;
private:
    Arguments m_args;
    InternalType m_internal;

public:
    Decorated ( Arguments args ) :m_args ( args ) 
    {
      static_assert( hasArrowOperator< Decoration<InternalType> >::value, "Wrong decoration (operator -> is not found)");
    }

    Decoration<InternalType> operator ->() {
        Decoration<InternalType> decoration ( m_internal, m_args );
        return decoration;
    }

    ~Decorated() {}
};

}

#endif
