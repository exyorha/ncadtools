#include <ncadtoollib/NGStream.h>

namespace ncadtoollib {
	NGStream::NGStream() = default;

	NGStream::~NGStream() = default;

	NGStream& NGStream::operator <<(uint64_t val) {
		uint8_t bytes[8];

		bytes[0] = static_cast<uint8_t>(val >> 56);
		bytes[1] = static_cast<uint8_t>(val >> 48);
		bytes[2] = static_cast<uint8_t>(val >> 40);
		bytes[3] = static_cast<uint8_t>(val >> 32);
		bytes[4] = static_cast<uint8_t>(val >> 24);
		bytes[5] = static_cast<uint8_t>(val >> 16);
		bytes[6] = static_cast<uint8_t>(val >> 8);
		bytes[7] = static_cast<uint8_t>(val);

		writeData(bytes, sizeof(bytes));

		return *this;
	}

	NGStream& NGStream::operator >>(uint64_t& val) {
		uint8_t bytes[8];

		readData(bytes, sizeof(bytes));

		val =
			(static_cast<uint64_t>(bytes[0]) << 56) |
			(static_cast<uint64_t>(bytes[1]) << 48) |
			(static_cast<uint64_t>(bytes[2]) << 40) |
			(static_cast<uint64_t>(bytes[3]) << 32) |
			(static_cast<uint64_t>(bytes[4]) << 24) |
			(static_cast<uint64_t>(bytes[5]) << 16) |
			(static_cast<uint64_t>(bytes[6]) << 8) |
			 static_cast<uint64_t>(bytes[7]);

		return *this;
	}

	NGStream& NGStream::operator <<(uint32_t val) {
		uint8_t bytes[4];

		bytes[0] = static_cast<uint8_t>(val >> 24);
		bytes[1] = static_cast<uint8_t>(val >> 16);
		bytes[2] = static_cast<uint8_t>(val >> 8);
		bytes[3] = static_cast<uint8_t>(val);

		writeData(bytes, sizeof(bytes));

		return *this;
	}

	NGStream& NGStream::operator >>(uint32_t& val) {
		uint8_t bytes[4];

		readData(bytes, sizeof(bytes));

		val =
			(static_cast<uint32_t>(bytes[0]) << 24) |
			(static_cast<uint32_t>(bytes[1]) << 16) |
			(static_cast<uint32_t>(bytes[2]) << 8) |
			(static_cast<uint32_t>(bytes[3]) << 0);

		return *this;

	}

	NGStream& NGStream::operator <<(uint16_t val) {
		uint8_t bytes[2];

		bytes[0] = static_cast<uint8_t>(val >> 8);
		bytes[1] = static_cast<uint8_t>(val);

		writeData(bytes, sizeof(bytes));

		return *this;
	}

	NGStream& NGStream::operator >>(uint16_t& val) {
		uint8_t bytes[2];

		readData(bytes, sizeof(bytes));		
		
		val =
			(static_cast<uint32_t>(bytes[0]) << 8) |
			(static_cast<uint32_t>(bytes[1]) << 0);

		return *this;
	}

	NGStream& NGStream::operator <<(uint8_t val) {
		writeData(&val, sizeof(val));

		return *this;
	}

	NGStream& NGStream::operator >>(uint8_t& val) {
		readData(&val, sizeof(val));

		return *this;
	}

	NGStream& NGStream::operator <<(double val) {
		union {
			uint64_t i;
			double f;
		} u;

		u.f = val;

		return *this << u.i;
	}

	NGStream& NGStream::operator >>(double& val) {
		union {
			uint64_t i;
			double f;
		} u;

		*this >> u.i;

		val = u.f;

		return *this;
	}
	
	NGStream& NGStream::operator <<(const std::string& val) {
		writeData(val.c_str(), val.size() + 1);
		return *this;
	}
	
	NGStream& NGStream::operator >>(std::string& val) {
		auto length = findTerminatorCharacter(0);
		unsigned char terminator;
		
		val.resize(length);

		readData(val.data(), length);
		readData(&terminator, sizeof(terminator));

		return *this;
	}
}
