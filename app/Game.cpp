#include "Game.h"

#include "Constants.h"

#include "ecs/Engine.h"

#include "systems/InputSystem.h"

Game::Game()
  : _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE)
{}

void Game::init()
{
  // TODO: Init font and stuff here
}

void Game::run()
{
  ecs::Engine engine;

  engine.addSystem(std::make_unique<InputSystem>(_window));

  //sf::Clock clock;
  while (_window.isOpen()) {
    _window.clear(sf::Color::Black);

    //sf::Time elapsed = clock.restart();
    engine.runOnce();

    _window.display();
  }
}