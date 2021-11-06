#include "Game.h"

#include "Constants.h"
#include "FontCache.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "ecs/Engine.h"
#include "ecs/Entity.h"

#include "systems/Input.h"
#include "systems/VisualBoxRender.h"
#include "systems/WorkerAI.h"
#include "systems/Velocity.h"

#include "components/Position.h"
#include "components/VisualBox.h"
#include "components/CommercialBuilding.h"
#include "components/SimAI.h"
#include "components/Velocity.h"

#include <iostream>

Game::Game()
  : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE)
{}

void Game::init()
{
  fontcache::init();
  ImGui::SFML::Init(_window);
}

std::unique_ptr<ecs::Entity> createTestCommercialBuilding()
{
  auto ent = std::make_unique<ecs::Entity>();

  sf::RectangleShape rect;
  rect.setSize(sf::Vector2f(50.0f, 50.0f));
  rect.setFillColor(sf::Color::Red);
  ent->addComp(std::make_unique<component::VisualBox>(std::move(rect)));
  ent->addComp(std::make_unique<component::Position>(sf::Vector2f(600.0f, 100.0f)));
  ent->addComp(std::make_unique<component::CommercialBuilding>());

  return ent;
}

std::unique_ptr<ecs::Entity> createTestSim()
{
  auto ent = std::make_unique<ecs::Entity>();

    sf::RectangleShape rect;
  rect.setSize(sf::Vector2f(10.0f, 10.0f));
  rect.setFillColor(sf::Color::White);
  ent->addComp(std::make_unique<component::VisualBox>(std::move(rect)));
  ent->addComp(std::make_unique<component::Position>(sf::Vector2f(10.0f, 10.0f)));
  ent->addComp(std::make_unique<component::Velocity>(sf::Vector2f(0.0f, 0.0f)));
  ent->addComp(std::make_unique<component::SimAI>());

  return ent;
}

void Game::run()
{
  ecs::Engine engine;

  engine.addSystem(std::make_unique<systems::Input>(_window));
  engine.addSystem(std::make_unique<systems::VisualBoxRender>(_window));
  engine.addSystem(std::make_unique<systems::WorkerAI>());
  engine.addSystem(std::make_unique<systems::Velocity>());

  engine.addEntity(createTestCommercialBuilding());
  engine.addEntity(createTestSim());

  sf::Clock clock;
  while (_window.isOpen()) {
    _window.clear(sf::Color::Black);
    sf::Time elapsed = clock.restart();
    engine.runOnce((double)elapsed.asSeconds());

    ImGui::SFML::Update(_window, elapsed);
    {
      ImGui::Begin("Debug");
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }    
    ImGui::SFML::Render(_window);

    _window.display();
  }

  ImGui::SFML::Shutdown();
}