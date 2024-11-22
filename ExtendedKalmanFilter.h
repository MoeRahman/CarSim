#pragma once
#include "IMU.h"

class ExtendedKalmanFilter{
public:
	//Linearize


	//IMU Fusion
	IMU::Vect2D imuFusion(double accelData) { imuPos.x, imuPos.y; };

private:

	IMU::Vect2D imuPos{ 0.0, 0.0};

};

