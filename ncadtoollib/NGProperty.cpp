#include <ncadtoollib/NGProperty.h>
#include <ncadtoollib/NGStream.h>

#include <stdexcept>
#include <string>
#include <sstream>

namespace ncadtoollib {

	std::string NGProperty::valueAsString() const {
		return {};
	}

	std::string NGProperty::valueAsVerilogFriendlyToken() const {
		return "1";
	}

	std::string NGPropertyInteger::valueAsString() const {
		return std::to_string(propertyValue);
	}

	std::string NGPropertyInteger::valueAsVerilogFriendlyToken() const {
		return std::to_string(propertyValue);
	}

	std::string NGPropertyFloat::valueAsString() const {
		return std::to_string(propertyValue);
	}

	std::string NGPropertyFloat::valueAsVerilogFriendlyToken() const {
		return std::to_string(propertyValue);
	}

	std::string NGPropertyString::valueAsString() const {
		return propertyValue.string();
	}

	std::string NGPropertyString::valueAsVerilogFriendlyToken() const {
		std::stringstream quotedValue;

		quotedValue << "\"";

		for (char character : propertyValue.string()) {
			if (character < 32 || character > 127) {
				quotedValue << "\\";
				quotedValue.width(3);
				quotedValue.fill('0');
				quotedValue << std::oct;
				quotedValue << character;
			}
			else if (character == '\\' || character == '\"') {
				quotedValue << "\\";
				quotedValue << character;
			}
			else {
				quotedValue << character;
			}
		}
		
		quotedValue << "\"";

		return quotedValue.str();
	}

	std::string NGPropertyTiming::valueAsString() const {
		std::stringstream ss;

		ss << "NGPropertyTiming<" << unknown1 << ", " << unknown2 << ", " << unknown3 << ">";

		return ss.str();
	}

	std::string NGPropertyPinref::valueAsString() const {
		std::stringstream ss;

		ss << "NGPropertyPinref<" << unknown1 << ", " << unknown2 << ", " << unknown3 << ", " << unknown4 << ", " << unknown5 << ", " << unknown6 << ">";

		return ss.str();
	}

	std::string NGPropertyParameter::valueAsString() const {
		std::stringstream ss;

		ss << "NGPropertyParameter<" << unknown2 << ">";

		return ss.str();
	}

	std::string NGPropertyTimingString::valueAsString() const {
		std::stringstream ss;

		ss << "NGPropertyTimingString<" << propertyValue.string() << ">";

		return ss.str();
	}

	NGStream& operator <<(NGStream& stream, const NGProperty& obj) {
		return stream << obj.propertyName;
	}

	NGStream& operator >>(NGStream& stream, NGProperty& obj) {
		return stream >> obj.propertyName;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyInteger& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.propertyValue;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyInteger& obj) {
		return stream >> static_cast<NGProperty&>(obj) >> obj.propertyValue;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyFloat& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.propertyValue;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyFloat& obj) {
		return stream >> static_cast<NGProperty&>(obj) >> obj.propertyValue;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyString& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.propertyValue;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyString& obj) {
		return stream >> static_cast<NGProperty&>(obj) >> obj.propertyValue;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyObject& obj) {
		throw std::logic_error("NGPropertyObject is not implemented");
	}

	NGStream& operator >>(NGStream& stream, NGPropertyObject& obj) {
		throw std::logic_error("NGPropertyObject is not implemented");
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyTiming& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.unknown1 << obj.unknown2 << obj.unknown3;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyTiming& obj) {
		return stream >> static_cast<NGProperty&>(obj) >> obj.unknown1 >> obj.unknown2 >> obj.unknown3;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyPinref& obj) {
		return stream
			<< static_cast<const NGProperty&>(obj)
			<< obj.unknown1
			<< obj.unknown2
			<< obj.unknown3
			<< obj.unknown4
			<< obj.unknown5
			<< obj.unknown6;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyPinref& obj) {
		return stream
			>> static_cast<NGProperty&>(obj)
			>> obj.unknown1
			>> obj.unknown2
			>> obj.unknown3
			>> obj.unknown4
			>> obj.unknown5
			>> obj.unknown6;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyParameter& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.unknown2;
	}

	NGStream& operator >>(NGStream& stream, NGPropertyParameter& obj) {
		return stream >> static_cast<NGProperty&>(obj) >> obj.unknown2;
	}

	NGStream& operator <<(NGStream& stream, const NGPropertyTimingString& obj) {
		return stream << static_cast<const NGProperty&>(obj) << obj.propertyValue;

	}
	NGStream& operator >>(NGStream& stream, NGPropertyTimingString& obj) {
		return stream << static_cast<const NGProperty&>(obj) >> obj.propertyValue;
	}
}