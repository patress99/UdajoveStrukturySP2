#include "vector.h"
#include "ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(this->memory_, other.memory_, other.size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure& Vector::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			this->size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memcpy(this->memory_, other.memory_, size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		if (this == &other) {
			return true;
		}
		else {
			return size_ == other.size_ && memcmp(memory_, other.memory_, size_) == 0;
		}
	}

	bool Vector::operator!=(const Vector& other) const
	{
		if (this == &other) {
			return true;
		}
		else {
			return size_ != other.size_ && memcmp(memory_, other.memory_, size_) == 0;
		}
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Out of bounds!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Out of bounds!");
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Out of bounds!");
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Out of bounds!");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Out of bounds!");

		if (&src == &dest && destStartIndex >= srcStartIndex && destStartIndex < srcStartIndex + length) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Out of bounds!");
		return reinterpret_cast<byte*>(memory_) + index;
	}

}