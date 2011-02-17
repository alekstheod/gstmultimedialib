#include "sfloat.h"
#include <Utilities/StrUtil/StrUtil.h>

using namespace std;
using namespace utils;

sfloat::sfloat(void) {
}

sfloat::sfloat(float arg) : numeric<float>(arg) {

}

sfloat::~sfloat(void)throw () {
}

std::wstring sfloat::ToXml(const std::wstring& propertyName)const {
    return ToXmlString(propertyName, StrUtil::ToWideString(_value));
}

std::wstring sfloat::GetValue(void)const {
    return StrUtil::ToWideString(_value);
}

bool sfloat::SetValue(const std::wstring& inputValue) {
    try {
        _value = StrUtil::lexical_cast<float>(inputValue);
    } catch (const utils::bad_cast&) {
        return false;
    }
    return true;
}