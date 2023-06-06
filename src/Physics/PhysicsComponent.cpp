//
// Created by r6awe on 6/6/2023.
//

#include "PhysicsComponent.h"

namespace Physics {

    PhysicsComponent::PhysicsComponent(Engine::GameObject *owner)
        : Engine::Component(owner), m_Position(owner->GetPosition()) {

    }

}
