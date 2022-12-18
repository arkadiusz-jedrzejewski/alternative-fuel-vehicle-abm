#include <iostream>
#include "HEV.h"

HEV::HEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, CarType carType, FunLevel funLevel) :
	Car(EngineType::HEV, safetyLevel, price, serviceAccess)
{
	this->carType = carType;
	this->funLevel = funLevel;

	partialUtilities.push_back(getPartialUtility(safetyLevel));
	partialUtilities.push_back(getPartialUtility(price));
	partialUtilities.push_back(getPartialUtility(serviceAccess));
	partialUtilities.push_back(getPartialUtility(carType));
	partialUtilities.push_back(getPartialUtility(funLevel));

	updateUtility();
}

void HEV::printProfile() const 
{
	std::cout << "Engine type: " << engineType << std::endl;
	std::cout << "Safety level: " << safetyLevel << std::endl;
	std::cout << "Spurchase price: " << price << std::endl;
	std::cout << "Access to service: " << serviceAccess << std::endl;
	std::cout << "Car type: " << carType << std::endl;
	std::cout << "Functionality level: " << funLevel << std::endl;
}

// functions that translate attributes on a given level to associated partial utilities
// partial utilities come form []
double HEV::getPartialUtility(SafetyLevel safetyLevel)
{
	switch (safetyLevel)
	{
	case SafetyLevel::VeryLow:
		return -0.834;
	case SafetyLevel::Low:
		return -0.591;
	case SafetyLevel::Medium:
		return 0.175;
	case SafetyLevel::High:
		return 0.577;
	case SafetyLevel::VeryHigh:
		return 0.672;
	}
}

double HEV::getPartialUtility(Price price)
{
	switch (price)
	{
	case Price::p100:
		return 0.782;
	case Price::p150:
		return 0.382;
	case Price::p200:
		return -0.018;
	case Price::p250:
		return -0.392;
	case Price::p300:
		return -0.753;
	}
}

double HEV::getPartialUtility(ServiceAccess serviceAccess)
{
	switch (serviceAccess)
	{
	case ServiceAccess::r10:
		return 0.166;
	case ServiceAccess::r40:
		return -0.037;
	case ServiceAccess::r70:
		return 0.197;
	case ServiceAccess::r100:
		return -0.281;
	case ServiceAccess::r130:
		return -0.045;
	}
}

double HEV::getPartialUtility(CarType carType)
{
	switch (carType)
	{
	case CarType::Urban:
		return -0.247;
	case CarType::Compact:
		return 0.047;
	case CarType::Sedan:
		return -0.105;
	case CarType::SUV:
		return 0.324;
	case CarType::VAN:
		return -0.018;
	}
}

double HEV::getPartialUtility(FunLevel funLevel)
{
	switch (funLevel)
	{
	case FunLevel::VeryLow:
		return -0.345;
	case FunLevel::Low:
		return -0.237;
	case FunLevel::Medium:
		return 0.307;
	case FunLevel::High:
		return 0.061;
	case FunLevel::VeryHigh:
		return 0.214;
	}
}