#include "GPS.h"

GPS::GPS(double gps_noise_stddev)
    : gps_noise_stddev(gps_noise_stddev),
      gps_noise_dist(0.0, gps_noise_stddev) {

    // Random number generator
    std::random_device rd;
    rng = std::default_random_engine(rd());
}

GPS::GPS2D GPS::getGPSData(double currentPosX, double currentPosY) {
    GPS2D gpsData{ 0.0, 0.0 };

    gpsData.x = currentPosX + gps_noise_dist(rng);
    gpsData.y = currentPosY + gps_noise_dist(rng);

    return gpsData;
}