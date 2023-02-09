#include <fstream>
#include "SquareLattice.h"


SquareLattice::SquareLattice(
	int L,
	bool heterogeneous_hev_susceptibilities,
	bool heterogeneous_phev_susceptibilities,
	bool heterogeneous_bev_susceptibilities,
	bool heterogeneous_driving_patterns,
	const std::vector<Car*>& cars,
	const std::vector<double>& dps) :
	Network(L* L, "SL", heterogeneous_hev_susceptibilities, heterogeneous_phev_susceptibilities, heterogeneous_bev_susceptibilities, heterogeneous_driving_patterns, cars, dps)
{
	this->L = L;

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (j == L - 1 && i != L - 1)
			{
				agents[i * L + j]->connect(agents[i * L]);
				agents[i * L + j]->connect(agents[(i + 1) * L + j]);
			}
			else if (i == L - 1 && j != L - 1)
			{
				agents[i * L + j]->connect(agents[i * L + j + 1]);
				agents[i * L + j]->connect(agents[j]);
			}
			else if (i == L - 1 && j == L - 1)
			{
				agents[i * L + j]->connect(agents[i * L]);
				agents[i * L + j]->connect(agents[j]);
			}
			else
			{
				agents[i * L + j]->connect(agents[i * L + j + 1]);
				agents[i * L + j]->connect(agents[(i + 1) * L + j]);
			}
		}
	}
}

SquareLattice::SquareLattice(
	int L, 
	bool heterogeneous_susceptibilities, 
	bool heterogeneous_driving_patterns, 
	const std::vector<Car*>& cars, 
	const std::vector<double>& dps) :
	Network(L * L, "SL", heterogeneous_susceptibilities, heterogeneous_driving_patterns, cars, dps)
{
	this->L = L;

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (j == L - 1 && i != L - 1)
			{
				agents[i * L + j]->connect(agents[i * L]);
				agents[i * L + j]->connect(agents[(i + 1) * L + j]);
			}
			else if (i == L - 1 && j != L - 1)
			{
				agents[i * L + j]->connect(agents[i * L + j + 1]);
				agents[i * L + j]->connect(agents[j]);
			}
			else if (i == L - 1 && j == L - 1)
			{
				agents[i * L + j]->connect(agents[i * L]);
				agents[i * L + j]->connect(agents[j]);
			}
			else 
			{
				agents[i * L + j]->connect(agents[i * L + j + 1]);
				agents[i * L + j]->connect(agents[(i + 1) * L + j]);
			}
		}
	}
}

void SquareLattice::printCarEngineMap(std::string fileName)
{
	std::fstream plik(fileName, std::ios::out);
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			plik << agents[i * L + j]->getCarEngineType() << "\t";
		}
		plik << "\n";
	}
}
