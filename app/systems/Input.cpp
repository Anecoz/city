#include "Input.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "../ecs/Engine.h"

#include <iostream>

namespace systems {

Input::Input(sf::RenderWindow& window)
  : _window(window)
{}

void Input::close()
{
  std::cout << "Closing!" << std::endl;
  _window.close();
}

void Input::run(ecs::Engine& engine, double delta)
{
  sf::Event event;
  while (_window.pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      close();
    }
  }
}

}