#pragma once
#include <string>
#include <vector>

// 3 engine types are considered: HEV (hybrid electric vehicle), PHEV (plug-in hybrid electric vehicle), and BEV (battery electric vehicle)
// NONE type corresponds to the lack of a car
enum class EngineType { HEV, PHEV, BEV, NONE }; 


// definition of car attributes distinguished in [...]
enum class SafetyLevel { VeryLow, Low, Medium, High, VeryHigh };
enum class Price { p100, p150, p200, p250, p300};
enum class ServiceAccess { r10, r40, r70, r100, r130 };
enum class CarType { Urban, Compact, Sedan, SUV, VAN };
enum class FunLevel { VeryLow, Low, Medium, High, VeryHigh };
enum class ChargingAccess { r10, r40, r70, r100, r130 };
enum class RangePHEV { r20, r40, r60, r80, r100 };
enum class RangeBEV { r100, r300, r500, r700, r900 };

// oveloading used for printing purpeses 
std::ostream& operator<<(std::ostream& os, const EngineType& engineType);
std::ostream& operator<<(std::ostream& os, const SafetyLevel& safetyLevel);
std::ostream& operator<<(std::ostream& os, const Price& price);
std::ostream& operator<<(std::ostream& os, const ServiceAccess& serviceAccess);
std::ostream& operator<<(std::ostream& os, const CarType& carType);
std::ostream& operator<<(std::ostream& os, const FunLevel& funLevel);
std::ostream& operator<<(std::ostream& os, const ChargingAccess& chargingAccess);
std::ostream& operator<<(std::ostream& os, const RangePHEV& range);
std::ostream& operator<<(std::ostream& os, const RangeBEV& range);

// Car is an abstract class of a car
class Car
{
protected:
	EngineType engineType;

	// SafetyLevel, Price, and ServiceAccess are 3 attributes that are shered by all types of vehicles
	SafetyLevel safetyLevel;
	Price price;
	ServiceAccess serviceAccess;

	std::vector<double> partialUtilities; // vector of partial utilites associated with the attributes of a car
	double utility; // the sum of partial utilities stored in partialUtilities

	Car(EngineType engineType, SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess);

public:
	void updateUtility();
	double getUtility() const;
	EngineType getEngineType() const;
	virtual double getPartialUtility(SafetyLevel safetyLevel) = 0;
	virtual double getPartialUtility(Price price) = 0;
	virtual double getPartialUtility(ServiceAccess serviceAccess) = 0;
	
	void printPartialUtilites() const;
	void printUtility() const;
};

