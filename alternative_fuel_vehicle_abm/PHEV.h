#pragma once
#include "Car.h"
class PHEV :
    public Car
{
private:
    ChargingAccess chargingAccess;
    RangePHEV range;
public:
    PHEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, ChargingAccess chargingAccess, RangePHEV range);
    void printProfile() const;

    double getPartialUtility(SafetyLevel safetyLevel);
    double getPartialUtility(Price price);
    double getPartialUtility(ServiceAccess serviceAccess);
    double getPartialUtility(ChargingAccess chargingAccess);
    double getPartialUtility(RangePHEV range);
};

