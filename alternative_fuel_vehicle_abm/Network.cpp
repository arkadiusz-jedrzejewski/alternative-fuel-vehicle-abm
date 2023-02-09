#include "Network.h"
#include <iostream>
#include <queue>
#include <fstream>


Network::Network(int N, std::string name, const std::vector<Car*>& cars)
{
	this->N = N;
	this->name = name;
	carEngineHistogram = std::vector<int>(4, 0);
	carEngineHistogram[3] = N;

	seed = 10;// std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::mt19937_64(seed);
	std::uniform_int_distribution<int> distrib(0, 10);
	std::uniform_real_distribution<double> distribR(0, 1);

	agents = std::vector<Agent*>(N);
	for (int i = 0; i < N; i++)
	{
		agents[i] = new Agent(i, generator);
		//agents[i] = new Agent(i);
		/*double prob = distribR(generator);
		if (prob < 0.928) {
			setCar(cars[distrib(generator)], agents[i]);
		}
		else if (prob < 0.968)
		{
			setCar(cars[distrib(generator)+25], agents[i]);
		}
		else {
			setCar(cars[distrib(generator) + 50], agents[i]);
		}*/
		
	}
	
}

Network::Network(
	int N,
	std::string name,
	bool heterogeneous_hev_susceptibilities,
	bool heterogeneous_phev_susceptibilities,
	bool heterogeneous_bev_susceptibilities,
	bool heterogeneous_driving_patterns,
	const std::vector<Car*>& cars,
	const std::vector<double>& dps)
{
	this->N = N;
	this->name = name;
	carEngineHistogram = std::vector<int>(4, 0);
	carEngineHistogram[3] = N;

	seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::mt19937_64(seed);
	std::uniform_int_distribution<int> distrib(0, 10);
	std::uniform_real_distribution<double> distribR(0, 1);

	agents = std::vector<Agent*>(N);
	for (int i = 0; i < N; i++)
	{
		agents[i] = new Agent(i, heterogeneous_hev_susceptibilities, heterogeneous_phev_susceptibilities, heterogeneous_bev_susceptibilities, heterogeneous_driving_patterns, generator, dps);
	}
}

Network::Network(
	int N, 
	std::string name, 
	bool heterogeneous_susceptibilities, 
	bool heterogeneous_driving_patterns, 
	const std::vector<Car*>& cars, 
	const std::vector<double>& dps)
{
	this->N = N;
	this->name = name;
	carEngineHistogram = std::vector<int>(4, 0);
	carEngineHistogram[3] = N;

	seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::mt19937_64(seed);
	std::uniform_int_distribution<int> distrib(0, 10);
	std::uniform_real_distribution<double> distribR(0, 1);

	agents = std::vector<Agent*>(N);
	for (int i = 0; i < N; i++)
	{
		agents[i] = new Agent(i, heterogeneous_susceptibilities, heterogeneous_driving_patterns, generator, dps);
	}
}

void Network::setCarEngineNumber(EngineType engineType, int number)
{
	switch (engineType)
	{
	case EngineType::HEV:
		carEngineHistogram[0] = number;
		break;
	case EngineType::PHEV:
		carEngineHistogram[1] = number;
		break;
	case EngineType::BEV:
		carEngineHistogram[2] = number;
		break;
	case EngineType::NONE:
		carEngineHistogram[3] = number;
		break;
	}
}

int Network::getCarEngineNumber(EngineType engineType)
{
	switch (engineType)
	{
	case EngineType::HEV:
		return carEngineHistogram[0];
	case EngineType::PHEV:
		return carEngineHistogram[1];
	case EngineType::BEV:
		return carEngineHistogram[2];
	case EngineType::NONE:
		return carEngineHistogram[3];
	}
}

Network::~Network()
{
	for (int i = 0; i < N; i++)
	{
		delete agents[i];
	}
	agents.clear();
}

int Network::getConnectionNumber() const
{
	int connectionNumber = 0;
	for (const Agent* agent : agents)
	{
		connectionNumber += agent->getNeighbourNumber();
	}
	return connectionNumber;
}

double Network::getAverageDegree() const
{
	return (double) getConnectionNumber() / N;
}

double Network::getLocalClusteringCoefficient(const Agent* agent) const
{
	int neighbourNumber = agent->getNeighbourNumber();
	if (neighbourNumber == 0 || neighbourNumber == 1)
	{
		return 0;
	}

	int connectionNumber = 0;
	for (const Agent* neighbour1 : agent->getNeighbours())
	{
		for (const Agent* neighbour2 : agent->getNeighbours())
		{
			if (neighbour1->connected(neighbour2) && neighbour1 != neighbour2)
			{
				connectionNumber++;
			}
		}
	}
	
	return connectionNumber / (neighbourNumber * ((double) neighbourNumber - 1));
}

double Network::getGlobalClusteringCoefficient() const
{
	double globalClusteringCoefficient = 0;
	for (const Agent* agent : agents)
	{
		globalClusteringCoefficient += getLocalClusteringCoefficient(agent);
	}
	globalClusteringCoefficient /= N;
	return globalClusteringCoefficient;
}

int Network::getPathLength(const Agent* agent) const
{
	std::vector<int> paths = std::vector<int>(N, -1);
	std::queue<const Agent*> queue;
	paths[agent->getIndex()] = 0;
	queue.push(agent);
	while (!queue.empty())
	{
		const Agent* agent = queue.front();
		queue.pop();
		for (const Agent* neighbour : agent->getNeighbours())
		{
			if (paths[neighbour->getIndex()] == -1)
			{
				paths[neighbour->getIndex()] = paths[agent->getIndex()] + 1;
				queue.push(neighbour);
			}
		}
	}

	int pathLength = 0;
	for (int path : paths)
	{
		if (path == -1)
		{
			path = 0;
		}
		pathLength += path;
	}
	return pathLength;
}

double Network::getAveragePathLenght() const
{
	double averagePathLength = 0;
	for (const Agent* agent : agents)
	{
		averagePathLength += getPathLength(agent);
	}
	averagePathLength /= (N * ((double) N - 1));
	return averagePathLength;
}

void Network::printNetwork() const
{
	for (const Agent* agent : agents)
	{
		std::cout << agent->getIndex() << ": ";
		for (const Agent* neighbour : agent->getNeighbours())
		{
			std::cout << neighbour->getIndex() << " ";
		}
		std::cout << std::endl;
	}
}

void Network::printCarEngineTypes() const
{
	for (const Agent* agent : agents)
	{
		std::cout << agent->getIndex() << ": " << agent->getCarEngineType() << std::endl;
	}
}

void Network::printCarEngineTypeDistirbution() const
{
	//std::vector<double> distribution = std::vector<double>(4, 0);
	//for (const Agent* agent : agents)
	//{
	//	switch (agent->getCarEngineType())
	//	{
	//	case EngineType::HEV:
	//		distribution[0]++;
	//		break;
	//	case EngineType::PHEV:
	//		distribution[1]++;
	//		break;
	//	case EngineType::BEV:
	//		distribution[2]++;
	//		break;
	//	case EngineType::NONE:
	//		distribution[3]++;
	//		break;
	//	}
	//}
	//for (double& prob : distribution)
	//{
	//	prob /= N;
	//}
	//std::cout << 
	//	EngineType::HEV << ": " << distribution[0] << " " <<
	//	EngineType::PHEV << ": " << distribution[1] << " " << 
	//	EngineType::BEV << ": " << distribution[2] << " " << 
	//	EngineType::NONE << ": " << distribution[3] << " " << std::endl;
	std::cout <<
		EngineType::HEV << ": " << carEngineHistogram[0] / (double) N << " " <<
		EngineType::PHEV << ": " << carEngineHistogram[1] / (double) N << " " <<
		EngineType::BEV << ": " << carEngineHistogram[2] / (double) N << " " <<
		EngineType::NONE << ": " << carEngineHistogram[3] / (double) N << " " << std::endl;
	//std::cout << "//////\n";
}

void Network::saveCarEngineTypeDistribution(std::fstream& plik) const
{
	plik << carEngineHistogram[0] / (double)N << "\t" <<
		carEngineHistogram[1] / (double)N << "\t" <<
		carEngineHistogram[2] / (double)N << "\t" <<
		carEngineHistogram[3] / (double)N << std::endl;
}

void Network::setCar(Car* car, Agent* agent)
{
	//set car distirbution at the beginning
	EngineType oldEngineType = agent->getCarEngineType();
	int oldCarNumber = getCarEngineNumber(oldEngineType);
	setCarEngineNumber(oldEngineType, oldCarNumber - 1);
	agent->setCar(car);
	EngineType newEngineType = agent->getCarEngineType();
	int newCarNumber = getCarEngineNumber(newEngineType);
	setCarEngineNumber(newEngineType, newCarNumber + 1);
}

void Network::setCars(const std::vector<Car*>& cars)
{
	
}

void Network::updateCar(const std::vector<Car*>& cars, const std::vector<double>& ads, double alpha_phev, double alpha_bev, Agent* agent)
{
	EngineType oldEngineType = agent->getCarEngineType();
	int oldCarNumber = getCarEngineNumber(oldEngineType);
	agent->updateCar(cars, carEngineHistogram, N, ads, alpha_phev, alpha_bev, generator);

	setCarEngineNumber(oldEngineType, oldCarNumber - 1);
	EngineType newEngineType = agent->getCarEngineType();
	int newCarNumber = getCarEngineNumber(newEngineType);
	setCarEngineNumber(newEngineType, newCarNumber + 1);
}

void Network::run(const std::vector<Car*>& cars, const std::vector<double>& ads, double alpha_phev, double alpha_bev, int T, std::string fileName)
{
	std::fstream plik(fileName, std::ios::out);
	std::uniform_int_distribution<int> uniform(0, N - 1);
	int agentIndex;
	this->saveCarEngineTypeDistribution(plik);
	for (int mcs = 0; mcs < T; mcs++)
	{
		for (int i = 0; i < N; i++)
		{
			
			agentIndex = uniform(generator);
			//std::cout << "chosen index:\t" << agentIndex<<std::endl;
			Agent* agent = agents[agentIndex];
			//std::cout << agent->getCarEngineType() << std::endl;
			//agent->printPreferences();
			updateCar(cars, ads, alpha_phev, alpha_bev, agent);
			
			
		}
		//this->printCarEngineTypeDistirbution();
		this->saveCarEngineTypeDistribution(plik);
	}
	this->printCarEngineMap("carMap.txt");
	plik.flush();
	plik.close();
}
