#include "Game.h"

#include "Constants.h"
#include "FontCache.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "ecs/Engine.h"

#include "systems/InputSystem.h"

#include <iostream>

Game::Game()
  : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE)
{}

void Game::init()
{
  fontcache::init();
  ImGui::SFML::Init(_window);
  _window.setFramerateLimit(60);
}

void Game::run()
{
  ecs::Engine engine;

  engine.addSystem(std::make_unique<InputSystem>(_window));

  sf::Clock clock;
  while (_window.isOpen()) {
    _window.clear(sf::Color::Black);
    sf::Time elapsed = clock.restart();
    engine.runOnce();

    ImGui::SFML::Update(_window, elapsed);

    ImGui::Begin("Hello, world!");
    if (ImGui::Button("Look at this pretty button")) {
      std::cout << "Pressed!" << std::endl;
    }
    ImGui::End();
    
    ImGui::SFML::Render(_window);

    _window.display();
  }

  ImGui::SFML::Shutdown();
}