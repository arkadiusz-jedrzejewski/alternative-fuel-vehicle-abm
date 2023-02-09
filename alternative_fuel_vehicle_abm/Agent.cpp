#include "Agent.h"
#include <iostream>
#include <random>
#include <iostream>
#include <numeric>

void Agent::set_driving_pattern(const std::vector<double>& dps, std::mt19937_64& generator)
{
	// set driving pattern to randomly chosen driving pattern from the vector dps
	std::uniform_int_distribution<int> uniform(0, dps.size()-1);
	this->dp = dps.at(uniform(generator));
}
Agent::Agent()
{
	this->index = NAN;
	this->car = NULL;  // NULL: agent does not have a car

	// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
	this->hev_susceptibilities.push_back(2.14);
	this->hev_susceptibilities.push_back(1.96);
	this->hev_susceptibilities.push_back(2.86);

	this->phev_susceptibilities.push_back(2.07);
	this->phev_susceptibilities.push_back(1.81);
	this->phev_susceptibilities.push_back(2.58);

	this->bev_susceptibilities.push_back(2.09);
	this->bev_susceptibilities.push_back(1.98);
	this->bev_susceptibilities.push_back(2.59);

	// set the mean value of driving pattern
	this->dp = 0.38;
}

// generate susceptibility from the empirical distribution for a given engine type (HEV, PHEV, BEV)
double marketing_susceptibility(EngineType engineType, std::mt19937_64& generator);
double global_influence_susceptibility(EngineType engineType, std::mt19937_64& generator);
double local_influence_susceptibility(EngineType engineType, std::mt19937_64& generator);

// generate all susceptibilities from the empirical distributions for a given engine type (HEV, PHEV, BEV)
std::vector<double> get_susceptibilities(EngineType engineType, std::mt19937_64& generator) {

	std::vector<double> result = std::vector<double>(3);

	result[0] = marketing_susceptibility(engineType, generator);
	result[1] = global_influence_susceptibility(engineType, generator);
	result[2] = local_influence_susceptibility(engineType, generator);

	return result;
}

double marketing_susceptibility(EngineType engineType, std::mt19937_64& generator) {
	std::uniform_real_distribution<double> uniform(0, 1);
	double variate = uniform(generator);

	switch (engineType)
	{
	case EngineType::HEV:
		if (variate <= 0.17785)
		{
			return 0;
		}
		else if (variate <= 0.29797)
		{
			return 1;
		}
		else if (variate <= 0.57098)
		{
			return 2;
		}
		else if (variate <= 0.80967)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::BEV:
		if (variate <= 0.16769)
		{
			return 0;
		}
		else if (variate <= 0.30462)
		{
			return 1;
		}
		else if (variate <= 0.59846)
		{
			return 2;
		}
		else if (variate <= 0.83846)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::PHEV:
		if (variate <= 0.19734)
		{
			return 0;
		}
		else if (variate <= 0.32816)
		{
			return 1;
		}
		else if (variate <= 0.60089)
		{
			return 2;
		}
		else if (variate <= 0.80044)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
}

double global_influence_susceptibility(EngineType engineType, std::mt19937_64& generator) {
	std::uniform_real_distribution<double> uniform(0, 1);
	double variate = uniform(generator);

	switch (engineType)
	{
	case EngineType::HEV:
		if (variate <= 0.23103)
		{
			return 0;
		}
		else if (variate <= 0.38449)
		{
			return 1;
		}
		else if (variate <= 0.61046)
		{
			return 2;
		}
		else if (variate <= 0.81619)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::BEV:
		if (variate <= 0.21250)
		{
			return 0;
		}
		else if (variate <= 0.36964)
		{
			return 1;
		}
		else if (variate <= 0.60714)
		{
			return 2;
		}
		else if (variate <= 0.82679)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::PHEV:
		if (variate <= 0.24590)
		{
			return 0;
		}
		else if (variate <= 0.42623)
		{
			return 1;
		}
		else if (variate <= 0.66667)
		{
			return 2;
		}
		else if (variate <= 0.84699)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
}

double local_influence_susceptibility(EngineType engineType, std::mt19937_64& generator) {
	std::uniform_real_distribution<double> uniform(0, 1);
	double variate = uniform(generator);

	switch (engineType)
	{
	case EngineType::HEV:
		if (variate <= 0.08834)
		{
			return 0;
		}
		else if (variate <= 0.14841)
		{
			return 1;
		}
		else if (variate <= 0.29682)
		{
			return 2;
		}
		else if (variate <= 0.60777)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::BEV:
		if (variate <= 0.18333)
		{
			return 0;
		}
		else if (variate <= 0.27778)
		{
			return 1;
		}
		else if (variate <= 0.38889)
		{
			return 2;
		}
		else if (variate <= 0.55556)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	case EngineType::PHEV:
		if (variate <= 0.17647)
		{
			return 0;
		}
		else if (variate <= 0.20168)
		{
			return 1;
		}
		else if (variate <= 0.37815)
		{
			return 2;
		}
		else if (variate <= 0.66387)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
}

Agent::Agent(int index)
{
	this->index = index;
	this->car = NULL;  // NULL: agent does not have a car

	// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
	this->hev_susceptibilities.push_back(2.14);
	this->hev_susceptibilities.push_back(1.96);
	this->hev_susceptibilities.push_back(2.86);

	this->phev_susceptibilities.push_back(2.07);
	this->phev_susceptibilities.push_back(1.81);
	this->phev_susceptibilities.push_back(2.58);

	this->bev_susceptibilities.push_back(2.09);
	this->bev_susceptibilities.push_back(1.98);
	this->bev_susceptibilities.push_back(2.59);

	// set the mean value of driving pattern
	this->dp = 0.38;
}

Agent::Agent(int index, std::mt19937_64& generator)
{
	this->index = index;
	this->car = NULL;  // NULL: agent does not have a car

	// set susceptibilities based on the empirical distributions
	hev_susceptibilities = get_susceptibilities(EngineType::HEV, generator);
	phev_susceptibilities = get_susceptibilities(EngineType::PHEV, generator);
	bev_susceptibilities = get_susceptibilities(EngineType::BEV, generator);
}

Agent::Agent(int index, bool heterogeneous_hev_susceptibilities, bool heterogeneous_phev_susceptibilities, bool heterogeneous_bev_susceptibilities, bool heterogeneous_driving_patterns, std::mt19937_64& generator, const std::vector<double>& dps)
{
	this->index = index;
	this->car = NULL;  // NULL: agent does not have a car

	if (heterogeneous_hev_susceptibilities)
	{
		// set susceptibilities based on the empirical distributions
		hev_susceptibilities = get_susceptibilities(EngineType::HEV, generator);
	}
	else
	{
		// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
		this->hev_susceptibilities.push_back(2.14);
		this->hev_susceptibilities.push_back(1.96);
		this->hev_susceptibilities.push_back(2.86);
	}

	if (heterogeneous_phev_susceptibilities)
	{
		// set susceptibilities based on the empirical distributions
		phev_susceptibilities = get_susceptibilities(EngineType::PHEV, generator);
	}
	else
	{
		// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
		this->phev_susceptibilities.push_back(2.07);
		this->phev_susceptibilities.push_back(1.81);
		this->phev_susceptibilities.push_back(2.58);
	}

	if (heterogeneous_bev_susceptibilities)
	{
		// set susceptibilities based on the empirical distributions
		bev_susceptibilities = get_susceptibilities(EngineType::BEV, generator);
	}
	else
	{
		// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
		this->bev_susceptibilities.push_back(2.09);
		this->bev_susceptibilities.push_back(1.98);
		this->bev_susceptibilities.push_back(2.59);
	}

	if (heterogeneous_driving_patterns)
	{
		// set driving pattern based on the empirical distribution
		this->set_driving_pattern(dps, generator);
	}
	else
	{
		// set the mean value of driving pattern
		this->dp = std::accumulate(dps.begin(), dps.end(), 0.0) / dps.size();
	}
}

Agent::Agent(int index, bool heterogeneous_susceptibilities, bool heterogeneous_driving_patterns, std::mt19937_64& generator, const std::vector<double>& dps)
{
	this->index = index;
	this->car = NULL;  // NULL: agent does not have a car

	if (heterogeneous_susceptibilities)
	{
		// set susceptibilities based on the empirical distributions
		hev_susceptibilities = get_susceptibilities(EngineType::HEV, generator);
		phev_susceptibilities = get_susceptibilities(EngineType::PHEV, generator);
		bev_susceptibilities = get_susceptibilities(EngineType::BEV, generator);
	}
	else
	{
		// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
		this->hev_susceptibilities.push_back(2.14);
		this->hev_susceptibilities.push_back(1.96);
		this->hev_susceptibilities.push_back(2.86);

		this->phev_susceptibilities.push_back(2.07);
		this->phev_susceptibilities.push_back(1.81);
		this->phev_susceptibilities.push_back(2.58);

		this->bev_susceptibilities.push_back(2.09);
		this->bev_susceptibilities.push_back(1.98);
		this->bev_susceptibilities.push_back(2.59);
	}
	
	if (heterogeneous_driving_patterns)
	{
		// set driving pattern based on the empirical distribution
		this->set_driving_pattern(dps, generator);
	}
	else
	{
		// set the mean value of driving pattern
		this->dp = std::accumulate(dps.begin(), dps.end(), 0.0) / dps.size();
	}
}

Agent::Agent(Car* car)
{
	this->index = NAN;
	this->car = car;  // agent has a car

	// set mean values for all susceptibilities ([0]: marketing, [1]: global influence, [2] local influence)
	this->hev_susceptibilities.push_back(2.14);
	this->hev_susceptibilities.push_back(1.96);
	this->hev_susceptibilities.push_back(2.86);

	this->phev_susceptibilities.push_back(2.07);
	this->phev_susceptibilities.push_back(1.81);
	this->phev_susceptibilities.push_back(2.58);

	this->bev_susceptibilities.push_back(2.09);
	this->bev_susceptibilities.push_back(1.98);
	this->bev_susceptibilities.push_back(2.59);

	// set the mean value of driving pattern
	this->dp = 0.38;
}

void Agent::updateCar(const std::vector<Car*>& cars, std::vector<int>& carEngineHistogram, int N, const std::vector<double>& ads, double alpha_phev, double alpha_bev, std::mt19937_64& generator)
{
	std::vector<double> probs(cars.size());
	double norm = 0;
	double prob;
	for (int i = 0; i < cars.size(); i++)
	{
		//std::cout << cars.at(i)->getEngineType()<<std::endl;
		//cars.at(i)->printPartialUtilites();

		prob = getProbability(cars.at(i), carEngineHistogram, N, ads, alpha_phev, alpha_bev, generator);
		probs.at(i) = prob;
		norm += prob;
	}
	
	if (norm != 0)
	{

		for (int i = 0; i < probs.size(); i++)
		{
			probs.at(i) /= norm;
		}

		std::vector<double> cdf(probs.size());
		cdf.at(0) = probs.at(0);
		for (int i = 1; i < cars.size(); i++)
		{
			cdf.at(i) = cdf.at(i - 1) + probs.at(i);
		}

		std::uniform_real_distribution<double> uniform(0, 1);
		double variate = uniform(generator);

		int chosenCarIndex = 0;
		while (variate > cdf.at(chosenCarIndex))
		{
			chosenCarIndex++;
		}
		car = cars.at(chosenCarIndex);
	}
}

void Agent::printCar() const
{
	std::cout << this->getCarEngineType() << std::endl;
	if (this->getCarEngineType() != EngineType::NONE)
	{
		car->printPartialUtilites();
		car->printUtility();
	}
}

EngineType Agent::getCarEngineType() const
{
	if (car == NULL)
	{
		return EngineType::NONE;
	}
	return car->getEngineType();
}

void Agent::setCar(Car* car)
{
	this->car = car;
}

void Agent::printPreferences() const
{
	for (double susceptibility : hev_susceptibilities)
	{
		std::cout << susceptibility << "\t";
	}
	std::cout << std::endl;
	for (double susceptibility : phev_susceptibilities)
	{
		std::cout << susceptibility << "\t";
	}
	std::cout << std::endl;
	for (double susceptibility : bev_susceptibilities)
	{
		std::cout << susceptibility << "\t";
	}
	std::cout << std::endl;
	std::cout << dp << std::endl;
}

bool Agent::connected(const Agent* agent) const
{
	if (this == agent)
	{
		return true;
	}
	else
	{
		for (Agent* neighbour : neighbours)
		{
			if (neighbour == agent)
			{
				return true;
			}
		}
		return false;
	}
}

bool Agent::connect(Agent* agent)
{
	if (this->connected(agent))
	{
		return false;
	}
	else
	{
		neighbours.push_back(agent);
		agent->neighbours.push_back(this);
		return true;
	}
}

std::vector<Agent*>::iterator Agent::find(Agent* agent)
{
	for (std::vector<Agent*>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
	{
		if (*it == agent)
		{
			return it;
		}
	}
}

bool Agent::disconnect(Agent* agent)
{
	if (this == agent)
	{
		return false;
	}
	if (this->connected(agent))
	{
		neighbours.erase(this->find(agent));
		agent->neighbours.erase(agent->find(this));
		return true;
	}
	else
	{
		return false;
	}
}

bool Agent::replace(Agent* agent, Agent* newAgent)
{
	if (this->connected(agent) && !this->connected(newAgent))
	{
		return this->disconnect(agent) && this->connect(newAgent);
	}
	return false;
	
}

int Agent::getIndex() const
{
	return index;
}

int Agent::getNeighbourNumber() const
{
	return neighbours.size();
}

const std::vector<Agent*>& Agent::getNeighbours() const
{
	return neighbours;
}

double Agent::getProbability(const Car* car, std::vector<int>& carEngineHistogram, int N, const std::vector<double>& ads, double alpha_phev, double alpha_bev, std::mt19937_64& generator) const
{
	EngineType carEngineType = car->getEngineType();
	double local_fraction = 0;  // fraction of neighbours with the same engine type
	for (const Agent* neighbour : neighbours)
	{
		//std::cout << this->index << "\t" << this->neighbours.size() <<"\t"<< carEngineType<<"\t neighbour:\t"<<neighbour->index << "\t" << neighbour->getCarEngineType() << std::endl;
		//std::cin.get();
		if (neighbour->getCarEngineType() == carEngineType)
		{
			//std::cout << neighbourFraction << std::endl;
			local_fraction++;
			//std::cout << neighbourFraction << std::endl;
		}
	}
	//std::cout << "end loop" << std::endl;
	local_fraction /= neighbours.size();
	//neighbourFraction = 0;
	//std::cout << "neighbour fraction:\t" << neighbourFraction << std::endl;

	double independent_probability = std::exp(car->getUtility());  //only based on the casr properties
	double willingness;
	double refueling_effect;

	//std::cout << "independent probability:\t" << independentProbability << std::endl;

	double global_fraction = 0;  // fraction of agents with the same engine type in the system
	switch (carEngineType)
	{
	case EngineType::HEV:
		global_fraction = carEngineHistogram[0];
		global_fraction /= N;

		willingness = hev_susceptibilities[0] * ads[0] + hev_susceptibilities[1] * global_fraction + hev_susceptibilities[2] * local_fraction + 1;
		refueling_effect = 1;
		break;
	case EngineType::PHEV:
		global_fraction = carEngineHistogram[1];
		global_fraction /= N;
		
		willingness =  phev_susceptibilities[0] * ads[1] + phev_susceptibilities[1] * global_fraction + phev_susceptibilities[2] * local_fraction + 1;
		refueling_effect = 1 - dp * std::exp(-alpha_phev * global_fraction);
		break;
	case EngineType::BEV:
		global_fraction = carEngineHistogram[2];
		global_fraction /= N;

		willingness =   bev_susceptibilities[0] * ads[2] + bev_susceptibilities[1] * global_fraction + bev_susceptibilities[2] * local_fraction + 1; 
		refueling_effect = 1 - dp * std::exp(-alpha_bev * global_fraction);
		break;
	}

	return willingness * refueling_effect * independent_probability;
}
