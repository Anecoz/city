#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
  Game();
  ~Game() = default;

  Game(Game&&) = delete;
  Game(const Game&) = delete;
  Game& operator=(Game&&) = delete;
  Game& operator=(const Game&) = delete;

  void init();
  void run();

private:
  sf::RenderWindow _window;
};