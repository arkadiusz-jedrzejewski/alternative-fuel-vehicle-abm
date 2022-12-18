#include <iostream>
#include "BEV.h"

BEV::BEV(SafetyLevel safetyLevel, Price price, ServiceAccess serviceAccess, ChargingAccess chargingAccess, RangeBEV range) :
	Car(EngineType::BEV, safetyLevel, price, serviceAccess)
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

void BEV::printProfile() const
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
double BEV::getPartialUtility(SafetyLevel safetyLevel)
{
	switch (safetyLevel)
	{
	case SafetyLevel::VeryLow:
		return -0.927;
	case SafetyLevel::Low:
		return -0.644;
	case SafetyLevel::Medium:
		return 0.039;
	case SafetyLevel::High:
		return 0.722;
	case SafetyLevel::VeryHigh:
		return 0.81;
	}
}

double BEV::getPartialUtility(Price price)
{
	switch (price)
	{
	case Price::p100:
		return 0.741;
	case Price::p150:
		return 0.463;
	case Price::p200:
		return -0.049;
	case Price::p250:
		return -0.361;
	case Price::p300:
		return -0.795;
	}
}

double BEV::getPartialUtility(ServiceAccess serviceAccess)
{
	switch (serviceAccess)
	{
	case ServiceAccess::r10:
		return 0.068;
	case ServiceAccess::r40:
		return 0.034;
	case ServiceAccess::r70:
		return -0.19;
	case ServiceAccess::r100:
		return 0.039;
	case ServiceAccess::r130:
		return 0.049;
	}
}

double BEV::getPartialUtility(ChargingAccess chargingAccess)
{
	switch (chargingAccess)
	{
	case ChargingAccess::r10:
		return 0.039;
	case ChargingAccess::r40:
		return 0.049;
	case ChargingAccess::r70:
		return 0.098;
	case ChargingAccess::r100:
		return 0.039;
	case ChargingAccess::r130:
		return -0.224;
	}
}

double BEV::getPartialUtility(RangeBEV range)
{
	switch (range)
	{
	case RangeBEV::r100:
		return -0.663;
	case RangeBEV::r300:
		return -0.098;
	case RangeBEV::r500:
		return 0.171;
	case RangeBEV::r700:
		return 0.283;
	case RangeBEV::r900:
		return 0.307;
	}
}
