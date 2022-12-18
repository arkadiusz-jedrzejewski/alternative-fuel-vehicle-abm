#pragma once
#include "Car.h"
class BEV :
    public Car
{
private:
    // two attributes specific to BEVs
    ChargingAccess chargingAccess;
    RangeBEV range;

public:
    BEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, ChargingAccess chargingAccess, RangeBEV range);
    void printProfile() const;

    double getPartialUtility(SafetyLevel safetyLevel);
    double getPartialUtility(Price price);
    double getPartialUtility(ServiceAccess serviceAccess);
    double getPartialUtility(ChargingAccess chargingAccess);
    double getPartialUtility(RangeBEV range);
};

