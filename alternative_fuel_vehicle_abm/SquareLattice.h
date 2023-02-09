#pragma once
#include "Network.h"
class SquareLattice :
    public Network
{
private:
    int L;
public:
    SquareLattice(
        int L,
        bool heterogeneous_hev_susceptibilities,
        bool heterogeneous_phev_susceptibilities,
        bool heterogeneous_bev_susceptibilities,
        bool heterogeneous_driving_patterns,
        const std::vector<Car*>& cars,
        const std::vector<double>& dps);
    void printCarEngineMap(std::string fileName);
    SquareLattice(
        int L, 
        bool heterogeneous_susceptibilities, 
        bool heterogeneous_driving_patterns, 
        const std::vector<Car*>& cars, 
        const std::vector<double>& dps);
    void printCarEngineMap(std::string fileName);
};

