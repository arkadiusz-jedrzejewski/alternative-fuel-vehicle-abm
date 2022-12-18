#pragma once
#include "Car.h"

class HEV :
    public Car
{
private:
    // two attributes specific to HEVs
    CarType carType;
    FunLevel funLevel;

public:
    HEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, CarType carType, FunLevel funLevel);
    void printProfile() const;

    double getPartialUtility(SafetyLevel safetyLevel);
    double getPartialUtility(Price price);
    double getPartialUtility(ServiceAccess serviceAccess);
    double getPartialUtility(CarType carType);
    double getPartialUtility(FunLevel funLevel);
};

