#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

#include "SFML/System/Vector2.hpp"

class Particle {
   public:
    sf::Vector2f position, previous_position, acceleration;
    bool is_pinned;

    Particle(float x, float y, bool is_pinned = false)
        : position{x, y},
          previous_position{x, y},
          acceleration{0, 0},
          is_pinned{is_pinned} {}

    void apply_force(const sf::Vector2f& force) {
        if (is_pinned) return;
        acceleration += force;
    }

    void update(float time_step) {
        if (is_pinned) return;

        // Verlet intehration: r_(n+1) = 2r_n - r_(n-1) + a_n * dt^2
        sf::Vector2f velocity = position - previous_position;
        previous_position = position;
        position += velocity + acceleration * time_step * time_step;
        acceleration = sf::Vector2f(0, 0);
    }

    void constraint_to_bounds(float width, float height) {
        if (position.x < 0)
            position.x = 0;
        else if (position.x > width)
            position.x = width;

        if (position.y < 0)
            position.y = 0;
        else if (position.y > height)
            position.y = height;
    }
};

#endif  // PARTICLE_HPP
