#pragma once

#ifndef GPS_H
#define GPS_H

#include <random>
#include "IMU.h"
#include <SFML/System/Vector2.hpp>

class GPS{
public:

	GPS(float gps_noise_stddev);

	Vector2f getGPSData(Vector2f currentPos);

private:
	// Noise standard deviation for GPS position
	float gps_noise_stddev;

	// Random number generator
	std::default_random_engine rng;
	std::normal_distribution<float> gps_noise_dist;
	
};

#endif

