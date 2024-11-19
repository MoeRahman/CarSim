#include "Car.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Car::Car(float startX, float startY, float startAngle)
    : posX(startX), posY(startY), angle(startAngle),wheelAngle(0.0), speed(0.0), maxSpeed(6.0), acc(0.2), turnFactor(0.8) {

    //Chassis
    chassis.setFillColor(sf::Color(0, 49, 82, 255));
    chassis.setOutlineColor(sf::Color::White);
    chassis.setOutlineThickness(1);
    chassis.setSize(sf::Vector2f(10.f, 20.f));
    chassis.setOrigin(5.f, 10.f);
    chassis.setPosition(posX, posY);
    
    //Wheel Left
    wheelL.setFillColor(sf::Color(0, 49, 82, 255));
    wheelL.setOutlineColor(sf::Color::White);
    wheelL.setOutlineThickness(1);
    wheelL.setSize(sf::Vector2f(2.f, 5.f));
    wheelL.setOrigin(1.f, 2.5f);
    wheelL.setPosition(posX, posY);

    //Wheel Right
    wheelR.setFillColor(sf::Color(0, 49, 82, 255));
    wheelR.setOutlineColor(sf::Color::White);
    wheelR.setOutlineThickness(1);
    wheelR.setSize(sf::Vector2f(2.f, 5.f));
    wheelR.setOrigin(1.f, 2.5f);
    wheelR.setPosition(posX, posY);

    //Back Wheels
    backWheelR.setFillColor(sf::Color::Black);
    backWheelR.setOutlineColor(sf::Color::White);
    backWheelR.setOutlineThickness(1);
    backWheelR.setSize(sf::Vector2f(2.f, 5.f));
    backWheelR.setOrigin(1.f, 2.5f);
    backWheelR.setPosition(posX, posY);
    backWheelL.setFillColor(sf::Color::Black);
    backWheelL.setOutlineColor(sf::Color::White);
    backWheelL.setOutlineThickness(1);
    backWheelL.setSize(sf::Vector2f(2.f, 5.f));
    backWheelL.setOrigin(1.f, 2.5f);
    backWheelL.setPosition(posX, posY);
}

void Car::handleInput() {
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        speed < maxSpeed ? speed += acc : speed = maxSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        speed > -maxSpeed ? speed -= acc*0.5 : speed = -maxSpeed;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        speed - acc > 0 ? speed -= acc*0.1 : (speed + acc < 0 ? speed += acc : speed = 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angle -= turnFactor * speed;
        wheelAngle -= 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angle += turnFactor * speed;
        wheelAngle += 2;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        wheelAngle > 0 ? wheelAngle -= 2 : (wheelAngle < 0 ? wheelAngle += 2 : wheelAngle = 0);
    }
}

void Car::update() {
    posX += speed * sin(angle * M_PI / 180);
    posY -= speed * cos(angle * M_PI / 180);
    chassis.setPosition(posX, posY);
    chassis.setRotation(angle);

    // Limit the wheel angle to a range, e.g., [-30, 30] degrees
    if (wheelAngle > 30) wheelAngle = 30;
    if (wheelAngle < -30) wheelAngle = -30;

    // Update left wheel position and rotation
    sf::Vector2f offsetL(-2.5f, 0.f); // Offset from the chassis center
    sf::Vector2f wheelLPos = chassis.getTransform().transformPoint(offsetL);
    wheelL.setPosition(wheelLPos);
    wheelL.setRotation(angle + wheelAngle); // Combine car and wheel angles

    // Update right wheel position and rotation (if needed)
    sf::Vector2f offsetR(12.5f, 0.f); // Offset from the chassis center
    sf::Vector2f wheelRPos = chassis.getTransform().transformPoint(offsetR);
    wheelR.setPosition(wheelRPos);
    wheelR.setRotation(angle + wheelAngle);

    // Update left wheel position and rotation
    sf::Vector2f backOffsetL(-2.5f, 20.f); // Offset from the chassis center
    sf::Vector2f backWheelLPos = chassis.getTransform().transformPoint(backOffsetL);
    backWheelL.setPosition(backWheelLPos);
    backWheelL.setRotation(angle);

    // Update right wheel position and rotation (if needed)
    sf::Vector2f backOffsetR(12.5f, 20.f); // Offset from the chassis center
    sf::Vector2f backWheelRPos = chassis.getTransform().transformPoint(backOffsetR);
    backWheelR.setPosition(backWheelRPos);
    backWheelR.setRotation(angle);


}

void Car::draw(sf::RenderWindow& window) {
    window.draw(chassis);
    window.draw(wheelL);
    window.draw(wheelR); 
    window.draw(backWheelL);
    window.draw(backWheelR);

}

float Car::getPosX() const {
    return posX;
}

float Car::getPosY() const {
    return posY;
}

float Car::getAngle() const {
    return angle;
}