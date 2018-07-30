#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

#include "population.hpp"
#include "chessboard64.hpp"
#include "chessboard64modify.hpp"

int FindOptimalPopulationClassicalGeneticAlgorithm
(
		char* nameFileToResult = "result.txt",
		int numberOfTries = 100,
		int startPopulationSize = 100,
		int endPopulationSize = 1000,
		int stepPopulationSize = 100,
		char crossing = 50,
		char mutation = 25,
		double desiredValue = 2011
)
{
	std::ofstream outputFile(nameFileToResult, std::ofstream::out);

	if (!outputFile.is_open()) {

		std::cerr << "Can't open " << nameFileToResult << " for writing" << std::endl;

		return 0;

	}
	for (int currentPopulationSize = startPopulationSize; currentPopulationSize <= endPopulationSize;
			currentPopulationSize += stepPopulationSize)
	{

		double totalElapsedTime = 0.F;

		int count_bad = 0;

		for (int tryIndex = 0; tryIndex < numberOfTries; tryIndex++)
		{

			int count;
			std::time_t timer_begin;
			std::time_t timer_end;
			do{
				std::cout << "currentPopulationSize: " << (int)currentPopulationSize << "\t"
					<< tryIndex << " ";
				CPopulation<CChomosomeChessboard64x64> pop(currentPopulationSize, (double)crossing / 100.0, (double)mutation / 100.0);
				timer_begin = clock();
				count = pop.searchSolution(desiredValue);
				timer_end = clock();
				if (count != -1)
					break;

				std::cout << "Bad!!! " << (timer_end - timer_begin) / CLOCKS_PER_SEC << std::endl;
				count_bad++;
				if (count_bad == numberOfTries)
				{
					std::cout << "Bad!!! " << (timer_end - timer_begin) / CLOCKS_PER_SEC << std::endl;
					count_bad++;
					if (count_bad == numberOfTries / 3)
					{
						totalElapsedTime = 0;
						tryIndex = numberOfTries;
						timer_end = timer_begin;
						break;
					}
				}
			} while (count == -1);

			totalElapsedTime += (timer_end - timer_begin) / CLOCKS_PER_SEC;
			std::cout << (timer_end - timer_begin) / CLOCKS_PER_SEC << std::endl;

		}

		outputFile << (int)currentPopulationSize << ", ";
		outputFile << (totalElapsedTime / numberOfTries) << " " << count_bad << std::endl;

		std::cout << "currentPopulationSize: " << (int)currentPopulationSize << "\t";
		std::cout << "Avg Time: " << (totalElapsedTime / numberOfTries) << "\t";
		std::cout << "Bad: " << count_bad << std::endl;

	}
	return 0;
}

template <class TestClass>
int TestGeneticAlgorithm
(
		char* nameFileToResult = "result.txt",
		bool modify = false,
		double desiredValue = 2011,
		int numberOfTries = 100,
		int PopulationSize = 100,
		char startCrossover = 10,
		char endCrossover = 90,
		char stepCrossover = 10,
		char startMutation = 5,
		char endMutation = 50,
		char stepMutation = 5
)
{

	std::ofstream outputFile(nameFileToResult, std::ofstream::out);

	if (!outputFile.is_open())
	{
		std::cerr << "Can't open " << nameFileToResult << " for writing" << std::endl;
		return 0;
	}

	for (char currentCrossover = startCrossover; currentCrossover <= endCrossover;
				currentCrossover += stepCrossover)
	{

		for (char currentMutation = startMutation; currentMutation <= endMutation;
				currentMutation += stepMutation)
		{
			double totalElapsedTime = 0.F;
			int count_bad = 0;

			for (int tryIndex = 0; tryIndex < numberOfTries; tryIndex++)
			{
				int count;
				std::time_t timer_begin;
				std::time_t timer_end;
				
				do{
					std::cout << tryIndex << " currentCrossover: " << (int)currentCrossover << "\t"
						<< "currentMutation: " << (int)currentMutation << "\t ";
					CPopulation<TestClass> pop(PopulationSize, (double)currentCrossover / 100.0, (double)currentMutation / 100.0);
					timer_begin = clock();
					count = pop.searchSolution(desiredValue, modify);
					timer_end = clock();
					if (count == -1)
					{
						std::cout << "Bad!!! " << (timer_end - timer_begin) / CLOCKS_PER_SEC << std::endl;
						count_bad++;
						if (count_bad == numberOfTries / 3)
						{
							totalElapsedTime = 0;
							tryIndex = numberOfTries;
							timer_end = timer_begin;
							break;
						}
					}
				} while (count == -1);
				totalElapsedTime += (timer_end - timer_begin) / CLOCKS_PER_SEC;
				std::cout << (timer_end - timer_begin) / CLOCKS_PER_SEC << std::endl;
			}
			outputFile << (int)currentCrossover << " ";
			outputFile << (int)currentMutation << " ";
			outputFile << (totalElapsedTime / numberOfTries) << " " << count_bad << std::endl;

			std::cout << "currentCrossover: " << (int)currentCrossover << "\t";
			std::cout << "currentMutation: " << (int)currentMutation << "\t";
			std::cout << "Avg Time: " << (totalElapsedTime / numberOfTries) << "\t";
			std::cout << "Bad: " << count_bad << std::endl;
		}
	}

	return 0;
}

void man(char *nameProg)
{
	std::cerr << "Wrong arguments!" << std::endl;
	std::cerr << "Usage: " << nameProg << " <Type Algoritm> <output CSV-file>" << std::endl;
	std::cerr << "Type Algoritm:" <<std::endl;
	std::cerr << "	-findOptimalPopClassic" <<std::endl;
	std::cerr << "	-classic" <<std::endl;
	std::cerr << "	-modify" <<std::endl;

	return;
}


int main( int argc, char* argv[] ) {

	if (argc != 3)
	{
		man(argv[0]);
		return 0;
	}

	if(!strcmp(argv[1], "-findOptimalPopClassic"))
	{
		FindOptimalPopulationClassicalGeneticAlgorithm(argv[1]);
	}
	else if(!strcmp(argv[1], "-classic"))
	{
		/*char* nameFileToResult = "result.txt",
			bool modify = false,
			double desiredValue = 2011,
			int numberOfTries = 100,
			int PopulationSize = 100,
			float startCrossover = 0.1,
			float endCrossover = 0.9,
			float stepCrossover = 0.1,
			float startMutation = 0.05,
			float endMutation = 0.5,
			float stepMutation = 0.05*/
		TestGeneticAlgorithm<CChomosomeChessboard64x64>(argv[2], false, 2011, 33, 100, 10, 90, 10, 5, 50, 5);
	}
	else if(!strcmp(argv[1], "-modify"))
	{
		TestGeneticAlgorithm<CChomosomeChessboard64x64Modify>(argv[2], true, 184, 33, 100, 10, 90, 10, 5, 50, 5);
	}
	else
	{
		man(argv[0]);
	}

	return 0;
}
