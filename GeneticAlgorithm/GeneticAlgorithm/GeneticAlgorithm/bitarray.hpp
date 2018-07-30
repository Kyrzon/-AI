

#ifndef BITARRAY_HPP_
#define BITARRAY_HPP_

#include <ostream>

class CBitArray {
private:
	int *array;
	int sizeInCells;
protected:
	int sizeInBits;
	void resize(const int newSizeInBits);
public:
	CBitArray(const int size = 32);
	CBitArray(const CBitArray &other);
	~CBitArray();
	int getSizeInBits() const;
	void setToZero(void);
	void setBitToZero(const int index);
	void setBitToOne(const int index);
	int getBitValue(const int index) const;
	void random(void);
	void display(void);
	int getOctet(int index) const;
	const CBitArray& operator =(const CBitArray &other);
	friend std::ostream& operator <<(std::ostream& out, CBitArray &array);
};


#endif /* BITARRAY_HPP_ */
