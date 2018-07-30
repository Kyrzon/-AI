
#include "bitarray.hpp"

#include <cstdlib>
#include <cstring>
#include <iostream>

void CBitArray::resize(const int newSizeInBits) {
	if (sizeInBits != newSizeInBits) {
		if (array)
			delete[] array;
		sizeInBits = newSizeInBits > 0 ? newSizeInBits : 1;
		sizeInCells = (sizeInBits >> 5) + 1;
		array = new int[sizeInCells];
	}
	setToZero();
}

CBitArray::CBitArray(const int size) {
	array = NULL;
	resize(size);
}

int CBitArray::getSizeInBits() const {
	return sizeInBits;
}

void CBitArray::setToZero(void) {

	memset(array, 0, sizeof(array[0]) * sizeInCells);

}

CBitArray::CBitArray(const CBitArray &other) {
	this->sizeInBits = other.sizeInBits;
	this->sizeInCells = other.sizeInCells;
	array = new int[sizeInCells];
	memcpy((void*) (this->array), (void *) (other.array),
			sizeof(this->array[0]) * this->sizeInCells);
}
const CBitArray& CBitArray::operator =(const CBitArray &other) {
	if (&other == this)
		return *this;
	sizeInBits = other.sizeInBits;
	sizeInCells = other.sizeInCells;
	if (array)
		delete[] array;
	array = new int[sizeInCells];
	if (other.array) {
		memcpy((void*) (this->array), (void*) (other.array),
				sizeof(array[0]) * sizeInCells);
	} else {
		this->setToZero();
	}
	return *this;
}
void CBitArray::setBitToZero(const int index) {
	int cellIndex = index >> 5;
	int mask = 0x01 << (index & 0x1F);
	array[cellIndex] &= ~mask;
}
void CBitArray::setBitToOne(const int index) {
	int cellIndex = index >> 5;
	int mask = 0x01 << (index & 0x1F);
	array[cellIndex] |= mask;
}
;
int CBitArray::getBitValue(const int index) const {
	int cellIndex = index >> 5;
	int mask = 0x01 << (index & 0x1F);
	return (array[cellIndex] & mask) ? 1 : 0;
}
;
void CBitArray::random(void) {
	for (int i = 0; i < sizeInBits; i++) {
		if ((rand() % 2) == 0) {
			this->setBitToZero(i);
		} else {
			this->setBitToOne(i);
		}
	}
}
int CBitArray::getOctet(int index) const {
	int bitIndex = index * 6;
	//int bitIndex = index * 3;
	int cellIndex = bitIndex >> 5;
	int bitOffset = bitIndex - (cellIndex << 5);
	//return (array[cellIndex] >> bitOffset) & 7;
	return (array[cellIndex] >> bitOffset) & 63;
}
std::ostream& operator <<(std::ostream& out, CBitArray &array) {
	for (int i = 0; i < array.sizeInBits; i++) {
		out << (array.getBitValue(i) == 0 ? "0" : "1");
	}
	return out;
}
void CBitArray::display(void) {
	for (int i = 0; i < sizeInBits; i++) {
		std::cout << (getBitValue(i) == 0 ? "0" : "1");
	}
}

CBitArray::~CBitArray() {
	delete[] array;
}

