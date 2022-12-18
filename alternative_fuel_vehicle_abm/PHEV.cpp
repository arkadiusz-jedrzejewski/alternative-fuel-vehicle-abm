#include <iostream>
#include "PHEV.h"

PHEV::PHEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, ChargingAccess chargingAccess, RangePHEV range) :
	Car(EngineType::PHEV, safetyLevel, price, serviceAccess)
{
	this->chargingAccess = chargingAccess;
	this->range = range;

	partialUtilities.push_back(getPartialUtility(safetyLevel));
	partialUtilities.push_back(getPartialUtility(price));
	partialUtilities.push_back(getPartialUtility(serviceAccess));
	partialUtilities.push_back(getPartialUtility(chargingAccess));
	partialUtilities.push_back(getPartialUtility(range));

	updateUtility();
}

void PHEV::printProfile() const
{
	std::cout << "Engine type: " << engineType << std::endl;
	std::cout << "Safety level: " << safetyLevel << std::endl;
	std::cout << "Spurchase price: " << price << std::endl;
	std::cout << "Access to service: " << serviceAccess << std::endl;
	std::cout << "Access to charging: " << chargingAccess << std::endl;
	std::cout << "Range: " << range << std::endl;
}

// functions that translate attributes on a given level to associated partial utilities
// partial utilities come form []
double PHEV::getPartialUtility(SafetyLevel safetyLevel)
{
	switch (safetyLevel)
	{
	case SafetyLevel::VeryLow:
		return -0.706;
	case SafetyLevel::Low:
		return -0.366;
	case SafetyLevel::Medium:
		return 0.077;
	case SafetyLevel::High:
		return 0.341;
	case SafetyLevel::VeryHigh:
		return 0.653;
	}
}

double PHEV::getPartialUtility(Price price)
{
	switch (price)
	{
	case Price::p100:
		return 0.694;
	case Price::p150:
		return 0.257;
	case Price::p200:
		return 0.014;
	case Price::p250:
		return -0.353;
	case Price::p300:
		return -0.612;
	}
}

double PHEV::getPartialUtility(ServiceAccess serviceAccess)
{
	switch (serviceAccess)
	{
	case ServiceAccess::r10:
		return -0.055;
	case ServiceAccess::r40:
		return 0.247;
	case ServiceAccess::r70:
		return -0.078;
	case ServiceAccess::r100:
		return 0.056;
	case ServiceAccess::r130:
		return -0.17;
	}
}

double PHEV::getPartialUtility(ChargingAccess chargingAccess)
{
	switch (chargingAccess)
	{
	case ChargingAccess::r10:
		return 0.223;
	case ChargingAccess::r40:
		return 0.283;
	case ChargingAccess::r70:
		return 0.076;
	case ChargingAccess::r100:
		return -0.194;
	case ChargingAccess::r130:
		return -0.388;
	}
}

double PHEV::getPartialUtility(RangePHEV range)
{
	switch (range)
	{
	case RangePHEV::r20:
		return -0.524;
	case RangePHEV::r40:
		return -0.254;
	case RangePHEV::r60:
		return -0.058;
	case RangePHEV::r80:
		return 0.365;
	case RangePHEV::r100:
		return 0.47;
	}
}