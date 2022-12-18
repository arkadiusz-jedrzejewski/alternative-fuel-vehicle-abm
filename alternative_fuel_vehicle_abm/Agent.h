#pragma once
#include "Car.h"
#include <random>

class Agent
{
private:
	int index;
	Car* car; // car
	std::vector<Agent*> neighbours; // vector of agent's neighbours 
	double dp; // driving pattern

	void set_driving_pattern(const std::vector<double>& dps, std::mt19937_64& generator);
	
public:
	std::vector<double> hev_susceptibilities;  // [0]: marketing, [1]: global influence, [2]: local influence
	std::vector<double> phev_susceptibilities;  // [0]: marketing, [1]: global influence, [2]: local influence
	std::vector<double> bev_susceptibilities;  // [0]: marketing, [1]: global influence, [2]: local influence

	Agent();
	Agent(int index);
	Agent(int index, std::mt19937_64& generator);
	Agent(int index, bool heterogeneous_susceptibilities, bool heterogeneous_driving_patterns, std::mt19937_64& generator, const std::vector<double>& dps);
	Agent(Car* car);

	void updateCar(const std::vector<Car*>&, std::vector<int>& carEngineHistogram, int N, const std::vector<double>& ads, double alpha_phev, double alpha_bev, std::mt19937_64& generator);
	void printCar() const;
	EngineType getCarEngineType() const;
	void setCar(Car* car);
	void printPreferences() const;

	bool connected(const Agent* agent) const;
	bool connect(Agent* agent);
	std::vector<Agent*>::iterator find(Agent* agent); //TODO const?
	bool disconnect(Agent* agent);
	bool replace(Agent* agent, Agent* newAgent); 

	int getIndex() const;
	int getNeighbourNumber() const;
	const std::vector<Agent*>& getNeighbours() const;

	double getProbability(const Car* car, std::vector<int>& carEngineHistogram, int N, const std::vector<double>& ads, double alpha_phev, double alpha_bev, std::mt19937_64& generator) const;
};

