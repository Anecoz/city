#pragma once

#include "../ecs/System.h"

namespace systems {

class Velocity : public ecs::System
{
public:
  Velocity() = default;
  ~Velocity() = default;

  void run(ecs::Engine& engine, double delta) override final;  
};

}