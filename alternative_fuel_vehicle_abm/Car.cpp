#include "Car.h"
#include <iostream>

Car::Car(EngineType engineType, SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess)
{
    this->engineType = engineType;
    this->safetyLevel = safetyLevel;
    this->price = price;
    this->serviceAccess = serviceAccess;

    this->utility = 0;
}

void Car::updateUtility()
{
    // updates the total utility of a car: it sums partial utilities 
    double utility = 0;
    for (double partialUtility: partialUtilities)
    {
        utility += partialUtility;
    }
    this->utility = utility;
}

double Car::getUtility() const
{
    return utility;
}

EngineType Car::getEngineType() const
{
    return engineType;
}

void Car::printPartialUtilites() const
{
    std::cout << "Partial Utilities:\n";
    for (double partialUtility : partialUtilities)
    {
        std::cout << partialUtility << "\t";
    }
    std::cout << std::endl;
}

void Car::printUtility() const
{
    std::cout << "Total utility: " << utility << std::endl;
}

// OVERLOADING
std::ostream& operator<<(std::ostream& os, const EngineType& engineType)
{
    switch (engineType)
    {
    case EngineType::HEV:
        os << 1;// "HEV";
        break;
    case EngineType::PHEV:
        os << 2;// "PHEV";
        break;
    case EngineType::BEV:
        os << 3;// "BEV";
        break;
    case EngineType::NONE:
        os << 0;// "NONE";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SafetyLevel& safetyLevel)
{
    switch (safetyLevel)
    {
    case SafetyLevel::VeryLow:
        os << "Very Low";
        break;
    case SafetyLevel::Low:
        os << "Low";
        break;
    case SafetyLevel::Medium:
        os << "Medium";
        break;
    case SafetyLevel::High:
        os << "High";
        break;
    case SafetyLevel::VeryHigh:
        os << "Very High";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Price& price)
{
    switch (price)
    {
    case Price::p100:
        os << "100 000 PLN";
        break;
    case Price::p150:
        os << "150 000 PLN";
        break;
    case Price::p200:
        os << "200 000 PLN";
        break;
    case Price::p250:
        os << "250 000 PLN";
        break;
    case Price::p300:
        os << "300 000 PLN";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ServiceAccess& serviceAccess)
{
    switch (serviceAccess)
    {
    case ServiceAccess::r10:
        os << "10 km";
        break;
    case ServiceAccess::r40:
        os << "40 km";
        break;
    case ServiceAccess::r70:
        os << "70 km";
        break;
    case ServiceAccess::r100:
        os << "100 km";
        break;
    case ServiceAccess::r130:
        os << "130 km";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CarType& carType)
{
    switch (carType)
    {
    case CarType::Urban:
        os << "Urban";
        break;
    case CarType::Compact:
        os << "Compact";
        break;
    case CarType::Sedan:
        os << "Sedan";
        break;
    case CarType::SUV:
        os << "SUV";
        break;
    case CarType::VAN:
        os << "VAN";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const FunLevel& funLevel)
{
    switch (funLevel)
    {
    case FunLevel::VeryLow:
        os << "Very Low";
        break;
    case FunLevel::Low:
        os << "Low";
        break;
    case FunLevel::Medium:
        os << "Medium";
        break;
    case FunLevel::High:
        os << "High";
        break;
    case FunLevel::VeryHigh:
        os << "Very High";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ChargingAccess& chargingAccess)
{
    switch (chargingAccess)
    {
    case ChargingAccess::r10:
        os << "10 km";
        break;
    case ChargingAccess::r40:
        os << "40 km";
        break;
    case ChargingAccess::r70:
        os << "70 km";
        break;
    case ChargingAccess::r100:
        os << "100 km";
        break;
    case ChargingAccess::r130:
        os << "130 km";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const RangePHEV& range)
{
    switch (range)
    {
    case RangePHEV::r20:
        os << "20 km";
        break;
    case RangePHEV::r40:
        os << "40 km";
        break;
    case RangePHEV::r60:
        os << "60 km";
        break;
    case RangePHEV::r80:
        os << "80 km";
        break;
    case RangePHEV::r100:
        os << "100 km";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const RangeBEV& range)
{
    switch (range)
    {
    case RangeBEV::r100:
        os << "100 km";
        break;
    case RangeBEV::r300:
        os << "300 km";
        break;
    case RangeBEV::r500:
        os << "500 km";
        break;
    case RangeBEV::r700:
        os << "700 km";
        break;
    case RangeBEV::r900:
        os << "900 km";
        break;
    }
    return os;
}