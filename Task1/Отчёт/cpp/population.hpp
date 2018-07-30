#ifndef POPULATION_HPP_
#define POPULATION_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "ichomosome.hpp"

template<class Ch> class CPopulation {
private:
	double *rouletteWheel;

	void updateRouletteWheel(void) {
		if (!rouletteWheel)
			rouletteWheel = new double[populationSize + 1];
		rouletteWheel[0] = .0l;
		for (int i = 1; i <= populationSize; i++) {
			rouletteWheel[i] = rouletteWheel[i - 1]
					+ chromosomes[i - 1].fitness();
		}
		double max = rouletteWheel[populationSize];
		for (int i = 1; i <= populationSize; i++) {
			rouletteWheel[i] /= max;
		}
	};


	int selectSingle(void)
	{
		double value = ((double) rand()) / ((double) RAND_MAX);
		int i;
		for (i = 0; i < populationSize && rouletteWheel[i] < value; ++i)
			;
		return i;
	};
	void runSelection(void) {
		for (int i = 0; i < matePoolSize; i++) {
			chromosomes.push_back(chromosomes[selectSingle()]);
		}
	};

	Ch MaxFitness(Ch chromosomeFirst, Ch chromosomeSecond)
	{
		if (chromosomeFirst.fitness() > chromosomeSecond.fitness())
			return chromosomeFirst;

		return chromosomeSecond;
	};

	void runTournamentSelection()
	{
		for (int i = 0; i < matePoolSize; i++)
		{
			chromosomes.push_back
			(
				MaxFitness
				(
					chromosomes[rand() % populationSize],
					MaxFitness
					(
						chromosomes[rand() % populationSize],
						chromosomes[rand() % populationSize]
					)
				)
			);
		}
	};

	void applyCrossover(void)
	{
		for (int i = 0; i < matePoolSize; i += 2)
		{

			Ch parent1 = chromosomes[populationSize + i];
			int splitter = chromosomes[populationSize + i].getSizeInBits();
			splitter = (rand() % (splitter & 0xFFFF))
						+ ((rand() % (splitter >> 4)) << 4);
			chromosomes[populationSize + i].copyBitRange(chromosomes[populationSize + i + 1], 0, splitter);
			chromosomes[populationSize + i + 1].copyBitRange(parent1, 0, splitter);

		}
	};


	void applyMutation(void)
	{
		for (int i = 0; i < populationSize; ++i)
		{
			if (rand()  <= (mutationProbability * RAND_MAX))
			{
				dynamic_cast<IChromosome&>(chromosomes[i]).mutate();
			}
		}
	};
protected:
	std::vector<Ch> chromosomes;
	int populationSize;
	int matePoolSize;
	float mutationProbability;
	float crossoverProbability;

public:
	CPopulation(int popSize = 100, float pc = 0.5, float pm = 0.05) {
		std::srand(std::time(NULL));
		populationSize = popSize < 1 ? 100 : popSize;
		crossoverProbability = pc < .0f || pc > 1.f ? 0.5f : pc;
		mutationProbability = pm < .0f || pm > 1.f ? 0.05f : pm;
		matePoolSize = populationSize * crossoverProbability;
		matePoolSize += matePoolSize % 2 == 1 ? 1 : 0;
		for (int i = 0; i < populationSize; i++) {
			chromosomes.push_back(Ch());
			chromosomes.back().random();
		}
		rouletteWheel = NULL;
	}
	void displayProperties(void) {
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "Population size: " << populationSize << std::endl;
		std::cout << "Mate pool size: " << matePoolSize << std::endl;
		std::cout << "Cross. probability: " << crossoverProbability << std::endl;
		std::cout << "Mut. probability: " << mutationProbability << std::endl;
		std::cout << "Chromosome size: " << chromosomes[0].getSizeInBits() << std::endl;
		std::cout << "---------------------------------------" << std::endl;
	}
	~CPopulation()
	{
		if(rouletteWheel)
			delete[] rouletteWheel;
	}
	void display() {
		for (int i = 0; i < populationSize; i++) {
			std::cout << "Chromosome index " << i << " : ";
			chromosomes[i].display();
			std::cout << " - fitness value: " << chromosomes[i].fitness();
			std::cout << std::endl;
		}
	}
	void runEpoch(bool modify = false) {
		applyMutation();
		if (modify){
			runTournamentSelection();
		}else
		{
			updateRouletteWheel();
			runSelection();
		}
		applyCrossover();
		std::sort(chromosomes.begin(), chromosomes.end());
		std::reverse(chromosomes.begin(), chromosomes.end());
		while (static_cast<int>(chromosomes.size()) != populationSize)
			chromosomes.pop_back();
	}
	int searchSolution(const double desiredValue, bool modify = false) {
		int count = 0;
		while (chromosomes[0].fitness() < desiredValue) {
			runEpoch(modify);
			count++;
			if(count==50000)
				return -1;
		}
		return count;
	}
	Ch& getBestSolution() {
		return chromosomes[0];
	}
};


#endif /* POPULATION_HPP_ */
