#ifndef UTILS_SMARTPTR_H
#define UTILS_SMARTPTR_H

#include <Utilities/SmartPtr/SharedPtr.h>

namespace utils {

	/// <summary>
	/// Simple reference counted smart pointer implementation
	/// </summary>
	template<class T>
	class SmartPtr {
		private:
			SharedPtr<T>* _ptr;

		public:
			/// <summary>
			/// Empty constructor will set the _ptr=NULL.
			/// </summary>
			SmartPtr(void);

			/// <summary>
			/// Constructor with arguments will initialize the object.
			/// </summary>
			SmartPtr(T* ptr);

			/// <summary>
			///
			/// </summary>
			SmartPtr(const SmartPtr<T>& smartPtr);

			/// <summary>
			///
			/// </summary>
			void Attach(T* ptr);

			/// <summary>
			///
			/// </summary>
			void Release(void);

			/// <summary>
			///
			/// </summary>
			SmartPtr & operator=(const SmartPtr<T>& smartPtr);

			/// <summary>
			///
			/// </summary>
			bool operator ==(const SmartPtr<T>& smartPtr) const;

			/// <summary>
			///
			/// </summary>
			bool operator ==(T* ptr) const;

			/// <summary>
			///
			/// </summary>
			bool operator !=(const SmartPtr<T>& smartPtr) const;

			/// <summary>
			/// Will return the holding instance pointer.
			/// </summary>
			T * operator->() const;

			/// <summary>
			/// Will return the holding instance pointer.
			/// </summary>
			T* GetPtr(void) const;

			/// <summary>
			/// Destructor.
			/// </summary>
			~SmartPtr(void);
	};

	template<class T>
	SmartPtr<T>::SmartPtr(void) {
		_ptr = NULL;
	}

	template<class T>
	SmartPtr<T>::SmartPtr(T* ptr) {
		if (ptr == 0) {
			_ptr = NULL;
		} else {
			_ptr = new SharedPtr<T> (ptr);
		}
	}

	template<class T>
	SmartPtr<T>::SmartPtr(const SmartPtr<T>& smartPtr) {
		_ptr = NULL;
		if (smartPtr._ptr != NULL) {
			smartPtr._ptr->AddRef();
			_ptr = smartPtr._ptr;
		}
	}

	template<class T>
	T* utils::SmartPtr<T>::GetPtr(void) const {
		if (_ptr == NULL) {
			return NULL;
		}

		return _ptr->GetPtr();
	}

	template<class T>
	T* SmartPtr<T>::operator->() const {
		return _ptr->operator ->();
	}

	template<class T>
	SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& smartPtr) {
		if(smartPtr._ptr==_ptr){
			return *this;
		}

		if (_ptr != 0) {
			_ptr->Release();
		}

		_ptr = smartPtr._ptr;
		if (_ptr != 0) {
			_ptr->AddRef();
		}

		return *this;
	}

	template<class T>
	bool SmartPtr<T>::operator==(const SmartPtr<T>& smartPtr) const {
		if (_ptr == smartPtr._ptr) {
			return true;
		}

		return false;
	}

	template<class T>
	bool SmartPtr<T>::operator==(T* ptr) const {
		if (_ptr == NULL) {
			if (ptr == NULL) {
				return true;
			} else {
				return false;
			}
		} else if (_ptr != NULL) {
			if (_ptr->operator ->() == ptr) {
				return true;
			} else {
				return false;
			}
		}

		return false;
	}

	template<class T>
	bool SmartPtr<T>::operator!=(const SmartPtr<T>& smartPtr) const {
		if (_ptr != smartPtr._ptr) {
			return true;
		}

		return false;
	}

	template<class T>
	void SmartPtr<T>::Attach(T* ptr) {
		if (_ptr != NULL) {
			_ptr->Release();
		}

		if (ptr != 0) {
			_ptr = new SharedPtr<T> (ptr);
		} else {
			_ptr = 0;
		}
	}

	template<class T>
	void SmartPtr<T>::Release(void) {
		if (_ptr != NULL) {
			_ptr->Release();
		}

		_ptr = NULL;
	}

	template<class T>
	SmartPtr<T>::~SmartPtr(void) {
		Release();
	}

}

#endif
