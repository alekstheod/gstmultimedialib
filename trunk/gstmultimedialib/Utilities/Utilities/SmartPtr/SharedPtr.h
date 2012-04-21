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

#include <Utilities/SmartPtr/SharedCounter.h>

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
    SharedCounter* _counter;
	T* _ptr;

public:
    /**
    *
	*/
    SharedPtr(void){
		_ptr = NULL;
		_counter = NULL;
	}

    /**
    * Will initialize the object by using the given
	* pointer. In case if the given pointer is NULL
	* SharedCounter will not be allocated and the
	* contained pointer will be initialized as NULL.
	*/
    SharedPtr(T* ptr){
		if (ptr == NULL) {
			_ptr = NULL;
			_counter = NULL;
		} else {
			_counter = new SharedCounter;
			_ptr = ptr;
		}
	}

    /**
    *
	*/
    SharedPtr(const SharedPtr<T>& smartPtr){
	    _ptr = NULL;
		_counter = NULL;
		if (smartPtr._counter != NULL) {
			smartPtr._counter->addRef();
			_counter = smartPtr._counter;
			_ptr = smartPtr._ptr;
		}
	}
	
    /**
    *
	*/
    template<class T2>
    SharedPtr(const SharedPtr<T2>& smartPtr){
	    _ptr = NULL;
		_counter = NULL;
		T* ptr = static_cast< T* > (smartPtr._ptr );
		if (smartPtr._counter != NULL) {
			smartPtr._counter->addRef();
			_ptr = ptr;
			_counter = smartPtr._counter;
		}
	}

    /**
    *
	*/
    template<class T2>
    void Attach(T2* ptr){
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
    SharedPtr & operator=(const SharedPtr<T2>& smartPtr){
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
    SharedPtr & operator=(const SharedPtr<T>& smartPtr){
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
    void release(void){
	    if (_counter != NULL && _counter->release() == 0 ) {
			delete _ptr;
		}

		_counter = NULL;
		_ptr = NULL;
	}

    /**
    *
	*/
    template<class T2>
    bool operator ==(const SharedPtr<T2>& smartPtr) const{
		T* ptr = static_cast< T* >( smartPtr.getPtr() );
		return (_ptr == ptr); 
	}

    /**
    *
	*/
    template<class T2>
    bool operator ==(const T2* ptr) const{
		bool result = false;
		static_cast< T* > ( ptr );
	    if (_ptr == NULL) {
			result =  (ptr == NULL) ;
		} else {
			result =  (_ptr == ptr);
		}

		return result;
	}

    /**
    *
	*/
    bool operator ==(const T* ptr) const{
		bool result = false;
	    if (_ptr == NULL) {
			result =  (ptr == NULL) ;
		} else {
			result =  (_ptr== ptr);
		}

		return result;
	}
	
	/**
	 * 
	 */
	SharedCounter* getCounter()const{
		return _counter;
	}
	
    /**
    *
	*/
    bool operator !=(const SharedPtr<T>& smartPtr) const{
		return  (_ptr != smartPtr._ptr) ;
	}
	
    /**
    * 
	*/
    template<class T2>
    bool operator !=(const SharedPtr<T2>& smartPtr) const{
		T* ptr = static_cast< T* >( smartPtr.getPtr() );
		return  (_ptr != ptr) ;
	}

    /**
    * Will return a pointer.
	*/
    T * operator->() const{
		return _ptr;
	}

    /**
    * Will return a pointer.
	*/
    T* getPtr(void) const{
		return _ptr;
	}

    /**
    *
	*/
    ~SharedPtr(void){
		release();
	}
};

}

template<class Var, class Var2>
static bool operator == (  const Var* arg1, const utils::SharedPtr< Var2 >& arg2 ){
	const Var2* tmp = static_cast< const Var2* >( arg1 );
	return  ( tmp == arg2.getPtr() );
}

#endif
