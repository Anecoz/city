#pragma once

#include "../ecs/System.h"

#include <SFML/Graphics.hpp>

namespace systems {

class Input : public ecs::System
{
public:
  Input(sf::RenderWindow& window);
  ~Input() = default;

  void run(ecs::Engine& engine, double delta) override final;  

private:
  void close();

  sf::RenderWindow& _window;
};

}