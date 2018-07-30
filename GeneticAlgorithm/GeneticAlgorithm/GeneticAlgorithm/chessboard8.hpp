

#ifndef CHESSBOARD8_HPP_
#define CHESSBOARD8_HPP_

#include "ichomosome.hpp"

class CChomosomeChessboard8x8: public IChromosome {
public:
	CChomosomeChessboard8x8(void) {
		this->CBitArray::resize(24);
		this->random();
	};

	double fitness(void) const {
		int count = 0;
		for (int x1 = 0; x1 < 7; ++x1) {
			int y1 = getOctet(x1);
			for (int x2 = x1 + 1; x2 < 8; ++x2) {
				int y2 = getOctet(x2);
				if (y1 == y2 || abs(x2 - x1) == abs(y2 - y1)) {
					++count;
				}
			}
		}
		return static_cast<double>(28 - count);
	}

	/*double fitness(void) const {
			int count = 0;
			bool left;
			bool right;
			bool down;
			for (int x1 = 0; x1 < 7; ++x1) {
				left = true;
				right = true;
				down = true;
				int y1 = getOctet(x1);
				for (int x2 = x1 + 1; x2 < 8; ++x2) {
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
			return static_cast<double>(28.1 - count);
		};*/
	;
	void interpret(void) {
		for (int i = 0; i < 8; ++i) {
			int octet = getOctet(i);
			for (int j = 0; j < octet; ++j)
				std::cout << "0";
			std::cout << "1";
			for (int j = octet + 1; j < 8; ++j)
				std::cout << "0";
			std::cout << std::endl;
		}
	};
};


#endif /* CHESSBOARD8_HPP_ */
