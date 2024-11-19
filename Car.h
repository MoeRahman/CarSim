#pragma once
#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

class Car {
private:
    float posX;
    float posY;
    float angle;
    float wheelAngle;
    float speed;
    float maxSpeed;
    float acc;
    float turnFactor;
    sf::RectangleShape chassis;
    sf::RectangleShape wheelL;
    sf::RectangleShape wheelR;
    sf::RectangleShape backWheelL;
    sf::RectangleShape backWheelR;

public:
    Car(float startX, float startY, float startAngle);

    void handleInput();
    void update();
    void draw(sf::RenderWindow& window);

    float getPosX() const;
    float getPosY() const;
    float getAngle() const;
};

#endif // CAR_H

