#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"

#include <SFML/Graphics.hpp>

namespace component {

class VisualBox : public ecs::Component
{
public:
  VisualBox(sf::RectangleShape&& shape)
    : _rect(std::move(shape))
  {}

  COMPONENT_ID(component::VISUAL_BOX_ID);

  sf::RectangleShape _rect;
};

}