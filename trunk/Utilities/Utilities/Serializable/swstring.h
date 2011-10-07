#pragma once
#include "sprimitive.h"
#include "lexical.h"
#include <string>

namespace utils {

class swstring: public sprimitive, public lexical<std::wstring> {
public:
	swstring(void);
	swstring(const wchar_t* str);
	swstring(const swstring& str);
	virtual std::wstring ToXml(const std::wstring& propertyName) const;
	virtual std::wstring GetValue(void) const;
	virtual bool SetValue(const std::wstring&);
	const wchar_t* c_str(void) const;
	virtual ~swstring(void) throw ();
};

}

