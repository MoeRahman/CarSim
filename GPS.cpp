#include "IMU.h"
#include "GPS.h"


GPS::GPS(float gps_noise_stddev)
    : gps_noise_stddev(gps_noise_stddev),
      gps_noise_dist(0.0, gps_noise_stddev) {

    // Random number generator
    std::random_device rd;
    rng = std::default_random_engine(rd());
}

Vector2f GPS::getGPSData(Vector2f currentPos) {
    
    Vector2f gpsData{currentPos.x + gps_noise_dist(rng), 
                     currentPos.y + gps_noise_dist(rng)};

    return gpsData;
}