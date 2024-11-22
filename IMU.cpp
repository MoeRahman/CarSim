#define _USE_MATH_DEFINES
#include <cmath>
#include "IMU.h"
#include <iostream>


IMU::IMU(double accel_noise_stddev, double gyro_noise_stddev)
    : accel_noise_stddev(accel_noise_stddev), gyro_noise_stddev(gyro_noise_stddev),
    accel_noise_dist(0.0, accel_noise_stddev), gyro_noise_dist(0.0, gyro_noise_stddev) {

    // Seed the random number generator
    std::random_device rd;
    rng = std::default_random_engine(rd());
}

// Function to simulate reading accelerometer data
IMU::Vect2D IMU::getAccelerometerData(double currentPosX, double currentPosY, double lastPosX, double lastPosY, double deltaTime) {
    Vect2D accelData{ 0.0, 0.0 };

    // Calculate change in position (velocity)
    Vect2D velData{ (currentPosX - lastPosX) / deltaTime , 
                    (currentPosY - lastPosY) / deltaTime };

    // Calculate acceleration (change in velocity / time)
    accelData.x = velData.x / deltaTime;
    accelData.y = velData.y / deltaTime;

    // Add Gaussian noise
    accelData.x += accel_noise_dist(rng);
    accelData.y += accel_noise_dist(rng);

    return accelData;
}

// Function to simulate reading gyroscope data
double IMU::getGyroscopeData(double currentAngle, double lastAngle, double deltaTime) {
    // Calculate change in angle
    double deltaAngle = currentAngle - lastAngle;

    // Normalize angle difference to handle wrap-around at 360 degrees
    if (deltaAngle > 180.0) deltaAngle -= 360.0;
    else if (deltaAngle < -180.0) deltaAngle += 360.0;

    // Calculate angular velocity (change in angle / time)
    double gyroData = deltaAngle / deltaTime; // Angular velocity in degrees per second

    // Add Gaussian noise
    gyroData += gyro_noise_dist(rng);

    return gyroData;
}

