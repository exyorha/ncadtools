#include <ncadtoollib/NGDesign.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGDesign& obj) {
		return stream
			<< obj.topModuleId
			<< obj.unknown2
			<< obj.unknown3
			<< obj.unknown4
			<< obj.unknown5
			<< obj.unknown6
			<< static_cast<uint32_t>(obj.blocks.size())
			<< static_cast<uint32_t>(obj.networks.size())
			<< static_cast<uint32_t>(obj.globalSignals.size())
			<< obj.blocks
			<< obj.networks
			<< obj.globalSignals;
	}

	NGStream& operator >>(NGStream& stream, NGDesign& obj) {
		uint32_t blockSize;
		uint32_t networkSize;
		uint32_t globalSignalSize;

		stream
			>> obj.topModuleId
			>> obj.unknown2
			>> obj.unknown3
			>> obj.unknown4
			>> obj.unknown5
			>> obj.unknown6
			>> blockSize
			>> networkSize
			>> globalSignalSize;

		obj.blocks.resize(blockSize);
		obj.networks.resize(networkSize);
		obj.globalSignals.resize(globalSignalSize);

		return stream
			>> obj.blocks
			>> obj.networks
			>> obj.globalSignals;
	}
}