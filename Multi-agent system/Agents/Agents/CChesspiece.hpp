#ifndef CHESSPIECE_HPP_
#define CHESSPIECE_HPP_

#include <string>

#define DWORD64 long long

class CChesspiece
{
public:
	CChesspiece();
	CChesspiece(std::pair< DWORD64, DWORD64 > coordinates);
	~CChesspiece();

	std::string GetName();
	DWORD64 GetXCoordinates();
	DWORD64 GetYCoordinates();
	std::pair< DWORD64, DWORD64 > GetCoordinates();

	void SetName(std::string name);
	void SetXCoordinates(DWORD64 X);
	void SetYCoordinates(DWORD64 Y);
	void SetCoordinates(std::pair< DWORD64, DWORD64 > coordinates);

	virtual bool TryHack(std::pair< DWORD64, DWORD64 > coordinates)=0;

private:
	std::string name;
	std::pair< DWORD64, DWORD64 > coordinates;

};

CChesspiece::CChesspiece()
{
}

CChesspiece::CChesspiece(std::pair< DWORD64, DWORD64 > coordinates)
{
	this->coordinates = coordinates;
}

CChesspiece::~CChesspiece()
{
}

std::string CChesspiece::GetName()
{
	return this->name;
}

DWORD64 CChesspiece::GetXCoordinates()
{
	return this->coordinates.first;
}

DWORD64 CChesspiece::GetYCoordinates()
{
	return this->coordinates.second;
}

std::pair< DWORD64, DWORD64 > CChesspiece::GetCoordinates()
{
	return this->coordinates;
}

void CChesspiece::SetName(std::string name)
{
	this->name = name;
	return;
}

void CChesspiece::SetXCoordinates(DWORD64 X)
{
	this->coordinates.first = X;
	return;
}

void CChesspiece::SetYCoordinates(DWORD64 Y)
{
	this->coordinates.second = Y;
	return;
}

void CChesspiece::SetCoordinates(std::pair< DWORD64, DWORD64 > coordinates)
{
	this->coordinates = coordinates;
	return;
}

#endif