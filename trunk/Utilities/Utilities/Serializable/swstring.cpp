#include "swstring.h"

using namespace std;
using namespace utils;

swstring::swstring(void) :
		lexical<wstring>() {
}

swstring::swstring(const swstring& str) :
		lexical<wstring>(str._value) {
	_value = str._value;
}

swstring::swstring(const wchar_t* str) :
		lexical<wstring>(wstring(str)) {
	_value = str;
}

swstring::~swstring(void) throw () {
}

std::wstring swstring::ToXml(const std::wstring& propertyName) const {
	return ToXmlString(propertyName, _value);
}

const wchar_t* swstring::c_str(void) const {
	return _value.c_str();
}

std::wstring swstring::GetValue(void) const {
	return _value;
}

bool swstring::SetValue(const std::wstring& inputValue) {
	_value = inputValue;
	return true;
}