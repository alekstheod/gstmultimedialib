#pragma once
#include "serializable.h"
#include <Utilities/SmartPtr/SmartPtr.h>

namespace utils {

    class complexserializable : public serializable {
    public:
        complexserializable(void);
        virtual const utils::SmartPtr<serializable> GetProperty(std::wstring& propertyName) = 0;
        virtual bool SetProperty(std::wstring& propertyName, const utils::SmartPtr<serializable>& property) = 0;
        virtual ~complexserializable(void)throw ();
    };

}

