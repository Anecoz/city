#include "VisualBoxRender.h"

#include "../components/ComponentIds.h"
#include "../components/VisualBox.h"
#include "../components/Position.h"

#include "../ecs/Engine.h"
#include "../ecs/Entity.h"

namespace systems {

VisualBoxRender::VisualBoxRender(sf::RenderWindow& window)
  : _window(window)
{}

void VisualBoxRender::run(ecs::Engine& engine, double delta)
{
  auto entities = engine.getEntitiesWithComp(component::VISUAL_BOX_ID);
  for (auto& ent: entities) {
    auto recComp = static_cast<component::VisualBox*>(ent->getComp(component::VISUAL_BOX_ID));
    auto posComp = static_cast<component::Position*>(ent->getComp(component::POS_ID));

    recComp->_rect.setPosition(posComp->_pos);

    _window.draw(recComp->_rect);
  }
}

}