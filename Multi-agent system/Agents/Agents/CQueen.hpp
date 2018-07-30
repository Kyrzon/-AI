#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "CChesspiece.hpp"

class CQueen : public CChesspiece
{
public:
	CQueen();
	CQueen(std::pair< DWORD64, DWORD64 > coordinates);
	~CQueen();

	bool TryHack(std::pair< DWORD64, DWORD64 > coordinates);

private:

};

CQueen::CQueen()
{
}

CQueen::CQueen(std::pair< DWORD64, DWORD64 > coordinates) : CChesspiece(coordinates)
{
	SetName("Queen");
}

CQueen::~CQueen(){}


/*
*	��������� ���������� ������, ������� �������� �������
*	���������� 1, ���� ����� �������
*	���������� 0, ���� �� ������ �������
*/
bool CQueen::TryHack(std::pair< DWORD64, DWORD64 > coordinates)
{
	if ((GetXCoordinates() == coordinates.first) || (GetYCoordinates() == coordinates.second))
		return 1;

	if (abs(GetXCoordinates() - coordinates.first) == abs(GetYCoordinates() - coordinates.second))
		return 1;

	return 0;
}

#endif	