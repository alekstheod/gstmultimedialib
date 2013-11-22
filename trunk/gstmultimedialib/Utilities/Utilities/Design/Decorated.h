#ifndef DECORATED_H
#define DECORATED_H
#include <tuple>
#include <memory>
#include "StateMachine.h"

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
    Decorated ( Arguments args ) :m_args ( args ) {}

    Decoration<InternalType> operator ->() {
        Decoration<InternalType> decoration ( m_internal, m_args );
        return decoration;
    }

    ~Decorated() {}
};

}

#endif
