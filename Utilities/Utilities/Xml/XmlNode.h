#pragma once
#include <Utilities/Xml/XmlException.h>
#include <Utilities/Xml/IXmlObjectStrategy.h>
#include <Utilities/Strategy/Strategy.h>
#include <vector>
#include <map>
#include <string>
#include <queue>

namespace utils {

    class XmlNode {
    private:
        std::wstring _objectName;
        std::map<std::wstring, std::wstring> _attributes;
        std::vector<XmlNode> _childObjects;
        std::wstring _xmlValue;

    public:
        static const wchar_t CONST_TAG_BEGIN_SYMBOL;
        static const wchar_t CONST_TAG_END_SYMBOL;
        static const wchar_t CONST_TAG_CLOSE_SYMBOL;
        static const wchar_t CONST_TEXT_START_SYMBOL;
        static const wchar_t CONST_LEXICAL_DELIMITER_SYMBOL;
        static const wchar_t CONST_TAG_ARGUMENT_SIGN_SYMBOL;
        static const std::wstring CONST_TAG_ARGUMENT_VALUE_DELIMITERS;
        static const std::wstring CONST_XML_DELIMITERS;

    private:
        void ReadAttributes(std::wstring& stream)throw (XmlException);
        std::wstring ReadAttributeName(std::wstring& stream)throw (XmlException);
        std::wstring ReadAttributeValue(std::wstring& stream)throw (XmlException);
        void ReadBody(std::wstring& stream)throw (XmlException);
        void ReadCloseTag(std::wstring& stream)throw (XmlException);
        bool IsEndOfTag(std::wstring& stream)throw (XmlException);
        bool IsACloseTagSymbols(std::wstring& stream);
        bool IsComment(const std::wstring& stream)throw (XmlException);
        void ReadComment(std::wstring& stream)throw (XmlException);

    public:
        XmlNode(std::wstring& stream)throw (XmlException);
        virtual ~XmlNode(void);
    };

}

