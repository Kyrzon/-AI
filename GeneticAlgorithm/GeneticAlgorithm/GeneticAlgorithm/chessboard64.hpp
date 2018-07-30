

#ifndef CHESSBOARD64_HPP_
#define CHESSBOARD64_HPP_


#include "ichomosome.hpp"

class CChomosomeChessboard64x64: public IChromosome {
public:
	CChomosomeChessboard64x64(void) {
		this->CBitArray::resize(384);
		this->random();
	};

	double fitness(void) const {
		int count = 0;
		for (int x1 = 0; x1 < 63; ++x1) {
			int y1 = getOctet(x1);
			for (int x2 = x1 + 1; x2 < 64; ++x2) {
				int y2 = getOctet(x2);
				if (y1 == y2 || abs(x2 - x1) == abs(y2 - y1)) {
					++count;
				}
			}
		}
		return static_cast<double>(2016.1 - count);
	};


	void interpret(void) {
		for (int i = 0; i < 64; ++i) {
			int octet = getOctet(i);
			for (int j = 0; j < octet; ++j)
				std::cout << "0";
			std::cout << "1";
			for (int j = octet + 1; j < 64; ++j)
				std::cout << "0";
			std::cout << std::endl;
		}
	};
};

#endif /* CHESSBOARD64_HPP_ */
