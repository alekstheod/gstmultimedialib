#ifndef UTILS_STRATEGY_H
#define UTILS_STRATEGY_H

#include <Utilities/SmartPtr/SmartPtr.h>

namespace utils {

    template<class T>
    class Strategy {
    private:
        SmartPtr<T> _strategy;
        LockObject _lockObject;

    public:
        Strategy(void);
        Strategy(const Strategy<T>& strategy);
        Strategy<T> & operator=(const Strategy<T>& strategy);
        bool operator==(T* ptr);
        bool operator!=(T* ptr);
        SmartPtr<T> operator->();
        bool RegisterEventStrategy(const SmartPtr<T>& eventStrategy);
        virtual ~Strategy(void);
    };

    template<class T>
    Strategy<T>::Strategy(void) {

    }

    template<class T>
    Strategy<T>::~Strategy(void) {

    }

    template<class T>
    bool Strategy<T>::RegisterEventStrategy(const SmartPtr<T>& eventStrategy) {
        try {
            AutoLock lock(_lockObject);
            _strategy = eventStrategy;
        } catch (const LockException&) {
            return false;
        }
        return true;
    }

    template<class T>
    SmartPtr<T> Strategy<T>::operator->() {
        SmartPtr<T> smartPtr;
        try {
            AutoLock lock(_lockObject);
            smartPtr = _strategy;
        } catch (const LockException&) {
            return NULL;
        }
        return smartPtr;
    }

    template<class T>
    Strategy<T>& Strategy<T>::operator=(const Strategy<T>& strategy) {
        AutoLock lock(strategy._lockObject);
        AutoLock mLock(_lockObject);
        _strategy = strategy._strategy;
        return *this;
    }

    template<class T>
    Strategy<T>::Strategy(const Strategy<T>& strategy) {
        AutoLock lock(strategy._lockObject);
        _strategy = strategy._strategy;
    }

    template<class T>
    bool Strategy<T>::operator==(T* ptr) {
        AutoLock lock(_lockObject);
        return _strategy.getPtr() == ptr;
    }

    template<class T>
    bool Strategy<T>::operator!=(T* ptr) {
        AutoLock lock(_lockObject);
        return _strategy.getPtr() != ptr;
    }
}

#endif
