#pragma once

#ifndef GPS_H
#define GPS_H

#include <random>


class GPS{
public:
	struct GPS2D {
		double x, y;
	};

	GPS(double gps_noise_stddev);

	GPS2D getGPSData(double currentPosX, double currentPosY);

private:
	// Noise standard deviation for GPS position
	double gps_noise_stddev;

	// Random number generator
	std::default_random_engine rng;
	std::normal_distribution<double> gps_noise_dist;
	
};

#endif

