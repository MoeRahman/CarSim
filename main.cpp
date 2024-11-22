#include "Car.h"
#include "GPS.h"
#include "IMU.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Trailing.h"

bool toggleSWITCH1{ false };
bool toggleSWITCH2{ false };
bool toggleSWITCH3{ false };
int toggleCOUNT{ 0 };

int main() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "EKF ROBOTICS SIM");
    window.setFramerateLimit(60);
    sf::View view1(window.getDefaultView());

    // Create a car object
    Car car(450.0f, 250.0f, 0.0f);

    Trail trail(500, 2); // REAL POSITION Trailing points
    Trail gpsTrail(1000, 2);// GPS Trailing points
    // IMU TRAIL
    // EKF FUSED TRAIL

    // IMU object (with noise standard deviations)
    IMU imu(0.1, 0.05);

    // GPS object (with noise standandard deviation)
    GPS gps(10);

    // Variables to store previous state
    float prevPosX = car.getPosX();
    float prevPosY = car.getPosY();
    float prevAngle = car.getAngle();

    // Time management
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            toggleCOUNT = 1;
            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            toggleCOUNT = 2;
        }

        // Time calculation
        float deltaTime = clock.restart().asSeconds();

        // Handle input and update the car's position and angle
        car.handleInput();
        car.update();

        // Get current state for IMU measurements
        float currentPosX = car.getPosX();
        float currentPosY = car.getPosY();
        float currentAngle = car.getAngle();

        // Get simulated IMU data
        IMU::Vect2D accelData = imu.getAccelerometerData(currentPosX, currentPosY, prevPosX, prevPosY, deltaTime);
        double gyroData = imu.getGyroscopeData(currentAngle, prevAngle, deltaTime);

        // Get simulated GPS data
        GPS::GPS2D gpsData = gps.getGPSData(currentPosX, currentPosY);

        // Print Sensor data for debugging
        //std::cout << accelData.x << ", " << accelData.y << ", " << gyroData << std::endl;
        //std::cout << gpsData.x << ", " << gpsData.y << std::endl;

        trail.addPoint(sf::Vector2f(car.getPosX(), car.getPosY()), sf::Color(255, 187, 0, 255));
        if (toggleCOUNT == 1) {
            gpsTrail.addPoint(sf::Vector2f(float(gpsData.x), float(gpsData.y)), sf::Color::White);
        }


        // Update previous state for next frame
        prevPosX = currentPosX;
        prevPosY = currentPosY;
        prevAngle = currentAngle;
        
        view1.setCenter(sf::Vector2f(currentPosX, currentPosY));

        window.clear(sf::Color(0,49,82,255));
        window.setView(view1);
        trail.draw(window);
        gpsTrail.draw(window);
        car.draw(window);
        window.display();
    }

    return 0;
}
