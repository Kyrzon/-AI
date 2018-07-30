/*
 * chessboard64modify.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: cvstudent
 */

/*
 * chessboard64.hpp
 *
 *  Created on: Mar 13, 2015
 *      Author: cvstudent
 */

#ifndef CHESSBOARD64MODIFY_HPP_
#define CHESSBOARD64MODIFY_HPP_


#include "ichomosome.hpp"

class CChomosomeChessboard64x64Modify: public IChromosome {
public:
	CChomosomeChessboard64x64Modify(void) {
		this->CBitArray::resize(384);
		this->random();
	};

	double fitness(void) const {
		int count = 0;
		bool left;
		bool right;
		bool down;
		for (int x1 = 0; x1 < 63; ++x1) {
			left = true;
			right = true;
			down = true;
			int y1 = getOctet(x1);
			for (int x2 = x1 + 1; x2 < 64; ++x2) {
				int y2 = getOctet(x2);
				if (y1 == y2 || abs(x2 - x1) == abs(y2 - y1))
				{
					if( ((y2 - y1) < 0) && left)
					{
						left = false;
						++count;
						if(!right && !down)
							break;
					}
					if( ((y2 - y1) > 0) && right)
					{
						right = false;
						++count;
						if(!left && !down)
							break;
					}
					if( (y1 == y2) && down)
					{
						down = false;
						++count;
						if(!left && !right)
							break;
					}
				}
			}
		}
		return static_cast<double>(189 - count);
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
