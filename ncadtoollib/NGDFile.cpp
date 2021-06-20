#include <ncadtoollib/NGDFile.h>
#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream& operator <<(NGStream& stream, const NGDFile& obj) {
		stream
			<< obj.signature
			<< obj.versionMajor
			<< obj.versionMinor
			<< obj.unknown1
			<< obj.isEncrypted
			<< obj.netlistNCH
			<< obj.netlistObject
			<< obj.hierarchyNCH
			<< obj.hierarchy;
	
		return stream;
	}

	NGStream& operator >>(NGStream& stream, NGDFile& obj) {
		stream >> obj.signature;
		if (obj.signature != NGDFile::expectedSignature) {
			throw std::runtime_error("Unexpected NGD file signature: read " + std::to_string(obj.signature) + ", expected " + std::to_string(NGDFile::expectedSignature));
		}

		stream >> obj.versionMajor >> obj.versionMinor >> obj.unknown1;

		if (obj.versionMajor != NGDFile::expectedVersionMajor ||
			obj.versionMinor != NGDFile::expectedVersionMinor ||
			obj.expectedUnknown1 != NGDFile::expectedUnknown1)
			throw std::runtime_error(std::string("unexpected NGD version: expected major ") + NGDFile::expectedVersionMajor + ", minor " + NGDFile::expectedVersionMinor + ", unknown1 " +
				std::to_string(NGDFile::expectedUnknown1) + ", got major " + obj.versionMajor + ", minor " + obj.versionMinor + ", unknown1 " + std::to_string(obj.unknown1));

		stream >> obj.isEncrypted;

		if (obj.isEncrypted)
			throw std::runtime_error("Encrypted NGD files are not yet supported");

		stream >> obj.netlistNCH;

		{
			NGStringCache::CurrentScope currentCache(&obj.netlistNCH);

			stream >> obj.netlistObject;
		}

		stream >> obj.hierarchyNCH;
		{
			NGStringCache::CurrentScope currentCache(&obj.hierarchyNCH);

			stream >> obj.hierarchy;
		}

		return stream;
	}

}