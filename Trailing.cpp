#include "Trailing.h"

// Constructor to initialize the max size of the trail
Trail::Trail(size_t maxPoints, float pointSize, const sf::Color& defaultColor)
    : maxTrailSize(maxPoints), pointRadius(pointSize / 2), defaultColor(defaultColor) {}

// Add a new point to the trail
void Trail::addPoint(const sf::Vector2f& position, const sf::Color& color) {
    // Add the point to the trail
    points.emplace_back(position, color);

    // Limit the number of points in the trail
    if (points.size() > maxTrailSize) {
        points.erase(points.begin()); // Remove the oldest point
    }

    // After adding the new point, adjust the alpha for all points in the trail
    for (size_t i = 0; i < points.size(); ++i) {
        // Calculate alpha based on how far the point is from the most recent one
        float alpha = 255.0f * (static_cast<float>(i) / points.size()); 
        points[i].color.a = static_cast<sf::Uint8>(alpha);
    }
}

void Trail::draw(sf::RenderWindow& window) {
    for (const auto& point : points) {
        sf::CircleShape circle(pointRadius); 
        circle.setPosition(point.position - sf::Vector2f(pointRadius, pointRadius)); 
        circle.setFillColor(point.color); 
        window.draw(circle); 
    }
}
