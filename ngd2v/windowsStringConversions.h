#ifndef WINDOWS_STRING_CONVERSIONS_H
#define WINDOWS_STRING_CONVERSIONS_H

#include <string>
#include <string_view>

std::string wideStringToUtf8String(const std::wstring_view& wideString);
std::wstring utf8StringToWideString(const std::string_view& utf8String);

#endif
