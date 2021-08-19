#pragma once

#include "../ecs/System.h"

#include <SFML/Graphics.hpp>

class InputSystem : public ecs::System
{
public:
  InputSystem(sf::RenderWindow& window);
  ~InputSystem() = default;

  void run(ecs::Engine& engine) override final;  

private:
  sf::RenderWindow& _window;
};