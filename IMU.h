#pragma once

#ifndef IMU_H
#define IMU_H

#include <random>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class IMU {
public:

    IMU(float accel_noise_stddev, float gyro_noise_stddev);

    // Simulates reading accelerometer data based on car's velocity and time step
    Vector2f getAccelerometerData(Vector2f currentPos, Vector2f lastPos, float deltaTime);

    // Simulates reading gyroscope data based on car's angle and time step
    float getGyroscopeData(float currentAngle, float lastAngle, float deltaTime);

    //IMU Fusion (integrate accelData -> position)
    Vector2f imuIntegration(Vector2f noisyAccelData, float deltaTime);

private:
    // Noise standard deviations for accelerometer and gyroscope
    float accel_noise_stddev;
    float gyro_noise_stddev;

    // Random number generators for Gaussian noise
    std::default_random_engine rng;
    std::normal_distribution<float> accel_noise_dist;
    std::normal_distribution<float> gyro_noise_dist;
};

#endif
