#ifndef NCADTOOLIB_NGINPUTSTREAM_H
#define NCADTOOLIB_NGINPUTSTREAM_H

#include "NGStream.h"

namespace ncadtoollib {
	class NGInputStream final : public NGStream {
	public:
		NGInputStream(const uint8_t* data, size_t dataSize);
		~NGInputStream();

	protected:
		void writeData(const void* data, size_t size) override;
		void readData(void* data, size_t size) override;
		size_t findTerminatorCharacter(char ch) const override;

	private:
		const uint8_t* m_ptr;
		const uint8_t* m_end;
	};
}

#endif
