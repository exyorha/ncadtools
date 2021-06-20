#ifndef NCADTOOLIB_NGDESIGN_H
#define NCADTOOLIB_NGDESIGN_H

#include <stdint.h>

#include <vector>

#include <ncadtoollib/NGTaggedUnion.h>
#include <ncadtoollib/NGLogBlock.h>
#include <ncadtoollib/NGPhysBlock.h>
#include <ncadtoollib/NGLogPrim.h>
#include <ncadtoollib/NGNetwork.h>
#include <ncadtoollib/NGSignal.h>

namespace ncadtoollib {
	class NGStream;

	using NGDModuleVariant = NGTaggedUnion<uint8_t,
		NGLogBlock,
		NGPhysBlock,
		NGLogPrim
	>;

	class NGDesign {
	public:
		uint32_t topModuleId;
		uint32_t unknown2;
		uint32_t unknown3;
		uint32_t unknown4;
		uint32_t unknown5;
		uint8_t  unknown6;
		//uint32_t blockCount;
		//uint32_t networkCount;
		//uint32_t globalSignalCount;

		std::vector<NGDModuleVariant> blocks;

		std::vector<NGNetwork> networks;
		std::vector<NGSignal> globalSignals;
	};	
	
	NGStream& operator <<(NGStream& stream, const NGDesign& obj);
	NGStream& operator >>(NGStream& stream, NGDesign& obj);

	template<typename... Args> 
	const NGBaseBlock& moduleFromVariant(const std::variant<Args...>& variant) {
		return std::visit([](const auto& val) -> const NGBaseBlock& { return val; }, variant);
	}
}

#endif
