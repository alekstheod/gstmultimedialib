#ifndef RECT_H
#define RECT_H

namespace gl{

template<typename T>
struct Rect {
    const T left;
    const T top;
    const T right;
    const T bottom;

    Rect(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {
	if ( left >= right || top >= bottom  ) {
	    throw GLException ( "GLDevice::GLDevice - Wrong window rect" );
	}
    }
    
    Rect& operator = (const Rect& other ){
      const_cast<T&>(left) = other.left;
      const_cast<T&>(top) = other.top;
      const_cast<T&>(right) = other.right;
      const_cast<T&>(bottom) = other.bottom;
    }
};

}

#endif