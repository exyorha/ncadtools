#ifndef NCADTOOLIB_NGDFILE_H
#define NCADTOOLIB_NGDFILE_H

#include <stdint.h>

#include <string>

#include <ncadtoollib/NGStringCache.h>
#include <ncadtoollib/NGObject.h>
#include <ncadtoollib/NGDesign.h>

namespace ncadtoollib {
	class NGStream;

	class NGDFile {
	public:
		uint32_t signature;
		std::string versionMajor;
		std::string versionMinor;
		
		uint8_t unknown1;
		
		uint8_t isEncrypted;

		NGStringCache netlistNCH;
		NGObject netlistObject;

		NGStringCache hierarchyNCH;
		NGDesign hierarchy;

		static constexpr uint32_t expectedSignature = 0xC0D0E0F0;
		static constexpr const char* expectedVersionMajor = "2";
		static constexpr const char* expectedVersionMinor = "15";
		static constexpr uint8_t expectedUnknown1 = 0;
	};

	NGStream& operator <<(NGStream& stream, const NGDFile& obj);
	NGStream& operator >>(NGStream& stream, NGDFile& obj);
}

#endif
