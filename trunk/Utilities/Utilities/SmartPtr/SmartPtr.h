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
        SmartPtr(void);
        SmartPtr(T* ptr);
        SmartPtr(const SmartPtr<T>& smartPtr);
        void Attach(T* ptr);
        void Release(void);
        SmartPtr & operator=(const SmartPtr<T>& smartPtr);
        bool operator ==(const SmartPtr<T>& smartPtr)const;
        bool operator ==(T* ptr)const;
        bool operator !=(const SmartPtr<T>& smartPtr)const;
        T * operator->()const;
        T* GetPtr(void)const;
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
    T* utils::SmartPtr<T>::GetPtr(void)const {
        if (_ptr == NULL) {
            return NULL;
        }

        return _ptr->GetPtr();
    }

    template<class T>
    T* SmartPtr<T>::operator->()const {
        return _ptr->operator ->();
    }

    template<class T>
    SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& smartPtr) {
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
    bool SmartPtr<T>::operator==(const SmartPtr<T>& smartPtr)const {
        if (_ptr == smartPtr._ptr) {
            return true;
        }

        return false;
    }

    template<class T>
    bool SmartPtr<T>::operator==(T* ptr)const {
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
    bool SmartPtr<T>::operator!=(const SmartPtr<T>& smartPtr)const {
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
            _ptr = new SharedPtr<T > (ptr);
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
