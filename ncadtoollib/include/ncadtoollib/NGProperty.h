#ifndef NCADTOOLIB_NGPROPERTY_H
#define NCADTOOLIB_NGPROPERTY_H

#include <ncadtoollib/NGCachedString.h>
#include <variant>

namespace ncadtoollib {
	class NGStream;

	class NGProperty {
	public:
		NGCachedString propertyName;

		virtual std::string valueAsString() const;
		virtual std::string valueAsVerilogFriendlyToken() const;
	};

	class NGPropertyInteger final : public NGProperty {
	public:
		uint32_t propertyValue;

		std::string valueAsString() const override;
		std::string valueAsVerilogFriendlyToken() const override;
	};

	class NGPropertyFloat final : public NGProperty {
	public:
		double propertyValue;

		std::string valueAsString() const override;
		std::string valueAsVerilogFriendlyToken() const override;
	};

	class NGPropertyString final : public NGProperty {
	public:
		NGCachedString propertyValue;

		std::string valueAsString() const override;
		std::string valueAsVerilogFriendlyToken() const override;
	};

	class NGPropertyObject final : public NGProperty {
	public:

	};

	class NGPropertyTiming final : public NGProperty {
	public:
		uint32_t unknown1;
		uint32_t unknown2;
		uint8_t  unknown3;

		std::string valueAsString() const override;
	};

	class NGPropertyPinref final : public NGProperty {
	public:
		uint16_t unknown1;
		uint8_t  unknown2;
		uint8_t  unknown3;
		uint32_t unknown4;
		uint32_t unknown5;
		uint8_t  unknown6;

		std::string valueAsString() const override;
	};

	class NGPropertyParameter final : public NGProperty {
	public:
		uint16_t unknown2;
		std::string valueAsString() const override;
	};

	class NGPropertyTimingString final : public NGProperty {
	public:
		NGCachedString propertyValue;
		std::string valueAsString() const override;
	};

	NGStream& operator <<(NGStream& stream, const NGProperty& obj);
	NGStream& operator >>(NGStream& stream, NGProperty& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyInteger& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyInteger& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyFloat& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyFloat& obj);
	
	NGStream& operator <<(NGStream& stream, const NGPropertyString& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyString& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyObject& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyObject& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyTiming& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyTiming &obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyPinref& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyPinref& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyParameter& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyParameter& obj);

	NGStream& operator <<(NGStream& stream, const NGPropertyTimingString& obj);
	NGStream& operator >>(NGStream& stream, NGPropertyTimingString& obj);

	template<typename... Args>
	const NGProperty& propertyFromVariant(const std::variant<Args...>& variant) {
		return std::visit([](const auto & val) -> const NGProperty& { return val; }, variant);
	}
}

#endif
