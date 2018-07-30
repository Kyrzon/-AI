#ifndef CCHESSBOARDAGENT_HPP_
#define CCHESSBOARDAGENT_HPP_

#include <algorithm>

#include "CAgent.hpp"
#include "CChessAgent.hpp"
#include "CChessBoard.hpp"
#include "CChesspiece.hpp"

class CChessBoardAgent : public СAgent
{
public:
	CChessBoardAgent();
	CChessBoardAgent(CChessBoard chessBoard);
	~CChessBoardAgent();

	std::vector< std::pair< DWORD64, DWORD64 > > FindSolution();
	bool AddDynamicFigure(CChesspiece *newFigure);
	bool AddStaticFigure(CChesspiece *newFigure);
	

private:
	CChessBoard chessBoard;
	std::vector< CChessAgent*> agents;

	void AddAgent(CChesspiece *newFigure);
};

CChessBoardAgent::CChessBoardAgent()
{
	srand(time(NULL));
}

CChessBoardAgent::CChessBoardAgent(CChessBoard chessBoard)
{
	this->chessBoard = chessBoard;
}

CChessBoardAgent::~CChessBoardAgent()
{
	for (DWORD64 i = agents.size()-1; i >= 0; --i)
	{
		agents.at(i)->~CChessAgent();
		agents.pop_back();
	}

	this->chessBoard.~CChessBoard();
}

/*
*	Добавляет фигуру и агента
*	Возвращает 1, если фигура добавлена
*	Возвращает 0, если фигуру невозможно добавить
*/
bool CChessBoardAgent::AddDynamicFigure(CChesspiece *newFigure)
{
	if (!this->chessBoard.AddFigure( newFigure ))
		return 0;

	for (DWORD64 i = 0; i < agents.size(); i++)
	{
		agents.at(i)->AddFigure( newFigure );
	}

	AddAgent(newFigure);

	return 1;
}

bool CChessBoardAgent::AddStaticFigure(CChesspiece *newFigure)
{
	if (!this->chessBoard.AddFigure(newFigure))
		return 0;

	for (DWORD64 i = 0; i < agents.size(); i++)
	{
		agents.at(i)->AddFigure(newFigure);
	}

	return 1;
}

void CChessBoardAgent::AddAgent(CChesspiece *newFigure)
{
	CChessAgent *newAgent = new CChessAgent();

	newAgent->SetMyFigure(newFigure);

	std::vector< CChesspiece* > tmp = chessBoard.GetFigures();
	tmp.pop_back();
	newAgent->SetOtherFigure(tmp);
	agents.push_back(newAgent);

	return;
}

std::vector< std::pair< DWORD64, DWORD64 > > CChessBoardAgent::FindSolution()
{
	std::time_t begin = clock();
	DWORD64 maxCountConflicts;
	DWORD64 countConflicts;
	DWORD64 step = 0;
	while ((clock() - begin) / CLOCKS_PER_SEC < 3600)	//6 минут
	{
		DWORD64 indexBadAgent;
		maxCountConflicts = 0;

		for (DWORD64 i = 0; i < agents.size(); i++)
		{
			countConflicts = agents.at(i)->GetCountConflicts();

			if (maxCountConflicts < countConflicts)
			{
				maxCountConflicts = countConflicts;
				indexBadAgent = i;
			}
			else if ((maxCountConflicts == countConflicts) && (rand() % 2))
			{
				indexBadAgent = i;
			}

		}

		if (maxCountConflicts == 0)
			break;

		
		agents.at(indexBadAgent)->MoveFigure(chessBoard.GetHorizontalSize(), chessBoard.GetVerticalSize());
		step++;

	}

	return chessBoard.GetCoordinateFigures();
}


#endif