#ifndef LOCKDECORATION_H
#define LOCKDECORATION_H
#include <tuple>
#include <mutex>
#include <locale>

namespace utils
{

template<typename InternalType>
class LockDecoration {
public:
  typedef std::mutex& Arguments;
  
private:
    std::mutex& m_mutex;
    InternalType& m_internal;
    bool m_doUnlock;

public:
    LockDecoration ( InternalType& internal, Arguments args ) : m_internal ( internal ),  m_mutex ( args ), m_doUnlock ( false ) {
        m_mutex.lock();
    }

    InternalType* operator -> () {
        m_doUnlock = true;
        return &m_internal;
    }

    ~LockDecoration() {
        if ( m_doUnlock ) {
            m_mutex.unlock();
        }
    }
};

}

#endif // LOCKDECORATION_H
