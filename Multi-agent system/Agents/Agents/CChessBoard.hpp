#ifndef CHESSBOARD_HPP_
#define CHESSBOARD_HPP_

#include <vector>
#include "CChesspiece.hpp"

class CChessBoard
{
public:
	CChessBoard();
	CChessBoard(DWORD64 horizontalSize, DWORD64 verticalSize);
	~CChessBoard();


	DWORD64 GetHorizontalSize();
	DWORD64 GetVerticalSize();
	std::vector< CChesspiece* > GetFigures();
	std::vector< std::pair< DWORD64, DWORD64 > > GetCoordinateFigures();
	CChesspiece* GetLastAddedFigure();

	bool AddFigure(CChesspiece *figure);
	bool CheckCoordinats(std::pair< DWORD64, DWORD64 > coordinates);
	void ShowBoard();


private:
	DWORD64 horizontalSize;
	DWORD64 verticalSize;
	std::vector< CChesspiece* > figures;
};

CChessBoard::CChessBoard()
{
	this->horizontalSize = 0;
	this->verticalSize = 0;
}

CChessBoard::CChessBoard(DWORD64 horizontalSize, DWORD64 verticalSize)
{
	this->horizontalSize = horizontalSize;
	this->verticalSize = verticalSize;
}

CChessBoard::~CChessBoard()
{
}

std::vector< CChesspiece* > CChessBoard::GetFigures()
{
	return this->figures;
}

CChesspiece* CChessBoard::GetLastAddedFigure()
{
	return this->figures.back();
}


/*
*	ƒобавл€ет фигуру
*	¬озвращает 1, если фигура добавлена
*	¬озвращает 0, если фигуру невозможно добавить
*/
bool CChessBoard::AddFigure(CChesspiece* figure)
{
	if (CheckCoordinats(figure->GetCoordinates()))
		return 0;

	this->figures.push_back(figure);

	return 1;
}

/*
*	ѕринимает координаты
*	¬озвращает 1, если координаты выход€т за пределы доски
*	¬озвращает 0, если координаты в пределах доски
*/
bool CChessBoard::CheckCoordinats(std::pair< DWORD64, DWORD64 > coordinates)
{
	if (coordinates.first >= this->horizontalSize || coordinates.first < 0)
		return 1;

	if (coordinates.second >= this->verticalSize || coordinates.second < 0)
		return 1;

	for (DWORD64 i = 0; i < figures.size(); i++)
	{
		if ((coordinates.first == figures.at(i)->GetXCoordinates()) && (coordinates.second == figures.at(i)->GetYCoordinates()))
		{
			return 1;
		}
	}

	return 0;
}

DWORD64 CChessBoard::GetHorizontalSize()
{
	return this->horizontalSize;
}

DWORD64 CChessBoard::GetVerticalSize()
{
	return this->verticalSize;
}

void CChessBoard::ShowBoard()
{
	int **board = new int *[verticalSize];

	for (DWORD64 i = 0; i < verticalSize; i++)
	{
		board[i] = new int[horizontalSize];
	}

	for (DWORD64 i = 0; i < horizontalSize; i++)
	{
		for (DWORD64 j = 0; j < verticalSize; j++)
			board[i][j] = false;
	}

	for (DWORD64 i = 0; i < figures.size(); i++)
	{
		board[figures.at(i)->GetXCoordinates()][figures.at(i)->GetYCoordinates()] = i+1;
	}

	for (DWORD64 i = 0; i < horizontalSize; i++)
	{
		for (DWORD64 j = 0; j < verticalSize; j++)
		{
			if (board[i][j]) 
				std::cout << "[" << board[i][j] << "]";
			else 
				std::cout << "[ ]";
		}
		std::cout << std::endl;
	}

	for (DWORD64 i = 0; i < verticalSize; i++) {
		delete[]board[i];
	}
	delete[]board;

}

std::vector< std::pair< DWORD64, DWORD64 > > CChessBoard::GetCoordinateFigures()
{
	std::vector < std::pair< DWORD64, DWORD64 > > coordinateFigures;

	for (DWORD64 i = 0; i < figures.size(); i++)
		coordinateFigures.push_back(figures.at(i)->GetCoordinates());

	return coordinateFigures;
}
#endif