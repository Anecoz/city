#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"

#include <SFML/Graphics.hpp>

namespace component {

class Velocity : public ecs::Component
{
public:
  Velocity(sf::Vector2f&& velocity)
    : _velocity(std::move(velocity))
  {}

  COMPONENT_ID(component::VELOCITY_ID);

  sf::Vector2f _velocity;
};

}