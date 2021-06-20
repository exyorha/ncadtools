#include <ncadtoollib/NGInputStream.h>

#include <stdexcept>

namespace ncadtoollib {
	NGInputStream::NGInputStream(const uint8_t* data, size_t dataSize) : m_ptr(data), m_end(data + dataSize) {

	}

	NGInputStream::~NGInputStream() = default;

	void NGInputStream::writeData(const void* data, size_t size) {
		(void)data;
		(void)size;

		throw std::logic_error("NGInputStream is read-only");
	}

	void NGInputStream::readData(void* data, size_t size) {
		if (size > m_end - m_ptr)
			throw std::runtime_error("premature end of stream");

		memcpy(data, m_ptr, size);
		m_ptr += size;
	}

	size_t NGInputStream::findTerminatorCharacter(char ch) const {
		auto ptr = static_cast<const uint8_t *>(memchr(m_ptr, ch, m_end - m_ptr));
		if (ptr == nullptr)
			throw std::logic_error("terminator character not found");

		return ptr - m_ptr;
	}
}