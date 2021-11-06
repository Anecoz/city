#pragma once

#include "../ecs/System.h"

#include <SFML/Graphics.hpp>

namespace systems {

class VisualBoxRender : public ecs::System
{
public:
  VisualBoxRender(sf::RenderWindow& window);

  void run(ecs::Engine& engine, double delta) override final;

private:
  sf::RenderWindow& _window;
};

}