#ifndef UTILS_SHAREDPTR_H
#define UTILS_SHAREDPTR_H

#include <Utilities/AutoLock/AutoLock.h>

namespace utils {

/// <summary>
/// Template of shared reference counted pointer.
/// </summary>

template<class T>
class SharedPtr {
private:
	/// <summary>
	///
	/// </summary>
	T* _ptr;

	/// <summary>
	///
	/// </summary>
	int _refCount;

	/// <summary>
	///
	/// </summary>
	LockObject _lockObject;

private:
	/// <summary>
	/// Destructor.
	/// </summary>
	~SharedPtr(void);

public:
	///<summary>
	/// Constructor.
	/// </summary>
	SharedPtr(T* ptr);

	/// <summary>
	///
	/// </summary>
	SharedPtr(const SharedPtr<T>& sharedPtr);

	/// <summary>
	///
	/// </summary>
	SharedPtr & operator=(const SharedPtr<T>&);

	/// <summary>
	///
	/// </summary>
	T * operator->();

	/// <summary>
	///
	/// </summary>
	T* getPtr(void) const;

	/// <summary>
	///
	/// </summary>
	unsigned int addRef(void);

	/// <summary>
	///
	/// </summary>
	unsigned int release(void);
};

template<class T>
T* SharedPtr<T>::operator->() {
	return _ptr;
}

template<class T>
T* SharedPtr<T>::getPtr(void) const {
	return _ptr;
}

template<class T>
SharedPtr<T>::SharedPtr(T* ptr) {
	_ptr = ptr;
	_refCount = 1;
}

template<class T>
unsigned int SharedPtr<T>::release(void) {
	int refCount;
	try {
		AutoLock lock(_lockObject);
		_refCount--;
		refCount = _refCount;
		if (_refCount == 0) {
			if (_ptr != 0) {
				delete _ptr;
				_ptr = 0;
			}
		}

	} catch (const utils::LockException&) {
		return _refCount;
	}

	if (refCount == 0) {
		delete this;
		return 0;
	} else {
		return refCount;
	}
}

template<class T>
unsigned int SharedPtr<T>::addRef(void) {
	int refCount = 0;
	try {
		AutoLock lock(_lockObject);
		_refCount++;
		refCount = _refCount;
		return _refCount;
	} catch (const utils::LockException&) {
		return refCount;
	}

	return refCount;
}

template<class T>
SharedPtr<T>::~SharedPtr(void) {
}

} //namespace close

#endif
