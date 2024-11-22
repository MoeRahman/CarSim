#define _USE_MATH_DEFINES
#include <cmath>
#include "IMU.h"
#include <iostream>

IMU::IMU(float accel_noise_stddev, float gyro_noise_stddev)
    : accel_noise_stddev(accel_noise_stddev), gyro_noise_stddev(gyro_noise_stddev),
    accel_noise_dist(0.0, accel_noise_stddev), gyro_noise_dist(0.0, gyro_noise_stddev) {

    // Seed the random number generator
    std::random_device rd;
    rng = std::default_random_engine(rd());
}

// Function to simulate reading accelerometer data
Vector2f IMU::getAccelerometerData(Vector2f currentPos, Vector2f lastPos, float deltaTime) {

    // Handle zero division 
    if (deltaTime == 0.0f) {
        throw std::invalid_argument("Zero Division");
    }
    
    // Calculate change in position (velocity)
    Vector2f velData{ static_cast<float>((currentPos.x - lastPos.x) / deltaTime) , 
                      static_cast<float>((currentPos.x - lastPos.y) / deltaTime) };

    // Calculate acceleration (change in velocity / time)
    Vector2f accelData { velData.x / deltaTime,
                         velData.y / deltaTime };

    // Add Gaussian noise
    accelData.x += accel_noise_dist(rng);
    accelData.y += accel_noise_dist(rng);

    return accelData;
}

// Function to simulate reading gyroscope data
float IMU::getGyroscopeData(float currentAngle, float lastAngle, float deltaTime) {

    // Calculate change in angle
    float deltaAngle = currentAngle - lastAngle;

    // Normalize angle difference to handle wrap-around at 360 degrees
    if (deltaAngle > 180.0) deltaAngle -= 360.0;
    else if (deltaAngle < -180.0) deltaAngle += 360.0;

    // Calculate angular velocity (change in angle / time)
    float gyroData = deltaAngle / deltaTime; // Angular velocity in degrees per second

    // Add Gaussian noise
    gyroData += gyro_noise_dist(rng);

    return gyroData;
}

// Compute position using noisy acceleration data
Vector2f IMU::imuIntegration(Vector2f noisyAccelData, float deltaTime) {

    // Calculate Velocity
    Vector2f velocity{ noisyAccelData.x * deltaTime,
                       noisyAccelData.y * deltaTime};

    return velocity;
}

