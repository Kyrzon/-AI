#ifndef CCHESSAGENT_HPP_
#define CCHESSAGENT_HPP_

#include <vector>
#include <ctime>

#include "CAgent.hpp"
#include "CChesspiece.hpp"
#include "CQueen.hpp"

class CChessAgent : public ÑAgent
{
public:
	CChessAgent();
	~CChessAgent();

	DWORD64 GetCountConflicts();
	void SetMyFigure(CChesspiece *myFigure);
	void SetOtherFigure(std::vector< CChesspiece* > otherFigures);

	void AddFigure(CChesspiece *newFigure);
	void MoveFigure(DWORD64 maxX, DWORD64 maxY);

private:
	CChesspiece *myFigure;
	std::vector< CChesspiece* > otherFigures;
	DWORD64 countConflicts;
};

CChessAgent::CChessAgent()
{
	std::srand(std::time(NULL));
}

CChessAgent::~CChessAgent()
{
	myFigure->~CChesspiece();
}

void CChessAgent::SetMyFigure(CChesspiece *myFigure)
{
	this->myFigure = myFigure;
	return;
}

void CChessAgent::SetOtherFigure(std::vector< CChesspiece* > otherFigures)
{
	this->otherFigures = otherFigures;
}

void CChessAgent::AddFigure(CChesspiece *newFigure)
{
	this->otherFigures.push_back(newFigure);
	return;
}

DWORD64 CChessAgent::GetCountConflicts()
{
	countConflicts = 0;
	for (DWORD64 i = 0; i < otherFigures.size(); i++)
	{
		countConflicts += otherFigures.at(i)->TryHack(myFigure->GetCoordinates());
		countConflicts += myFigure->TryHack(otherFigures.at(i)->GetCoordinates());
	}
	return countConflicts;
}

void CChessAgent::MoveFigure(DWORD64 maxX, DWORD64 maxY)
{
	
	DWORD64 tryX;
	DWORD64 tryY;
	bool good = false;
	while (!good)
	{
		tryX = rand() % maxX;
		tryY = rand() % maxY;
		good = true;
		for (DWORD64 i = 0; i < otherFigures.size(); i++)
		{
			if ((tryX == otherFigures.at(i)->GetXCoordinates()) && (tryY == otherFigures.at(i)->GetYCoordinates()))
			{
				good = false;
				break;
			}
		}
	}

	myFigure->SetCoordinates(std::make_pair(tryX, tryY));

	return;
}

#endif