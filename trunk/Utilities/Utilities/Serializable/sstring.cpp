#include "sstring.h"

using namespace std;
using namespace utils;

sstring::sstring(void) : lexical<string>() {
}

sstring::sstring(const char* str) : lexical<string>(string(str)) {

}

sstring::sstring(const sstring& str) : lexical<string>(str._value) {

}

sstring::~sstring(void)throw () {
}

std::wstring sstring::ToXml(const std::wstring& propertyName)const {
    return ToXmlString(propertyName, wstring(_value.begin(), _value.end()));
}

const char* sstring::c_str(void)const {
    return _value.c_str();
}

std::wstring sstring::GetValue(void)const {
    return wstring(_value.begin(), _value.end());
}

bool sstring::SetValue(const std::wstring& inputValue) {
    _value = string(inputValue.begin(), inputValue.end());
    return true;
}
