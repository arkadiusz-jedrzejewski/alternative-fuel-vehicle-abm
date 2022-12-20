// alternative_fuel_vehicle_abm.cpp : alternative fuel vehicle agent-based model

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <direct.h>
#include <fstream>

#include "Car.h"
#include "HEV.h"
#include "PHEV.h"
#include "BEV.h"
#include "Agent.h"
#include "WattsStrogatz.h"
#include "SquareLattice.h"

int main(int argc, char** argv)
{
    std::vector<Car*> HEVs; 
    /* 
    HEVs vector contains 25 hybrid electric vehicles with profiles from Table 13 in:
    Kowalska-Pyzalska, A., Michalski, R., Kott, M., Skowrońska-Szmer, A., Kott, J., 
    Consumer preferences towards alternative fuel vehicles. Results from the conjoint analysis,
    Renewable and Sustainable Energy Reviews 155 (2022) 111776 
    doi: 10.1016/j.rser.2021.111776
    */

    HEVs.push_back(new HEV(SafetyLevel::Low, Price::p150, ServiceAccess::r130, CarType::Urban, FunLevel::Low));
    HEVs.push_back(new HEV(SafetyLevel::VeryHigh, Price::p300, ServiceAccess::r40, CarType::Urban, FunLevel::VeryHigh));
    HEVs.push_back(new HEV(SafetyLevel::Medium, Price::p250, ServiceAccess::r130, CarType::Compact, FunLevel::VeryLow));
    HEVs.push_back(new HEV(SafetyLevel::VeryHigh, Price::p150, ServiceAccess::r100, CarType::Sedan, FunLevel::VeryLow));
    HEVs.push_back(new HEV(SafetyLevel::VeryLow, Price::p300, ServiceAccess::r130, CarType::VAN, FunLevel::Medium));

    HEVs.push_back(new HEV(SafetyLevel::VeryHigh, Price::p200, ServiceAccess::r130, CarType::SUV, FunLevel::High));
    HEVs.push_back(new HEV(SafetyLevel::Low, Price::p100, ServiceAccess::r100, CarType::VAN, FunLevel::High));
    HEVs.push_back(new HEV(SafetyLevel::Medium, Price::p150, ServiceAccess::r70, CarType::VAN, FunLevel::VeryHigh));
    HEVs.push_back(new HEV(SafetyLevel::Medium, Price::p100, ServiceAccess::r40, CarType::SUV, FunLevel::Low));
    HEVs.push_back(new HEV(SafetyLevel::VeryLow, Price::p100, ServiceAccess::r10, CarType::Urban, FunLevel::VeryLow));

    HEVs.push_back(new HEV(SafetyLevel::High, Price::p100, ServiceAccess::r130, CarType::Sedan, FunLevel::VeryHigh));
    HEVs.push_back(new HEV(SafetyLevel::High, Price::p150, ServiceAccess::r10, CarType::SUV, FunLevel::Medium));
    HEVs.push_back(new HEV(SafetyLevel::Low, Price::p300, ServiceAccess::r70, CarType::SUV, FunLevel::VeryLow));
    HEVs.push_back(new HEV(SafetyLevel::VeryLow, Price::p250, ServiceAccess::r100, CarType::SUV, FunLevel::VeryHigh));
    HEVs.push_back(new HEV(SafetyLevel::VeryHigh, Price::p100, ServiceAccess::r70, CarType::Compact, FunLevel::Medium));

    HEVs.push_back(new HEV(SafetyLevel::Medium, Price::p200, ServiceAccess::r100, CarType::Urban, FunLevel::Medium));
    HEVs.push_back(new HEV(SafetyLevel::High, Price::p250, ServiceAccess::r70, CarType::Urban, FunLevel::High));
    HEVs.push_back(new HEV(SafetyLevel::VeryLow, Price::p200, ServiceAccess::r70, CarType::Sedan, FunLevel::Low));
    HEVs.push_back(new HEV(SafetyLevel::Medium, Price::p300, ServiceAccess::r10, CarType::Sedan, FunLevel::High));
    HEVs.push_back(new HEV(SafetyLevel::VeryLow, Price::p150, ServiceAccess::r40, CarType::Compact, FunLevel::High));

    HEVs.push_back(new HEV(SafetyLevel::Low, Price::p250, ServiceAccess::r40, CarType::Sedan, FunLevel::Medium));
    HEVs.push_back(new HEV(SafetyLevel::High, Price::p200, ServiceAccess::r40, CarType::VAN, FunLevel::VeryLow));
    HEVs.push_back(new HEV(SafetyLevel::Low, Price::p200, ServiceAccess::r10, CarType::Compact, FunLevel::VeryHigh));
    HEVs.push_back(new HEV(SafetyLevel::VeryHigh, Price::p250, ServiceAccess::r10, CarType::VAN, FunLevel::Low));
    HEVs.push_back(new HEV(SafetyLevel::High, Price::p300, ServiceAccess::r100, CarType::Compact, FunLevel::Low));

    std::vector<PHEV*> PHEVs; 
    /* 
    PHEVs vector contains 25 plug-in hybrid electric vehicles with profiles from Table 16 in:
    Kowalska-Pyzalska, A., Michalski, R., Kott, M., Skowrońska-Szmer, A., Kott, J.,
    Consumer preferences towards alternative fuel vehicles. Results from the conjoint analysis,
    Renewable and Sustainable Energy Reviews 155 (2022) 111776 
    doi: 10.1016/j.rser.2021.111776
    */

    PHEVs.push_back(new PHEV(SafetyLevel::Medium, Price::p300, ServiceAccess::r70, ChargingAccess::r40, RangePHEV::r60));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryHigh, Price::p150, ServiceAccess::r70, ChargingAccess::r100, RangePHEV::r20));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryHigh, Price::p250, ServiceAccess::r130, ChargingAccess::r70, RangePHEV::r100));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryLow, Price::p150, ServiceAccess::r40, ChargingAccess::r70, RangePHEV::r60));
    PHEVs.push_back(new PHEV(SafetyLevel::Low, Price::p200, ServiceAccess::r40, ChargingAccess::r100, RangePHEV::r40));

    PHEVs.push_back(new PHEV(SafetyLevel::Medium, Price::p250, ServiceAccess::r40, ChargingAccess::r130, RangePHEV::r20));
    PHEVs.push_back(new PHEV(SafetyLevel::Medium, Price::p200, ServiceAccess::r10, ChargingAccess::r70, RangePHEV::r80));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryHigh, Price::p200, ServiceAccess::r100, ChargingAccess::r10, RangePHEV::r60));
    PHEVs.push_back(new PHEV(SafetyLevel::Low, Price::p300, ServiceAccess::r100, ChargingAccess::r70, RangePHEV::r20));
    PHEVs.push_back(new PHEV(SafetyLevel::Low, Price::p250, ServiceAccess::r70, ChargingAccess::r10, RangePHEV::r80));

    PHEVs.push_back(new PHEV(SafetyLevel::Low, Price::p100, ServiceAccess::r130, ChargingAccess::r130, RangePHEV::r60));
    PHEVs.push_back(new PHEV(SafetyLevel::Medium, Price::p150, ServiceAccess::r130, ChargingAccess::r10, RangePHEV::r40));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryHigh, Price::p300, ServiceAccess::r10, ChargingAccess::r130, RangePHEV::r40));
    PHEVs.push_back(new PHEV(SafetyLevel::High, Price::p300, ServiceAccess::r40, ChargingAccess::r10, RangePHEV::r100));
    PHEVs.push_back(new PHEV(SafetyLevel::Medium, Price::p100, ServiceAccess::r100, ChargingAccess::r100, RangePHEV::r100));

    PHEVs.push_back(new PHEV(SafetyLevel::High, Price::p100, ServiceAccess::r70, ChargingAccess::r70, RangePHEV::r40));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryLow, Price::p100, ServiceAccess::r10, ChargingAccess::r10, RangePHEV::r20));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryHigh, Price::p100, ServiceAccess::r40, ChargingAccess::r40, RangePHEV::r80));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryLow, Price::p250, ServiceAccess::r100, ChargingAccess::r40, RangePHEV::r40));
    PHEVs.push_back(new PHEV(SafetyLevel::High, Price::p200, ServiceAccess::r130, ChargingAccess::r40, RangePHEV::r20));

    PHEVs.push_back(new PHEV(SafetyLevel::High, Price::p150, ServiceAccess::r100, ChargingAccess::r130, RangePHEV::r80));
    PHEVs.push_back(new PHEV(SafetyLevel::High, Price::p250, ServiceAccess::r10, ChargingAccess::r100, RangePHEV::r60));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryLow, Price::p300, ServiceAccess::r130, ChargingAccess::r100, RangePHEV::r80));
    PHEVs.push_back(new PHEV(SafetyLevel::VeryLow, Price::p200, ServiceAccess::r70, ChargingAccess::r130, RangePHEV::r100));
    PHEVs.push_back(new PHEV(SafetyLevel::Low, Price::p150, ServiceAccess::r10, ChargingAccess::r40, RangePHEV::r100));

    std::vector<BEV*> BEVs; 
    /*
    BEVs vector contains 25 battery electric vehicles with profiles from Table 17 in:
    Kowalska-Pyzalska, A., Michalski, R., Kott, M., Skowrońska-Szmer, A., Kott, J.,
    Consumer preferences towards alternative fuel vehicles. Results from the conjoint analysis,
    Renewable and Sustainable Energy Reviews 155 (2022) 111776 
    doi: 10.1016/j.rser.2021.111776
    */

    BEVs.push_back(new BEV(SafetyLevel::VeryLow, Price::p250, ServiceAccess::r100, ChargingAccess::r100, RangeBEV::r500));
    BEVs.push_back(new BEV(SafetyLevel::Medium, Price::p300, ServiceAccess::r40, ChargingAccess::r100, RangeBEV::r700));
    BEVs.push_back(new BEV(SafetyLevel::VeryHigh, Price::p300, ServiceAccess::r100, ChargingAccess::r70, RangeBEV::r100));
    BEVs.push_back(new BEV(SafetyLevel::VeryHigh, Price::p250, ServiceAccess::r70, ChargingAccess::r40, RangeBEV::r300));
    BEVs.push_back(new BEV(SafetyLevel::High, Price::p250, ServiceAccess::r40, ChargingAccess::r130, RangeBEV::r100));

    BEVs.push_back(new BEV(SafetyLevel::Low, Price::p150, ServiceAccess::r70, ChargingAccess::r100, RangeBEV::r100));
    BEVs.push_back(new BEV(SafetyLevel::Low, Price::p100, ServiceAccess::r40, ChargingAccess::r70, RangeBEV::r300));
    BEVs.push_back(new BEV(SafetyLevel::VeryLow, Price::p150, ServiceAccess::r40, ChargingAccess::r40, RangeBEV::r900));
    BEVs.push_back(new BEV(SafetyLevel::Low, Price::p250, ServiceAccess::r130, ChargingAccess::r10, RangeBEV::r700));
    BEVs.push_back(new BEV(SafetyLevel::Medium, Price::p150, ServiceAccess::r100, ChargingAccess::r10, RangeBEV::r300));

    BEVs.push_back(new BEV(SafetyLevel::Low, Price::p300, ServiceAccess::r10, ChargingAccess::r40, RangeBEV::r500));
    BEVs.push_back(new BEV(SafetyLevel::Low, Price::p200, ServiceAccess::r100, ChargingAccess::r130, RangeBEV::r900));
    BEVs.push_back(new BEV(SafetyLevel::High, Price::p300, ServiceAccess::r70, ChargingAccess::r10, RangeBEV::r900));
    BEVs.push_back(new BEV(SafetyLevel::High, Price::p200, ServiceAccess::r10, ChargingAccess::r100, RangeBEV::r300));
    BEVs.push_back(new BEV(SafetyLevel::VeryLow, Price::p100, ServiceAccess::r10, ChargingAccess::r10, RangeBEV::r100));

    BEVs.push_back(new BEV(SafetyLevel::VeryLow, Price::p200, ServiceAccess::r70, ChargingAccess::r70, RangeBEV::r700));
    BEVs.push_back(new BEV(SafetyLevel::Medium, Price::p250, ServiceAccess::r10, ChargingAccess::r70, RangeBEV::r900));
    BEVs.push_back(new BEV(SafetyLevel::VeryHigh, Price::p150, ServiceAccess::r10, ChargingAccess::r130, RangeBEV::r700));
    BEVs.push_back(new BEV(SafetyLevel::VeryHigh, Price::p200, ServiceAccess::r40, ChargingAccess::r10, RangeBEV::r500));
    BEVs.push_back(new BEV(SafetyLevel::Medium, Price::p100, ServiceAccess::r70, ChargingAccess::r130, RangeBEV::r500));

    BEVs.push_back(new BEV(SafetyLevel::High, Price::p100, ServiceAccess::r100, ChargingAccess::r40, RangeBEV::r700));
    BEVs.push_back(new BEV(SafetyLevel::VeryHigh, Price::p100, ServiceAccess::r130, ChargingAccess::r100, RangeBEV::r900));
    BEVs.push_back(new BEV(SafetyLevel::High, Price::p150, ServiceAccess::r130, ChargingAccess::r70, RangeBEV::r500));
    BEVs.push_back(new BEV(SafetyLevel::Medium, Price::p200, ServiceAccess::r130, ChargingAccess::r40, RangeBEV::r100));
    BEVs.push_back(new BEV(SafetyLevel::VeryLow, Price::p300, ServiceAccess::r130, ChargingAccess::r130, RangeBEV::r300));

    std::vector<Car*> cars(HEVs); // cars vector contains all 75 from HEVs, PHEVs, and BEVs vectors
    cars.insert(cars.end(), PHEVs.begin(), PHEVs.end());
    cars.insert(cars.end(), BEVs.begin(), BEVs.end());

    // load driving patterns from dp.txt to dp_tab vector
    // dp.txt generated by [...]
    std::ifstream dp_file("dp.txt"); 
    std::string line;
    std::vector<double> dp_tab;
    if (dp_file.is_open())
    {
        while (std::getline(dp_file, line))
        {
            double var;
            dp_tab.push_back(std::stod(line));
        }
        dp_file.close();
    }

    
    // model parameters
    std::string network_type = argv[1]; // network type: "SL" - square lattice, "WS" - Watts Strogatz network
    bool heterogeneous_susceptibilities = atoi(argv[2]); // true: agets have heterogeneous susceptibilities; false: all agents have the same susceptibilities
    bool heterogeneous_driving_patterns = atoi(argv[3]); // true: agets have heterogeneous driving patterns; false: all agents have the same driving pattern
    double alpha_phev = atof(argv[4]); // calibration parameter; responsible for refueling effect (REF) for PHEV
    double alpha_bev = atof(argv[5]); // calibration parameter; responsible for refueling effect (REF) for BEV
    double h_hev = atof(argv[6]); // advertisement strength of HEV 
    double h_phev = atof(argv[7]); // advertisement strength of PHEV
    double h_bev = atof(argv[8]); // advertisement strength of BEV
    int time_horizon = atoi(argv[9]); // simulation length in Monte Carlo steps
    std::string fileName = argv[10]; // path to or name of an output file
    
    Network* network = NULL;
    if (network_type == "SL")
    {
        int L = atoi(argv[11]); // linera lattice size (N = L x L: number of agents)
    
        network = new SquareLattice(L, heterogeneous_susceptibilities, heterogeneous_driving_patterns, cars, dp_tab);
    }
    else if (network_type == "WS")
    {
        int N = atoi(argv[11]); // number of agents (nodes)
        int k = atoi(argv[12]); // average node degree (k must be divisible by 2)
        double beta = atof(argv[13]); // rewiring probability
    
        network = new WattsStrogatz(N, k, beta, heterogeneous_susceptibilities, heterogeneous_driving_patterns, cars, dp_tab);
    }
     
    std::vector<double> ads = { h_hev, h_phev, h_bev };
     
    network->run(cars, ads, alpha_phev, alpha_bev, time_horizon, fileName); // run a simulation
    

    for (Car* car : cars)
    {
        delete car;
    }
    cars.clear();
    HEVs.clear();
    PHEVs.clear();
    BEVs.clear();
}
