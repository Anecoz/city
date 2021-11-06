#pragma once

#include "ComponentIds.h"
#include "../ecs/Component.h"

namespace component {

class CommercialBuilding : public ecs::Component
{
public:
  CommercialBuilding()
  {}

  COMPONENT_ID(component::COMMERCIAL_BUILDING_ID);
};

}