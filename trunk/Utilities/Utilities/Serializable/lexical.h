#pragma once

template<class T>
class lexical {
protected:
    T _value;

public:
    lexical(void);
    lexical(T arg);
    lexical(const lexical& arg);
    const lexical<T> & operator =(const lexical<T>& arg);
    const lexical<T> & operator +(const lexical<T>& arg);
    bool operator ==(const lexical<T>& arg);
    lexical<T> operator +=(const lexical<T>& arg);
    virtual ~lexical(void)throw ();
};

template<class T>
lexical<T>::lexical(void) {

}

template<class T>
lexical<T>::lexical(T arg) {
    _value = arg;
}

template<class T>
lexical<T>::lexical(const lexical<T>& arg) {
    _value = arg._value;
}

template<class T>
lexical<T>::~lexical(void) throw () {
}

template<class T>
bool lexical<T>::operator==(const lexical<T>& arg) {
    return _value == arg._value;
}

template<class T>
const lexical<T>& lexical<T>::operator+(const lexical<T>& arg) {
    return _value + arg._value;
}

template<class T>
const lexical<T>& lexical<T>::operator=(const lexical<T>& arg) {
    _value = arg._value;
    return *this;
}

template<class T>
lexical<T> lexical<T>::operator+=(const lexical<T>& arg) {
    return _value += arg._value;
}
