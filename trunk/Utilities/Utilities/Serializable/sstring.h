#pragma once
#include <string>
#include "sprimitive.h"
#include "lexical.h"

namespace utils {

class sstring: public sprimitive, public lexical<std::string> {
public:
	sstring(void);
	sstring(const char* str);
	sstring(const sstring& str);
	virtual std::wstring ToXml(const std::wstring& propertyName) const;
	virtual std::wstring GetValue(void) const;
	virtual bool SetValue(const std::wstring&);
	const char* c_str(void) const;
	virtual ~sstring(void) throw ();
};

}

