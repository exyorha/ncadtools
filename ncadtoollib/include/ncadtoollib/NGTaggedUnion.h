#ifndef NCADTOOLIB_H
#define NCADTOOLIB_H

#include <stdint.h>

#include <variant>
#include <stdexcept>
#include <string>

namespace ncadtoollib {
	class NGStream;

	template<typename TagType, typename... Args>
	class NGTaggedUnion final  {
	public:
		std::variant<Args...> variant;		
	};

	template<typename TagType, typename... Args>
	NGStream& operator <<(NGStream& stream, const NGTaggedUnion<TagType, Args...>& obj) {
		stream << static_cast<TagType>(obj.variant.index());

		std::visit([&stream](const auto& value) {
			stream << value;
		}, obj.variant);

		return stream;
	}

	template<typename Variant, size_t Index = 0>
	void ngTaggedUnionVariantFromTag(Variant& variant, size_t index) {
		if constexpr (Index >= std::variant_size_v<Variant>) {
			throw std::runtime_error("invalid union tag: " + std::to_string(Index + index));
		}
		else {
			if (index == 0) {
				variant.template emplace<Index>();
			}
			else {
				ngTaggedUnionVariantFromTag<Variant, Index + 1>(variant, index - 1);
			}
		}
	}

	template<typename TagType, typename... Args>
	NGStream& operator >>(NGStream& stream, NGTaggedUnion<TagType, Args...>& obj) {
		TagType tag;
		stream >> tag;

		ngTaggedUnionVariantFromTag(obj.variant, tag);

		std::visit([&stream](auto& value) {
			stream >> value;
		}, obj.variant);

		return stream;
	}
}

#endif
