#include "InputSystem.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "../ecs/Engine.h"

#include <iostream>

InputSystem::InputSystem(sf::RenderWindow& window)
  : _window(window)
{}

void InputSystem::run(ecs::Engine& engine)
{
  sf::Event event;
  while (_window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      std::cout << "Closing!" << std::endl;
      _window.close();
    }
  }
}