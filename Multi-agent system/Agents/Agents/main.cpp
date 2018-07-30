#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>

#include "CChessBoardAgent.hpp"
#include "CQueen.hpp"

std::vector< std::pair< DWORD64, DWORD64 > > GetSolution(std::vector< std::pair< int, int > > initialArrangement, int boardSize)
{
	CChessBoard chessBoard(boardSize, boardSize);
	CChessBoardAgent boardAgent(chessBoard);

	for (int i = 0; i < initialArrangement.size(); i++)
		if(!boardAgent.AddDynamicFigure(new CQueen(initialArrangement.at(i))))
			std::cerr << "Not added figure (" << initialArrangement.at(i).first << "; " << initialArrangement.at(i).second << ")" << std::endl;

	return boardAgent.FindSolution();
}

int main( int argc, char* argv[] ) {

	if (argc != 3) 
	{
		std::cout << "Usage: " << argv[0] << " <input filename> <output filename>" << std::endl;
		return -1;
	}

	std::string inputFilename = argv[ 1 ];
	std::ifstream inputStream( inputFilename.c_str() );
	std::string singleLine;
	std::vector< std::string > inputLines;

	while( getline ( inputStream, singleLine ) ) 
	{
		inputLines.push_back( singleLine );
	}

	inputStream.close();

	if (inputLines.size() <= 0)
	{
		std::cerr << "Wrong input file" << std::endl;
		return -1;
	}

	int boardSize = -1;
	std::stringstream ss( inputLines[ 0 ] );
	try {
		ss << std::dec;
		ss >> boardSize;
	} catch (...) {
		std::cout << "BAD TRY1" << std::endl;
	}

	if( inputLines.size() == static_cast< size_t >( boardSize + 1 ) ) 
	{
		std::vector< std::pair< int, int > > initialArrangement;

		for( int index = 1; index <= boardSize; index++ ) 
		{
			int x = -1, y = -1;
			std::stringstream ss( inputLines[ index ] );	
			try {
				ss << std::dec;
				ss >> x >> y;
			} catch (...) {
				std::cout << "BAD TRY2" << std::endl;
			}

			if( x >= 0 && y >= 0 && x < boardSize && y < boardSize ) 
			{
				initialArrangement.push_back( std::make_pair( x, y ) );
			}
		}

		std::vector< std::pair< DWORD64, DWORD64 > > solutionArrangement = GetSolution(initialArrangement, boardSize);

		std::string outputFilename = argv[ 2 ];
		std::ofstream outputStream( outputFilename.c_str() );

		std::string answer;
		answer.assign( boardSize * boardSize, '.' );

		std::vector< std::pair< DWORD64, DWORD64 > >::iterator it = solutionArrangement.begin();
		std::vector< std::pair< DWORD64, DWORD64 > >::iterator itEnd = solutionArrangement.end();

		for(; it != itEnd; it++ ) 
		{
			int offset = it->first * boardSize + it->second;
			answer[ offset ] = 'X';
		}

		for( int lineIndex = 0; lineIndex < boardSize; lineIndex++ ) 
		{
			outputStream << answer.substr( lineIndex * boardSize, boardSize ) << std::endl;
		}
		outputStream.close();
	}

	return 0;
}
