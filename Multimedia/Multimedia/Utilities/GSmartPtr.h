/*
 * GSmartPtr.h
 *
 *  Created on: Jun 8, 2010
 *      Author: m1cro
 */

#ifndef GSMARTPTR_H_
#define GSMARTPTR_H_
#include <gst/gst.h>

namespace multimedia {

	template<class T>
	class GSmartPtr {
		private:
			T* _ptr;

		public:
			GSmartPtr(void);
			GSmartPtr(T* ptr);
			GSmartPtr(const GSmartPtr<T>& gPtr);
			void Attach(T* ptr);
			void Release(void);
			bool operator ==(GSmartPtr<T> gPtr) const;
			bool operator !=(GSmartPtr<T> gPtr) const;
			T* operator->(void);
			T* GetPtr(void);
			const GSmartPtr<T>& operator =(const GSmartPtr<T>& gPtr);
			virtual ~GSmartPtr(void);
	};

	template<class T>
	GSmartPtr<T>::GSmartPtr(void) {
		_ptr = NULL;
	}

	template<class T>
	GSmartPtr<T>::GSmartPtr(T* ptr) {
		if (ptr != NULL) {
			gst_object_ref(ptr);
		}

		_ptr = ptr;
	}

	template<class T>
	GSmartPtr<T>::GSmartPtr(const GSmartPtr<T>& gPtr) {
		//GstObject* ptr=static_cast<GstObject*>(gPtr._ptr);
		if (gPtr._ptr != NULL) {
			gst_object_ref(gPtr._ptr);
		}

		_ptr = gPtr._ptr;
	}

	template<class T>
	void GSmartPtr<T>::Attach(T* ptr) {
		if (_ptr != NULL) {
			gst_object_unref(_ptr);
		}

		if (ptr != NULL) {
			gst_object_ref(ptr);
		}
		_ptr = ptr;
	}

	template<class T>
	void GSmartPtr<T>::Release(void) {
		if (_ptr != NULL) {
			gst_object_unref(_ptr);
		}

		_ptr = NULL;
	}

	template<class T>
	T* GSmartPtr<T>::operator->(void) {
		return _ptr;
	}

	template<class T>
	T* GSmartPtr<T>::GetPtr(void) {
		return _ptr;
	}

	template<class T>
	bool GSmartPtr<T>::operator ==(GSmartPtr<T> gPtr) const {
		return _ptr == gPtr._ptr;
	}

	template<class T>
	bool GSmartPtr<T>::operator !=(GSmartPtr<T> gPtr) const {
		return _ptr != gPtr._ptr;
	}

	template<class T>
	const GSmartPtr<T>& GSmartPtr<T>::operator =(const GSmartPtr<T>& gPtr) {
		//GstElement* ptr=static_cast<GstElement*>(gPtr._ptr);
		if (_ptr != NULL) {
			gst_object_unref(_ptr);
		}

		if (gPtr._ptr != NULL) {
			gst_object_ref(gPtr._ptr);
		}

		_ptr = gPtr._ptr;
		return *this;
	}

	template<class T>
	GSmartPtr<T>::~GSmartPtr(void) {
		if (_ptr != NULL) {
			gst_object_unref(_ptr);
		}
	}

}

#endif /* GSMARTPTR_H_ */
