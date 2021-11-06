#include "WorkerAI.h"

#include "../components/ComponentIds.h"
#include "../components/SimAI.h"
#include "../components/Position.h"
#include "../components/Velocity.h"
#include "../components/CommercialBuilding.h"
#include "../ecs/Engine.h"

namespace systems {

namespace {

sf::Vector2f normalize(const sf::Vector2f& v)
{
  double len = std::sqrt(v.x * v.x + v.y * v.y);
  return sf::Vector2f(v.x / (float)len, v.y / (float)len);
}

double g_SimSpeed = 50.0;

}

void WorkerAI::run(ecs::Engine& engine, double delta)
{
  auto ents = engine.getEntitiesWithComp(component::SIM_AI_ID);
  auto commercialEnts = engine.getEntitiesWithComp(component::COMMERCIAL_BUILDING_ID);

  for (auto ent: ents) {
    auto simComp = static_cast<component::SimAI*>(ent->getComp(component::SIM_AI_ID));
    auto posComp = static_cast<component::Position*>(ent->getComp(component::POS_ID));
    auto velComp = static_cast<component::Velocity*>(ent->getComp(component::VELOCITY_ID));
    
    if (!simComp->_employed) {
      // Look for an employer
      // TODO: Check if there are open spots at this employer, for now just use first one in list
      if (!commercialEnts.empty()) {
        simComp->_employed = true;
        simComp->_employer = commercialEnts[0]->id();

        auto empPosComp = static_cast<component::Position*>(commercialEnts[0]->getComp(component::POS_ID));
        velComp->_velocity = (float)g_SimSpeed * normalize(empPosComp->_pos - posComp->_pos);
      }
    }
    else {
      // TOOD: Check state, going to work, at work, at home etc
    }
  }
}

}