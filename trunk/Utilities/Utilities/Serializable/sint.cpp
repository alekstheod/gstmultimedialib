#include "sint.h"
#include <sstream>
#include <Utilities/StrUtil/StrUtil.h>

using namespace std;
using namespace utils;

sint::sint(void) : numeric<int>(0) {
}

sint::sint(int arg) : numeric<int>(arg) {
}

sint::sint(const sint& arg) : numeric<int>(arg._value) {

}

sint::~sint(void)throw () {
}

std::wstring sint::ToXml(const std::wstring& propertyName)const {
    return ToXmlString(propertyName, StrUtil::toWideString(_value));
}

std::wstring sint::GetValue(void)const {
    return StrUtil::toWideString(_value);
}

bool sint::SetValue(const std::wstring& inputValue) {
    try {
        _value = StrUtil::lexical_cast<int>(inputValue);
    } catch (const utils::bad_cast&) {
        return false;
    }
    return true;
}