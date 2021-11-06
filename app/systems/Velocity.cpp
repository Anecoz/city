#include "Velocity.h"

#include "../components/ComponentIds.h"
#include "../components/Velocity.h"
#include "../components/Position.h"
#include "../ecs/Engine.h"

namespace systems {

void Velocity::run(ecs::Engine& engine, double delta)
{
  auto ents = engine.getEntitiesWithComp(component::VELOCITY_ID);

  for (auto ent: ents) {
    auto velComp = static_cast<component::Velocity*>(ent->getComp(component::VELOCITY_ID));
    auto posComp = static_cast<component::Position*>(ent->getComp(component::POS_ID));

    posComp->_pos.x += velComp->_velocity.x * (float)delta;
    posComp->_pos.y += velComp->_velocity.y * (float)delta;
  }
}

}