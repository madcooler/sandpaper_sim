#pragma once
#include <random>


// return number between min and max
inline double getUniformRandomNumber ( double min , double max )
{
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen ( rd () );
	std::uniform_real_distribution<> distr ( min , max );
	return distr ( gen );
}

