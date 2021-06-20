#ifndef NCADTOOLIB_NGSTREAM_H
#define NCADTOOLIB_NGSTREAM_H

#include <string>
#include <vector>

namespace ncadtoollib {
	class NGStream {
	protected:
		NGStream();
		~NGStream();

	public:
		NGStream(const NGStream& other) = delete;
		NGStream &operator = (const NGStream& other) = delete;

		NGStream& operator <<(uint64_t val);
		NGStream& operator >>(uint64_t& val);

		NGStream& operator <<(uint32_t val);
		NGStream& operator >>(uint32_t &val);

		NGStream& operator <<(uint16_t val);
		NGStream& operator >>(uint16_t& val);

		NGStream& operator <<(uint8_t val);
		NGStream& operator >>(uint8_t& val);

		NGStream& operator <<(double val);
		NGStream& operator >>(double& val);

		NGStream& operator <<(const std::string &val);
		NGStream& operator >>(std::string& val);

		template<typename T>
		NGStream& operator <<(const std::vector<T>& val) {
			for (const auto& entry : val) {
				*this << entry;
			}

			return *this;
		}

		template<typename T>
		NGStream& operator >>(std::vector<T>& val) {
			for (auto& entry : val) {
				*this >> entry;
			}

			return *this;
		}

	protected:
		virtual void writeData(const void* data, size_t size) = 0;
		virtual void readData(void* data, size_t size) = 0;
		virtual size_t findTerminatorCharacter(char ch) const = 0;
	};
}

#endif
