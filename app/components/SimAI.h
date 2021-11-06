#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h" // For ID...

namespace component {

class SimAI : public ecs::Component
{
public:
  SimAI()
  {}

  COMPONENT_ID(component::SIM_AI_ID);

  bool _employed = false;
  ecs::EntityID _employer;
};

}