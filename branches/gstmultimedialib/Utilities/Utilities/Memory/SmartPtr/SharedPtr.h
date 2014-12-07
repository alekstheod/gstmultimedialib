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

#ifndef UTILS_SMARTPTR_H
#define UTILS_SMARTPTR_H

#include <Utilities/Memory/SmartPtr/SharedCounter.h>

namespace utils {

/**
* SmartPtr class represent a container for the
* typical c++ pointers. Each pointer which will
* be handled by this class will be assotiated with
* an instance of SharedCounter. SharedCounter will
* be responsible to count the number of references
* which are point to the contained pointer.
*/
template<class T>
class SharedPtr {
private:
    /**
     * Instance of the shared reference
     * counter. Needed in order to
     * counter the object's references.
     */
    SharedCounter* _counter;

    /**
     * Instance of the object stored
     * on the curren object.
     */
    T* _ptr;

public:
    /**
    * Empty constructor will initialize the object.
    * The counter and instance of the stored
    * object will be initialized as NULL.
    */
    SharedPtr(void) {
        _ptr = NULL;
        _counter = NULL;
    }

    /**
    * Will initialize the object by using the given
    * pointer. In case if the given pointer is NULL
    * SharedCounter will not be allocated and the
    * contained pointer will be initialized as NULL.
    */
    SharedPtr(T* ptr) {
        if (ptr == NULL) {
            _ptr = NULL;
            _counter = NULL;
        } else {
            _counter = new SharedCounter;
            _ptr = ptr;
        }
    }

    /**
    * Copy constructor. Will set the instance of
    * the given object and increase the reference 
    * counter.
    * @param arg Instance of the @link = 'SharedPtr'
    * which represent the new object.
    */
    SharedPtr(const SharedPtr<T>& arg) {
        _ptr = NULL;
        _counter = NULL;
        if (arg._counter != NULL) {
            arg._counter->addRef();
            _counter = arg._counter;
            _ptr = arg._ptr;
        }
    }

    /**
    *
    */
    template<class T2>
    SharedPtr(const SharedPtr<T2>& smartPtr) {
        _ptr = NULL;
        _counter = NULL;
        T* ptr = static_cast< T* > (smartPtr.getPtr() );
        if (smartPtr.getCounter() != NULL) {
            smartPtr.getCounter()->addRef();
            _ptr = ptr;
            _counter = smartPtr.getCounter();
        }
    }

    /**
    *
    */
    template<class T2>
    void Attach(T2* ptr) {
        release();
        T* newPtr = static_cast< T* >(ptr);
        if (newPtr != NULL) {
            _ptr = ptr;
            _counter = new SharedCounter;
        }
    }

    /**
    *
    */
    template<class T2>
    SharedPtr & operator=(const SharedPtr<T2>& smartPtr) {
        static_cast< T* >( smartPtr.getPtr() );
        if (smartPtr.getPtr() == _ptr) {
            return *this;
        }

        release();
        if (smartPtr.getCounter() !=NULL) {
            _counter = smartPtr.getCounter();
            _counter->addRef();
            _ptr = smartPtr.getPtr();
        }

        return *this;
    }

    /**
    * Will asssign the pointer from the given instance
    * of SmartPtr to the current instance of this class.
    * the shared counter will be incremented if and only if
    * the given container contains an instance of SharedCounter.
    */
    SharedPtr & operator=(const SharedPtr<T>& smartPtr) {
        if (smartPtr._ptr == _ptr) {
            return *this;
        }

        release();
        if (smartPtr._counter !=NULL) {
            _counter = smartPtr._counter;
            _counter->addRef();
            _ptr = smartPtr._ptr;
        }

        return *this;
    }

    /**
    * Will decrement the number of the referenced object.
    * in case of SharedCounter::release return 0, this method
    * will release the instances of SharedCounter and shared pointer.
    */
    void release(void) {
        if (_counter != NULL) {
            _counter->release( _ptr );
        }

        _counter = NULL;
        _ptr = NULL;
    }

    /**
     * Overloading of > operator
     * needed for the stl key based containers
     */
    bool operator > ( const utils::SharedPtr< T >& second ) const {
        return _ptr > second.getPtr();
    }

    /**
    * Overloading of >= operator
    * needed for the stl key based containers
    */
    bool operator >= ( const utils::SharedPtr< T >& second ) const {
        return _ptr >= second.getPtr();
    }

    /**
    * Overloading of < operator
    * needed for the stl key based containers
    */
    bool operator < ( const utils::SharedPtr< T >& second ) const {
        return _ptr < second.getPtr();
    }

        /**
    *
    */
    template<class T2>
    bool operator == (const T2* ptr) const {
        T* second = static_cast< T* > ( ptr );
        return second == _ptr;
    }

    /**
    *
    */
    bool operator == (const T* ptr ) const {
        return ptr == _ptr;
    }
    
    /**
    * Overloading of <= operator
    * needed for the stl key based containers
    */
    bool operator <= ( const utils::SharedPtr< T >& second ) const {
        return _ptr <= second.getPtr();
    }

    bool operator != (const T* second)const {
        return  (_ptr != second ) ;
    }

    bool operator != (const utils::SharedPtr<T> second)const {
        return  (second.getPtr() != _ptr ) ;
    }

    /**
     *
     */
    SharedCounter* getCounter()const {
        return _counter;
    }

    /**
    * Will return a pointer.
    */
    T * operator->() const {
        return _ptr;
    }

    /**
    * Will return a pointer.
    */
    T* getPtr(void) const {
        return _ptr;
    }

    /**
    *
    */
    ~SharedPtr(void) {
        release();
    }
};

}


template<class T, class T2>
static bool operator == (  const utils::SharedPtr<T> arg1, const utils::SharedPtr< T2 >& arg2 ) {
    const T2* tmp = static_cast< const T2* >( arg1.getPtr() );
    return  ( tmp == arg2.getPtr() );
}

template<class T, class T2>
static bool operator == (  const T* arg1, const utils::SharedPtr< T2 >& arg2 ) {
    const T2* tmp = static_cast< const T2* >( arg1 );
    return  ( tmp == arg2.getPtr() );
}

#endif
