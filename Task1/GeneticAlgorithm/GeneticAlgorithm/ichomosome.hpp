/*
 * ichomosome.hpp
 *
 *  Created on: Mar 2, 2015
 *      Author: cvstudent
 */

#ifndef ICHOMOSOME_HPP_
#define ICHOMOSOME_HPP_

#include <cstdlib>

#include "bitarray.hpp"

class IChromosome: public CBitArray {
public:
	IChromosome(int size = 32) {
		this->CBitArray::resize(size);
	};
	void mutate() {
		int index = rand() % sizeInBits;
		if (getBitValue(index) == 1) {
			setBitToZero(index);
		} else {
			setBitToOne(index);
		}
	}
	void copyBitRange(const IChromosome& src, const int start,
			const int finish) {
		if (this->sizeInBits != src.getSizeInBits())
			return;
		int begin = start < 0 ? 0 : start;
		int end = finish > sizeInBits ? sizeInBits : finish;
		for (int i = begin; i < end; i++) {
			if (src.getBitValue(i) == 1)
				setBitToOne(i);
			else
				setBitToZero(i);
		}
	}
	friend bool operator <(const IChromosome& a, const IChromosome& b);
	virtual double fitness(void) const = 0;
	virtual void interpret(void) = 0;
};

bool operator <(const IChromosome& a, const IChromosome& b) {
	return a.fitness() < b.fitness();
}
;

#endif /* ICHOMOSOME_HPP_ */
