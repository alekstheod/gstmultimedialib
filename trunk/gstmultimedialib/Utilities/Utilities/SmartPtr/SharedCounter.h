/**
*  Copyright (c) 2011, Alex Theodoridis
*  All rights reserved.

*  Redistribution and use in source and binary forms, with
*  or without modification, are permitted provided that the
*  following conditions are met:
*  Redistributions of source code must retain the above
*  copyright notice, this list of conditions and the following disclaimer.
*  Redistributions in binary form must reproduce the above
*  copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials
*  provided with the distribution.

*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
*  AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
*  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
*  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE,
*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*/


#ifndef UTILS_SHAREDPTR_H
#define UTILS_SHAREDPTR_H

#include <Utilities/AutoLock/AutoLock.h>

namespace utils {

/**
* Represent the shared counter
* needed for internal usage by the
* SharedPtr.
*/
class SharedCounter {
private:
    /**
     * The reference counter.
     * Needed in order to count 
     * the references to the shared
     * object.
     */
    int _refCount;

    /**
     * Instance of the lock object.
     * Needed in order to implement
     * the shared pointer in the
     * multithreaded environment.
     */
    LockObject _lockObject;

private:
    /**
     * Destructor, need to be 
     * private since this object
     * cannot be destroyed by any
     * external class.
     */
    ~SharedCounter(void) {
    }

public:
    /**
     * Empty constructor will initialize the object.
     * the _refCount variable will be set to 1.
     */
    SharedCounter() {
        _refCount = 1;
    }

    /**
     * Will add a new reference to the
     * shared counter.
     */
    unsigned int addRef(void) {
        int refCount = 0;
        try {
            AutoLock lock(_lockObject);
            _refCount++;
            refCount = _refCount;
        } catch (const utils::LockException&) {
            return refCount;
        }

        return refCount;
    }

    /**
     * Will decrease the number of references to this
     * current instance of SharedCounter.
     * In case if the number of references are equal with 0
     * this method will release the current instance;
     */
    unsigned int release(void) {
        int refCount;
        try {
            AutoLock lock(_lockObject);
            _refCount--;
            refCount = _refCount;
        } catch (const utils::LockException&) {
            return _refCount;
        }

        if( refCount == 0 ) {
            delete this;
        }

        return refCount;
    }

    /**
    * Will return the current count of references to this
    * shared counter.
    */
    unsigned int getCount() {
        return _refCount;
    }
};

}//namespace close

#endif
