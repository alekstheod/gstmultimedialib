/*
 * GSmartPtr.h
 *
 *  Created on: Jun 8, 2010
 *      Author: m1cro
 */

#ifndef GSMARTPTR_H_
#define GSMARTPTR_H_
#include <gst/gst.h>

namespace multimedia
{

template<class T>
class GSmartPtr
{
private:
    T* m_ptr;

public:
    GSmartPtr ( void );
    GSmartPtr ( T* ptr );
    GSmartPtr ( const GSmartPtr<T>& gPtr );
    void attach ( T* ptr );
    void release ( void );
    bool operator == ( GSmartPtr<T> gPtr ) const;
    bool operator != ( GSmartPtr<T> gPtr ) const;
    T* operator-> ( void );
    T* getPtr ( void );
    const T* getPtr ( void ) const;
    const GSmartPtr<T>& operator = ( const GSmartPtr<T>& gPtr );
    virtual ~GSmartPtr ( void );
};

template<class T>
GSmartPtr<T>::GSmartPtr ( void )
{
    m_ptr = NULL;
}

template<class T>
GSmartPtr<T>::GSmartPtr ( T* ptr )
{
    if ( ptr != NULL ) {
        gst_object_ref ( ptr );
    }

    m_ptr = ptr;
}

template<class T>
GSmartPtr<T>::GSmartPtr ( const GSmartPtr<T>& gPtr )
{
    if ( gPtr.m_ptr != NULL ) {
        gst_object_ref ( gPtr.m_ptr );
    }

    m_ptr = gPtr.m_ptr;
}

template<class T>
void GSmartPtr<T>::attach ( T* ptr )
{
    if ( m_ptr != NULL ) {
        gst_object_unref ( m_ptr );
    }

    if ( ptr != NULL ) {
        gst_object_ref ( ptr );
    }
    m_ptr = ptr;
}

template<class T>
void GSmartPtr<T>::release ( void )
{
    if ( m_ptr != NULL ) {
        gst_object_unref ( m_ptr );
    }

    m_ptr = NULL;
}

template<class T>
T* GSmartPtr<T>::operator-> ( void )
{
    return m_ptr;
}

template<class T>
T* GSmartPtr<T>::getPtr ( void )
{
    return m_ptr;
}

template<class T>
const T* GSmartPtr<T>::getPtr ( void ) const
{
    return m_ptr;
}

template<class T>
bool GSmartPtr<T>::operator == ( GSmartPtr<T> gPtr ) const
{
    return m_ptr == gPtr.m_ptr;
}

template<class T>
bool GSmartPtr<T>::operator != ( GSmartPtr<T> gPtr ) const
{
    return m_ptr != gPtr.m_ptr;
}

template<class T>
const GSmartPtr<T>& GSmartPtr<T>::operator = ( const GSmartPtr<T>& gPtr )
{
    if ( m_ptr != NULL ) {
        gst_object_unref ( m_ptr );
    }

    if ( gPtr.m_ptr != NULL ) {
        gst_object_ref ( gPtr.m_ptr );
    }

    m_ptr = gPtr.m_ptr;
    return *this;
}

template<class T>
GSmartPtr<T>::~GSmartPtr ( void )
{
    if ( m_ptr != NULL ) {
        gst_object_unref ( m_ptr );
    }
}

}

#endif /* GSMARTPTR_H_ */
