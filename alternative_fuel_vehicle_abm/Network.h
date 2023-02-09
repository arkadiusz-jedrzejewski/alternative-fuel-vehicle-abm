#pragma once
#include <chrono>
#include "Agent.h"
#include "Car.h"

class Network
{
public:
	int N; //number of agents
private:
	std::string name;
	
	unsigned seed;
	std::vector<int> carEngineHistogram;

protected:
	
	std::mt19937_64 generator;
	Network(int N, std::string name, const std::vector<Car*>& cars);
	Network(
		int N,
		std::string name,
		bool heterogeneous_hev_susceptibilities,
		bool heterogeneous_phev_susceptibilities,
		bool heterogeneous_bev_susceptibilities,
		bool heterogeneous_driving_patterns,
		const std::vector<Car*>& cars,
		const std::vector<double>& dps);
	Network(
		int N, 
		std::string name, 
		bool heterogeneous_susceptibilities, 
		bool heterogeneous_driving_patterns, 
		const std::vector<Car*>& cars, 
		const std::vector<double>& dps);
	void setCarEngineNumber(EngineType engineType, int number);
	int getCarEngineNumber(EngineType engineTyper);

public:
	std::vector<Agent*> agents;
	~Network();
	int getConnectionNumber() const;
	double getAverageDegree() const;
	double getLocalClusteringCoefficient(const Agent* agent) const;
	double getGlobalClusteringCoefficient() const;
	int getPathLength(const Agent* agent) const; 
	double getAveragePathLenght() const;

	void printNetwork() const;
	void printCarEngineTypes() const;
	void printCarEngineTypeDistirbution() const;
	void saveCarEngineTypeDistribution(std::fstream& plik) const;

	void setCar(Car* car, Agent* agent);
	void setCars(const std::vector<Car*>& cars);
	void updateCar(const std::vector<Car*>& cars, const std::vector<double>& ads, double alpha_phev, double alpha_bev, Agent* agent);
	void run(const std::vector<Car*>& cars, const std::vector<double>& ads, double alpha_phev, double alpha_bev, int T, std::string fileName);
	virtual void printCarEngineMap(std::string fileName) = 0;
};

