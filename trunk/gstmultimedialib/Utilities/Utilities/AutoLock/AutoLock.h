/*
 * AutoLock.h
 *
 *  Created on: May 2, 2010
 *      Author: m1cro
 */

#ifndef UTILS_AUTOLOCK_H
#define UTILS_AUTOLOCK_H

#include <Utilities/AutoLock/LockException.h>

namespace utils {

/**
 * AutoLock represents the
 * automatic lock guard.
 */
template<class T>
class AutoLock {
private:
    const T& _lockObject;

private:
  AutoLock(const AutoLock&);
  AutoLock& operator=(const AutoLock&);
  void* operator new(std::size_t);
  void* operator new[](std::size_t);
  void operator delete(void*);
  void operator delete[](void*);
  AutoLock* operator&();
  
public:
    AutoLock( const T& lockObject, unsigned int waitTime = T::CONST_DEFAULT_LOCK_TIMEOUT ):
        _lockObject(lockObject) {
        if (!_lockObject.lock(waitTime)) {
            throw LockException("AutoLock::AutoLock - LockObject::Lock failed");
        }
    }
    
    ~AutoLock(void) throw (){
      _lockObject.unlock();
    }
};

}

#endif
