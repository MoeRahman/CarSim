#pragma once

#ifndef IMU_H
#define IMU_H

#include <random>

class IMU {
public:

    struct Vect2D {
        double x, y;
    };

    IMU(double accel_noise_stddev, double gyro_noise_stddev);

    // Simulates reading accelerometer data based on car's velocity and time step
    Vect2D getAccelerometerData(double currentPosX, double currentPosY, double lastPosX, double lastPosY, double deltaTime);

    // Simulates reading gyroscope data based on car's angle and time step
    double getGyroscopeData(double currentAngle, double lastAngle, double deltaTime);

private:
    // Noise standard deviations for accelerometer and gyroscope
    double accel_noise_stddev;
    double gyro_noise_stddev;

    // Random number generators for Gaussian noise
    std::default_random_engine rng;
    std::normal_distribution<double> accel_noise_dist;
    std::normal_distribution<double> gyro_noise_dist;
};

#endif
