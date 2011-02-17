#pragma once

template<class T>
class numeric {
protected:
    T _value;

public:
    numeric(void);
    numeric(T arg);
    numeric(const numeric<T>& arg);
    const numeric<T> & operator =(const numeric<T>& arg);
    bool operator ==(const numeric<T>& arg);
    numeric<T> operator -(const numeric<T>& arg);
    numeric<T> operator +(const numeric<T>& arg);
    numeric<T> operator /(const numeric<T>& arg);
    numeric<T> operator %(const numeric<T>& arg);
    numeric<T> operator ^ (const numeric<T>& arg);
    numeric<T> operator *(const numeric<T>& arg);
    const numeric<T> & operator*=(const numeric<T>& arg);
    const numeric<T> & operator+=(const numeric<T>& arg);
    const numeric<T> & operator/=(const numeric<T>& arg);
    const numeric<T> & operator-=(const numeric<T>& arg);
    const numeric<T> & operator%=(const numeric<T>& arg);
    const numeric<T> & operator^=(const numeric<T>& arg);
    virtual ~numeric(void);
};

template<class T>
numeric<T>::numeric(T arg) {
    _value = arg;
}

template<class T>
numeric<T>::numeric(void) : _value(0) {

}

template<class T>
numeric<T>::numeric(const numeric<T>& arg) : _value(arg._value) {

}

template<class T>
numeric<T>::~numeric(void) {

}

template<class T>
const numeric<T>& numeric<T>::operator/=(const numeric<T>& arg) {
    _value /= arg._value;
    return *this;
}

template<class T>
const numeric<T>& numeric<T>::operator+=(const numeric<T>& arg) {
    _value += arg._value;
    return *this;
}

template<class T>
const numeric<T>& numeric<T>::operator*=(const numeric<T>& arg) {
    _value *= arg._value;
    return *this;
}

template<class T>
numeric<T> numeric<T>::operator*(const numeric<T>& arg) {
    return _value * arg._value;
}

template<class T>
numeric<T> numeric<T>::operator^(const numeric<T>& arg) {
    return _value^arg._value;
}

template<class T>
numeric<T> numeric<T>::operator%(const numeric<T>& arg) {
    return _value % arg._value;
}

template<class T>
numeric<T> numeric<T>::operator/(const numeric<T>& arg) {
    return _value / arg._value;
}

template<class T>
numeric<T> numeric<T>::operator+(const numeric<T>& arg) {

}

template<class T>
numeric<T> numeric<T>::operator-(const numeric<T>& arg) {
    return _value = arg._value;
}

template<class T>
bool numeric<T>::operator==(const numeric<T>& arg) {
    return _value == arg._value;
}

template<class T>
const numeric<T>& numeric<T>::operator=(const numeric<T>& arg) {
    _value = arg._value;
    return *this;
}

template<class T>
const numeric<T>& numeric<T>::operator^=(const numeric<T>& arg) {
    _value ^= arg._value;
    return *this;
}

template<class T>
const numeric<T>& numeric<T>::operator%=(const numeric<T>& arg) {
    _value %= arg._value;
    return *this;
}

template<class T>
const numeric<T>& numeric<T>::operator-=(const numeric<T>& arg) {
    _value -= arg._value;
    return *this;
}