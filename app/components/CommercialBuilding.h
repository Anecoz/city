#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"

#include <cstdint>

namespace component {

class CommercialBuilding : public ecs::Component
{
public:
  CommercialBuilding()
  {}

  COMPONENT_ID(component::COMMERCIAL_BUILDING_ID);

  std::size_t _maxWorkers;
  std::size_t _numWorkers = 0;
  // TODO: Education level required?
};

}