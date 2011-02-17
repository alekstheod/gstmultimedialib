/*
 * LinLockObject.h
 *
 *  Created on: May 2, 2010
 *      Author: m1cro
 */

#ifndef UTILS_LLOCKOBJECT_H
#define UTILS_LLOCKOBJECT_H

#ifdef linux
#include <Utilities/AutoLock/LockException.h>
#include <pthread.h>

namespace utils {

    class LLockObject {
    private:
        pthread_mutex_t _mutex;
        int _errorCode;

    public:
        LLockObject();
        bool Lock(unsigned int waitTime)const;
        bool Unlock(void)const;
        virtual ~LLockObject()throw ();
    };

}
#endif

#endif
