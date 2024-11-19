#ifndef TRAILING_H
#define TRAILING_H

#include <SFML/Graphics.hpp>
#include <vector>

class Trail {
public:
    Trail(size_t maxPoints, float pointSize, const sf::Color& defaultColor = sf::Color::White);

    void addPoint(const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
    void draw(sf::RenderWindow& window);

private:
    struct TrailPoint {
        sf::Vector2f position;
        sf::Color color;

        TrailPoint(const sf::Vector2f& pos, const sf::Color& col)
            : position(pos), color(col) {}
    };

    size_t maxTrailSize;                       // Maximum number of points in the trail
    float pointRadius;                         // Radius of each point
    sf::Color defaultColor;                    // Default color for points
    std::vector<TrailPoint> points;            // Trail points
};

#endif // TRAILING_H
