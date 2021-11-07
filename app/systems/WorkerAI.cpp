#include "WorkerAI.h"

#include "../components/ComponentIds.h"
#include "../components/SimAI.h"
#include "../components/Position.h"
#include "../components/Velocity.h"
#include "../components/CommercialBuilding.h"
#include "../ecs/Engine.h"

#include <iostream>

namespace systems {

namespace {

sf::Vector2f normalize(const sf::Vector2f& v)
{
  double len = std::sqrt(v.x * v.x + v.y * v.y);
  return sf::Vector2f(v.x / (float)len, v.y / (float)len);
}

double distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double g_SimSpeed = 50.0;

}

void goToWork(ecs::Engine& engine, ecs::Entity& entity)
{
  auto simComp = entity.getComp<component::SimAI>();
  if (!simComp->_employed) {
    std::cout << "Entity " << std::to_string(entity.id()) << " cannot go to work because he has no employer" << std::endl;
    return;
  }

  auto employer = engine.getEntityById(simComp->_employer);
  auto buildingComp = employer->getComp<component::CommercialBuilding>();
  auto empPosComp = employer->getComp<component::Position>();
  auto posComp = entity.getComp<component::Position>();
  auto velComp = entity.getComp<component::Velocity>();
  velComp->_velocity = (float)g_SimSpeed * normalize(empPosComp->_pos - posComp->_pos);

  simComp->_state = component::SimAI::State::GoingToWork;
}

bool arrivedAtWork(ecs::Engine& engine, ecs::Entity& entity)
{
  auto simComp = entity.getComp<component::SimAI>();
  auto posComp = entity.getComp<component::Position>();

  auto employer = engine.getEntityById(simComp->_employer);
  auto empPosComp = employer->getComp<component::Position>();

  if (distance(empPosComp->_pos, posComp->_pos) <= 5.0) {
    return true;
  }
  return false;
}

void startWorking(ecs::Entity& entity)
{
  auto velComp = entity.getComp<component::Velocity>();
  auto simComp = entity.getComp<component::SimAI>();
  simComp->_state = component::SimAI::State::Working;
  velComp->_velocity.x = 0;
  velComp->_velocity.y = 0;
}

void WorkerAI::run(ecs::Engine& engine, double delta)
{
  auto ents = engine.getEntitiesWithComp(component::SIM_AI_ID);
  auto commercialEnts = engine.getEntitiesWithComp(component::COMMERCIAL_BUILDING_ID);

  for (auto ent: ents) {
    auto simComp = ent->getComp<component::SimAI>();
    auto posComp = ent->getComp<component::Position>();
    auto velComp = ent->getComp<component::Velocity>();
    
    if (!simComp->_employed) {
      // Look for an employer
      // TODO: Check education level required
      for (auto employerEnt: commercialEnts) {
        auto buildingComp = employerEnt->getComp<component::CommercialBuilding>();
        if (buildingComp->_numWorkers < buildingComp->_maxWorkers) {
          simComp->_employed = true;
          simComp->_employer = employerEnt->id();

          buildingComp->_numWorkers++;
        }
      }
    }
    
    switch (simComp->_state) {
      case component::SimAI::State::Home:
        goToWork(engine, *ent);
        break;
      case component::SimAI::State::GoingToWork:
        if (arrivedAtWork(engine, *ent)) {
          startWorking(*ent);
        }
        break;
      case component::SimAI::State::Working:
        break;
      case component::SimAI::State::GoingHome:
        break;
    }
  }
}

}