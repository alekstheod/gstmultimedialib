#include "sbool.h"

using namespace utils;

const std::wstring sbool::CONST_BOOL_TRUE_DESCRIPTION = L"TRUE";
const std::wstring sbool::CONST_BOOL_FALSE_DESCRIPTION = L"FALSE";

sbool::sbool(void) {
}

sbool::sbool(bool value) {
    _value = value;
}

sbool::sbool(const sbool& arg) {
    _value = arg._value;
}

sbool::~sbool(void)throw () {
}

std::wstring sbool::ToXml(const std::wstring& propertyName)const {
    if (_value) {
        return ToXmlString(propertyName, CONST_BOOL_TRUE_DESCRIPTION);
    }
    return ToXmlString(propertyName, CONST_BOOL_FALSE_DESCRIPTION);
}

std::wstring sbool::GetValue(void)const {
    if (_value) {
        return CONST_BOOL_TRUE_DESCRIPTION;
    }
    return CONST_BOOL_FALSE_DESCRIPTION;
}

bool sbool::SetValue(const std::wstring& inputValue) {
    if (inputValue == CONST_BOOL_TRUE_DESCRIPTION) {
        _value = true;
        return true;
    } else if (inputValue == CONST_BOOL_FALSE_DESCRIPTION) {
        _value = false;
        return true;
    }
    return false;
}

const sbool& sbool::operator=(const sbool& arg) {
    _value = arg._value;
    return *this;
}

bool sbool::operator==(const sbool& arg)const {
    return _value == arg._value;
}
