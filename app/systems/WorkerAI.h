#pragma once

#include "../ecs/System.h"

namespace systems {

class WorkerAI : public ecs::System
{
public:
  WorkerAI() = default;
  ~WorkerAI() = default;

  void run(ecs::Engine& engine, double delta) override final;  
};

}