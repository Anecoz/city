#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"

#include <SFML/Graphics.hpp>

namespace component {

class Position : public ecs::Component
{
public:
  Position(sf::Vector2f&& pos)
    : _pos(std::move(pos))
  {}

  COMPONENT_ID(component::POS_ID);

  sf::Vector2f _pos;
};

}