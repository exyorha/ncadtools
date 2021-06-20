#include "windowsStringConversions.h"

#include <Windows.h>

#include <stdexcept>

std::string wideStringToUtf8String(const std::wstring_view& wideString) {
	if (wideString.empty())
		return {};

	auto length = WideCharToMultiByte(CP_UTF8, 0, wideString.data(), wideString.size(), nullptr, 0, nullptr, nullptr);
	if (length == 0)
		throw std::runtime_error("WideCharToMultiByte failed");

	std::string output;
	output.resize(length);

	length = WideCharToMultiByte(CP_UTF8, 0, wideString.data(), wideString.size(), output.data(), output.size(), nullptr, nullptr);
	if(length == 0)
		throw std::runtime_error("WideCharToMultiByte failed");

	return output;
}

std::wstring utf8StringToWideString(const std::string_view& utf8String) {
	if (utf8String.empty())
		return {};

	auto length = MultiByteToWideChar(CP_UTF8, 0, utf8String.data(), utf8String.size(), nullptr, 0);
	if (length == 0)
		throw std::runtime_error("WideCharToMultiByte failed");

	std::wstring output;
	output.resize(length);

	length = MultiByteToWideChar(CP_UTF8, 0, utf8String.data(), utf8String.size(), output.data(), output.size());
	if (length == 0)
		throw std::runtime_error("WideCharToMultiByte failed");

	return output;
}