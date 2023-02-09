#include "WattsStrogatz.h"
#include <fstream>

WattsStrogatz::WattsStrogatz(
	int N,
	int k,
	double beta,
	bool heterogeneous_hev_susceptibilities,
	bool heterogeneous_phev_susceptibilities,
	bool heterogeneous_bev_susceptibilities,
	bool heterogeneous_driving_patterns,
	const std::vector<Car*>& cars,
	const std::vector<double>& dps) :
	Network(N, "WS", heterogeneous_hev_susceptibilities, heterogeneous_phev_susceptibilities, heterogeneous_bev_susceptibilities, heterogeneous_driving_patterns, cars, dps)
{
	this->k = k;
	this->beta = beta;

	int m = k / 2;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < N; j++)
		{
			agents[j]->connect(agents[(j + 1 + i) % N]);
		}
	}

	std::uniform_real_distribution<double> uniformReal(0.0, 1.0);
	std::uniform_int_distribution<int> uniformInt(0, N - 1);
	double variateReal;
	double variateInt;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < N; j++)
		{
			variateReal = uniformReal(generator);
			if (variateReal < beta)
			{
				Agent* neighbour = agents[(j + 1 + i) % N];
				Agent* potentialNeighbour;
				do
				{
					variateInt = uniformInt(generator);
					potentialNeighbour = agents[variateInt];
				} while (!agents[j]->replace(neighbour, potentialNeighbour));
			}
		}
	}
}

WattsStrogatz::WattsStrogatz(
	int N, 
	int k, 
	double beta, 
	bool heterogeneous_susceptibilities, 
	bool heterogeneous_driving_patterns, 
	const std::vector<Car*>& cars, 
	const std::vector<double>& dps) :
	Network(N, "WS", heterogeneous_susceptibilities, heterogeneous_driving_patterns, cars, dps)
{
	this->k = k;
	this->beta = beta;

	int m = k / 2;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < N; j++)
		{
			agents[j]->connect(agents[(j + 1 + i) % N]);
		}
	}

	std::uniform_real_distribution<double> uniformReal(0.0, 1.0);
	std::uniform_int_distribution<int> uniformInt(0, N - 1);
	double variateReal;
	double variateInt;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < N; j++)
		{
			variateReal = uniformReal(generator);
			if (variateReal < beta)
			{
				Agent* neighbour = agents[(j + 1 + i) % N];
				Agent* potentialNeighbour;
				do
				{
					variateInt = uniformInt(generator);
					potentialNeighbour = agents[variateInt];
				} while (!agents[j]->replace(neighbour, potentialNeighbour));
			}
		}
	}
}

void WattsStrogatz::printCarEngineMap(std::string fileName)
{
	std::fstream plik(fileName, std::ios::out);
	for (int i= 0; i < N; i++)
	{
		plik << agents[i]->getCarEngineType() << "\t";
	}
	plik << "\n";
}
