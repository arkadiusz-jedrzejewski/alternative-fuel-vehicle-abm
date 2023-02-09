#pragma once
#include "Network.h"
class WattsStrogatz :
    public Network
{
private:
    int k; //average node degree (should be devisible by 2)
    double beta;
public:
    WattsStrogatz(
        int N,
        int k,
        double beta,
        bool heterogeneous_m_influence,
        bool heterogeneous_g_influence,
        bool heterogeneous_l_influence,
        bool heterogeneous_driving_patterns,
        const std::vector<Car*>& cars,
        const std::vector<double>& dps);
    WattsStrogatz(
        int N, 
        int k, 
        double beta, 
        bool heterogeneous_susceptibilities, 
        bool heterogeneous_driving_patterns, 
        const std::vector<Car*>& cars, 
        const std::vector<double>& dps);
    void printCarEngineMap(std::string fileName);
};

